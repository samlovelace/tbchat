cmake_minimum_required(VERSION 3.8)

project(tbchat)

find_package(Boost REQUIRED COMPONENTS system)

# Download and add nlohmann/json as a dependency
include(FetchContent)
FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.10.5 # or latest version
)
FetchContent_MakeAvailable(json)

set(TBCHAT_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/src/main.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/Room.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/RoomsHandler.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/Server.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/User.cpp
)

add_executable(${PROJECT_NAME} ${TBCHAT_SOURCES})

include_directories(${PROJECT_NAME} 
    ${CMAKE_CURRENT_LIST_DIR}/include
)

target_link_libraries(${PROJECT_NAME} pthread Boost::system nlohmann_json::nlohmann_json)