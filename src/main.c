#include <raylib.h>

#include "DoraRush/player.h"
#include "DoraRush/pipe.h"
#include "DoraRush/coin.h"
#include "Menu/menu.h"

#define PIPE_COUNT 4
#define CLOSING_TIME 3.0f

typedef enum
{
    STATE_MENU,
    STATE_PLAYING,
    STATE_GAMEOVER,
    STATE_CLOSING
} GameState;


/* =========================================================
   RESET DORARUSH
   ========================================================= */

void ResetDoraRush(
    Player *player,
    Pipe pipe[],
    Coin coin[],
    int screenWidth,
    int screenHeight)
{
    /*
     * Reset player
     */
    InitPlayer(
        player,
        screenWidth,
        screenHeight
    );

    /*
     * Reset pipes
     */
    for (int i = 0; i < PIPE_COUNT; i++)
    {
        InitPipe(
            &pipe[i],
            screenWidth
        );

        pipe[i].x += i * 350;
    }

    /*
     * Reset DoraCakes
     *
     * IMPORTANT:
     * This is your existing DoraCake system.
     * We are NOT changing the texture or
     * spawning system here.
     */
    for (int i = 0; i < PIPE_COUNT; i++)
    {
        InitCoin(
            &coin[i],
            &pipe[i]
        );
    }
}


/* =========================================================
   MAIN
   ========================================================= */

int main()
{
    const int screenWidth = 1280;
    const int screenHeight = 720;


    /* =====================================================
       WINDOW
       ===================================================== */

    InitWindow(
        screenWidth,
        screenHeight,
        "DoraCade"
    );

    /*
     * IMPORTANT:
     * Raylib normally uses ESC to close the window.
     *
     * We disable that because ESC is now used for:
     *
     * GAME OVER
     *      ↓
     * ESC
     *      ↓
     * CLOSING SCENE
     */
    SetExitKey(KEY_NULL);

    SetTargetFPS(60);


    /* =====================================================
       TEXTURES
       ===================================================== */

    /*
     * DoraRush pipe texture
     */
    Texture2D pipeTexture =
        LoadTexture(
            "../assets/textures/pipe.png"
        );


    /*
     * Background
     */
    Texture2D backgroundTexture =
        LoadTexture(
            "../assets/textures/background.png"
        );


    /*
     * Closing scene
     */
    Texture2D closingTexture =
        LoadTexture(
            "../assets/textures/doracade_closing.png"
        );


    /* =====================================================
       DORARUSH OBJECTS
       ===================================================== */

    Player player;

    Pipe pipe[PIPE_COUNT];

    /*
     * KEEPING YOUR EXACT DORACAKE SYSTEM
     */
    Coin coin[PIPE_COUNT];


    /* =====================================================
       MENU
       ===================================================== */

    Menu menu;

    InitMenu(
        &menu,
        screenWidth,
        screenHeight
    );


    /* =====================================================
       INITIALIZE DORARUSH
       ===================================================== */

    ResetDoraRush(
        &player,
        pipe,
        coin,
        screenWidth,
        screenHeight
    );


    /*
     * IMPORTANT:
     *
     * ResetDoraRush only initializes the DoraCakes.
     *
     * We still need to load their textures.
     *
     * This is your original system.
     */
    for (int i = 0; i < PIPE_COUNT; i++)
    {
        LoadCoinTexture(&coin[i]);
    }


    /* =====================================================
       GAME STATE
       ===================================================== */

    GameState gameState = STATE_MENU;

    int score = 0;

    float closingTimer = 0.0f;


    /* =====================================================
       MAIN LOOP
       ===================================================== */

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();


        /* =================================================
           MENU
           ================================================= */

        if (gameState == STATE_MENU)
        {
            /*
             * Update launcher/menu
             */
            UpdateMenu(
                &menu,
                dt
            );


            /*
             * ENTER selects a game
             */
            if (menu.state == MENU_SELECTION &&
                IsKeyPressed(KEY_ENTER))
            {
                int selectedGame =
                    GetSelectedGame(&menu);


                /* =========================================
                   DORARUSH
                   ========================================= */

                if (selectedGame == 0)
                {
                    /*
                     * Reset DoraRush
                     */
                    ResetDoraRush(
                        &player,
                        pipe,
                        coin,
                        screenWidth,
                        screenHeight
                    );

                    /*
                     * Reset score
                     */
                    score = 0;

                    /*
                     * Start DoraRush
                     */
                    gameState = STATE_PLAYING;
                }


                /* =========================================
                   DORAMAZE
                   ========================================= */

                else if (selectedGame == 1)
                {
                    /*
                     * DoraMaze will be connected here later.
                     */
                }


                /* =========================================
                   GADGET INVADERS
                   ========================================= */

                else if (selectedGame == 2)
                {
                    /*
                     * Gadget Invaders will be connected here later.
                     */
                }
            }
        }


        /* =================================================
           DORARUSH
           ================================================= */

        else if (gameState == STATE_PLAYING)
        {
            /*
             * Update player
             */
            UpdatePlayer(
                &player,
                screenWidth,
                screenHeight,
                dt
            );


            /* =============================================
               PIPES
               ============================================= */

            for (int i = 0; i < PIPE_COUNT; i++)
            {
                UpdatePipe(
                    &pipe[i],
                    pipe,
                    PIPE_COUNT,
                    screenWidth,
                    dt
                );


                /*
                 * Pipe score
                 */
                if (CheckPipeScore(
                        &player,
                        &pipe[i]))
                {
                    score++;
                }


                /*
                 * Pipe collision
                 */
                if (CheckPipeCollision(
                        &player,
                        &pipe[i],
                        screenHeight))
                {
                    gameState = STATE_GAMEOVER;
                }
            }


            /* =============================================
               DORACAKES
               ============================================= */

            for (int i = 0; i < PIPE_COUNT; i++)
            {
                /*
                 * KEEPING YOUR EXACT SYSTEM
                 */
                UpdateCoin(
                    &coin[i],
                    &pipe[i]
                );


                /*
                 * DoraCake collision
                 */
                if (CheckCoinCollision(
                        &player,
                        &coin[i]))
                {
                    score += 5;
                }
            }
        }


        /* =================================================
           GAME OVER
           ================================================= */

        else if (gameState == STATE_GAMEOVER)
        {
            /*
             * Restart with R
             */
            if (IsKeyPressed(KEY_R))
            {
                ResetDoraRush(
                    &player,
                    pipe,
                    coin,
                    screenWidth,
                    screenHeight
                );

                score = 0;

                gameState = STATE_PLAYING;
            }


            /*
             * ESC
             *
             * ESC no longer closes Raylib because
             * SetExitKey(KEY_NULL) was used above.
             */
            if (IsKeyPressed(KEY_ESCAPE))
            {
                closingTimer = 0.0f;

                gameState = STATE_CLOSING;
            }
        }


        /* =================================================
           CLOSING SCENE
           ================================================= */

        else if (gameState == STATE_CLOSING)
        {
            /*
             * Count closing-scene time
             */
            closingTimer += dt;


            /*
             * After 3 seconds:
             *
             * CLOSING SCENE
             *       ↓
             * GAME SELECTION
             *
             * We deliberately skip MENU_OPENING.
             */
            if (closingTimer >= CLOSING_TIME)
            {
                menu.state = MENU_SELECTION;

                menu.timer = 0.0f;

                menu.selectedGame = 0;

                closingTimer = 0.0f;

                gameState = STATE_MENU;
            }
        }


        /* =================================================
           DRAW
           ================================================= */

        BeginDrawing();


        /* =================================================
           MENU DRAWING
           ================================================= */

        if (gameState == STATE_MENU)
        {
            ClearBackground(BLACK);

            DrawMenu(&menu);
        }


        /* =================================================
           DORARUSH DRAWING
           ================================================= */

        else if (gameState == STATE_PLAYING ||
                 gameState == STATE_GAMEOVER)
        {
            /*
             * Background
             */
            if (backgroundTexture.id != 0)
            {
                Rectangle source =
                {
                    0,
                    0,
                    (float)backgroundTexture.width,
                    (float)backgroundTexture.height
                };

                Rectangle destination =
                {
                    0,
                    0,
                    (float)screenWidth,
                    (float)screenHeight
                };

                DrawTexturePro(
                    backgroundTexture,
                    source,
                    destination,
                    (Vector2){0, 0},
                    0.0f,
                    WHITE
                );
            }
            else
            {
                ClearBackground(SKYBLUE);
            }


            /*
             * Player
             */
            DrawPlayer(&player);


            /*
             * Pipes
             */
            for (int i = 0; i < PIPE_COUNT; i++)
            {
                DrawPipe(
                    &pipe[i],
                    pipeTexture,
                    screenHeight
                );
            }


            /*
             * KEEPING YOUR EXACT DORACAKE DRAWING
             */
            for (int i = 0; i < PIPE_COUNT; i++)
            {
                DrawCoin(&coin[i]);
            }


            /*
             * Score
             */
            DrawText(
                TextFormat(
                    "Score: %d",
                    score
                ),
                screenWidth / 2 - 60,
                20,
                30,
                DARKGRAY
            );


            /* =============================================
               GAME OVER SCREEN
               ============================================= */

            if (gameState == STATE_GAMEOVER)
            {
                DrawText(
                    "GAME OVER",
                    470,
                    280,
                    50,
                    RED
                );

                DrawText(
                    "Press R to Restart",
                    450,
                    350,
                    25,
                    DARKGRAY
                );

                DrawText(
                    "Press ESC for Main Menu",
                    420,
                    390,
                    25,
                    DARKGRAY
                );
            }


            DrawFPS(10, 10);
        }


        /* =================================================
           CLOSING SCENE DRAWING
           ================================================= */

        else if (gameState == STATE_CLOSING)
        {
            if (closingTexture.id != 0)
            {
                Rectangle source =
                {
                    0,
                    0,
                    (float)closingTexture.width,
                    (float)closingTexture.height
                };

                Rectangle destination =
                {
                    0,
                    0,
                    (float)screenWidth,
                    (float)screenHeight
                };

                DrawTexturePro(
                    closingTexture,
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
                 * Fallback if the image
                 * cannot be loaded.
                 */
                ClearBackground(BLACK);

                DrawText(
                    "DoraCade",
                    screenWidth / 2 - 150,
                    screenHeight / 2,
                    50,
                    WHITE
                );
            }
        }


        EndDrawing();
    }


    /* =====================================================
       CLEANUP
       ===================================================== */

    UnloadTexture(pipeTexture);

    UnloadTexture(backgroundTexture);

    UnloadTexture(closingTexture);


    for (int i = 0; i < PIPE_COUNT; i++)
    {
        UnloadCoinTexture(&coin[i]);
    }


    /*
     * Menu cleanup
     */
    UnloadMenu(&menu);


    CloseWindow();

    return 0;
}