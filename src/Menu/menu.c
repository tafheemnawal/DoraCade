#include "menu.h"
#include <raylib.h>

#define OPENING_TIME 2.5f
#define GAME_COUNT 3


/* =========================================================
   INITIALIZE MENU
   ========================================================= */

void InitMenu(Menu *menu, int screenWidth, int screenHeight)
{
    menu->state = MENU_OPENING;

    menu->timer = 0.0f;

    menu->selectedGame = 0;

    menu->screenWidth = screenWidth;
    menu->screenHeight = screenHeight;


    /*
     * DoraCade opening logo
     */
    menu->logo = LoadTexture(
        "../assets/textures/doracade_logo.png"
    );


    /*
     * NEW:
     * Game-selection background
     */
    menu->background = LoadTexture(
        "../assets/textures/menu_background.png"
    );
}


/* =========================================================
   UPDATE MENU
   ========================================================= */

void UpdateMenu(Menu *menu, float dt)
{
    /*
     * Opening screen
     */
    if (menu->state == MENU_OPENING)
    {
        menu->timer += dt;

        /*
         * After 2.5 seconds,
         * go to game selection.
         */
        if (menu->timer >= OPENING_TIME)
        {
            menu->state = MENU_SELECTION;

            menu->timer = 0.0f;
        }

        return;
    }


    /*
     * Game selection
     */
    if (menu->state == MENU_SELECTION)
    {
        /*
         * UP
         */
        if (IsKeyPressed(KEY_UP))
        {
            menu->selectedGame--;

            if (menu->selectedGame < 0)
            {
                menu->selectedGame = GAME_COUNT - 1;
            }
        }


        /*
         * DOWN
         */
        if (IsKeyPressed(KEY_DOWN))
        {
            menu->selectedGame++;

            if (menu->selectedGame >= GAME_COUNT)
            {
                menu->selectedGame = 0;
            }
        }
    }
}


/* =========================================================
   DRAW MENU
   ========================================================= */

void DrawMenu(Menu *menu)
{
    /* =====================================================
       OPENING SCREEN
       ===================================================== */

    if (menu->state == MENU_OPENING)
    {
        /*
         * Draw DoraCade logo full-screen
         */
        if (menu->logo.id != 0)
        {
            Rectangle source =
            {
                0,
                0,
                (float)menu->logo.width,
                (float)menu->logo.height
            };


            Rectangle destination =
            {
                0,
                0,
                (float)menu->screenWidth,
                (float)menu->screenHeight
            };


            DrawTexturePro(
                menu->logo,
                source,
                destination,
                (Vector2){0, 0},
                0.0f,
                WHITE
            );
        }

        return;
    }


    /* =====================================================
       GAME SELECTION SCREEN
       ===================================================== */

    if (menu->state == MENU_SELECTION)
    {
        /*
         * -------------------------------------------------
         * BACKGROUND
         * -------------------------------------------------
         */

        if (menu->background.id != 0)
        {
            Rectangle source =
            {
                0,
                0,
                (float)menu->background.width,
                (float)menu->background.height
            };


            /*
             * Calculate scale while preserving
             * the original image proportions.
             */
            float scaleX =
                (float)menu->screenWidth /
                (float)menu->background.width;

            float scaleY =
                (float)menu->screenHeight /
                (float)menu->background.height;

            float scale =
                (scaleX > scaleY)
                ? scaleX
                : scaleY;


            float width =
                menu->background.width * scale;

            float height =
                menu->background.height * scale;


            /*
             * Center the image.
             *
             * This crops a little from the sides/top
             * instead of distorting the artwork.
             */
            Rectangle destination =
            {
                (menu->screenWidth - width) / 2.0f,
                (menu->screenHeight - height) / 2.0f,
                width,
                height
            };


            DrawTexturePro(
                menu->background,
                source,
                destination,
                (Vector2){0, 0},
                0.0f,
                WHITE
            );
        }
        else
        {
            /*
             * Fallback if image isn't found.
             */
            ClearBackground(DARKBLUE);
        }


        /*
         * -------------------------------------------------
         * DARK PANEL BEHIND MENU
         * -------------------------------------------------
         *
         * This makes the text easier to read while
         * keeping the background visible.
         */

        DrawRectangle(
            menu->screenWidth / 2 - 230,
            60,
            460,
            570,
            (Color){0, 0, 0, 150}
        );


        /*
         * -------------------------------------------------
         * TITLE
         * -------------------------------------------------
         */

        DrawText(
            "DORACADE",
            menu->screenWidth / 2 - 150,
            90,
            50,
            WHITE
        );


        DrawText(
            "CHOOSE YOUR GAME",
            menu->screenWidth / 2 - 125,
            160,
            22,
            LIGHTGRAY
        );


        /*
         * -------------------------------------------------
         * DORARUSH
         * -------------------------------------------------
         */

        DrawText(
            "DoraRush",
            menu->screenWidth / 2 - 100,
            250,
            40,
            menu->selectedGame == 0
                ? RED
                : WHITE
        );


        /*
         * -------------------------------------------------
         * DORAMAN
         * -------------------------------------------------
         */

        DrawText(
            "DoraMan",
            menu->screenWidth / 2 - 100,
            330,
            40,
            menu->selectedGame == 1
                ? RED
                : WHITE
        );


        /*
         * -------------------------------------------------
         * GADGET INVADERS
         * -------------------------------------------------
         */

        DrawText(
            "Gadget Invaders",
            menu->screenWidth / 2 - 145,
            410,
            40,
            menu->selectedGame == 2
                ? RED
                : WHITE
        );


        /*
         * -------------------------------------------------
         * SELECTION ARROW
         * -------------------------------------------------
         */

        DrawText(
            ">",
            menu->screenWidth / 2 - 155,
            250 + menu->selectedGame * 80,
            40,
            RED
        );


        /*
         * -------------------------------------------------
         * CONTROLS
         * -------------------------------------------------
         */

        DrawText(
            "UP / DOWN  -  SELECT",
            menu->screenWidth / 2 - 110,
            510,
            18,
            LIGHTGRAY
        );


        DrawText(
            "ENTER  -  PLAY",
            menu->screenWidth / 2 - 80,
            545,
            18,
            LIGHTGRAY
        );


        /*
         * Small IUT identity
         */
        DrawText(
            "ISLAMIC UNIVERSITY OF TECHNOLOGY",
            menu->screenWidth / 2 - 145,
            590,
            14,
            LIGHTGRAY
        );
    }
}


/* =========================================================
   GET SELECTED GAME
   ========================================================= */

int GetSelectedGame(Menu *menu)
{
    return menu->selectedGame;
}


/* =========================================================
   UNLOAD MENU
   ========================================================= */

void UnloadMenu(Menu *menu)
{
    if (menu->logo.id != 0)
    {
        UnloadTexture(menu->logo);
    }


    /*
     * Unload new menu background
     */
    if (menu->background.id != 0)
    {
        UnloadTexture(menu->background);
    }
}