#include "game.hpp"
#include "gameOver.hpp"

using namespace GameTextures;
using namespace GameSounds;

using namespace collision;
using namespace myMath;
using namespace TowerData;


float Game::sTimeScale = 1.f;
float Game::sBaseVolume = 0.8f;
float Game::sActualVolume = 0.8f;
EnemyWave* Game::sWave = nullptr;
Grid Game::sGridData = {};

Game::~Game()
{
    if(!mTowerlist.empty())
    {
        for(Tower* curr : mTowerlist)
            delete curr;

        mTowerlist.clear();
    }

    sPath.clear();

    if(!UIelements.empty())
    {
        for(UIElement* curr : UIelements)
            delete curr;
            
        UIelements.clear();
    }

    delete sPlayer;
    delete sWave;
}

void Game::Start() 
{
    sPlayer = new Player(500, 100);
    sWave = new EnemyWave(sGridData.waveList);
    mSelectedTowerType = nullptr;
    mPtrTowerSelected = nullptr;

    InitButton();
    InitText();
    sWave->Start();
}

void Game::Update()
{
    CheckStatTowerDisplay();
    Scene::Update();
    sWave->Update(sTimeScale);

    if(sPlayer->GetLife() <= 0)
        Scene::ChangeScene(new GameOver(*this));

    if(sTimeScale == 2)
    {
        ((Button*)UIelements[1])->mSprite.SetTexture(SpeedTextureX2);
        ((Button*)UIelements[1])->mHoverSprite.SetTexture(SpeedTextureX2);
        ((Button*)UIelements[1])->mPressedSprite.SetTexture(SpeedTextureX2);
    }
    else 
    {
        ((Button*)UIelements[1])->mSprite.SetTexture(SpeedTextureX1);
        ((Button*)UIelements[1])->mHoverSprite.SetTexture(SpeedTextureX1);
        ((Button*)UIelements[1])->mPressedSprite.SetTexture(SpeedTextureX1);
    }

    CheckAvailableTiles(Vec2(2, 2));
    CheckForWin();

    for (int i = 0; i < (int)sWave->sEnemies.size(); i++)
    {
        if(sWave->sEnemies[i]->GetLife() <= 0)
        {
            delete sWave->sEnemies[i];
            sWave->sEnemies.erase(sWave->sEnemies.begin() + i);
            i--;
        }
    }


    int j = 0;
    for(Tower* curr : mTowerlist)
    {
        if(curr->isTowerToSell)
        {
            int index = FindButtonSelected(*curr);
            delete UIelements[index];
            UIelements.erase(UIelements.begin() + index);
            delete curr;
            mTowerlist.erase(mTowerlist.begin() + j); 
            mPtrTowerSelected = nullptr;
        }
        j++;
    }
}

void Game::CheckForWin()
{
    if(sWave->waveIndex == sWave->waveData.size() && sWave->sEnemies.size() == 0)
        Scene::ChangeScene(new WinScreen(sWave->waveIndex));
}

void Game::Render()
{
    for (int i = 0; i < gridWidth; i++)
    {
        for (int j = 0; j < gridHeight; j++)
        {
            if(sGridData.dataGrid[i][j] >= 2)
            {
                Sprite(Vec2(0, 5) + sGridData.mBiomeOffset,
                 tileSet, Vec2(36, 21), Vec2(0, 0)).Draw(Box{i * 40.f, j * 40.f, 40, 40}, 0);
            }
            sGridData.spriteGrid[i][j].Draw(Box{i * 40.f + caseSize / 2, j * 40.f + caseSize / 2, 40, 40}, 0);
        }
    }

    if (mSelectedTowerType)
    {
        Vec2 gridMousePos = toVec2(GetMousePosition()).floor(40);
        Color freePlace;
        
        if(CheckAvailableTiles(Vec2(mSelectedTowerType->towerSize, mSelectedTowerType->towerSize)))
            freePlace = {70, 70, 255, 70};
        else
            freePlace = {255, 70, 70, 70};

        switch (mSelectedTowerType->type)
        {
        case TT_COMMON:
            Sprite({19,10}, enemySet, {23,13}, {20,20}).Draw(Box(gridMousePos.x + 20 + 0, gridMousePos.y + 20 + 0, 40, 40), 0);
            DrawCircle(gridMousePos.x + 20, gridMousePos.y + 20, TowerData::Common.range, freePlace);
            break;

        case TT_CRYO:
            Sprite({20,9}, enemySet, {23,13}, {20,20}).Draw(Box(gridMousePos.x + 20 + 0, gridMousePos.y + 20 + 0, 40, 40), 0);
            DrawCircle(gridMousePos.x + 20, gridMousePos.y + 20, TowerData::Cryo.range, freePlace);
            break;

        case TT_BOMB:
            Sprite({22,8}, enemySet, {23,13}, {20,20}).Draw(Box(gridMousePos.x + 20 + 0, gridMousePos.y + 20 + 0, 40, 40), 0);
            DrawCircle(gridMousePos.x + 20, gridMousePos.y + 20, TowerData::Bomb.range, freePlace);
            break;

        case TT_STATUE:
            Sprite({3, 19}, TowerSet, {29, 23}, {20,20}, 2).Draw(Box(gridMousePos.x + 20, gridMousePos.y + 20, 80, 80), 0);
            DrawCircle(gridMousePos.x + 40, gridMousePos.y + 40, TowerData::Statue.range, freePlace);
            break;

        default:
            break;
        } 
    }

    Scene::Render();
    sWave->Render();

    for (Tower *curr : mTowerlist)
    {
        if(curr->mType != TT_STATUE) 
        {
            myMath::Vec2 position = curr->GetPosition();
            Sprite(Vec2{20,7}, enemySet, Vec2{23,13}, Vec2(20, 20)).Draw(Box{position.x, position.y, 40, 40}, 0); 
        }
        curr->UpdateAndDraw();
    }

    if(UIelements[mItStatTower[1]]->isActive)
        DrawCircle(mPtrTowerSelected->GetPosition().x, mPtrTowerSelected->GetPosition().y, mPtrTowerSelected->GetRange(), {70, 70, 255, 90});

    if(sTimeScale == 0)
    {
        DrawRectangle(0, 0, 1920, 1080, Color{0,0,0,150});
        DrawTexture(HUD, GetScreenWidth()/2-350, GetScreenHeight()/2-100, WHITE);
        for (int i = 2; i <= 4; i++)
            UIelements[i]->isActive = true;    
    }

    else
    {
        for (int i = 2; i <= 4; i++)
            UIelements[i]->isActive = false;
    }
}

void Game::GetInput()
{
    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && mSelectedTowerType)
    {
        if (CheckAvailableTiles(Vec2(mSelectedTowerType->towerSize, mSelectedTowerType->towerSize)))
        {
            switch (mSelectedTowerType->type)
            {
            case (TT_COMMON):
                mTowerlist.push_back(new CommonTower(toVec2(GetMousePosition()).floor(40) + (Vec2){20, 20}, FlameShotSound));
                sPlayer->BuyTower(TowerData::Common.cost);

                UIelements.push_back(new Button(collision::Box(toVec2(GetMousePosition()).floor(40).x, toVec2(GetMousePosition()).floor(40).y, 40, 40),
                    [](Button* self)
                    {
                        ((Game*)self->mUserPtr)->mPtrTowerSelected = ((Game*)self->mUserPtr)->FindTowerSelected();
                        ((Game*)self->mUserPtr)->ActiveStatTower();
                    }, 
                    Sound(TouretPlacedSound), {0,0,0,0}, 
                    Sprite({21, 0}, enemySet, {23, 13}, {0, 0}), this, Sprite({21, 0}, enemySet, {23, 13}, {0, 0}),
                    Sprite({21, 0}, enemySet, {23, 13}, {0, 0}), false));

                mPtrTowerSelected = mTowerlist.back();
                mTowerSelected = *mPtrTowerSelected;
                ActiveStatTower();
                break;

            case (TT_CRYO):
                mTowerlist.push_back(new CryoTower(toVec2(GetMousePosition()).floor(40) + (Vec2){20, 20}, CryoShotSound));
                sPlayer->BuyTower(TowerData::Cryo.cost);

                UIelements.push_back(new Button(collision::Box(toVec2(GetMousePosition()).floor(40).x, toVec2(GetMousePosition()).floor(40).y, 40, 40),
                    [](Button* self)
                    {
                        ((Game*)self->mUserPtr)->mPtrTowerSelected = ((Game*)self->mUserPtr)->FindTowerSelected();
                        ((Game*)self->mUserPtr)->ActiveStatTower();
                    }, 
                    Sound(TouretPlacedSound), {0,0,0,0}, 
                    Sprite({21, 0}, enemySet, {23, 13}, {0, 0}), this, Sprite({21, 0}, enemySet, {23, 13}, {0, 0}),
                    Sprite({21, 0}, enemySet, {23, 13}, {0, 0}), false));

                mPtrTowerSelected = mTowerlist.back();
                mTowerSelected = *mPtrTowerSelected;
                ActiveStatTower();
                break;

            case (TT_BOMB):
                mTowerlist.push_back(new BombTower(toVec2(GetMousePosition()).floor(40) + (Vec2){20, 20}, BombShotSound));
                sPlayer->BuyTower(TowerData::Bomb.cost);

                UIelements.push_back(new Button(collision::Box(toVec2(GetMousePosition()).floor(40).x, toVec2(GetMousePosition()).floor(40).y, 40, 40),
                    [](Button* self)
                    {
                        ((Game*)self->mUserPtr)->mPtrTowerSelected = ((Game*)self->mUserPtr)->FindTowerSelected();
                        ((Game*)self->mUserPtr)->ActiveStatTower();
                    }, 
                    Sound(TouretPlacedSound), {0,0,0,0}, 
                    Sprite({21, 0}, enemySet, {23, 13}, {0, 0}), this, Sprite({21, 0}, enemySet, {23, 13}, {0, 0}),
                    Sprite({21, 0}, enemySet, {23, 13}, {0, 0}), false));

                mPtrTowerSelected = mTowerlist.back();
                mTowerSelected = *mPtrTowerSelected;
                ActiveStatTower();
                break;

            case (TT_STATUE):
                mTowerlist.push_back(new StatueTower(toVec2(GetMousePosition()).floor(40) + (Vec2){40, 40}, CryoShotSound));
                sPlayer->BuyTower(TowerData::Statue.cost);

                UIelements.push_back(new Button(collision::Box(toVec2(GetMousePosition()).floor(40).x, toVec2(GetMousePosition()).floor(40).y, 80, 80),
                    [](Button* self)
                    {
                        ((Game*)self->mUserPtr)->mPtrTowerSelected = ((Game*)self->mUserPtr)->FindTowerSelected();
                        ((Game*)self->mUserPtr)->ActiveStatTower();
                    }, 
                    Sound(TouretPlacedSound), {0,0,0,0}, 
                    Sprite({21, 0}, enemySet, {23, 13}, {0, 0}), this, Sprite({21, 0}, enemySet, {23, 13}, {0, 0}),
                    Sprite({21, 0}, enemySet, {23, 13}, {0, 0}), false));

                mPtrTowerSelected = mTowerlist.back();
                mTowerSelected = *mPtrTowerSelected;
                ActiveStatTower();
                break;

            case (TT_NULL):
                break;
            }
        }
        mSelectedTowerType = nullptr;
    }
}

void Game::InitButton()
{
    UIelements.push_back(new Button(collision::Box(1700, 30, 200, 80),
    [](Button *self)
    {
        GamePause();
    }, 
    Sound(ClickSound), Color{0, 0, 0, 0},
    Sprite({0, 0}, PauseTexture, {1, 3}, {0, 0}), this, Sprite({0, 1}, PauseTexture, {1, 3}, {0, 0}),
    Sprite({0, 2}, PauseTexture, {1, 3}, {0, 0}), true));

    UIelements.push_back(new Button(collision::Box(1550, 30, 125, 80),
    [](Button* self)
    {
        GameAcceleration();
    }, 
    Sound(ClickSound), Color{0, 0, 0, 0},
    Sprite({0, 0}, SpeedTextureX1, {1, 3}, {0, 0}), nullptr, Sprite({0, 1}, SpeedTextureX1, {1, 3}, {0, 0}), 
    Sprite({0, 2}, SpeedTextureX1, {1, 3}, {0, 0}), false));

    UIelements.push_back(new Button(collision::Box((GetScreenWidth()/2-350)+277, (GetScreenHeight()/2-100)+60, 100, 80),
    [](Button* self)
    {
        if(Game::sActualVolume != 0.f) 
            CheckAndSetVolume(0.f);

        else if(Game::sActualVolume == 0.f)
            CheckAndSetVolume(0.8f);
        GamePause();
    }, 
    Sound(ClickSound), Color{0, 0, 0, 0},
    Sprite({0, 0}, SoundTexture, {1, 3}, {0, 0}), nullptr, Sprite({0, 1}, SoundTexture, {1, 3}, {0, 0}), 
    Sprite({0, 2}, SoundTexture, {1, 3}, {0, 0}), false, false));

    UIelements.push_back(new Button(collision::Box((GetScreenWidth()/2-350)+400, (GetScreenHeight()/2-100)+60, 200, 80),
    [](Button* self)
    {
        GamePause();
    }, 
    Sound(ClickSound), Color{0, 0, 0, 0},
    Sprite({0, 0}, ResumeTexture, {1, 3}, {0, 0}), nullptr, Sprite({0, 1}, ResumeTexture, {1, 3}, {0, 0}), 
    Sprite({0, 2}, ResumeTexture, {1, 3}, {0, 0}), false, false));

    UIelements.push_back(new Button(collision::Box((GetScreenWidth()/2-350)+50, (GetScreenHeight()/2-100)+60, 200, 80),
    [](Button* self)
    {
        GamePause();
        ((Game*)self->mUserPtr)->mTowerlist.clear();
        ((Game*)self->mUserPtr)->sPath.clear();
        ((Game*)self->mUserPtr)->sWave->sEnemies.clear();
        ChangeScene(new LevelSelect());
    }, 
    Sound(ClickSound), Color{0, 0, 0, 0},
    Sprite({0, 0}, QuitTexture, {1, 3}, {0, 0}), this, Sprite({0, 1}, QuitTexture, {1, 3}, {0, 0}), 
    Sprite({0, 2}, QuitTexture, {1, 3}, {0, 0}), false, false));

    UIelements.push_back(new Button(collision::Box((GetScreenWidth()/2-350)+50, (GetScreenHeight()/2-100)+60, 200, 80),
    [](Button* self)
    {
        GamePause();
    }, 
    Sound(ClickSound), Color{0, 0, 0, 0},
    Sprite({0, 0}, ResumeTexture, {1, 3}, {0, 0}), this, Sprite({0, 1}, ResumeTexture, {1, 3}, {0, 0}), 
    Sprite({0, 2}, ResumeTexture, {1, 3}, {0, 0}), false, false));

    UIelements.push_back(new Button(collision::Box(1800, 150, 60, 60),
    [](Button* self)
    {
        if (((Game *)self->mUserPtr)->sPlayer->GetGold() >= TowerData::Common.cost)
            ((Game *)self->mUserPtr)->mSelectedTowerType = &TowerData::Common;
    }, 
    Sound(TouretPlacedSound), BLUE, 
    Sprite({19, 10}, enemySet, {23, 13}, {0, 0}), this,  Sprite({19, 10}, enemySet, {23, 13}, {0, 0}),
    Sprite({19, 10}, enemySet, {23, 13}, {0, 0}), false));

    UIelements.push_back(new Button(collision::Box(1800, 250, 60, 60),
    [](Button* self)
    { 
        if(((Game *)self->mUserPtr)->sPlayer->GetGold() >= TowerData::Cryo.cost)
            ((Game *)self->mUserPtr)->mSelectedTowerType = &TowerData::Cryo; 
    }, 
    Sound(TouretPlacedSound), BLUE, 
    Sprite({20, 9}, enemySet, {23, 13}, {0, 0}), this, Sprite({20, 9}, enemySet, {23, 13}, {0, 0}),
    Sprite({20, 9}, enemySet, {23, 13}, {0, 0}), false));


    UIelements.push_back(new Button(collision::Box(1800, 350, 60, 60),
    [](Button* self)
    { 
        if(((Game *)self->mUserPtr)->sPlayer->GetGold() >= TowerData::Bomb.cost)
            ((Game *)self->mUserPtr)->mSelectedTowerType = &TowerData::Bomb; 
    }, 
    Sound(TouretPlacedSound), BLUE, 
    Sprite({22, 8}, enemySet, {23, 13}, {0, 0}), this, Sprite({22, 8}, enemySet, {23, 13}, {0, 0}),
    Sprite({22, 8}, enemySet, {23, 13}, {0, 0}), false));

    UIelements.push_back(new Button(collision::Box(370, 910, 55, 55),
    [](Button* self)
    { 
        if(((Game*)self->mUserPtr)->sPlayer->GetGold() >= ((Game*)self->mUserPtr)->mTowerSelected.GetCost())
        {
            ((Game*)self->mUserPtr)->UpgradeTowerSelected();
            ((Game*)self->mUserPtr)->sPlayer->BuyTower(((Game*)self->mUserPtr)->mTowerSelected.GetCost());
        }
    }, 
    Sound(ClickSound), {0,0,0,165}, 
    Sprite({16, 0}, enemySet, {23, 13}, {0, 0}), this, Sprite({16, 0}, enemySet, {23, 13}, {0, 0}),
    Sprite({16, 0}, enemySet, {23, 13}, {0, 0}), false, false));

    mItStatTower[0] = (int)UIelements.size() - 1;

    UIelements.push_back(new Button(collision::Box(370, 970, 55, 55),
    [](Button* self)
    { 
        ((Game*)self->mUserPtr)->SellTowerSelected();
    }, 
    Sound(ClickSound), {0,0,0,165}, 
    Sprite({17, 0}, enemySet, {23, 13}, {0, 0}), this, Sprite({17, 0}, enemySet, {23, 13}, {0, 0}),
    Sprite({17, 0}, enemySet, {23, 13}, {0, 0}), false, false));

    mItStatTower[1] = (int)UIelements.size() - 1;

    UIelements.push_back(new Button(collision::Box(1800, 450, 60, 60),
    [](Button *self)
    { 
        if(((Game *)self->mUserPtr)->sPlayer->GetGold() >= TowerData::Statue.cost)
        {
            ((Game *)self->mUserPtr)->mSelectedTowerType = &TowerData::Statue; 
        }
    }, Sound(TouretPlacedSound), BLUE, 
    Sprite({3, 18}, TowerSet, {29, 22}, {0, 0}, 2), this, Sprite({3, 18}, TowerSet, {29, 22}, {0, 0}, 2),
    Sprite({3, 18}, TowerSet, {29, 22}, {0, 0}, 2), false));

    mItStatTower[7] = (int)UIelements.size() - 1; 
}

void Game::InitText()
{
    UIelements.push_back(new UIText(Box(1790, 120, 85, 30), BLUE, " $", &TowerData::Common.cost));
    UIelements.push_back(new UIText(Box(1790, 220, 85, 30), BLUE, " $", &TowerData::Cryo.cost));
    UIelements.push_back(new UIText(Box(1790, 320, 85, 30), BLUE, " $", &TowerData::Bomb.cost));
    UIelements.push_back(new UIText(Box(1790, 420, 85, 30), BLUE, " $", &TowerData::Statue.cost));

    UIelements.push_back(new UIText(Box(1650, 850, 200, 60), DARKGREEN," $",&sPlayer->GetGold()));
    UIelements.push_back(new UIText(Box(1650, 950, 200, 60), RED," %",&sPlayer->GetLife()));

    UIelements.push_back(new UIText(Box(440, 925, 300, 30), {255,255,255,160}, " $ - Upgrade", &mTowerSelected.mCost, false));
    mItStatTower[2] = (int)UIelements.size() - 1;
    UIelements.push_back(new UIText(Box(440, 980, 300, 30), {255,255,255,160}, " $ - Sell", &mTowerSelected.mCost, false));
    mItStatTower[3] = (int)UIelements.size() - 1;
    UIelements.push_back(new UIText(Box(50, 900, 300, 30), {255,255,255,160}, " damage", &mTowerSelected.mDamage, false));
    mItStatTower[4] = (int)UIelements.size() - 1;
    UIelements.push_back(new UIText(Box(50, 950, 300, 30), {255,255,255,160}, " attack speed", &mTowerSelected.mAttackSpeed, false));
    mItStatTower[5] = (int)UIelements.size() - 1;
    UIelements.push_back(new UIText(Box(50, 1000, 300, 30), {255,255,255,160}, " range", &mTowerSelected.mRange, false));
    mItStatTower[6] = (int)UIelements.size() - 1;
}

bool Game::CheckAvailableTiles(myMath::Vec2 TouretSize)
{
    myMath::Vec2 MousPos = myMath::toVec2(GetMousePosition()).floor(40)/40;

    for(int i = 0; i < TouretSize.x; i++)
    {
        for(int j = 0; j < TouretSize.y; j++)
        {
            if(sGridData.dataGrid[(int)MousPos.x + i][(int)MousPos.y + j])
                return false;
                
            for(Tower* curr : mTowerlist)
            {
                if(Collision((Box){curr->GetPosition().x - 20, curr->GetPosition().y - 20, (int)TouretSize.x * 40, (int)TouretSize.y * 40}, toVec2(GetMousePosition())))
                    return false;
            }

        }
    }
    return true;
}

std::vector<myMath::Vec2> Game::GetPath(int index)
{
    return sGridData.paths[index];
}

Player* Game::GetPlayer()
{
    return sPlayer;
}

std::vector<Tower*> Game::GetTowers() const
{
    return mTowerlist;
}

void Game::ActivePauseButton()
{
    for(int i = 2; i < 5; i++) 
        UIelements[i]->isActive = !UIelements[i]->isActive;
}

void Game::GamePause()
{
    if(sTimeScale != 0.f) 
        sTimeScale = 0.f; 
    else
        sTimeScale = 1.f;
}

void Game::GameAcceleration()
{
    if(sTimeScale == 2.f)
        sTimeScale = 1.f;
    else
        sTimeScale = 2.f;
}

void Game::CheckAndSetVolume(float gameNewVolume)
{
    sActualVolume = gameNewVolume;
    SetMasterVolume(sActualVolume);
}