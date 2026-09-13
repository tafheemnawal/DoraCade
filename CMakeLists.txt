cmake_minimum_required(VERSION 3.20)

project(DoraCade C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

find_package(raylib REQUIRED)

add_executable(DoraCade
    src/main.c

    src/Audio/audio.c

    src/DoraInvaders/dora_invaders.c

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

# Put the executable in build/release/
set_target_properties(DoraCade PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/release"
)

# Copy assets beside the executable after every successful build
add_custom_command(TARGET DoraCade POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:DoraCade>/assets"
)