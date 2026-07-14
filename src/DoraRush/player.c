/*
 * DoraCade
 * Game: DoraRush
 * File: player.c
 * Purpose: Handles player movement, physics and rendering.
 */
#include "player.h"

void UpdatePlayer(Player *player, int screenWidth, int screenHeight, float dt)
{
    const float gravity = 1000.0f;

    if (IsKeyPressed(KEY_SPACE))
    {
        player->velocityY = -200.0f;
    }

    player->velocityY += gravity * dt;

    player->y += player->velocityY * dt;
    // Don't let the player go above the screen
    if (player->y < 0)
    {
        player->y = 0;
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
        84,
        84};
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

    player->width = 84;
    player->height = 84;

    player->x = (screenWidth - player->width) / 2;
    player->y = (screenHeight - player->height) / 2;
}