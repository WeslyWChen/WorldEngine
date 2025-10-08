set(MODULE_NAME RenderOpenGl)
make_shared_module(${MODULE_NAME} .)
add_library(WorldEngine::RenderOpenGl ALIAS RenderOpenGl)

target_link_libraries(${MODULE_NAME} PUBLIC WorldEngine::RenderInterface)