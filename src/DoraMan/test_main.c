#include <raylib.h>
#include "maze.h"
#include "pacplayer.h"
#include "pellet.h"
#include "ghost.h"

int main(void)
{
    const int screenWidth = MAZE_COLS * TILE_SIZE;
    const int screenHeight = MAZE_ROWS * TILE_SIZE;

    InitWindow(screenWidth, screenHeight, "DoraMan Test");
    SetTargetFPS(60);

    PacPlayer pac;
    InitPacPlayer(&pac);
    InitPellets(pac.row, pac.col);

    Ghost ghost;
    InitGhost(&ghost, MAZE_ROWS - 2, MAZE_COLS - 2);

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

            if (CheckGhostCollision(&ghost, pac.x, pac.y))
            {
                gameOver = 1;
            }
        }

        if (gameOver && IsKeyPressed(KEY_R))
        {
            InitPacPlayer(&pac);
            InitPellets(pac.row, pac.col);
            InitGhost(&ghost, MAZE_ROWS - 2, MAZE_COLS - 2);
            score = 0;
            gameOver = 0;
        }

        BeginDrawing();
        ClearBackground(BLACK);

        DrawMaze();
        DrawPellets();
        DrawPacPlayer(&pac);
        DrawGhost(&ghost);

        DrawText(TextFormat("Score: %d", score), 10, 10, 20, WHITE);

        if (gameOver)
        {
            DrawText("GAME OVER", screenWidth / 2 - 120, screenHeight / 2 - 20, 40, RED);
            DrawText("Press R to Restart", screenWidth / 2 - 100, screenHeight / 2 + 30, 20, WHITE);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}