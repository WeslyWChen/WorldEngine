//
// Created by WeslyChen on 2024/2/25.
//
#include "GlfwWindowSystem.h"

#include "GlfwWindowComponent.h"
#include "VulkanManager.h"

using namespace std;

void GlfwWindowSystem::OnInit()
{
    if (VkRCenter::instance()->windowEntity != entt::null)
        return;

    auto& world = VkRCenter::instance()->world;
    auto& windowEntity = VkRCenter::instance()->windowEntity;

    windowEntity = world.create();
    auto& windowComponent = world.emplace<GlfwWindowComponent>(windowEntity);

    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    Logger::Log(Logger::Level::Info, "VulkanRender", "Create GlfwWindow.");
    windowComponent.window = glfwCreateWindow(windowComponent.width, windowComponent.height, windowComponent.windowName.c_str(), nullptr, nullptr);

    glfwSetFramebufferSizeCallback(windowComponent.window, OnFramebufferResize);
}

void GlfwWindowSystem::OnDestroy()
{
    if (VkRCenter::instance()->windowEntity == entt::null)
        return;

    auto windowComponent = VkRCenter::instance()->GetComponentFromWindow<GlfwWindowComponent>();
    if (nullptr == windowComponent)
        return;

    glfwDestroyWindow(windowComponent->window);
    glfwTerminate();

    VkRCenter::instance()->world.destroy(VkRCenter::instance()->windowEntity);
    VkRCenter::instance()->windowEntity = entt::null;
}

void GlfwWindowSystem::OnUpdate() {}

void GlfwWindowSystem::OnFramebufferResize(GLFWwindow* window, int width, int height)
{
    auto& world = VkRCenter::instance()->world;
    auto windowEntity = VkRCenter::instance()->windowEntity;

    if (windowEntity == entt::null)
        return;
    if (auto resizeComponent = world.try_get<WindowResizeComponent>(windowEntity); resizeComponent)
    {
        resizeComponent->width = width;
        resizeComponent->height = height;
    }
    else
    {
        auto& newResizeComponent = world.emplace<WindowResizeComponent>(windowEntity);
        newResizeComponent.width = width;
        newResizeComponent.height = height;
    }
}