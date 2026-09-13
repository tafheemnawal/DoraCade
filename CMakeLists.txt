cmake_minimum_required(VERSION 3.20)

project(DoraCade C)

set(CMAKE_C_STANDARD 17)

find_package(raylib REQUIRED)

add_executable(DoraCade
    src/main.c
    src/Audio/audio.c
    src/GadgetInvaders/gadget_invaders.c
    src/DoraRush/player.c
    src/DoraRush/pipe.c
    src/DoraRush/coin.c
    src/DoraRush/highscore.c
    src/Menu/menu.c
    src/DoraMan/maze.c
    src/DoraMan/pacplayer.c
    src/DoraMan/pellet.c
    src/DoraMan/ghost.c
    src/DoraMan/doraman_highscore.c
)
target_link_libraries(DoraCade PRIVATE raylib)