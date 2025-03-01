cmake_minimum_required(VERSION 3.15)
project(WellSpring-Pool)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(external/glm)
add_subdirectory(external/SDL3)

file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE HEADERS include/*.h include/*.hpp)

add_library(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PUBLIC include external/glm external/SDL3/include)

target_link_libraries(${PROJECT_NAME} SDL3::SDL3)