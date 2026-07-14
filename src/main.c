#include <raylib.h>
#include "DoraRush/player.h"
#include "DoraRush/pipe.h"
#include "DoraRush/coin.h" 

int main()
{
    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "DoraCade");

    Player player;
    Pipe pipe;
    Coin coin;

    InitPlayer(&player, screenWidth, screenHeight);
    InitPipe(&pipe, screenWidth);
    InitCoin(&coin, &pipe);
    LoadCoinTexture(&coin);
    SetTargetFPS(60);

    int gameState = 1;
    int score = 0;

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

        if (gameState == 1)
        {
            UpdatePlayer(&player, screenWidth, screenHeight, dt);
            UpdatePipe(&pipe, screenWidth, dt);
            UpdateCoin(&coin, &pipe);

            if (CheckPipeScore(&player, &pipe))
            {
                score++;
            }

            if (CheckCoinCollision(&player, &coin))  
            {
                score += 5;
            }

            if (CheckPipeCollision(&player, &pipe, screenHeight))
            {
                gameState = 2;
            }
        }

        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawPlayer(&player);
        DrawPipe(&pipe, screenHeight);
        DrawCoin(&coin);

        if (gameState == 2)
        {
            DrawText("GAME OVER", 470, 300, 50, RED);
            DrawText("Press R to Restart", 430, 360, 25, DARKGRAY);
        }

        if (IsKeyPressed(KEY_R) && gameState == 2)
        {
            InitPlayer(&player, screenWidth, screenHeight);
            InitPipe(&pipe, screenWidth);
            InitCoin(&coin, &pipe);
            score = 0;

            gameState = 1;
        }

        DrawFPS(10, 10);
        DrawText(TextFormat("Score: %d", score), screenWidth / 2 - 60, 20, 30, DARKGRAY);

        EndDrawing();
    }

    UnloadCoinTexture(&coin);
    UnloadTexture(pipe.texture);
    CloseWindow();

    return 0;
}