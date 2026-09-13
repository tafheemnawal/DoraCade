#include "audio.h"
#include <raylib.h>

static Music introMusic;
static Music gameMusic;
static Sound transitionSound;

void InitGameAudio(void)
{
    InitAudioDevice();

    introMusic = LoadMusicStream("../assets/sounds/intro_music.mp3");
    introMusic.looping = 1;

    gameMusic = LoadMusicStream("../assets/sounds/transition.mp3");
    gameMusic.looping = 1;

    transitionSound = LoadSound("../assets/sounds/transition.mp3");
}

void UpdateGameAudio(void)
{
    if (IsMusicStreamPlaying(introMusic))
    {
        UpdateMusicStream(introMusic);
    }

    if (IsMusicStreamPlaying(gameMusic))
    {
        UpdateMusicStream(gameMusic);
    }
}

void PlayIntroMusic(void)
{
    StopMusicStream(gameMusic);
    StopMusicStream(introMusic);

    PlayMusicStream(introMusic);
}

void StopIntroMusic(void)
{
    StopMusicStream(introMusic);
}

void PlayGameMusic(void)
{
    StopMusicStream(introMusic);
    StopMusicStream(gameMusic);

    PlayMusicStream(gameMusic);
}

void StopGameMusic(void)
{
    StopMusicStream(gameMusic);
}

void PlayTransitionSound(void)
{
    PlaySound(transitionSound);
}

void UnloadGameAudio(void)
{
    UnloadMusicStream(introMusic);
    UnloadMusicStream(gameMusic);
    UnloadSound(transitionSound);

    CloseAudioDevice();
}