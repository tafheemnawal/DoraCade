#include <raylib.h>
typedef struct
{
    float x;
    float y;
    float speed;

    int width;
    int height;

    Color color;
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

    if (player->x > screenWidth - player->width)
    {
        player->x = screenWidth - player->width;
    }

    if (player->y < 0)
    {
        player->y = 0;
    }

    if (player->y > screenHeight - player->height)
    {
        player->y = screenHeight - player->height;
    }
}
void DrawPlayer(Player *player)
{
    DrawRectangle(
        player->x,
        player->y,
        player->width,
        player->height,
        BLUE);
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
    player.width = 50;
    player.height = 50;
    player.color = BLUE;

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();
        UpdatePlayer(&player, screenWidth, screenHeight, dt);

        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawPlayer(&player);
        DrawFPS(10, 10);
        DrawText("Welcome to DoraCade!", 420, 300, 40, BLUE);
        DrawText("Level 1", 560, 360, 30, RED);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}