set(MODULE_NAME Module)
make_shared_module(${MODULE_NAME} .)
add_library(WorldEngine::Module ALIAS Module)