cmake_minimum_required(VERSION 3.8)

project(tbchat)

find_package(Boost REQUIRED COMPONENTS system)

set(TBCHAT_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/src/main.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/Server.cpp
)

add_executable(${PROJECT_NAME} ${TBCHAT_SOURCES})

include_directories(${PROJECT_NAME} 
    ${CMAKE_CURRENT_LIST_DIR}/include
)

target_link_libraries(${PROJECT_NAME} pthread Boost::system)