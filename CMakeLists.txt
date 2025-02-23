cmake_minimum_required(VERSION 3.5)

# Project name and version
project(RayTracer VERSION 1.0)

# Options for optional dependencies
option(SFML "Hook SFML" ON)
option(STB_IMAGE_WRITE "Hook stb_image_write" ON)
option(OPENMP "Enable OpenMP" ON)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set output directory for runtime binaries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# Executable
add_executable(${PROJECT_NAME}
        src/main.cpp

        src/application/app.cpp
        src/application/app.h

        src/core/image.h
        src/core/image.cpp
        src/core/camera.h
        src/core/camera.cpp
        src/core/scene.h
        src/core/scene.cpp

        src/materials/material.h
        src/materials/material.cpp
        src/materials/lambertian.h
        src/materials/lambertian.cpp
        src/materials/metal.h
        src/materials/metal.cpp

        src/shapes/hittable.h
        src/shapes/hittable.cpp
        src/shapes/plan.h
        src/shapes/plan.cpp
        src/shapes/sphere.h
        src/shapes/sphere.cpp

        src/utils/color.h
        src/utils/color.cpp
        src/utils/math.h
        src/utils/math.cpp
        src/utils/ray.h
        src/utils/ray.cpp
        src/utils/vec3.h
        src/utils/vec3.cpp
)


set(DATA_DIR "${CMAKE_SOURCE_DIR}/data/")
set(OUT_DIR "${CMAKE_SOURCE_DIR}/out/")
target_compile_definitions(${PROJECT_NAME} PUBLIC DATA_DIR=\"${DATA_DIR}\")
target_compile_definitions(${PROJECT_NAME} PUBLIC OUT_DIR=\"${OUT_DIR}\")

target_include_directories(${PROJECT_NAME} PRIVATE src)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall)


# Libraries
include(FetchContent)

if (STB_IMAGE_WRITE)
    message(STATUS "Fetching stb_image_write")
    FetchContent_Declare(
            stb_image_write
            GIT_REPOSITORY https://github.com/nothings/stb.git
            GIT_TAG master
    )
    FetchContent_MakeAvailable(stb_image_write)
    target_include_directories(${PROJECT_NAME} PRIVATE ${stb_image_write_SOURCE_DIR})
    target_compile_definitions(${PROJECT_NAME} PRIVATE -DLIB_STB_IMAGE_WRITE)

endif ()

if (SFML)
    message(STATUS "Fetching SFML")
    FetchContent_Declare(
            SFML
            GIT_REPOSITORY https://github.com/SFML/SFML.git
            GIT_TAG 2.6.1
    )
    FetchContent_MakeAvailable(SFML)
    message(STATUS "Fetching SFML done")
    target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics sfml-window sfml-system)
    target_compile_definitions(${PROJECT_NAME} PRIVATE -DLIB_SFML)
endif ()

if (OPENMP)
    find_package(OpenMP)
    if (OpenMP_CXX_FOUND)
        target_compile_options(${PROJECT_NAME} PRIVATE ${OpenMP_CXX_FLAGS})
        target_link_libraries(${PROJECT_NAME} PRIVATE OpenMP::OpenMP_CXX gomp)
        target_compile_definitions(${PROJECT_NAME} PRIVATE -DLIB_OPENMP)
    endif ()
endif ()


