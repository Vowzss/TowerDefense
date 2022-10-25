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
    GameSounds::EventSound = LoadSound("Assets/Sounds/MenuSounds/EventSound.wav");
    GameSounds::QuitSound = LoadSound("Assets/Sounds/MenuSounds/Quit.wav");

    GameSounds::CastleAttackedSound = LoadSound("assets/Sounds/GameSounds/CastleAttacked.wav");
    GameSounds::DeadSound = LoadSound("assets/Sounds/GameSounds/DeadSound.wav");

    GameSounds::FlameShotSound = LoadSound("assets/Sounds/GameSounds/FlameShot.wav");
    GameSounds::CryoShotSound = LoadSound("assets/Sounds/GameSounds/CryoShot.wav");
    GameSounds::BombShotSound = LoadSound("assets/Sounds/GameSounds/BombShot.wav");

    GameSounds::GameOverSound = LoadSound("assets/Sounds/GameSounds/GameOver.wav");
    GameSounds::GameWinSound = LoadSound("assets/Sounds/GameSounds/SuccessWave.wav");

    GameSounds::TouretBuyingSound = LoadSound("assets/Sounds/GameSounds/TouretBuying.wav"); 
    GameSounds::TouretPlacedSound = LoadSound("assets/Sounds/GameSounds/TouretPlaced.wav"); 
    GameSounds::TouretBrokenSound = LoadSound("assets/Sounds/GameSounds/TouretBroken.wav");

    GameSounds::AmbiantSound = LoadSound("assets/Sounds/AmbiantSound.wav");

    GameSounds::ClickSound = LoadSound("assets/Sounds/ClickSound.wav");

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