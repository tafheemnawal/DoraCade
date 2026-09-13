#ifndef DORA_INVADERS_H
#define DORA_INVADERS_H
#include "raylib.h"

extern Sound shootSound;

//gadget type
typedef enum
{
    DORACAKE,
    BAMBOO_COPTER,
    TIME_MACHINE,
    SMALL_LIGHT,
    BIG_LIGHT

} GadgetType;
typedef struct
{
    GadgetType type;   // Which gadget (door, copter, etc.)

    Vector2 position;  // x and y position on screen

    float speed;       // Falling speed

    int points;        // Score when shot

    bool active;       // Is this gadget currently falling?

} Gadget;

Gadget CreateGadget();



void UpdateGadget(
    Gadget *gadget,
    float deltaTime
);


void DrawGadget(Gadget gadget);


void ResetGadget(Gadget *gadget);


typedef struct
{
    Rectangle bounds;  // x, y, width, height
    float speed;       // Pixels per second

} InvaderPlayer;

// Bullet fired by player
typedef struct
{
    Vector2 position;

    float speed;

    bool active;

} InvaderBullet;



// Main Dora Invaders game data
// Main Dora Invaders game data
typedef struct
{
    InvaderPlayer player;

    InvaderBullet bullet;

    Gadget gadgets[5];

    int score;

    int misses;

    bool gameOver;
    float spawnTimer;

} DoraInvadersGame;

// Player functions
InvaderPlayer CreateInvaderPlayer(
    int screenWidth,
    int screenHeight
);

void UpdateInvaderPlayer(
    InvaderPlayer *player,
    int screenWidth,
    float deltaTime
);

void DrawInvaderPlayer(
    InvaderPlayer player
);

// Bullet functions
void FireInvaderBullet(
    InvaderBullet *bullet,
    InvaderPlayer player
);

// Initialize the complete Dora Invaders game
void InitDoraInvaders(
    DoraInvadersGame *game,
    int screenWidth,
    int screenHeight
);
// Update complete Dora Invaders game
void UpdateDoraInvaders(
    DoraInvadersGame *game,
    int screenWidth,
    float deltaTime
);
// Draw complete Dora Invaders game
void DrawDoraInvaders(
    DoraInvadersGame game
);

void LoadDoraInvadersTextures();

#endif