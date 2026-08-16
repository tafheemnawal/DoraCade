#ifndef DORA_INVADERS_H
#define DORA_INVADERS_H
#include "raylib.h"

//gadget type
typedef enum
{
    ANYWHERE_DOOR,
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



void UpdateGadget(Gadget *gadget);


void DrawGadget(Gadget gadget);


void ResetGadget(Gadget *gadget);
typedef struct
{
    Rectangle bounds;  // x, y, width, height
    float speed;       // Pixels per second

} InvaderPlayer;


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

#endif