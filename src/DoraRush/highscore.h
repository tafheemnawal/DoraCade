#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#define MAX_SCORES 3
#define NAME_LENGTH 20

typedef struct
{
    char name[NAME_LENGTH];
    int score;
} HighScore;

void LoadHighScores(HighScore scores[]);
void SaveHighScores(HighScore scores[]);
void AddHighScore(HighScore scores[], const char *name, int score);
void DrawHighScores(HighScore scores[], int screenWidth);

#endif