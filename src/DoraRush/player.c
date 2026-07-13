#include "player.h"

void UpdatePlayer(Player *player, int screenWidth, int screenHeight, float dt)
{
    const float gravity = 1000.0f;

    // 1. Check for flap FIRST
    if (IsKeyPressed(KEY_SPACE))
    {
        player->velocityY = -400.0f;
    }

    // 2. Apply gravity
    player->velocityY += gravity * dt;

    // 3. Move player
    player->y += player->velocityY * dt;

    // 4. Handle collisions
    if (player->y > screenHeight - player->height)
    {
        player->y = screenHeight - player->height;
        player->velocityY = 0;
    }

    if (player->y < 0)
    {
        player->y = 0;
    }

    if (player->y > screenHeight - player->height)
    {
        player->y = screenHeight - player->height;
        player->velocityY = 0;
    }
}

void DrawPlayer(Player *player)
{
    Rectangle source = {
        0,
        0,
        (float)player->texture.width,
        (float)player->texture.height};

    Rectangle destination = {
        player->x,
        player->y,
        64,
        64};
    Vector2 origin = {0, 0};

    DrawTexturePro(
        player->texture,
        source,
        destination,
        origin,
        0.0f,
        WHITE);
}

void InitPlayer(Player *player, int screenWidth, int screenHeight)
{
    player->velocityY = 0.0f;
    player->color = BLUE;

    player->texture = LoadTexture("../assets/textures/flying doraemon.png");

    player->width = 64;
    player->height = 64;

    player->x = (screenWidth - player->width) / 2;
    player->y = (screenHeight - player->height) / 2;
}