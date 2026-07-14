#include "pipe.h"
#include <raylib.h>

void InitPipe(Pipe *pipe, int screenWidth)
{
    pipe->x = screenWidth + 200;
    pipe->gapY = 350;
    pipe->width = 90;
    pipe->gapHeight = 180;
    pipe->scored = 0;
}

void UpdatePipe(Pipe *pipe, int screenWidth, float dt)
{
#define PIPE_SPEED 300.0f

    pipe->justRespawned = 0;

    // Move pipe left
    pipe->x -= PIPE_SPEED * dt;

    // Respawn if it leaves the screen
    if (pipe->x + pipe->width < 0)
    {
        pipe->x = screenWidth + GetRandomValue(20, 500);
        pipe->gapY = GetRandomValue(100, 540);
        pipe->scored = 0; 
    }
}

void DrawPipe(Pipe *pipe, int screenHeight)
{
    Rectangle source = {
        534,
        0,
        309,
        (float)pipe->texture.height};

    Rectangle destTop = {
        pipe->x,
        0,
        pipe->width,
        pipe->gapY};

    DrawTexturePro(
        pipe->texture,
        source,
        destTop,
        (Vector2){0, 0},
        0,
        WHITE);

    // Bottom pipe
    Rectangle destBottom = {
        pipe->x,
        pipe->gapY + pipe->gapHeight,
        pipe->width,
        screenHeight - (pipe->gapY + pipe->gapHeight)};
    DrawTexturePro(
        pipe->texture,
        source,
        destBottom,
        (Vector2){0, 0},
        0,
        WHITE);
}
int CheckPipeCollision(Player *player, Pipe *pipe, int screenHeight)
{
    Rectangle playerRect = {
        player->x,
        player->y,
        player->width,
        player->height};

    Rectangle topPipeRect = {
        pipe->x,
        0,
        pipe->width,
        pipe->gapY};

    Rectangle bottomPipeRect = {
        pipe->x,
        pipe->gapY + pipe->gapHeight,
        pipe->width,
        screenHeight - (pipe->gapY + pipe->gapHeight)};

    if (CheckCollisionRecs(playerRect, topPipeRect) ||
        CheckCollisionRecs(playerRect, bottomPipeRect))
    {
        return 1;
    }

    // Ground collision
    if (player->y + player->height >= screenHeight)
    {
        return 1;
    }

    return 0;
}
int CheckPipeScore(Player *player, Pipe *pipe)
{
    // Player has fully passed the pipe's right edge, and it hasn't been counted yet
    if (pipe->scored == 0 && (pipe->x + pipe->width) < player->x)
    {
        pipe->scored = 1;
        return 1;
    }
    return 0;
}