set(MODULE_NAME Logger)
make_shared_module(${MODULE_NAME} .)
add_library(WorldEngine::Logger ALIAS Logger)

target_link_libraries(${MODULE_NAME} PRIVATE spdlog)