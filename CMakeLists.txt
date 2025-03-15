cmake_minimum_required(VERSION 3.5)

project(RayTracer VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

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

# stb_image
message(STATUS "Fetching stb_image")
FetchContent_Declare(
        stb_image
        GIT_REPOSITORY https://github.com/nothings/stb.git
        GIT_TAG master
)
FetchContent_MakeAvailable(stb_image)
target_include_directories(${PROJECT_NAME} PRIVATE ${stb_image_SOURCE_DIR})


# SFML
message(STATUS "Fetching SFML")
FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.1
)
FetchContent_MakeAvailable(SFML)
message(STATUS "Fetching SFML done")
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics sfml-window sfml-system)

# OpenMP
find_package(OpenMP REQUIRED)
target_compile_options(${PROJECT_NAME} PRIVATE ${OpenMP_CXX_FLAGS})
target_link_libraries(${PROJECT_NAME} PRIVATE OpenMP::OpenMP_CXX gomp)

# nlohmann_json
message(STATUS "Fetching nlohmann_json")
set(JSON_BuildTests OFF CACHE INTERNAL "")
FetchContent_Declare(
        json
        DOWNLOAD_NO_EXTRACT ON
        URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
)
FetchContent_MakeAvailable(json)
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)
