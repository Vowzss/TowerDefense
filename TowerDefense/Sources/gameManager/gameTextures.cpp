#include "gameTextures.hpp"

Texture2D GameTextures::StudioLogo;

Texture2D GameTextures::tileSet;
Texture2D GameTextures::enemySet;
Texture2D GameTextures::TowerSet;

Texture2D GameTextures::slimeAnim;
Texture2D GameTextures::spiritAnim;
Texture2D GameTextures::cyclopeAnim;
Texture2D GameTextures::skeletonAnim;
Texture2D GameTextures::beastAnim;
Texture2D GameTextures::KnightAnim;

Texture2D GameTextures::smokeFX;
Texture2D GameTextures::sparkFX;
Texture2D GameTextures::circleFX;

Texture2D GameTextures::EditorTexture;
Texture2D GameTextures::QuitTexture;
Texture2D GameTextures::PlayTexture;
Texture2D GameTextures::PauseTexture;
Texture2D GameTextures::ResumeTexture;
Texture2D GameTextures::SoundTexture;
Texture2D GameTextures::YesTexture;
Texture2D GameTextures::NoTexture;
Texture2D GameTextures::CreditsTexture;
Texture2D GameTextures::HowToPlayTexture;
Texture2D GameTextures::SpeedTextureX1;
Texture2D GameTextures::SpeedTextureX2;

Texture2D GameTextures::levelSelect;
Texture2D GameTextures::HUD;
Texture2D GameTextures::InfoBox;

Texture2D GameTextures::CandyBackground;
Texture2D GameTextures::DeadBackground;
Texture2D GameTextures::DesertBackground;
Texture2D GameTextures::JungleBackground;
Texture2D GameTextures::PlaineBackground;
Texture2D GameTextures::SnowBackground;
Texture2D GameTextures::GameOverBackground;

Texture2D GameTextures::YouWonScreen;
Texture2D GameTextures::GameOverScreen;
Texture2D GameTextures::EditorBackground;
Texture2D GameTextures::HowToPlayScreen;

void InitTextures()
{
    GameTextures::StudioLogo = LoadTexture("Resources/StudioLogo.png");

    GameTextures::tileSet = LoadTexture("Resources/Map/TilesetFloor.png");
    GameTextures::enemySet = LoadTexture("Resources/Map/TilesetEnemies.png");
    GameTextures::TowerSet = LoadTexture("Resources/Map/TowerSet.png");
    
    GameTextures::slimeAnim = LoadTexture("Resources/Enemies/Slime.png");
    GameTextures::spiritAnim = LoadTexture("Resources/Enemies/Spirit.png");
    GameTextures::cyclopeAnim = LoadTexture("Resources/Enemies/Cyclope.png");
    GameTextures::skeletonAnim = LoadTexture("Resources/Enemies/Skeleton.png");
    GameTextures::beastAnim = LoadTexture("Resources/Enemies/Beast.png");
    GameTextures::KnightAnim = LoadTexture("Resources/Enemies/Knight.png");

    GameTextures::smokeFX = LoadTexture("Resources/Animations/Smoke.png");
    GameTextures::circleFX = LoadTexture("Resources/Animations/Circle.png");
    GameTextures::sparkFX = LoadTexture("Resources/Animations/Spark.png");

    GameTextures::EditorTexture = LoadTexture("Resources/Buttons/EditorButton.png");
    GameTextures::QuitTexture = LoadTexture("Resources/Buttons/QuitButton.png");
    GameTextures::PlayTexture = LoadTexture("Resources/Buttons/PlayButton.png");
    GameTextures::PauseTexture = LoadTexture("Resources/Buttons/PauseButton.png");
    GameTextures::ResumeTexture = LoadTexture("Resources/Buttons/ResumeButton.png");
    GameTextures::SoundTexture = LoadTexture("Resources/Buttons/SoundButton.png");
    GameTextures::YesTexture = LoadTexture("Resources/Buttons/YesButton.png");
    GameTextures::NoTexture = LoadTexture("Resources/Buttons/NoButton.png");
    GameTextures::CreditsTexture = LoadTexture("Resources/Buttons/CreditsButton.png");
    GameTextures::HowToPlayTexture = LoadTexture("Resources/Buttons/HowToPlayButton.png");
    GameTextures::SpeedTextureX1 = LoadTexture("Resources/Buttons/SpeedButtonX1.png");
    GameTextures::SpeedTextureX2 = LoadTexture("Resources/Buttons/SpeedButtonX2.png");

    GameTextures::levelSelect = LoadTexture("Resources/Menu/LevelSelect.png");
    GameTextures::HUD = LoadTexture("Resources/Menu/HUD.png");
    GameTextures::InfoBox = LoadTexture("Resources/Menu/InfoBox.png");

    GameTextures::CandyBackground = LoadTexture("Resources/Backgrounds/Candy.png");
    GameTextures::DeadBackground = LoadTexture("Resources/Backgrounds/Dead.png");
    GameTextures::DesertBackground = LoadTexture("Resources/Backgrounds/Desert.png");
    GameTextures::JungleBackground = LoadTexture("Resources/Backgrounds/Jungle.png");
    GameTextures::PlaineBackground = LoadTexture("Resources/Backgrounds/Plaine.png");
    GameTextures::SnowBackground = LoadTexture("Resources/Backgrounds/Snow.png");
    GameTextures::GameOverBackground = LoadTexture("Resources/Backgrounds/Gameover.png");

    GameTextures::YouWonScreen = LoadTexture("Resources/Others/YouWonScreen.png");
    GameTextures::GameOverScreen = LoadTexture("Resources/Others/GameOverScreen.png");
    GameTextures::EditorBackground = LoadTexture("Resources/Others/EditorBackground.png");
    GameTextures::HowToPlayScreen = LoadTexture("Resources/Others/HowToPlayScreen.png");
}

void UnloadAllTextures()
{
    UnloadTexture(GameTextures::tileSet);
    UnloadTexture(GameTextures::enemySet);
    UnloadTexture(GameTextures::TowerSet);
    
    UnloadTexture(GameTextures::slimeAnim);
    UnloadTexture(GameTextures::spiritAnim);
    UnloadTexture(GameTextures::cyclopeAnim);
    UnloadTexture(GameTextures::skeletonAnim);
    UnloadTexture(GameTextures::beastAnim);

    UnloadTexture(GameTextures::smokeFX);

    UnloadTexture(GameTextures::EditorTexture);
    UnloadTexture(GameTextures::QuitTexture);
    UnloadTexture(GameTextures::PlayTexture);
    UnloadTexture(GameTextures::PauseTexture);
    UnloadTexture(GameTextures::ResumeTexture);
    UnloadTexture(GameTextures::SoundTexture);
    UnloadTexture(GameTextures::SpeedTextureX1);
    UnloadTexture(GameTextures::SpeedTextureX2);

    UnloadTexture(GameTextures::levelSelect);
    UnloadTexture(GameTextures::HUD);
    UnloadTexture(GameTextures::InfoBox);

    UnloadTexture(GameTextures::CandyBackground);
    UnloadTexture(GameTextures::DeadBackground);
    UnloadTexture(GameTextures::DesertBackground);
    UnloadTexture(GameTextures::JungleBackground);
    UnloadTexture(GameTextures::PlaineBackground);
    UnloadTexture(GameTextures::SnowBackground);
    UnloadTexture(GameTextures::GameOverBackground);

    UnloadTexture(GameTextures::YouWonScreen);
    UnloadTexture(GameTextures::GameOverScreen);
    UnloadTexture(GameTextures::EditorBackground);
    UnloadTexture(GameTextures::HowToPlayScreen);
}