#ifndef PACPLAYER_H
#define PACPLAYER_H

typedef struct
{
    int row;
    int col;
    float x;
    float y;
} PacPlayer;

void InitPacPlayer(PacPlayer *pac);
void DrawPacPlayer(PacPlayer *pac);

#endif