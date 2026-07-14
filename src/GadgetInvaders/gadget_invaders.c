#include "gadget_invaders.h"
#include <stdlib.h>

static int GetGadgetPoints(GadgetType type)
{
    switch(type)
    {
        case ANYWHERE_DOOR:
            return 50;

        case BAMBOO_COPTER:
            return 10;

        case TIME_MACHINE:
            return 100;

        case SMALL_LIGHT:
            return 20;

        case BIG_LIGHT:
            return 40;

        default:
            return 0;
    }
}


// Helper function: temporary colors
// Later replaced with PNG textures
static Color GetGadgetColor(GadgetType type)
{
    switch(type)
    {
        case ANYWHERE_DOOR:
            return BLUE;

        case BAMBOO_COPTER:
            return GREEN;

        case TIME_MACHINE:
            return PURPLE;

        case SMALL_LIGHT:
            return YELLOW;

        case BIG_LIGHT:
            return RED;

        default:
            return WHITE;
    }
}
// Create a new gadget
Gadget CreateGadget()
{
    Gadget gadget;

    // Random gadget type (5 types)
    gadget.type = GetRandomValue(0, 4);

    // Starting position
    gadget.position.x = GetRandomValue(50, 750); 
    gadget.position.y = -50;

    // High falling speed
    gadget.speed = GetRandomValue(5, 10);

    // Assign points
    switch(gadget.type)
    {
        case ANYWHERE_DOOR:
            gadget.points = 50;
            break;

        case BAMBOO_COPTER:
            gadget.points = 10;
            break;

        case TIME_MACHINE:
            gadget.points = 100;
            break;

        case SMALL_LIGHT:
            gadget.points = 20;
            break;

        case BIG_LIGHT:
            gadget.points = 40;
            break;
    }


    gadget.active = true;

    return gadget;
}
void UpdateGadget(Gadget *gadget)
{
    if(gadget->active)
    {
        gadget->position.y += gadget->speed;


        // If gadget reaches bottom
        if(gadget->position.y > GetScreenHeight())
        {
            gadget->active = false;
        }
    }
}

void DrawGadget(Gadget gadget)
{
    if(gadget.active)
    {
        DrawCircle(
            gadget.position.x,
            gadget.position.y,
            20,
            RED
        );
    }
}
void ResetGadget(Gadget *gadget)
{
    gadget->type = GetRandomValue(0,4);

    gadget->position.x = GetRandomValue(50,750);
    gadget->position.y = -50;

    gadget->speed = GetRandomValue(5,10);

    gadget->active = true;
}
