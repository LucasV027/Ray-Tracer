cmake_minimum_required(VERSION 3.0)

project(RayTracer)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# Libraries
include(FetchContent)

# stb_image_write
message(STATUS "Fetching stb_image_write")
FetchContent_Declare(
    stb_image_write
    GIT_REPOSITORY https://github.com/nothings/stb.git
    GIT_TAG        master
)
FetchContent_MakeAvailable(stb_image_write)
message(STATUS "Fetching stb_image_write done")

# SFML
message(STATUS "Fetching SFML")
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG        2.6.1
)
FetchContent_MakeAvailable(SFML)
message(STATUS "Fetching SFML done")

# OpenMP
find_package(OpenMP REQUIRED)

# Executable
file(GLOB_RECURSE SOURCES src/*.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -fopenmp)
target_include_directories(${PROJECT_NAME} PRIVATE src)
target_include_directories(${PROJECT_NAME}  PRIVATE ${stb_image_write_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics sfml-window sfml-system OpenMP::OpenMP_CXX)

