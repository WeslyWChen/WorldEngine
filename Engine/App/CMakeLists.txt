set(MODULE_NAME App)
make_shared_module(${MODULE_NAME} .)
add_library(WorldEngine::App ALIAS App)

target_link_libraries(${MODULE_NAME} PUBLIC WorldEngine::WorldEngine)
target_link_libraries(${MODULE_NAME} PRIVATE WorldEngine::RenderManager WorldEngine::GameEngine)