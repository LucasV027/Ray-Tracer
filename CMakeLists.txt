cmake_minimum_required(VERSION 3.0)

project(RayTracer)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Libraries
include(FetchContent)

FetchContent_Declare(
    stb_image_write
    GIT_REPOSITORY https://github.com/nothings/stb.git
    GIT_TAG        master
)

FetchContent_MakeAvailable(stb_image_write)

find_package(OpenMP REQUIRED)

# Executable
file(GLOB_RECURSE SOURCES src/*.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -fopenmp)
target_include_directories(${PROJECT_NAME} PRIVATE src)
target_include_directories(${PROJECT_NAME}  PRIVATE ${stb_image_write_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE OpenMP::OpenMP_CXX)
