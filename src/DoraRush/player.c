#include "player.h"

void UpdatePlayer(Player *player, int screenWidth, int screenHeight, float dt)
{
    const float gravity = 1000.0f;
    player->velocityY += gravity * dt;
    player->y += player->velocityY * dt;

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