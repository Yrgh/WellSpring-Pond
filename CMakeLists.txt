cmake_minimum_required(VERSION 3.15)
project(WellSpring-Pool)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# option(VULKAN_SDK_PATH "Path to Vulkan SDK" "")

# if(NOT VULKAN_SDK_PATH)
#   message(WARNING "Vulkan SDK path not provided. Attempting to locate it.")
#   find_package(Vulkan REQUIRED)
#   if(NOT Vulkan_FOUND)
#     message(FATAL_ERROR "Vulkan SDK is required but not found!")
#   endif()
# else()
#   set(Vulkan_INCLUDE_DIR "${VULKAN_SDK_PATH}/Include" CACHE PATH "Vulkan SDK Include Path")
#   set(Vulkan_LIBRARY "${VULKAN_SDK_PATH}/Lib" CACHE PATH "Vulkan SDK Library Path")
#   message(STATUS "Using Vulkan SDK from: ${VULKAN_SDK_PATH}")
# endif()

add_subdirectory(external/glm)
add_subdirectory(external/SDL3)

file(GLOB_RECURSE SOURCES src/**.cpp)
file(GLOB_RECURSE HEADERS include/**.h include/**.hpp)

add_library(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PUBLIC include/WellSpring-Pool external/glm external/SDL3/include #[[${Vulkan_INCLUDE_DIR}]])

#target_link_directories(${PROJECT_NAME} PUBLIC ${Vulkan_LIBRARY})

target_link_libraries(${PROJECT_NAME} SDL3::SDL3)

add_executable(Example src/example/main.cpp)

target_link_libraries(Example PRIVATE ${PROJECT_NAME})