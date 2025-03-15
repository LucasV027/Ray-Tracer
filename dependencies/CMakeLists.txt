include(FetchContent)

# SFML
FetchContent_Declare(
        sfml
        GIT_REPOSITORY https://github.com/SFML/SFML
        GIT_TAG 3.0.0
)
add_subdirectory(sfml)

# Dear ImGui
FetchContent_Declare(
        imgui
        GIT_REPOSITORY https://github.com/ocornut/imgui
        GIT_TAG v1.91.1
)
FetchContent_MakeAvailable(imgui)

# ImGui-SFML
FetchContent_Declare(
        imgui-sfml
        GIT_REPOSITORY https://github.com/SFML/imgui-sfml
        GIT_TAG v3.0
)
add_subdirectory(imgui-sfml)

# stb_image
FetchContent_Declare(
        stb
        GIT_REPOSITORY https://github.com/nothings/stb.git
        GIT_TAG master
)
add_subdirectory(stb)

# nlohmann_json
FetchContent_Declare(
        nlohmann_json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.11.3
        #        DOWNLOAD_NO_EXTRACT ON
        #        URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
)
add_subdirectory(nlohmann_json)




