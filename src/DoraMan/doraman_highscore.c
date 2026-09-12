#include "doraman_highscore.h"

#include <stdio.h>
#include <string.h>
#include <raylib.h>

#define DORAMAN_SCORE_FILE "doraman_scores.txt"

void LoadDoraManHighScores(DoraManHighScore scores[])
{
    FILE *file = fopen(DORAMAN_SCORE_FILE, "r");

    if (file == NULL)
    {
        for (int i = 0; i < MAX_DORAMAN_SCORES; i++)
        {
            strcpy(scores[i].name, "---");
            scores[i].score = 0;
        }
        return;
    }

    for (int i = 0; i < MAX_DORAMAN_SCORES; i++)
    {
        if (fscanf(file, "%19s %d", scores[i].name, &scores[i].score) != 2)
        {
            strcpy(scores[i].name, "---");
            scores[i].score = 0;
        }
    }

    fclose(file);
}

void SaveDoraManHighScores(DoraManHighScore scores[])
{
    FILE *file = fopen(DORAMAN_SCORE_FILE, "w");

    if (file == NULL)
        return;

    for (int i = 0; i < MAX_DORAMAN_SCORES; i++)
    {
        fprintf(file, "%s %d\n", scores[i].name, scores[i].score);
    }

    fclose(file);
}

void AddDoraManHighScore(DoraManHighScore scores[], const char *name, int score)
{
    if (score <= scores[MAX_DORAMAN_SCORES - 1].score)
        return;

    strncpy(scores[MAX_DORAMAN_SCORES - 1].name, name, DORAMAN_NAME_LENGTH - 1);
    scores[MAX_DORAMAN_SCORES - 1].name[DORAMAN_NAME_LENGTH - 1] = '\0';
    scores[MAX_DORAMAN_SCORES - 1].score = score;

    for (int i = MAX_DORAMAN_SCORES - 1; i > 0; i--)
    {
        if (scores[i].score > scores[i - 1].score)
        {
            DoraManHighScore temp = scores[i];
            scores[i] = scores[i - 1];
            scores[i - 1] = temp;
        }
    }

    SaveDoraManHighScores(scores);
}

void DrawDoraManHighScores(DoraManHighScore scores[], int screenWidth)
{
    DrawText("TOP 3 SCORES", screenWidth / 2 - 130, 100, 40, WHITE);

    for (int i = 0; i < MAX_DORAMAN_SCORES; i++)
    {
        DrawText(
            TextFormat("%d. %s    %d", i + 1, scores[i].name, scores[i].score),
            screenWidth / 2 - 130,
            180 + i * 50,
            25,
            YELLOW
        );
    }
}