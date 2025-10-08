set(MODULE_NAME RenderManager)
make_shared_module(${MODULE_NAME} .)
add_library(WorldEngine::RenderManager ALIAS RenderManager)

target_link_libraries(${MODULE_NAME} PUBLIC WorldEngine::RenderInterface)
target_link_libraries(${MODULE_NAME} PRIVATE WorldEngine::RenderOpenGl WorldEngine::Module glfw glad)