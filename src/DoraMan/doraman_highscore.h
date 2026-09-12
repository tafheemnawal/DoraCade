#ifndef DORAMAN_HIGHSCORE_H
#define DORAMAN_HIGHSCORE_H

#define MAX_DORAMAN_SCORES 3
#define DORAMAN_NAME_LENGTH 20

typedef struct
{
    char name[DORAMAN_NAME_LENGTH];
    int score;
} DoraManHighScore;

void LoadDoraManHighScores(DoraManHighScore scores[]);
void SaveDoraManHighScores(DoraManHighScore scores[]);
void AddDoraManHighScore(DoraManHighScore scores[], const char *name, int score);
void DrawDoraManHighScores(DoraManHighScore scores[], int screenWidth);

#endif