cmake_minimum_required(VERSION 3.10)

project(xvkSampleApplication)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(glfw3 3.3 REQUIRED)

add_executable(xvkSampleApplication "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")

target_include_directories(xvkSampleApplication
PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}/.."
	"${CMAKE_CURRENT_SOURCE_DIR}/../glfw/include"
)

target_link_libraries(xvkSampleApplication
	dl
	glfw
)
