set(MODULE_NAME WeRenderInterface)
make_shared_module(${MODULE_NAME} .)

target_link_libraries(${MODULE_NAME} PUBLIC WorldEngine)