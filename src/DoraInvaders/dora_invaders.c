#include "dora_invaders.h"
#include <stdlib.h>
#include <stddef.h>

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


    gadget.type = (GadgetType)GetRandomValue(
    ANYWHERE_DOOR,
    BIG_LIGHT
);

    // Starting position
    gadget.position.x = GetRandomValue(50, 750);
    gadget.position.y = -50;

    // Falling speed
   gadget.speed = GetRandomValue(80, 150);

    // Points based on type
    gadget.points = GetGadgetPoints(gadget.type);

    gadget.active = true;

    return gadget;
}
void UpdateGadget(
    Gadget *gadget,
    float deltaTime
)
{
    if(gadget == NULL)
        return;


    if(gadget->active)
    {
        // Move gadget downward using time-based movement
        gadget->position.y += gadget->speed * deltaTime;


        // If gadget reaches bottom of screen
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
    if(gadget == NULL)
        return;

    *gadget = CreateGadget();
}
void UpdateInvaderPlayer(InvaderPlayer *player, int screenWidth, float deltaTime)
{
    if (player == NULL)
        return;

    if (IsKeyDown(KEY_LEFT))
        player->bounds.x -= player->speed * deltaTime;

    if (IsKeyDown(KEY_RIGHT))
        player->bounds.x += player->speed * deltaTime;

    // Clamp inside the screen
    if (player->bounds.x < 0)
        player->bounds.x = 0;

    if (player->bounds.x + player->bounds.width > screenWidth)
        player->bounds.x = screenWidth - player->bounds.width;
}
void DrawInvaderPlayer(
    InvaderPlayer player
)
{
    DrawRectangleRec(
        player.bounds,
        SKYBLUE
    );
}

// Bullet fired by player
void FireInvaderBullet(
    InvaderBullet *bullet,
    InvaderPlayer player
)
{
    if(bullet == NULL)
        return;


    // Fire only if no bullet exists
    if(!bullet->active)
    {
        bullet->position.x =
            player.bounds.x +
            player.bounds.width / 2;

        bullet->position.y =
            player.bounds.y;


        bullet->speed = 500;

        bullet->active = true;
    }
}

// Create player at bottom-center of screen
InvaderPlayer CreateInvaderPlayer(
    int screenWidth,
    int screenHeight
)
{
    InvaderPlayer player;

    // Player size
    player.bounds.width = 60;
    player.bounds.height = 30;

    // Start position
    player.bounds.x =
        (screenWidth - player.bounds.width) / 2;

    player.bounds.y =
        screenHeight - player.bounds.height - 20;

    // Movement speed
    player.speed = 300;

    return player;
}
// Initialize Dora Invaders game
void InitDoraInvaders(
    DoraInvadersGame *game,
    int screenWidth,
    int screenHeight
)
{
    if(game == NULL)
        return;


    // Create player
    game->player =
        CreateInvaderPlayer(
            screenWidth,
            screenHeight
        );


    // Create gadgets
    for(int i = 0; i < 5; i++)
    {
        game->gadgets[i] =
            CreateGadget();
    }


    // Reset score
    game->score = 0;
}
// Update complete Dora Invaders game
void UpdateDoraInvaders(
    DoraInvadersGame *game,
    int screenWidth,
    float deltaTime
)
{
    if(game == NULL)
        return;


    // Update player
    UpdateInvaderPlayer(
        &game->player,
        screenWidth,
        deltaTime
    );

    // Fire bullet
if(IsKeyPressed(KEY_SPACE))
{
    FireInvaderBullet(
        &game->bullet,
        game->player
    );
}

// Update bullet
if(game->bullet.active)
{
    game->bullet.position.y -=
        game->bullet.speed * deltaTime;


    // Remove bullet when it leaves screen
    if(game->bullet.position.y < 0)
    {
        game->bullet.active = false;
    }
}

 // Check bullet collision with gadgets
if(game->bullet.active)
{
    for(int i = 0; i < 5; i++)
    {
        if(game->gadgets[i].active)
        {
            Rectangle gadgetRect =
            {
                game->gadgets[i].position.x - 20,
                game->gadgets[i].position.y - 20,
                40,
                40
            };


            Rectangle bulletRect =
            {
                game->bullet.position.x - 3,
                game->bullet.position.y,
                6,
                15
            };


            if(CheckCollisionRecs(
                bulletRect,
                gadgetRect))
            {
                game->gadgets[i].active = false;

                game->score +=
                    game->gadgets[i].points;

                game->bullet.active = false;
            }
        }
    }
}


    // Update gadgets
   for(int i = 0; i < 5; i++)
{
    UpdateGadget(
        &game->gadgets[i],
        deltaTime
    );
      if(!game->gadgets[i].active)
    {
        ResetGadget(
            &game->gadgets[i]
        );
    }
}
}


// Draw complete Dora Invaders game
void DrawDoraInvaders(
    DoraInvadersGame game
)
{
    // Draw player
    DrawInvaderPlayer(
        game.player
    );

// Draw bullet
if(game.bullet.active)
{
    DrawRectangle(
        game.bullet.position.x - 3,
        game.bullet.position.y,
        6,
        15,
        WHITE
    );
}


    // Draw gadgets
    for(int i = 0; i < 5; i++)
    {
        DrawGadget(
            game.gadgets[i]
        );
    }

// Draw score
DrawText(
    TextFormat("Score: %d", game.score),
    20,
    20,
    30,
    WHITE
);

}