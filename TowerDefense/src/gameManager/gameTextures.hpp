#pragma once

#include <iostream> 
#include <raylib.h>

namespace GameTextures
{
    extern Texture2D StudioLogo;

    extern Texture2D tileSet;
    extern Texture2D enemySet;
    extern Texture2D TowerSet;

    extern Texture2D slimeAnim;
    extern Texture2D spiritAnim;
    extern Texture2D cyclopeAnim;
    extern Texture2D skeletonAnim;
    extern Texture2D beastAnim;
    extern Texture2D KnightAnim;

    extern Texture2D smokeFX;
    extern Texture2D circleFX;
    extern Texture2D sparkFX;

    extern Texture2D EditorTexture;
    extern Texture2D QuitTexture;
    extern Texture2D PlayTexture;
    extern Texture2D PauseTexture;
    extern Texture2D ResumeTexture;
    extern Texture2D SoundTexture;
    extern Texture2D YesTexture;
    extern Texture2D NoTexture;
    extern Texture2D CreditsTexture;
    extern Texture2D HowToPlayTexture;
    extern Texture2D SpeedTextureX1;
    extern Texture2D SpeedTextureX2;


    extern Texture2D levelSelect;
    extern Texture2D HUD;
    extern Texture2D InfoBox;

    extern Texture2D CandyBackground;
    extern Texture2D DeadBackground;
    extern Texture2D DesertBackground;
    extern Texture2D JungleBackground;
    extern Texture2D PlaineBackground;
    extern Texture2D SnowBackground;
    extern Texture2D GameOverBackground;

    extern Texture2D YouWonScreen;
    extern Texture2D GameOverScreen;
    extern Texture2D EditorBackground;
    extern Texture2D HowToPlayScreen;
}

void InitTextures();
void UnloadAllTextures();