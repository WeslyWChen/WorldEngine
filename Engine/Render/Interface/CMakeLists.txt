set(MODULE_NAME RenderInterface)
make_shared_module(${MODULE_NAME} .)
add_library(WorldEngine::RenderInterface ALIAS RenderInterface)

target_link_libraries(${MODULE_NAME} PUBLIC WorldEngine::WorldEngine)