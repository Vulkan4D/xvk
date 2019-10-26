cmake_minimum_required(VERSION 3.10)

project(xvkSampleApplication)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(xvkSampleApplication "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")

target_include_directories(xvkSampleApplication
PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}/.."
	"${CMAKE_CURRENT_SOURCE_DIR}/../glfw/include"
)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/../glfw" "${CMAKE_BINARY_DIR}/glfw")
# find_package(glfw3 3.3 REQUIRED)

target_link_libraries(xvkSampleApplication
	dl
	glfw
)
