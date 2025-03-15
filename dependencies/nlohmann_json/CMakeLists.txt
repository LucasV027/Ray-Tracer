message(STATUS "Fetching Nlohmann_json...")

set(JSON_BuildTests OFF CACHE INTERNAL "")

FetchContent_MakeAvailable(nlohmann_json)