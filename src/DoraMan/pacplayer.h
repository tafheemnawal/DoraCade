#ifndef PACPLAYER_H
#define PACPLAYER_H

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
} PacPlayer;

void InitPacPlayer(PacPlayer *pac);
void UpdatePacPlayer(PacPlayer *pac, float dt);
void DrawPacPlayer(PacPlayer *pac);

#endif