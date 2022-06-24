#include "gameSelector.hpp"
#include "game.hpp"

using namespace myMath;
using namespace collision;

using namespace GameSounds;
using namespace GameTextures;

void LevelSelect::InfoBoxManager(int _levelIndex)
{
    if(ShowInfoBox)
    {
        for(int i = 0; i < 12; i++)
            UIelements[i]->isActive = true;

        for(int i = 12; i < 14; i++)
            UIelements[i]->isActive = false;
    }
    else
    {
        LevelSelected = _levelIndex;
        CheckLevelToSetPos();
        for(int i = 0; i < 12; i++)
            UIelements[i]->isActive = false;

        for(int i = 12; i < 14; i++)
            UIelements[i]->isActive = true; 
    }

    ShowInfoBox = !ShowInfoBox;
}

void LevelSelect::CheckIfDisplayInfoBox()
{
    if(ShowInfoBox == true) 
    {
        DrawTexture(InfoBox, (float)GetScreenWidth()/2-325, (float)GetScreenHeight()/2-452, WHITE);
        DrawText(LevelSelectedNumber[LevelSelected].c_str(), (float)GetScreenWidth()/2-120, (float)GetScreenHeight()/2-400, 60, WHITE);
        DrawText(LevelSelectedName[LevelSelected].c_str(), LevelTextPosition.x, LevelTextPosition.y, 60, WHITE);
        DrawText("Do you want to play this level ?", (float)GetScreenWidth()/2-280, (float)GetScreenHeight()/2+220, 35, WHITE);
    }
}

void LevelSelect::CheckLevelToSetPos()
{
    if(LevelSelected == 0) LevelTextPosition = {GetScreenWidth()/2-230, GetScreenHeight()/2-330};
    if(LevelSelected == 1) LevelTextPosition = {GetScreenWidth()/2-234, GetScreenHeight()/2-330};
    if(LevelSelected == 2) LevelTextPosition = {GetScreenWidth()/2-200, GetScreenHeight()/2-330};
    if(LevelSelected == 3) LevelTextPosition = {GetScreenWidth()/2-315, GetScreenHeight()/2-330};
    if(LevelSelected == 4) LevelTextPosition = {GetScreenWidth()/2-110, GetScreenHeight()/2-330};
    if(LevelSelected == 5) LevelTextPosition = {GetScreenWidth()/2-250, GetScreenHeight()/2-330};
    if(LevelSelected == 6) LevelTextPosition = {GetScreenWidth()/2-200, GetScreenHeight()/2-330};
    if(LevelSelected == 7) LevelTextPosition = {GetScreenWidth()/2-285, GetScreenHeight()/2-330};
    if(LevelSelected == 8) LevelTextPosition = {GetScreenWidth()/2-220, GetScreenHeight()/2-330}; 
    if(LevelSelected == 9) LevelTextPosition = {GetScreenWidth()/2-220, GetScreenHeight()/2-330};
    if(LevelSelected == 10) LevelTextPosition = {GetScreenWidth()/2-175, GetScreenHeight()/2-330};
    if(LevelSelected == 11) LevelTextPosition = {GetScreenWidth()/2-175, GetScreenHeight()/2-330};
}

void SetTextForLevelSelected(char LevelSelectedNumber[1000], char LevelSelectedName[1000])
{
    DrawText(LevelSelectedNumber, (float)GetScreenWidth()/2-120, (float)GetScreenHeight()/2-400, 60, WHITE);
    DrawText(LevelSelectedName, (float)GetScreenWidth()/2-265, (float)GetScreenHeight()/2-320, 60, WHITE);
}

void LevelSelect::InfoBoxButtons()
{
    UIelements.push_back(new Button{(collision::Box){(float)GetScreenWidth()/2-225, (float)GetScreenHeight()/2+280, 200, 125}, 
    [](Button* self)
    {
        Scene::ChangeScene(new Game(((LevelSelect*)self->mUserPtr)->levelToLoad));
    }, 
    Sound(ClickSound), Color{0, 0, 0, 0},
    Sprite({0, 0}, YesTexture, {1, 3}, {0, 0}), this, Sprite({0, 1}, YesTexture, {1, 3}, {0, 0}), 
    Sprite({0, 2}, YesTexture, {1, 3}, {0, 0}), false, false});

    UIelements.push_back(new Button(collision::Box((float)GetScreenWidth()/2+25, (float)GetScreenHeight()/2+280, 200, 125),
    [](Button* self)
    {
        ((LevelSelect*)self->mUserPtr)->InfoBoxManager(0);
    }, 
    Sound(ClickSound), Color{0, 0, 0, 0},
    Sprite({0, 0}, NoTexture, {1, 3}, {0, 0}), this, Sprite({0, 1}, NoTexture, {1, 3}, {0, 0}), 
    Sprite({0, 2}, NoTexture, {1, 3}, {0, 0}), false, false));
}

void LevelSelect::LevelMenu()
{
    UIelements.push_back(new Button{(collision::Box){837, 247, 30, 50},
    [](Button* self)
    {   
        ((LevelSelect*)self->mUserPtr)->InfoBoxManager(0);
        ((LevelSelect*)self->mUserPtr)->LoadLevelData("save/map3.bin");
    }, Sound(ClickSound), Color{255, 255, 255, 80}, "", this});

    UIelements.push_back(new Button{(collision::Box){1364, 387, 30, 50},
    [](Button* self)
    {
        ((LevelSelect*)self->mUserPtr)->InfoBoxManager(1);
        ((LevelSelect*)self->mUserPtr)->LoadLevelData("save/map1.bin");
    }, Sound(ClickSound), Color{255, 255, 255, 80}, "", this});

    UIelements.push_back(new Button{(collision::Box){1624, 413, 30, 50},
    [](Button* self)
    {
        ((LevelSelect*)self->mUserPtr)->InfoBoxManager(2);
        ((LevelSelect*)self->mUserPtr)->LoadLevelData("save/map5.bin");
    }, Sound(ClickSound), Color{255, 255, 255, 80}, "", this});

    UIelements.push_back(new Button{(collision::Box){1456, 615, 30, 50},
    [](Button* self)
    {
        ((LevelSelect*)self->mUserPtr)->InfoBoxManager(3);
        ((LevelSelect*)self->mUserPtr)->LoadLevelData("save/map6.bin");
    }, Sound(ClickSound), Color{255, 255, 255, 80}, "", this});

    UIelements.push_back(new Button{(collision::Box){1317, 808, 30, 50},
    [](Button* self)
    {
        ((LevelSelect*)self->mUserPtr)->InfoBoxManager(4);
        ((LevelSelect*)self->mUserPtr)->LoadLevelData("save/map4.bin");
    }, Sound(ClickSound), Color{255, 255, 255, 80}, "", this});

    UIelements.push_back(new Button{(collision::Box){1116, 495, 30, 50},
    [](Button* self)
    {
        ((LevelSelect*)self->mUserPtr)->InfoBoxManager(5);
        ((LevelSelect*)self->mUserPtr)->LoadLevelData("save/map8.bin");
    }, Sound(ClickSound), Color{255, 255, 255, 80}, "", this});

    UIelements.push_back(new Button{(collision::Box){857, 602, 30, 50},
    [](Button* self)
    {
        ((LevelSelect*)self->mUserPtr)->InfoBoxManager(6);
        ((LevelSelect*)self->mUserPtr)->LoadLevelData("save/map12.bin");
    }, Sound(ClickSound), Color{255, 255, 255, 80}, "", this});

    UIelements.push_back(new Button{(collision::Box){584, 458, 30, 50},
    [](Button* self)
    {
        ((LevelSelect*)self->mUserPtr)->InfoBoxManager(7);
        ((LevelSelect*)self->mUserPtr)->LoadLevelData("save/map2.bin");
    }, Sound(ClickSound), Color{255, 255, 255, 80}, "", this});

    UIelements.push_back(new Button{(collision::Box){622, 592, 30, 50},
    [](Button* self)
    {
        ((LevelSelect*)self->mUserPtr)->InfoBoxManager(8);
        ((LevelSelect*)self->mUserPtr)->LoadLevelData("save/map11.bin");
    }, Sound(ClickSound), Color{255, 255, 255, 80}, "", this});

    UIelements.push_back(new Button{(collision::Box){423, 632, 30, 50},
    [](Button* self)
    {
        ((LevelSelect*)self->mUserPtr)->InfoBoxManager(9);
        ((LevelSelect*)self->mUserPtr)->LoadLevelData("save/map7.bin");
    }, Sound(ClickSound), Color{255, 255, 255, 80}, "", this});

    UIelements.push_back(new Button{(collision::Box){456, 719, 30, 50},
    [](Button* self)
    {
        ((LevelSelect*)self->mUserPtr)->InfoBoxManager(10);
        ((LevelSelect*)self->mUserPtr)->LoadLevelData("save/map9.bin");
    }, Sound(ClickSound), Color{255, 255, 255, 80}, "", this});

    UIelements.push_back(new Button{(collision::Box){317, 801, 30, 50},
    [](Button* self)
    {
        ((LevelSelect*)self->mUserPtr)->InfoBoxManager(11);
        ((LevelSelect*)self->mUserPtr)->LoadLevelData("save/map10.bin");
    }, Sound(ClickSound), Color{255, 255, 255, 80}, "", this});

    InfoBoxButtons();
}

void LevelSelect::Start()
{
    LevelMenu();
    {
        LevelSelectedNumber[0] = "LEVEL 3"; LevelSelectedName[0] = "DEATH VALLEY";
        LevelSelectedNumber[1] = "LEVEL 1"; LevelSelectedName[1] = "HERO'S START";
        LevelSelectedNumber[2] = "LEVEL 6"; LevelSelectedName[2] = "BLACK TRACK"; 
        LevelSelectedNumber[3] = "LEVEL 5"; LevelSelectedName[3] = "UNSAFE ASCENSION"; 
        LevelSelectedNumber[4] = "LEVEL 4"; LevelSelectedName[4] = "MIRAGE"; 
        LevelSelectedNumber[5] = "LEVEL 8"; LevelSelectedName[5] = "V FOR VICTORY"; 
        LevelSelectedNumber[6] = "LEVEL 10"; LevelSelectedName[6] = "HERO'S REST";
        LevelSelectedNumber[7] = "LEVEL 2"; LevelSelectedName[7] = "SUNFLOWER FIELD";
        LevelSelectedNumber[8] = "LEVEL 9"; LevelSelectedName[8] = "CANDY ESCAPE";
        LevelSelectedNumber[9] = "LEVEL 8"; LevelSelectedName[9]  = "CLOSE COMBAT"; 
        LevelSelectedNumber[10] = "LEVEL 11"; LevelSelectedName[10] = "DEMON KEY";
        LevelSelectedNumber[11] = "LEVEL 12"; LevelSelectedName[11] = "BRAINF*CK"; 
    }

    UIelements.push_back(new Button(collision::Box(1700, 30, 200, 80),
    [](Button* self)
    {
        Scene::ChangeScene(new Menu());
    }, 
    Sound(ClickSound), Color{0, 0, 0, 0},
    Sprite({0, 0}, QuitTexture, {1, 3}, {0, 0}), this, Sprite({0, 1}, QuitTexture, {1, 3}, {0, 0}), 
    Sprite({0, 2}, QuitTexture, {1, 3}, {0, 0}), true));
}

void LevelSelect::Update()
{
    DrawTexture(levelSelect, 0, 0, WHITE);
    CheckIfDisplayInfoBox();

    Scene::Update();
}

void LevelSelect::Render()
{
    if(ShowInfoBox)
    {
        for (int i = 0; i < gridWidth; i++)
        {
            for (int j = 0; j < gridHeight; j++)
            {
                if(levelToLoad.dataGrid[i][j] >= 2)
                {
                    Sprite(Vec2(0, 6) + levelToLoad.mBiomeOffset, tileSet, Vec2(36, 21), Vec2(15, 15), 0).Draw(Box(i * 12 + 690, j * 12 + 350, 12, 12), 0);
                }
                levelToLoad.spriteGrid[i][j].Draw(Box(i * 12 + 690, j * 12 + 350, 12, 12), 0);
            }
        }
    }
}

void LevelSelect::LoadLevelData(std::string FileName)
{
    for (int i = 0; i < 4; i++)
    {
        levelToLoad.paths[i].clear();
    }
    
    for (int i = 0; i < (int)levelToLoad.waveList.size(); i++)
    {
        levelToLoad.waveList[i].pathToFollow.clear();
        levelToLoad.waveList[i].timeBeforeNextEnemy.clear();
        levelToLoad.waveList[i].Wave.clear();
    }
    levelToLoad.waveList.clear();
    

    FILE* file = fopen(FileName.c_str(), "rb");
    if(file)
    {
        fread(&levelToLoad.dataGrid, sizeof(int[gridWidth][gridHeight]), 1, file);
        fread(&levelToLoad.mBiomeOffset, sizeof(Vec2), 1, file);
        fread(&levelToLoad.pathSize, sizeof(int), 4, file);
        
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < levelToLoad.pathSize[i]; j++)
            {
                Vec2 wayPoint;
                fread(&wayPoint, sizeof(Vec2), 1, file);
                levelToLoad.paths[i].push_back(wayPoint);
            }
        }

        fread(&levelToLoad.waveCount, sizeof(int), 1, file);
        for (int i = 0; i < levelToLoad.waveCount; i++)
        {
            levelToLoad.waveList.push_back({});
            fread(&levelToLoad.waveList[i].wavesize, sizeof(int), 1, file);
            
            for (int j = 0; j < levelToLoad.waveList[i].wavesize; j++)
            {
                levelToLoad.waveList[i].Wave.push_back({});
                levelToLoad.waveList[i].timeBeforeNextEnemy.push_back({});
                levelToLoad.waveList[i].pathToFollow.push_back({});
                fread(&levelToLoad.waveList[i].Wave[j], sizeof(EnemyType), 1, file);
                fread(&levelToLoad.waveList[i].timeBeforeNextEnemy[j], sizeof(float), 1, file);
                fread(&levelToLoad.waveList[i].pathToFollow[j], sizeof(int), 1, file);
            }
        }
        
        fclose(file);
        for (int i = 0; i < gridWidth; i++)
        {
            for (int j = 0; j < gridHeight; j++)
                levelToLoad.UpdateSprite(Vec2(i, j));
        }

        for (int i = 0; i < 4; i++)
        {
            for(Vec2& curr : levelToLoad.paths[i])
                curr += Vec2(0.5f, 0.5f);
        } 
    }
}

