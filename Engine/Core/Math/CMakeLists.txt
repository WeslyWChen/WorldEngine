set(MODULE_NAME Math)
make_shared_module(${MODULE_NAME} .)
add_library(WorldEngine::Math ALIAS Math)

target_link_libraries(${MODULE_NAME} PRIVATE glm)