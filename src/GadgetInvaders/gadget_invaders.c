#include "gadget_invaders.h"

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

    // Random gadget type
    gadget.type = GetRandomValue(0, 4);

    // Starting position
    gadget.position.x = GetRandomValue(50, 750);
    gadget.position.y = -50;

    // Falling speed
    gadget.speed = GetRandomValue(5, 10);

    // Points based on type
    gadget.points = GetGadgetPoints(gadget.type);

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
    GetGadgetColor(gadget.type)
);
    }
}
void ResetGadget(Gadget *gadget)
{
    *gadget = CreateGadget();
}