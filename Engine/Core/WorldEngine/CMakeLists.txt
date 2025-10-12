set(MODULE_NAME WorldEngine)
make_shared_module(${MODULE_NAME} .)
add_library(WorldEngine::WorldEngine ALIAS WorldEngine)

target_link_libraries(${MODULE_NAME} PUBLIC WorldEngine::Math WorldEngine::Module)