#include <raylib.h>
#include <string.h>

#include "DoraRush/player.h"
#include "DoraRush/pipe.h"
#include "DoraRush/coin.h"
#include "DoraRush/highscore.h"
#include "Menu/menu.h"

#include "DoraMan/maze.h"          
#include "DoraMan/pacplayer.h"     
#include "DoraMan/pellet.h"         
#include "DoraMan/ghost.h"         
#include "DoraMan/doraman_highscore.h"   

#define PIPE_COUNT 4
#define CLOSING_TIME 3.0f

typedef enum
{
    STATE_MENU,
    STATE_PLAYING,
    STATE_GAMEOVER,
    STATE_CLOSING,
    STATE_DORAMAN,           
    STATE_DORAMAN_GAMEOVER   
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
   RESET DORAMAN
   ========================================================= */

void ResetDoraMan(PacPlayer *pac, Ghost *ghost, int startRow, int startCol)
{
    InitPacPlayer(pac);
    InitPellets(pac->row, pac->col);
    InitGhost(ghost, startRow, startCol);
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
     * ESC is controlled by our game states.
     * It must NOT close the Raylib window.
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
       HIGH SCORES
       ===================================================== */

    HighScore highScores[MAX_SCORES];

    /*
     * Load saved scores from scores.txt
     */
    LoadHighScores(highScores);

    /*
     * Player name entered after Game Over
     */
    char playerName[NAME_LENGTH] = "";

    int nameLength = 0;

    /*
     * Controls the different Game Over screens
     */
    bool enteringName = false;
    bool showingHighScores = false;


    /* =====================================================
       DORAMAN OBJECTS
       ===================================================== */

    PacPlayer pac;
    Ghost ghost;

    Texture2D doramanBackgroundTexture = LoadTexture("assets/textures/doraman_background.png");

    DoraManHighScore doramanHighScores[MAX_DORAMAN_SCORES];
    LoadDoraManHighScores(doramanHighScores);

    char doramanPlayerName[DORAMAN_NAME_LENGTH] = "";
    int doramanNameLength = 0;
    int doramanEnteringName = 0;
    int doramanShowingHighScores = 0;

    int doramanScore = 0;


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
                     * Reset high-score screen state
                     */
                    enteringName = false;
                    showingHighScores = false;

                    playerName[0] = '\0';
                    nameLength = 0;

                    /*
                     * Start DoraRush
                     */
                    gameState = STATE_PLAYING;
                }


                /* =========================================
                   DORAMAN
                   ========================================= */

                else if (selectedGame == 1)
                {
                    /*
                    * Reset DoraMan
                    */
                    ResetDoraMan(&pac, &ghost, MAZE_ROWS - 2, MAZE_COLS - 2);
                    LoadPacPlayerTexture(&pac);
                    LoadGhostTexture(&ghost);

                    doramanScore = 0;
                    doramanEnteringName = 0;
                    doramanShowingHighScores = 0;
                    doramanPlayerName[0] = '\0';
                    doramanNameLength = 0;

                    /*
                    * Start DoraMan
                    */
                    gameState = STATE_DORAMAN;
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

                    /*
                     * Start player-name entry
                     */
                    enteringName = true;
                    showingHighScores = false;

                    playerName[0] = '\0';
                    nameLength = 0;
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
            /* =============================================
               ENTER PLAYER NAME
               ============================================= */

            if (enteringName)
            {
                /*
                 * Read typed characters
                 */
                int key = GetCharPressed();

                while (key > 0)
                {
                    /*
                     * Accept printable ASCII characters
                     */
                    if (key >= 32 &&
                        key <= 125 &&
                        nameLength < NAME_LENGTH - 1)
                    {
                        playerName[nameLength] =
                            (char)key;

                        nameLength++;

                        playerName[nameLength] =
                            '\0';
                    }

                    key = GetCharPressed();
                }


                /*
                 * Backspace
                 */
                if (IsKeyPressed(KEY_BACKSPACE) &&
                    nameLength > 0)
                {
                    nameLength--;

                    playerName[nameLength] =
                        '\0';
                }


                /*
                 * ENTER:
                 *
                 * Save score
                 *      ↓
                 * Show TOP 3
                 */
                if (IsKeyPressed(KEY_ENTER))
                {
                    /*
                     * If the player entered nothing,
                     * use "Player".
                     */
                    if (nameLength == 0)
                    {
                        strcpy(
                            playerName,
                            "Player"
                        );
                    }


                    /*
                     * Add score to Top 3
                     */
                    AddHighScore(
                        highScores,
                        playerName,
                        score
                    );


                    /*
                     * Move to Top 3 screen
                     */
                    enteringName = false;
                    showingHighScores = true;
                }
            }


            /* =============================================
               TOP 3 SCORES
               ============================================= */

            else if (showingHighScores)
            {
                /*
                 * ENTER hides the high-score screen.
                 */
                if (IsKeyPressed(KEY_ENTER))
                {
                    showingHighScores = false;
                }
            }


            /* =============================================
               NORMAL GAME OVER
               ============================================= */

            else
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

                    enteringName = false;
                    showingHighScores = false;

                    playerName[0] = '\0';
                    nameLength = 0;

                    gameState = STATE_PLAYING;
                }


                /*
                 * ESC
                 *
                 * ESC no longer closes Raylib because
                 * SetExitKey(KEY_NULL) was used above.
                 *
                 * GAME OVER
                 *      ↓
                 * ESC
                 *      ↓
                 * CLOSING SCENE
                 */
                if (IsKeyPressed(KEY_ESCAPE))
                {
                    closingTimer = 0.0f;

                    gameState = STATE_CLOSING;
                }
            }
        }


        /* =================================================
            DORAMAN
           ================================================= */

        else if (gameState == STATE_DORAMAN)
        {
            UpdatePacPlayer(&pac, dt);
            UpdateGhost(&ghost, dt);

            if (CollectPellet(pac.row, pac.col))
            {
                doramanScore += 10;
            }

            if (AllPelletsCollected())
            {
                ResetDoraMan(&pac, &ghost, MAZE_ROWS - 2, MAZE_COLS - 2);
            }

            if (CheckGhostCollision(&ghost, pac.x, pac.y))
            {
                gameState = STATE_DORAMAN_GAMEOVER;
                doramanEnteringName = 1;
                doramanPlayerName[0] = '\0';
                doramanNameLength = 0;
            }

            if (IsKeyPressed(KEY_ESCAPE))
            {
                UnloadPacPlayerTexture(&pac);
                UnloadGhostTexture(&ghost);
                closingTimer = 0.0f;
                gameState = STATE_CLOSING;
            }
        }


        /* =================================================
            DORAMAN GAME OVER
           ================================================= */

        else if (gameState == STATE_DORAMAN_GAMEOVER)
        {
            if (doramanEnteringName)
            {
                int key = GetCharPressed();
                while (key > 0)
                {
                    if (key >= 32 && key <= 125 && doramanNameLength < DORAMAN_NAME_LENGTH - 1)
                    {
                        doramanPlayerName[doramanNameLength] = (char)key;
                        doramanNameLength++;
                        doramanPlayerName[doramanNameLength] = '\0';
                    }
                    key = GetCharPressed();
                }

                if (IsKeyPressed(KEY_BACKSPACE) && doramanNameLength > 0)
                {
                    doramanNameLength--;
                    doramanPlayerName[doramanNameLength] = '\0';
                }

                if (IsKeyPressed(KEY_ENTER))
                {
                    if (doramanNameLength == 0)
                    {
                        strcpy(doramanPlayerName, "Player");
                    }

                    AddDoraManHighScore(doramanHighScores, doramanPlayerName, doramanScore);

                    doramanEnteringName = 0;
                    doramanShowingHighScores = 1;
                }
            }
            else if (doramanShowingHighScores)
            {
                if (IsKeyPressed(KEY_R))
                {
                    ResetDoraMan(&pac, &ghost, MAZE_ROWS - 2, MAZE_COLS - 2);
                    LoadPacPlayerTexture(&pac);
                    LoadGhostTexture(&ghost);
                    doramanScore = 0;
                    doramanShowingHighScores = 0;
                    gameState = STATE_DORAMAN;
                }
            }

            if (IsKeyPressed(KEY_ESCAPE))
            {
                UnloadPacPlayerTexture(&pac);
                UnloadGhostTexture(&ghost);
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
                /*
                 * =========================================
                 * ENTER NAME
                 * =========================================
                 */

                if (enteringName)
                {
                    DrawText(
                        "GAME OVER",
                        470,
                        220,
                        50,
                        RED
                    );

                    DrawText(
                        "Enter your name:",
                        470,
                        300,
                        30,
                        DARKGRAY
                    );


                    /*
                     * Name input box
                     */
                    DrawRectangle(
                        430,
                        350,
                        420,
                        55,
                        LIGHTGRAY
                    );


                    DrawText(
                        playerName,
                        450,
                        365,
                        30,
                        BLACK
                    );


                    DrawText(
                        "Press ENTER to save your score",
                        390,
                        440,
                        25,
                        DARKGRAY
                    );
                }


                /*
                 * =========================================
                 * TOP 3 SCORES
                 * =========================================
                 */

                else if (showingHighScores)
                {
                    DrawHighScores(
                        highScores,
                        screenWidth
                    );


                    DrawText(
                        "Press ENTER to continue",
                        430,
                        380,
                        25,
                        DARKGRAY
                    );
                }


                /*
                 * =========================================
                 * NORMAL GAME OVER
                 * =========================================
                 */

                else
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
            }


            DrawFPS(10, 10);
        }


        /* =================================================
           DORAMAN DRAWING
           ================================================= */

        else if (gameState == STATE_DORAMAN ||
                gameState == STATE_DORAMAN_GAMEOVER)
        {
            DrawTexturePro(
                doramanBackgroundTexture,
                (Rectangle){ 0, 0, (float)doramanBackgroundTexture.width, (float)doramanBackgroundTexture.height },
                (Rectangle){ 0, 0, (float)screenWidth, (float)screenHeight },
                (Vector2){ 0, 0 },
                0.0f,
                WHITE
            );

            DrawMaze();
            DrawPellets();
            DrawPacPlayer(&pac);
            DrawGhost(&ghost);

            DrawText(TextFormat("Score: %d", doramanScore), 10, 10, 20, WHITE);

            if (gameState == STATE_DORAMAN_GAMEOVER)
            {
                if (doramanEnteringName)
                {
                    DrawText("GAME OVER", screenWidth / 2 - 150, screenHeight / 2 - 60, 50, WHITE);
                    DrawText("Enter your name: ", screenWidth / 2 - 120, screenHeight / 2, 20, YELLOW);
                    DrawText(playerName, screenWidth / 2 + 70, screenHeight / 2, 20, WHITE);
                }
                else if (doramanShowingHighScores)
                {
                    DrawDoraManHighScores(highScores, screenWidth);
                    DrawText("Press R to restart", screenWidth / 2 - 100, screenHeight / 2 + 60, 20, WHITE);
                }
            }
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


    /*
     * KEEPING YOUR EXACT DORACAKE CLEANUP
     */
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