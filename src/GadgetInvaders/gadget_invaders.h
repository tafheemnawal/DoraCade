#ifndef GADGET_INVADERS_H
#define GADGET_INVADERS_H
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
// Create a new gadget
Gadget CreateGadget();


// Update falling movement
void UpdateGadget(Gadget *gadget);


// Draw gadget on screen
void DrawGadget(Gadget gadget);


// Reset gadget after missing/hitting
void ResetGadget(Gadget *gadget);
 

#endif