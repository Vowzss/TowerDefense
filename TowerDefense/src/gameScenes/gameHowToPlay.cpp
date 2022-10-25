#include <string.h>

#include "gameHowToPlay.hpp"
#include "../gameManager/gameSounds.hpp"
#include "../gameManager/gameTextures.hpp"

#include "menu.hpp"

using namespace GameSounds;
using namespace GameTextures;

using namespace myMath;

void HowToPlay::Start()
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

    mTextToDisplay[0] = "How does it work?";
    mTextToDisplay[1] = "Many enemies will spawn from";
    mTextToDisplay[2] = "different locations depending on";
    mTextToDisplay[3] = "the map you are playing on.";

    mTextToDisplay[4] = "There are 6 types of enemies:";
    mTextToDisplay[5] = "You will have to kill them before";
    mTextToDisplay[6] = "they reach the other border.";

    mTextToDisplay[7] = "There are 4 types of towers:";

    mTextToDisplay[9] = "12 Differents Levels and ";
    mTextToDisplay[10] = "6 Different Biomes Available.";

    mTextToDisplay[11] = "You can also create your own map!";

    UIelements.push_back(new Button(collision::Box(810, 860, 280, 110),
    [](Button* self)
    {
        Scene::ChangeScene(new Menu());
    }, 
    Sound(ClickSound), Color{0, 0, 0, 0},
    Sprite({0, 0}, QuitTexture, {1, 3}, {0, 0}), this, Sprite({0, 1}, QuitTexture, {1, 3}, {0, 0}), 
    Sprite({0, 2}, QuitTexture, {1, 3}, {0, 0}), true));
    
}


void HowToPlay::Update()
{
    
    Scene::Update();
    
}

void HowToPlay::Render()
{
    DrawTexture(mBackground, 0, 0, WHITE);
    DrawTexture(HowToPlayScreen, (float)GetScreenWidth()/2-325, (float)GetScreenHeight()/2-452, WHITE);

    DrawText(mTextToDisplay[0].c_str(), PosX+30, PosY-20, 55, WHITE);

    DrawText(mTextToDisplay[1].c_str(), PosX-15, PosY+50, 40, WHITE);
    DrawText(mTextToDisplay[2].c_str(), PosX-10, PosY+90, 35, WHITE);
    DrawText(mTextToDisplay[3].c_str(), PosX+30, PosY+130, 35, WHITE);

    DrawText(mTextToDisplay[4].c_str(), PosX-40, PosY+190, 40, WHITE);
    DrawText(mTextToDisplay[5].c_str(), PosX-10, PosY+310, 35, WHITE);
    DrawText(mTextToDisplay[6].c_str(), PosX+15, PosY+350, 35, WHITE);

    DrawText(mTextToDisplay[7].c_str(), PosX-35, PosY+410, 40, WHITE);
    DrawText(mTextToDisplay[8].c_str(), PosX+14, PosY+450, 35, WHITE);

    DrawText(mTextToDisplay[9].c_str(), PosX+55, PosY+550, 35, WHITE);
    DrawText(mTextToDisplay[10].c_str(), PosX+35, PosY+590, 35, WHITE);

    DrawText(mTextToDisplay[11].c_str(), PosX-28, PosY+650, 35, WHITE);
}