set(MODULE_NAME WeApp)
make_shared_module(${MODULE_NAME} .)

target_link_libraries(${MODULE_NAME} PUBLIC WorldEngine)
target_link_libraries(${MODULE_NAME} PRIVATE WeRenderManager)