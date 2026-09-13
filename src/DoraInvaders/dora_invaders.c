#include "dora_invaders.h"
#include <stdlib.h>
#include <stddef.h>
static Texture2D doracakeTexture;
static Texture2D bambooCopterTexture;
static Texture2D timeMachineTexture;
static Texture2D smallLightTexture;
static Texture2D bigLightTexture;
void LoadDoraInvadersTextures()
{
    doracakeTexture = LoadTexture(
        "assets/textures/dora_invaders/doracake.png"
    );

    bambooCopterTexture = LoadTexture(
        "assets/textures/dora_invaders/bamboo_copter.png"
    );

    timeMachineTexture = LoadTexture(
        "assets/textures/dora_invaders/time_machine.png"
    );

    smallLightTexture = LoadTexture(
        "assets/textures/dora_invaders/small_light.png"
    );

    bigLightTexture = LoadTexture(
        "assets/textures/dora_invaders/big_light.png"
    );


}

static int GetGadgetPoints(GadgetType type)
{
    switch(type)
    {
        case DORACAKE:
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
        case DORACAKE:
            return ORANGE;

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
    DORACAKE,
    BIG_LIGHT
); 

    // Starting position
    gadget.position.x = GetRandomValue(250, GetScreenWidth() - 250);
    gadget.position.y = -50;

    // Falling speed
  gadget.speed = GetRandomValue(70, 120);

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
    }
}


void DrawGadget(Gadget gadget)
{
    if(!gadget.active)
        return;

    Texture2D currentTexture;

    switch(gadget.type)
    {
        case DORACAKE:
            currentTexture = doracakeTexture;
            break;

        case BAMBOO_COPTER:
            currentTexture = bambooCopterTexture;
            break;

        case TIME_MACHINE:
            currentTexture = timeMachineTexture;
            break;

        case SMALL_LIGHT:
            currentTexture = smallLightTexture;
            break;

        case BIG_LIGHT:
            currentTexture = bigLightTexture;
            break;

        default:
            currentTexture = doracakeTexture;
            break;
    }

    Rectangle source =
    {
        0,
        0,
        (float)currentTexture.width,
        (float)currentTexture.height
    };

    Rectangle destination =
    {
        gadget.position.x,
        gadget.position.y,
        50,
        50
    };

    DrawTexturePro(
        currentTexture,
        source,
        destination,
        (Vector2){25, 25},
        0.0f,
        WHITE
    );
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


        bullet->speed = 700;

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
    screenHeight - player.bounds.height - 10;

    // Movement speed
    player.speed = 500;

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


    // Create all 5 gadgets with different entry times
for(int i = 0; i < 5; i++)
{
    game->gadgets[i] = CreateGadget();

    game->gadgets[i].position.x =
        GetRandomValue(250, screenWidth - 250);

    game->gadgets[i].position.y =
        -100 - (i * 300);
}

    // Reset score
    game->score = 0;
    game->misses = 0;
    game->gameOver = false;
    game->bullet.active = false;

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

   if(game->gameOver)
{
    if(IsKeyPressed(KEY_ENTER))
    {
        InitDoraInvaders(
            game,
            screenWidth,
            GetScreenHeight()
        );
    }

    return;
}


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

    PlaySound(shootSound);
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
                game->gadgets[i].position.x,
                game->gadgets[i].position.y,
                50,
                50
            };


            Rectangle bulletRect =
            {
                game->bullet.position.x - 5,
                game->bullet.position.y,
                10,
                20
            };


            if(CheckCollisionRecs(
                bulletRect,
                gadgetRect))
            {
             game->score += game->gadgets[i].points;

            game->bullet.active = false;

            ResetGadget(
                    &game->gadgets[i]
                );
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


// Gadget reached bottom (missed)
if(game->gadgets[i].active &&
   game->gadgets[i].position.y > GetScreenHeight())
{
    game->misses++;

    if(game->misses >= 5)
    {
        game->gameOver = true;
    }

    game->gadgets[i].active = false;
}
}

// Refill empty gadget slots
for(int i = 0; i < 5; i++)
{
    if(!game->gadgets[i].active)
    {
        game->gadgets[i] = CreateGadget();

        game->gadgets[i].position.x =
            GetRandomValue(250, screenWidth - 250);

        game->gadgets[i].position.y = -100;

        break;
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
    // Glow effect
    DrawCircle(
        game.bullet.position.x,
        game.bullet.position.y + 8,
        8,
        Fade(BLUE, 0.4f)
    );

    // Main energy bullet
    DrawRectangle(
        game.bullet.position.x - 5,
        game.bullet.position.y,
        10,
        20,
        SKYBLUE
    );

    // Bright center
    DrawRectangle(
        game.bullet.position.x - 2,
        game.bullet.position.y,
        4,
        20,
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

DrawText(
    TextFormat("Lives: %d", 5 - game.misses),
    20,
    60,
    30,
    WHITE
);

if(game.gameOver)
{
    DrawText(
        "GAME OVER",
        250,
        220,
        50,
        RED
    );

    DrawText(
        TextFormat("Final Score: %d", game.score),
        250,
        280,
        30,
        WHITE
    );

    DrawText(
        "Press ENTER to Restart",
        220,
        340,
        30,
        YELLOW
    );
}
}


