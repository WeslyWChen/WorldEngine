set(MODULE_NAME WeRenderOpenGl)
make_shared_module(${MODULE_NAME} .)

target_link_libraries(${MODULE_NAME} PUBLIC WeRenderInterface)