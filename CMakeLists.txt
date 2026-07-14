cmake_minimum_required(VERSION 3.20)

project(DoraCade C)

set(CMAKE_C_STANDARD 17)

find_package(raylib REQUIRED)

add_executable(DoraCade
    src/main.c
    src/GadgetInvaders/gadget_invaders.c
    src/DoraRush/player.c
    src/DoraRush/pipe.c
    src/DoraRush/coin.c
)
target_link_libraries(DoraCade PRIVATE raylib)