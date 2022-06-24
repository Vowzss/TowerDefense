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
    GameTextures::StudioLogo = LoadTexture("assets/StudioLogo.png");

    GameTextures::tileSet = LoadTexture("assets/Map/TilesetFloor.png");
    GameTextures::enemySet = LoadTexture("assets/Map/TilesetEnemies.png");
    GameTextures::TowerSet = LoadTexture("assets/Map/TowerSet.png");
    
    GameTextures::slimeAnim = LoadTexture("assets/Enemies/Slime.png");
    GameTextures::spiritAnim = LoadTexture("assets/Enemies/Spirit.png");
    GameTextures::cyclopeAnim = LoadTexture("assets/Enemies/Cyclope.png");
    GameTextures::skeletonAnim = LoadTexture("assets/Enemies/Skeleton.png");
    GameTextures::beastAnim = LoadTexture("assets/Enemies/Beast.png");
    GameTextures::KnightAnim = LoadTexture("assets/Enemies/Knight.png");

    GameTextures::smokeFX = LoadTexture("assets/Animations/Smoke.png");
    GameTextures::circleFX = LoadTexture("assets/Animations/Circle.png");
    GameTextures::sparkFX = LoadTexture("assets/Animations/Spark.png");

    GameTextures::EditorTexture = LoadTexture("assets/Buttons/EditorButton.png");
    GameTextures::QuitTexture = LoadTexture("assets/Buttons/QuitButton.png");
    GameTextures::PlayTexture = LoadTexture("assets/Buttons/PlayButton.png");
    GameTextures::PauseTexture = LoadTexture("assets/Buttons/PauseButton.png");
    GameTextures::ResumeTexture = LoadTexture("assets/Buttons/ResumeButton.png");
    GameTextures::SoundTexture = LoadTexture("assets/Buttons/SoundButton.png");
    GameTextures::YesTexture = LoadTexture("assets/Buttons/YesButton.png");
    GameTextures::NoTexture = LoadTexture("assets/Buttons/NoButton.png");
    GameTextures::CreditsTexture = LoadTexture("assets/Buttons/CreditsButton.png");
    GameTextures::HowToPlayTexture = LoadTexture("assets/Buttons/HowToPlayButton.png");
    GameTextures::SpeedTextureX1 = LoadTexture("assets/Buttons/SpeedButtonX1.png");
    GameTextures::SpeedTextureX2 = LoadTexture("assets/Buttons/SpeedButtonX2.png");

    GameTextures::levelSelect = LoadTexture("assets/Menu/LevelSelect.png");
    GameTextures::HUD = LoadTexture("assets/Menu/HUD.png");
    GameTextures::InfoBox = LoadTexture("assets/Menu/InfoBox.png");

    GameTextures::CandyBackground = LoadTexture("assets/Backgrounds/Candy.png");
    GameTextures::DeadBackground = LoadTexture("assets/Backgrounds/Dead.png");
    GameTextures::DesertBackground = LoadTexture("assets/Backgrounds/Desert.png");
    GameTextures::JungleBackground = LoadTexture("assets/Backgrounds/Jungle.png");
    GameTextures::PlaineBackground = LoadTexture("assets/Backgrounds/Plaine.png");
    GameTextures::SnowBackground = LoadTexture("assets/Backgrounds/Snow.png");
    GameTextures::GameOverBackground = LoadTexture("assets/Backgrounds/Gameover.png");

    GameTextures::YouWonScreen = LoadTexture("assets/Others/YouWonScreen.png");
    GameTextures::GameOverScreen = LoadTexture("assets/Others/GameOverScreen.png");
    GameTextures::EditorBackground = LoadTexture("assets/Others/EditorBackground.png");
    GameTextures::HowToPlayScreen = LoadTexture("assets/Others/HowToPlayScreen.png");
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