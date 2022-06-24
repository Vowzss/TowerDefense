#pragma once

#include <raylib.h>
#include <iostream>

namespace GameSounds
{
    extern Sound EventSound;
    extern Sound ClickSound;
    extern Sound QuitSound;

    extern Sound CastleAttackedSound;
    extern Sound DeadSound;

    extern Sound FlameShotSound;
    extern Sound CryoShotSound;
    extern Sound BombShotSound;

    extern Sound GameOverSound;
    extern Sound GameWinSound;

    extern Sound TouretBuyingSound;
    extern Sound TouretPlacedSound;
    extern Sound TouretBrokenSound;

    extern Sound AmbiantSound;

    extern Sound ClickSound;
}

void InitSounds();
void UnloadAllSounds();
void SetSoundsVolume();