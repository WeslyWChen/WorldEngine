set(MODULE_NAME SignalCenter)
make_shared_module(${MODULE_NAME} .)
add_library(WorldEngine::SignalCenter ALIAS SignalCenter)

target_link_libraries(${MODULE_NAME} PRIVATE WorldEngine::Module)