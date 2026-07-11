#include <raylib.h>

int main(void)
{
    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "DoraCade");

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("Welcome to DoraCade!", 420, 300, 40, BLUE);
        DrawText("Level 1", 560, 360, 30, RED);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}