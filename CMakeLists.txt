cmake_minimum_required(VERSION 3.21)
set(PROJECT_NAME "opengl-basics")
project(${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 23)

include_directories(third-party)
include_directories(third-party/glfw/include)

add_subdirectory(third-party/glad)
add_subdirectory(third-party/glfw)

#GLFW additions
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

file(GLOB SOURCES
        src/*.cpp
        third-party/stb_image/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} GLAD glfw)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets)
