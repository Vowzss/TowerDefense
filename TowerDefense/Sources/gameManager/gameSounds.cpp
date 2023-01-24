#include "gameSounds.hpp"

Sound GameSounds::EventSound;
Sound GameSounds::QuitSound;

Sound GameSounds::CastleAttackedSound;
Sound GameSounds::DeadSound;

Sound GameSounds::FlameShotSound;
Sound GameSounds::CryoShotSound;
Sound GameSounds::BombShotSound;

Sound GameSounds::GameOverSound;
Sound GameSounds::GameWinSound;

Sound GameSounds::TouretBuyingSound;
Sound GameSounds::TouretPlacedSound;
Sound GameSounds::TouretBrokenSound;

Sound GameSounds::AmbiantSound;

Sound GameSounds::ClickSound;

void InitSounds()
{
    GameSounds::EventSound = LoadSound("Resources/Sounds/MenuSounds/EventSound.wav");
    GameSounds::QuitSound = LoadSound("Resources/Sounds/MenuSounds/Quit.wav");

    GameSounds::CastleAttackedSound = LoadSound("Resources/Sounds/GameSounds/CastleAttacked.wav");
    GameSounds::DeadSound = LoadSound("Resources/Sounds/GameSounds/DeadSound.wav");

    GameSounds::FlameShotSound = LoadSound("Resources/Sounds/GameSounds/FlameShot.wav");
    GameSounds::CryoShotSound = LoadSound("Resources/Sounds/GameSounds/CryoShot.wav");
    GameSounds::BombShotSound = LoadSound("Resources/Sounds/GameSounds/BombShot.wav");

    GameSounds::GameOverSound = LoadSound("Resources/Sounds/GameSounds/GameOver.wav");
    GameSounds::GameWinSound = LoadSound("Resources/Sounds/GameSounds/SuccessWave.wav");

    GameSounds::TouretBuyingSound = LoadSound("Resources/Sounds/GameSounds/TouretBuying.wav"); 
    GameSounds::TouretPlacedSound = LoadSound("Resources/Sounds/GameSounds/TouretPlaced.wav"); 
    GameSounds::TouretBrokenSound = LoadSound("Resources/Sounds/GameSounds/TouretBroken.wav");

    GameSounds::AmbiantSound = LoadSound("Resources/Sounds/AmbiantSound.wav");

    GameSounds::ClickSound = LoadSound("Resources/Sounds/ClickSound.wav");

    SetSoundsVolume();
}

void UnloadAllSounds()
{
    UnloadSound(GameSounds::EventSound);
    UnloadSound(GameSounds::QuitSound);

    UnloadSound(GameSounds::CastleAttackedSound);
    UnloadSound(GameSounds::DeadSound);

    UnloadSound(GameSounds::FlameShotSound);
    UnloadSound(GameSounds::CryoShotSound);
    UnloadSound(GameSounds::BombShotSound);

    UnloadSound(GameSounds::GameOverSound);
    UnloadSound(GameSounds::GameWinSound);

    UnloadSound(GameSounds::TouretBuyingSound); 
    UnloadSound(GameSounds::TouretPlacedSound); 
    UnloadSound(GameSounds::TouretBrokenSound);

    UnloadSound(GameSounds::AmbiantSound);

    UnloadSound(GameSounds::ClickSound);
}

void SetSoundsVolume()
{
    SetSoundVolume(GameSounds::EventSound, 0.05f);
    SetSoundVolume(GameSounds::ClickSound, 0.05f);
    SetSoundVolume(GameSounds::QuitSound, 0.05f);

    SetSoundVolume(GameSounds::CastleAttackedSound, 1.f);
    SetSoundVolume(GameSounds::DeadSound, 0.05f);

    SetSoundVolume(GameSounds::FlameShotSound, 0.05f);
    SetSoundVolume(GameSounds::CryoShotSound, 0.05f);
    SetSoundVolume(GameSounds::BombShotSound, 0.05f);

    SetSoundVolume(GameSounds::GameOverSound, 0.05f);
    SetSoundVolume(GameSounds::GameWinSound, 0.05f);

    SetSoundVolume(GameSounds::TouretBuyingSound, 0.05f);
    SetSoundVolume(GameSounds::TouretPlacedSound, 0.05f);
    SetSoundVolume(GameSounds::TouretBrokenSound, 0.05f);

    SetSoundVolume(GameSounds::AmbiantSound, 0.1f);

    //SetSoundVolume(GameSounds::ClickSound, 0.5f);
}