set(MODULE_NAME RenderManager)
make_shared_module(${MODULE_NAME} .)
add_library(WorldEngine::RenderManager ALIAS RenderManager)

target_link_libraries(${MODULE_NAME} PUBLIC WorldEngine::RenderInterface WorldEngine::WorldEngine)
target_link_libraries(${MODULE_NAME} PRIVATE glfw glad WorldEngine::SignalCenter)