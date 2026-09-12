#ifndef PACPLAYER_H
#define PACPLAYER_H

#include <raylib.h>

typedef struct
{
    int row;
    int col;
    int targetRow;
    int targetCol;
    float x;
    float y;
    int dirRow;
    int dirCol;
    float speed;
    float rotation;
    Texture2D texture;
} PacPlayer;

void InitPacPlayer(PacPlayer *pac);
void LoadPacPlayerTexture(PacPlayer *pac);
void UnloadPacPlayerTexture(PacPlayer *pac);
void UpdatePacPlayer(PacPlayer *pac, float dt);
void DrawPacPlayer(PacPlayer *pac);

#endif