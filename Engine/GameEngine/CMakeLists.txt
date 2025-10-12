set(MODULE_NAME GameEngine)
make_shared_module(${MODULE_NAME} .)
add_library(WorldEngine::GameEngine ALIAS GameEngine)

target_link_libraries(${MODULE_NAME} PUBLIC WorldEngine::Module WorldEngine::WorldEngine)