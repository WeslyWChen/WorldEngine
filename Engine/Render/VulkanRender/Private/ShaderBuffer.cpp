//
// Created by WeslyChen on 2024/2/4.
//
#include "ShaderBuffer.h"

#include "UniformBuffer.h"
#include "VulkanComponent.h"

using namespace std;

ShaderBuffer::ShaderBuffer()
{
    CreateUniformBuffers();
}

ShaderBuffer::~ShaderBuffer()
{
    ReleaseBuffer();
}

void ShaderBuffer::OnMeshUpdate(const MeshComponent& mesh)
{
    CreateVertexBuffer(mesh.vertices);

    mIndexSize = mesh.indices.size();

    CreateIndexBuffer(mesh.indices);
}

void ShaderBuffer::CreateVertexBuffer(const std::vector<Vertex>& vertices)
{
    auto deviceComponent = VkRCenter::instance()->GetComponentFromVulkan<VulkanDeviceComponent>();
    if (!deviceComponent || !deviceComponent->physicalDevice || !deviceComponent->logicDevice)
        return;

    VkDeviceSize bufferSize = sizeof(vertices[0]) * vertices.size();

    VkBuffer stagingBuffer;
    VkDeviceMemory stagingBufferMemory;
    CreateBuffer(bufferSize,
                 VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
                 VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                 stagingBuffer,
                 stagingBufferMemory);

    void* data = nullptr;
    vkMapMemory(deviceComponent->logicDevice, stagingBufferMemory, 0, bufferSize, 0, &data);
    memcpy(data, vertices.data(), (size_t)bufferSize);
    vkUnmapMemory(deviceComponent->logicDevice, stagingBufferMemory);

    CreateBuffer(bufferSize,
                 VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
                 VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
                 mVertexBuffer,
                 mVertexBufferMemory);

    CopyBuffer(stagingBuffer, mVertexBuffer, bufferSize);

    vkDestroyBuffer(deviceComponent->logicDevice, stagingBuffer, nullptr);
    vkFreeMemory(deviceComponent->logicDevice, stagingBufferMemory, nullptr);
}

void ShaderBuffer::CreateIndexBuffer(const vector<uint16>& indices)
{
    auto deviceComponent = VkRCenter::instance()->GetComponentFromVulkan<VulkanDeviceComponent>();
    if (!deviceComponent || !deviceComponent->physicalDevice || !deviceComponent->logicDevice)
        return;

    VkDeviceSize bufferSize = sizeof(indices[0]) * indices.size();

    VkBuffer stagingBuffer;
    VkDeviceMemory stagingBufferMemory;
    CreateBuffer(bufferSize,
                 VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
                 VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                 stagingBuffer,
                 stagingBufferMemory);

    void* data = nullptr;
    vkMapMemory(deviceComponent->logicDevice, stagingBufferMemory, 0, bufferSize, 0, &data);
    memcpy(data, indices.data(), (size_t)bufferSize);
    vkUnmapMemory(deviceComponent->logicDevice, stagingBufferMemory);

    CreateBuffer(bufferSize,
                 VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
                 VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
                 mIndexBuffer,
                 mIndexBufferMemory);

    CopyBuffer(stagingBuffer, mIndexBuffer, bufferSize);

    vkDestroyBuffer(deviceComponent->logicDevice, stagingBuffer, nullptr);
    vkFreeMemory(deviceComponent->logicDevice, stagingBufferMemory, nullptr);
}

void ShaderBuffer::CreateUniformBuffers()
{
    auto deviceComponent = VkRCenter::instance()->GetComponentFromVulkan<VulkanDeviceComponent>();
    if (!deviceComponent || !deviceComponent->physicalDevice || !deviceComponent->logicDevice)
        return;

    VkDeviceSize bufferSize = sizeof(UniformBufferObject);

    mUniformBuffers.resize(VulkanDeviceComponent::MAX_FRAMES_IN_FLIGHT);
    mUniformBuffersMemory.resize(VulkanDeviceComponent::MAX_FRAMES_IN_FLIGHT);
    mUniformBuffersMapped.resize(VulkanDeviceComponent::MAX_FRAMES_IN_FLIGHT);

    for (size_t i = 0; i < VulkanDeviceComponent::MAX_FRAMES_IN_FLIGHT; i++)
    {
        CreateBuffer(bufferSize,
                     VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
                     VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                     mUniformBuffers[i],
                     mUniformBuffersMemory[i]);

        vkMapMemory(deviceComponent->logicDevice, mUniformBuffersMemory[i], 0, bufferSize, 0, &mUniformBuffersMapped[i]);
    }
}

void ShaderBuffer::CreateBuffer(
        VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory)
{
    auto deviceComponent = VkRCenter::instance()->GetComponentFromVulkan<VulkanDeviceComponent>();
    if (!deviceComponent || !deviceComponent->physicalDevice || !deviceComponent->logicDevice)
        return;

    VkBufferCreateInfo bufferInfo{};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = size;
    bufferInfo.usage = usage;
    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    auto vkResult = vkCreateBuffer(deviceComponent->logicDevice, &bufferInfo, nullptr, &buffer);
    if (vkResult != VK_SUCCESS)
        return;

    VkMemoryRequirements memRequirements;
    vkGetBufferMemoryRequirements(deviceComponent->logicDevice, buffer, &memRequirements);

    VkMemoryAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo.allocationSize = memRequirements.size;
    allocInfo.memoryTypeIndex = deviceComponent->FindMemoryType(memRequirements.memoryTypeBits, properties);

    vkResult = vkAllocateMemory(deviceComponent->logicDevice, &allocInfo, nullptr, &bufferMemory);
    if (vkResult != VK_SUCCESS)
        return;

    vkBindBufferMemory(deviceComponent->logicDevice, buffer, bufferMemory, 0);
}

void ShaderBuffer::CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size)
{
    auto deviceComponent = VkRCenter::instance()->GetComponentFromVulkan<VulkanDeviceComponent>();
    if (!deviceComponent || !deviceComponent->physicalDevice || !deviceComponent->logicDevice)
        return;

    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandPool = deviceComponent->commandPool;
    allocInfo.commandBufferCount = 1;

    VkCommandBuffer commandBuffer;
    vkAllocateCommandBuffers(deviceComponent->logicDevice, &allocInfo, &commandBuffer);

    VkCommandBufferBeginInfo beginInfo{};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
    vkBeginCommandBuffer(commandBuffer, &beginInfo);

    VkBufferCopy copyRegion{};
    copyRegion.srcOffset = 0;  // Optional
    copyRegion.dstOffset = 0;  // Optional
    copyRegion.size = size;
    vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, 1, &copyRegion);

    vkEndCommandBuffer(commandBuffer);

    VkSubmitInfo submitInfo{};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &commandBuffer;
    vkQueueSubmit(deviceComponent->graphicsQueue, 1, &submitInfo, VK_NULL_HANDLE);
    vkQueueWaitIdle(deviceComponent->graphicsQueue);

    vkFreeCommandBuffers(deviceComponent->logicDevice, deviceComponent->commandPool, 1, &commandBuffer);
}

void ShaderBuffer::ReleaseBuffer()
{
    auto deviceComponent = VkRCenter::instance()->GetComponentFromVulkan<VulkanDeviceComponent>();
    if (!deviceComponent || !deviceComponent->physicalDevice || !deviceComponent->logicDevice)
        return;

    if (mVertexBuffer)
    {
        vkDestroyBuffer(deviceComponent->logicDevice, mVertexBuffer, nullptr);
        mVertexBuffer = nullptr;
    }

    if (mVertexBufferMemory)
    {
        vkFreeMemory(deviceComponent->logicDevice, mVertexBufferMemory, nullptr);
        mVertexBufferMemory = nullptr;
    }

    if (mIndexBuffer)
    {
        vkDestroyBuffer(deviceComponent->logicDevice, mIndexBuffer, nullptr);
        mIndexBuffer = nullptr;
    }

    if (mIndexBufferMemory)
    {
        vkFreeMemory(deviceComponent->logicDevice, mIndexBufferMemory, nullptr);
        mIndexBufferMemory = nullptr;
    }

    for (size_t i = 0; i < VulkanDeviceComponent::MAX_FRAMES_IN_FLIGHT; i++)
    {
        vkDestroyBuffer(deviceComponent->logicDevice, mUniformBuffers[i], nullptr);
        vkFreeMemory(deviceComponent->logicDevice, mUniformBuffersMemory[i], nullptr);
    }
    mUniformBuffers.clear();
    mUniformBuffersMemory.clear();
    mUniformBuffersMapped.clear();
}
