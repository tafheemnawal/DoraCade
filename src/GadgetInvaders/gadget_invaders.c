#include "gadget_invaders.h"
#include <stdlib.h>


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


