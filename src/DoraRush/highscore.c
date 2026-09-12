#include "highscore.h"

#include <stdio.h>
#include <string.h>
#include <raylib.h>

#define SCORE_FILE "scores.txt"

void LoadHighScores(HighScore scores[])
{
    FILE *file = fopen(SCORE_FILE, "r");

    if (file == NULL)
    {
        for (int i = 0; i < MAX_SCORES; i++)
        {
            strcpy(scores[i].name, "---");
            scores[i].score = 0;
        }

        return;
    }

    for (int i = 0; i < MAX_SCORES; i++)
    {
        if (fscanf(
                file,
                "%19s %d",
                scores[i].name,
                &scores[i].score) != 2)
        {
            strcpy(scores[i].name, "---");
            scores[i].score = 0;
        }
    }

    fclose(file);
}

void SaveHighScores(HighScore scores[])
{
    FILE *file = fopen(SCORE_FILE, "w");

    if (file == NULL)
        return;

    for (int i = 0; i < MAX_SCORES; i++)
    {
        fprintf(
            file,
            "%s %d\n",
            scores[i].name,
            scores[i].score
        );
    }

    fclose(file);
}

void AddHighScore(
    HighScore scores[],
    const char *name,
    int score)
{
    if (score <= scores[MAX_SCORES - 1].score)
        return;

    strncpy(
        scores[MAX_SCORES - 1].name,
        name,
        NAME_LENGTH - 1
    );

    scores[MAX_SCORES - 1].name[NAME_LENGTH - 1] = '\0';

    scores[MAX_SCORES - 1].score = score;

    for (int i = MAX_SCORES - 1; i > 0; i--)
    {
        if (scores[i].score > scores[i - 1].score)
        {
            HighScore temp = scores[i];

            scores[i] = scores[i - 1];
            scores[i - 1] = temp;
        }
    }

    SaveHighScores(scores);
}

void DrawHighScores(
    HighScore scores[],
    int screenWidth)
{
    DrawText(
        "TOP 3 SCORES",
        screenWidth / 2 - 130,
        100,
        40,
        DARKBLUE
    );

    for (int i = 0; i < MAX_SCORES; i++)
    {
        DrawText(
            TextFormat(
                "%d. %s    %d",
                i + 1,
                scores[i].name,
                scores[i].score
            ),
            screenWidth / 2 - 130,
            180 + i * 50,
            25,
            DARKGRAY
        );
    }
}