#include <raylib.h>
#include <string.h>
#include "maze.h"
#include "pacplayer.h"
#include "pellet.h"
#include "ghost.h"
#include "doraman_highscore.h"

int main(void)
{
    const int screenWidth = MAZE_COLS * TILE_SIZE;
    const int screenHeight = MAZE_ROWS * TILE_SIZE;

    InitWindow(screenWidth, screenHeight, "DoraMan Test");

    Texture2D backgroundTexture = LoadTexture("../assets/textures/doraman_background.png");

    SetTargetFPS(60);

    PacPlayer pac;
    InitPacPlayer(&pac);
    LoadPacPlayerTexture(&pac);
    InitPellets(pac.row, pac.col);

    Ghost ghost;
    InitGhost(&ghost, MAZE_ROWS - 2, MAZE_COLS - 2);
    LoadGhostTexture(&ghost);

    DoraManHighScore highScores[MAX_DORAMAN_SCORES];
    LoadDoraManHighScores(highScores);

    char playerName[DORAMAN_NAME_LENGTH] = "";
    int nameLength = 0;
    int enteringName = 0;
    int showingHighScores = 0;

    int score = 0;
    int gameOver = 0;

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

        if (!gameOver)
        {
            UpdatePacPlayer(&pac, dt);
            UpdateGhost(&ghost, dt);

            if (CollectPellet(pac.row, pac.col))
            {
                score += 10;
            }

            if (AllPelletsCollected())
            {
                InitPacPlayer(&pac);
                InitPellets(pac.row, pac.col);
                InitGhost(&ghost, MAZE_ROWS - 2, MAZE_COLS - 2);
                // score is NOT reset here — it carries over
            }

            if (CheckGhostCollision(&ghost, pac.x, pac.y))
            {
                gameOver = 1;
                enteringName = 1;
                playerName[0] = '\0';
                nameLength = 0;
            }
        }
        else if (enteringName)
        {
            int key = GetCharPressed();
            while (key > 0)
            {
                if (key >= 32 && key <= 125 && nameLength < DORAMAN_NAME_LENGTH - 1)
                {
                    playerName[nameLength] = (char)key;
                    nameLength++;
                    playerName[nameLength] = '\0';
                }
                key = GetCharPressed();
            }

            if (IsKeyPressed(KEY_BACKSPACE) && nameLength > 0)
            {
                nameLength--;
                playerName[nameLength] = '\0';
            }

            if (IsKeyPressed(KEY_ENTER))
            {
                if (nameLength == 0)
                {
                    strcpy(playerName, "Player");
                }

                AddDoraManHighScore(highScores, playerName, score);

                enteringName = 0;
                showingHighScores = 1;
            }
        }
        else if (showingHighScores)
        {
            if (IsKeyPressed(KEY_ENTER))
            {
                showingHighScores = 0;
            }

            if (IsKeyPressed(KEY_R))
            {
                InitPacPlayer(&pac);
                InitPellets(pac.row, pac.col);
                InitGhost(&ghost, MAZE_ROWS - 2, MAZE_COLS - 2);
                score = 0;
                gameOver = 0;
                showingHighScores = 0;
            }
        }

        BeginDrawing();
        ClearBackground(BLACK);

        DrawTexturePro(
            backgroundTexture,
            (Rectangle){ 0, 0, (float)backgroundTexture.width, (float)backgroundTexture.height },
            (Rectangle){ 0, 0, (float)screenWidth, (float)screenHeight },
            (Vector2){ 0, 0 },
            0.0f,
            WHITE
        );

        DrawMaze();
        DrawPellets();
        DrawPacPlayer(&pac);
        DrawGhost(&ghost);

        DrawText(TextFormat("Score: %d", score), 10, 10, 20, WHITE);

        if (enteringName)
        {
            DrawText("GAME OVER", screenWidth / 2 - 150, screenHeight / 2 - 60, 50, WHITE);
            DrawText("Enter your name: ", screenWidth / 2 - 120, screenHeight / 2, 20, YELLOW);
            DrawText(playerName, screenWidth / 2 + 70, screenHeight / 2, 20, WHITE);
        }
        else if (showingHighScores)
        {
            DrawDoraManHighScores(highScores, screenWidth);
            DrawText("Press R to restart", screenWidth / 2 - 100, screenHeight / 2 + 60, 20, WHITE);
        }

        EndDrawing();
    }

    UnloadTexture(backgroundTexture);
    UnloadGhostTexture(&ghost);
    UnloadPacPlayerTexture(&pac);
    CloseWindow();
    return 0;
}