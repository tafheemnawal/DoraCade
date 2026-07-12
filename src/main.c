#include <raylib.h>
#include "player.h"


int main()
{
    const int screenWidth = 1280;
    const int screenHeight = 720;


    InitWindow(screenWidth, screenHeight, "DoraCade");


    Player player;


    InitPlayer(&player, screenWidth, screenHeight);

    SetTargetFPS(60);


    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();


        UpdatePlayer(&player, screenWidth, screenHeight, dt);


        BeginDrawing();

        ClearBackground(RAYWHITE);


        DrawPlayer(&player);


        DrawFPS(10,10);

        DrawText("Welcome to DoraCade!",420,300,40,BLUE);
        DrawText("Level 1",560,360,30,RED);


        EndDrawing();
    }


    CloseWindow();


    return 0;
}