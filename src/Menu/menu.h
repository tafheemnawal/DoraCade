#ifndef MENU_H
#define MENU_H

#include <raylib.h>

typedef enum
{
    MENU_OPENING,
    MENU_SELECTION
} MenuState;

typedef struct
{
    MenuState state;

    float timer;

    int selectedGame;

    int screenWidth;
    int screenHeight;

    Texture2D logo;
    Texture2D background;

} Menu;

void InitMenu(Menu *menu, int screenWidth, int screenHeight);

void UpdateMenu(Menu *menu, float dt);

void DrawMenu(Menu *menu);

int GetSelectedGame(Menu *menu);

void UnloadMenu(Menu *menu);

#endif