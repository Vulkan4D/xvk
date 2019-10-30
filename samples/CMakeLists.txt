cmake_minimum_required(VERSION 3.10)

project(xvkSamples)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/build/samples_bin")

add_definitions(-D_DEBUG)

include_directories(
	"${CMAKE_CURRENT_SOURCE_DIR}/.."
	"${CMAKE_CURRENT_SOURCE_DIR}/../glfw/include"
)

# You do not need to compile and link with GLFW if you choose another library to display on screen
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/../glfw" "${CMAKE_BINARY_DIR}/glfw")
# find_package(glfw3 3.3 REQUIRED)

if(WIN32)
	link_libraries(glfw)
else()
	link_libraries(dl glfw)
endif()

add_subdirectory("1_basic_vulkan_init")
add_subdirectory("2_basic_glfw_window")
