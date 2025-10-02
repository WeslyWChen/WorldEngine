cmake_minimum_required(VERSION 3.26)

project(WorldEngine)

include(CmakeUtils/ModuleFunction.cmake)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out/bin)

include_directories(${CMAKE_CURRENT_LIST_DIR}/ThirdParty)

add_subdirectory(Engine)
add_subdirectory(ThirdParty)