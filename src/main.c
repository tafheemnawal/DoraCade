#include <raylib.h>
#define PLAYER_SIZE 50
typedef struct
{
    float x;
    float y;
    float speed;
} Player;
void UpdatePlayer(Player *player, int screenWidth, int screenHeight, float dt)
{ // update
    if (IsKeyDown(KEY_D))
    {
        player->x += player->speed * dt;
    }
    if (IsKeyDown(KEY_A))
    {
        player->x -= player->speed * dt;
    }

    if (IsKeyDown(KEY_W))
    {
        player->y -= player->speed * dt;
    }

    if (IsKeyDown(KEY_S))
    {
        player->y += player->speed * dt;
    }

    // Keep player inside the window
    if (player->x < 0)
    {
        player->x = 0;
    }

    if (player->x > screenWidth - PLAYER_SIZE)
    {
        player->x = screenWidth - PLAYER_SIZE;
    }

    if (player->y < 0)
    {
        player->y = 0;
    }

    if (player->y > screenHeight - PLAYER_SIZE)
    {
        player->y = screenHeight - PLAYER_SIZE;
    }
}

int main(void)
{
    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "DoraCade");

    Player player;

    player.x = 400;
    player.y = 300;
    player.speed = 300;

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();
        UpdatePlayer(&player, screenWidth, screenHeight, dt);

        BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawRectangle(
            player.x,
            player.y,
            PLAYER_SIZE,
            PLAYER_SIZE,
            BLUE);
        DrawFPS(10, 10);
        DrawText("Welcome to DoraCade!", 420, 300, 40, BLUE);
        DrawText("Level 1", 560, 360, 30, RED);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}