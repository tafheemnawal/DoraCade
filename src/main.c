#include <raylib.h>
#include "DoraRush/player.h"
#include "DoraRush/pipe.h"
#include "DoraRush/coin.h"

#define PIPE_COUNT 4

int main()
{
    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "DoraCade");
    Texture2D pipeTexture = LoadTexture("../assets/textures/pipe.png");
    Texture2D backgroundTexture = LoadTexture("../assets/textures/background.png");

    Player player;
    Pipe pipe[PIPE_COUNT];
    Coin coin[PIPE_COUNT];

    InitPlayer(&player, screenWidth, screenHeight);

    for (int i = 0; i < PIPE_COUNT; i++)
    {
        InitPipe(&pipe[i], screenWidth);
        pipe[i].x += i * 350;
    }

    for (int i = 0; i < PIPE_COUNT; i++)
    {
        InitCoin(&coin[i], &pipe[i]);
        LoadCoinTexture(&coin[i]);
    }

    SetTargetFPS(60);
    int gameState = 1;
    int score = 0;

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

        if (gameState == 1)
        {
            UpdatePlayer(&player, screenWidth, screenHeight, dt);

            for (int i = 0; i < PIPE_COUNT; i++)
            {
                UpdatePipe(
                    &pipe[i],
                    pipe,
                    PIPE_COUNT,
                    screenWidth,
                    dt
                );

                if (CheckPipeScore(&player, &pipe[i]))
                {
                    score++;
                }

                if (CheckPipeCollision(&player, &pipe[i], screenHeight))
                {
                    gameState = 2;
                }
            }

            for (int i = 0; i < PIPE_COUNT; i++)
            {
                UpdateCoin(&coin[i], &pipe[i]);

                if (CheckCoinCollision(&player, &coin[i]))
                {
                    score += 5;
                }
            }
        }

        BeginDrawing();

        DrawTexture(backgroundTexture, 0, 0, WHITE);

        DrawPlayer(&player);

        for (int i = 0; i < PIPE_COUNT; i++)
        {
            DrawPipe(&pipe[i], pipeTexture, screenHeight);
        }

        for (int i = 0; i < PIPE_COUNT; i++)
        {
            DrawCoin(&coin[i]);
        }

        if (gameState == 2)
        {
            DrawText("GAME OVER", 470, 300, 50, RED);
            DrawText("Press R to Restart", 430, 360, 25, DARKGRAY);
        }

        if (IsKeyPressed(KEY_R) && gameState == 2)
        {
            InitPlayer(&player, screenWidth, screenHeight);

            for (int i = 0; i < PIPE_COUNT; i++)
            {
                InitPipe(&pipe[i], screenWidth);
                pipe[i].x += i * 350;
            }

            for (int i = 0; i < PIPE_COUNT; i++)
            {
                InitCoin(&coin[i], &pipe[i]);
            }

            score = 0;
            gameState = 1;
        }

        DrawFPS(10, 10);
        DrawText(TextFormat("Score: %d", score),
                 screenWidth / 2 - 60,
                 20,
                 30,
                 DARKGRAY);

        EndDrawing();
    }
    UnloadTexture(pipeTexture);
    UnloadTexture(backgroundTexture);

    for (int i = 0; i < PIPE_COUNT; i++)
    {
        UnloadCoinTexture(&coin[i]);
    }
    CloseWindow();

    return 0;
}