#include "gameCredits.hpp"

using namespace collision;
using namespace GameSounds;
using namespace GameTextures;

void GameCredits::Start()
{
    switch(rand() % 5)
    {
        case(0) : mBackground = SnowBackground;
        break;

        case(1) : mBackground = DesertBackground;
        break;
        
        case(2) : mBackground = DeadBackground;
        break;

        case(3) : mBackground = PlaineBackground;
        break;

        case(4) : mBackground = JungleBackground;
        break;
        
        case(5) : mBackground = CandyBackground;
        break;       
    }

    mTextToDisplay[0] = "An Appenzeller Production";

    mTextToDisplay[5] = "Powered by RayLib.";

    mTextToDisplay[6] = "Graphics are free of rights.";

    UIelements.push_back(new Button(collision::Box(810, 860, 280, 110),
    [](Button* self)
    {
        Scene::ChangeScene(new Menu());
    }, 
    Sound(ClickSound), Color{0, 0, 0, 0},
    Sprite({0, 0}, QuitTexture, {1, 3}, {0, 0}), this, Sprite({0, 1}, QuitTexture, {1, 3}, {0, 0}), 
    Sprite({0, 2}, QuitTexture, {1, 3}, {0, 0}), true));

    
}

void GameCredits::Update()
{
    Scene::Update();
}

void GameCredits::Render()
{
    DrawTexture(mBackground, 0, 0, WHITE);
    DrawTexture(InfoBox, (float)GetScreenWidth()/2-325, (float)GetScreenHeight()/2-452, WHITE);

    DrawText(mTextToDisplay[0].c_str(), PosX+30, PosY, 35, WHITE);
    DrawText(mTextToDisplay[1].c_str(), PosX+240, PosY+55, 35, WHITE);
    DrawText(mTextToDisplay[2].c_str(), PosX+49, PosY+120, 55, WHITE);
    DrawText(mTextToDisplay[3].c_str(), PosX+99, PosY+175, 55, WHITE);
    DrawText(mTextToDisplay[4].c_str(), PosX-1, PosY+230, 55, WHITE);
    DrawText(mTextToDisplay[5].c_str(), PosX+14, PosY+310, 55, WHITE);

    DrawText(mTextToDisplay[6].c_str(), PosX+99, PosY+400, 25, WHITE);
    DrawText(mTextToDisplay[7].c_str(), PosX+29, PosY+440, 25, WHITE);

    DrawTexture(StudioLogo, PosX+120, PosY+465, WHITE);
}