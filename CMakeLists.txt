cmake_minimum_required(VERSION 3.21)
set(PROJECT_NAME "opengl-basics")
project(${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 23)

include_directories(third-party)
include_directories(third-party/glfw/include)
include_directories(third-party/glm/glm)
include_directories(third-party/imgui)
include_directories(third-party/imgui/backends)
include_directories(third-party/ImGuizmo)

add_subdirectory(third-party/glad)
add_subdirectory(third-party/glfw)
add_subdirectory(third-party/glm)

#GLFW additions
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)


file(GLOB_RECURSE SOURCES src/*.cpp src/*.h)

file(GLOB IMGUI_SOURCES "third-party/imgui/*.h"
        "third-party/imgui/*.cpp"
        "third-party/imgui/backends/imgui_impl_glfw.cpp"
        "third-party/imgui/backends/imgui_impl_opengl3.cpp")

file(GLOB IMGUIZMO_SOURCES "third-party/ImGuizmo/*.h"
        "third-party/ImGuizmo/*.cpp")

file(GLOB STB_IMAGE_SOURCES third-party/stb_image/*.cpp)

add_library(ThirdPartyLibs ${IMGUI_SOURCES} ${IMGUIZMO_SOURCES} ${STB_IMAGE_SOURCES})

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} GLAD glfw glm ThirdPartyLibs)

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets)
