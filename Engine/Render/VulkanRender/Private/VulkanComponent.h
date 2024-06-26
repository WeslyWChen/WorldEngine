//
// Created by WeslyChen on 2024/3/7.
//
#ifndef WORLDENGINE_VULKANCOMPONENT_H
#define WORLDENGINE_VULKANCOMPONENT_H

#include "VkRCenter.h"

struct VulkanInstanceComponent
{
    VkInstance instance = nullptr;

    bool applyValidationLayer = false;
    VkDebugUtilsMessengerEXT debugMessenger = nullptr;
};

struct QueueFamilyIndices
{
    std::optional<uint32> graphicsFamily{};
    std::optional<uint32> presentFamily{};

    bool IsComplete() const { return graphicsFamily.has_value() && presentFamily.has_value(); }
};
struct SwapChainSupportDetails
{
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};
struct VulkanSurfaceComponent
{
    VkSurfaceKHR surface = nullptr;
    VkSurfaceCapabilitiesKHR surfaceCapabilities;
    VkSurfaceFormatKHR expectSurfaceFormat;
    VkPresentModeKHR expectPresentMode;
    VkExtent2D expectSwapChainExtent;
    uint32 expectSwapChainBufferCount = 1;

    QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device) const;
    SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device) const;
    VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats) const;
    VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes) const;
    VkExtent2D ChooseSwapExtent(VkPhysicalDevice device, const VkSurfaceCapabilitiesKHR& capabilities) const;
    void update(VkPhysicalDevice device);
};

struct VulkanDeviceComponent
{
    constexpr static int MAX_FRAMES_IN_FLIGHT = 2;

    VkPhysicalDevice physicalDevice = nullptr;
    VkDevice logicDevice = nullptr;
    VkQueue graphicsQueue = nullptr;
    VkQueue presentQueue = nullptr;
    VkCommandPool commandPool = nullptr;

    std::vector<VkCommandBuffer> commandBuffers;
    std::vector<VkSemaphore> imageAvailableSemaphores;
    std::vector<VkSemaphore> renderFinishedSemaphores;
    std::vector<VkFence> inFlightFences;

    uint32 FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties) const;
};

struct VulkanRenderPassComponent
{
    VkRenderPass renderPass = nullptr;
};

#endif  // WORLDENGINE_VULKANCOMPONENT_H
