cmake_minimum_required(VERSION 3.28)
project(serialize_test)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)

FetchContent_Declare(
        enet
        GIT_REPOSITORY "https://github.com/lsalzman/enet.git"
        GIT_TAG "v1.3.18"
        GIT_PROGRESS TRUE
        EXCLUDE_FROM_ALL
)
FetchContent_MakeAvailable(enet)
set(ENET_INCLUDE_DIR ${enet_SOURCE_DIR}/include)

option(SKIP_PERFORMANCE_COMPARISON "Skip building performance sandbox comparison (requires boost)" TRUE)
FetchContent_Declare(
        cereal
        GIT_REPOSITORY "https://github.com/USCiLab/cereal.git"
        GIT_TAG "v1.3.2"
        GIT_PROGRESS TRUE
        EXCLUDE_FROM_ALL
)
FetchContent_MakeAvailable(cereal)
set(CEREAL_INCLUDE_DIR ${cereal_SOURCE_DIR}/include)

add_executable(${PROJECT_NAME}
        client.cpp
        headers/player.h
        headers/net_common.h
)
target_include_directories(${PROJECT_NAME} PRIVATE ${ENET_INCLUDE_DIR} ${CEREAL_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} enet cereal)

add_executable(Server
        server.cpp
        headers/player.h
        headers/net_common.h
)
target_include_directories(Server PRIVATE ${ENET_INCLUDE_DIR} ${CEREAL_INCLUDE_DIR})
target_link_libraries(Server enet cereal)