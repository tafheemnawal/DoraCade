#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"


typedef struct
{
    float x;
    float y;
    float speed;

    int width;
    int height;

    Color color;

} Player;


// Function declarations
void UpdatePlayer(Player *player, int screenWidth, int screenHeight, float dt);

void DrawPlayer(Player *player);

void InitPlayer(Player *player, int screenWidth, int screenHeight);


#endif