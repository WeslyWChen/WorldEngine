set(MODULE_NAME WeRenderManager)
make_shared_module(${MODULE_NAME} .)

target_link_libraries(${MODULE_NAME} PUBLIC WeRenderInterface)
target_link_libraries(${MODULE_NAME} PRIVATE WeRenderOpenGl WeModule glfw glad)