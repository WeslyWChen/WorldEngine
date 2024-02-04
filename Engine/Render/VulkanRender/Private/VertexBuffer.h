//
// Created by WeslyChen on 2024/2/4.
//
#ifndef WORLDENGINE_VERTEXBUFFER_H
#define WORLDENGINE_VERTEXBUFFER_H

#include "Core/Geometry/MeshComponent.h"
#include "VulkanResource.h"

class VertexBuffer final
{
public:
    VertexBuffer() = default;
    ~VertexBuffer();
    VertexBuffer(const VertexBuffer&) = delete;
    VertexBuffer& operator=(const VertexBuffer&) = delete;

public:
    VkBuffer GetBufferHandle() const { return mVertexBuffer; }

    void OnMeshUpdate(const MeshComponent& mesh);

private:
    void CreateBuffer(const std::vector<Vertex>& vertices);
    void ReleaseBuffer();

private:
    VkBuffer mVertexBuffer = nullptr;
    VkDeviceMemory mVertexBufferMemory = nullptr;
};

#endif  // WORLDENGINE_VERTEXBUFFER_H