#include "levelEditor.hpp"

#include "../gameScenes/menu.hpp"

#include "../gameManager/gameTextures.hpp"
#include "../gameManager/gameSounds.hpp"

using namespace GameTextures;
using namespace GameSounds;

using namespace myMath;
using namespace collision;


LevelEditor::~LevelEditor()
{
    for (std::vector<Button*> currVec : enemyButtons)
    {
        for (Button* curr : currVec)
        {
            delete curr;
        }
        currVec.clear();
    }
    enemyButtons.clear();
}

Vec2 LevelEditor::GetMouseInGridPos()
{
    return ((toVec2(GetMousePosition())) / caseSize).floor(1) - Vec2{1, 1};
}

bool LevelEditor::IsPathValid(int i)
{
    if(grid.paths[i].size() >= 2)
    {
        if(grid.GridCell(grid.paths[i].at(grid.paths[i].size() - 1)) == -1)
        {
            return true;
        }else
        {
            return false;
        }
    }else
    {
        return false;
    }
}

void LevelEditor::Start()
{
    grid.mBiomeOffset = Vec2(0, 0);
    waveEditorParent = Vec2{30, 930};
    for (int i = 0; i < gridWidth; i++)
    {
        for (int j = 0; j < gridHeight; j++)
        {
            grid.dataGrid[i][j] = 0;
        }
    }
    mCurrentFile = "save/map1.bin";
    Load();
    for (int i = 0; i < gridWidth; i++)
    {
        for (int j = 0; j < gridHeight; j++)
        {
            grid.UpdateSprite(Vec2(i, j));
        }
    }
    currentWaveEdit = 0;
    currentPathEdit = 0;
    selected = EL_ROAD;
    editionMode = EM_MAP;
    if(grid.waveList.size() == 0)
    {
        grid.waveList.push_back((EnemyWaveData){});
        enemyButtons.push_back({});
    }
    InitThemeButton();
    InitElementButton();
    InitPathButton();
    InitWaveButton();
    InitNavigationButton();
    popUpTime = 0;
}

void LevelEditor::Update()
{
    Scene::Update();
    //DrawRectangleRoundedLines(Box(1540, 530, 50, 50).toRec(), 0.5f, 8, 5, BLACK);
    if(popUpTime >= 0)
        popUpTime -= GetFrameTime();
}

void LevelEditor::Render()
{
    DrawTexture(EditorBackground, 0, 0, WHITE);
    DisplayGrid();
    DisplayPath();
    DisplayWave();
    Box selectionBox;
    if(editionMode == EM_MAP)
    {
        switch(selected)
        {
            case(EL_ROAD) : selectionBox = Box(1540, 530, 50, 50); break;
            case(EL_BUSH1) : selectionBox = Box(1540, 450, 50, 50); break;
            case(EL_BUSH2) : selectionBox = Box(1620, 450, 50, 50); break;
            case(EL_BUSH3) : selectionBox = Box(1620, 530, 50, 50); break;
            case(EL_BUSH4) : selectionBox = Box(1700, 450, 50, 50); break;
            case(EL_BUSH5) : selectionBox = Box(1700, 530, 50, 50); break;
            case(EL_BUSH6) : selectionBox = Box(1540, 610, 50, 50); break;
            case(EL_BUSH7) : selectionBox = Box(1700, 610, 50, 50); break;
            case(EL_BUSH8) : selectionBox = Box(1620, 610, 50, 50); break;
            case(EL_BUSH9) : selectionBox = Box(1540, 690, 50, 50); break;
            case(EL_TREE) : selectionBox = Box(1620, 690, 50, 50); break;
            default:;
        }
    }else if(editionMode == EM_PATH)
    {
        switch(currentPathEdit)
        {
            case(0) : selectionBox = Box(1540, 800, 100, 30); break;
            case(1) : selectionBox = Box(1660, 800, 100, 30); break;
            case(2) : selectionBox = Box(1540, 850, 100, 30); break;
            case(3) : selectionBox = Box(1660, 850, 100, 30); break;
        }
    }

    if(mCurrentFile == "save/map1.bin")
        DrawRectangleRoundedLines(Box(1780, 20, 100, 30).toRec(), 0.5f, 6, 5, BLUE);
    if(mCurrentFile == "save/map2.bin")
        DrawRectangleRoundedLines(Box(1780, 60, 100, 30).toRec(), 0.5f, 6, 5, BLUE);
    if(mCurrentFile == "save/map3.bin")
        DrawRectangleRoundedLines(Box(1780, 100, 100, 30).toRec(), 0.5f, 6, 5, BLUE);
    if(mCurrentFile == "save/map4.bin")
        DrawRectangleRoundedLines(Box(1780, 140, 100, 30).toRec(), 0.5f, 6, 5, BLUE);
    if(mCurrentFile == "save/map5.bin")
        DrawRectangleRoundedLines(Box(1780, 180, 100, 30).toRec(), 0.5f, 6, 5, BLUE);
    if(mCurrentFile == "save/map6.bin")
        DrawRectangleRoundedLines(Box(1780, 220, 100, 30).toRec(), 0.5f, 6, 5, BLUE);
    if(mCurrentFile == "save/map7.bin")
        DrawRectangleRoundedLines(Box(1780, 260, 100, 30).toRec(), 0.5f, 6, 5, BLUE);
    if(mCurrentFile == "save/map8.bin")
        DrawRectangleRoundedLines(Box(1780, 300, 100, 30).toRec(), 0.5f, 6, 5, BLUE);
    if(mCurrentFile == "save/map9.bin")
        DrawRectangleRoundedLines(Box(1780, 340, 100, 30).toRec(), 0.5f, 6, 5, BLUE);
    if(mCurrentFile == "save/map10.bin")
        DrawRectangleRoundedLines(Box(1780, 380, 100, 30).toRec(), 0.5f, 6, 5, BLUE);
    if(mCurrentFile == "save/map11.bin")
        DrawRectangleRoundedLines(Box(1780, 420, 100, 30).toRec(), 0.5f, 6, 5, BLUE);
    if(mCurrentFile == "save/map12.bin")
        DrawRectangleRoundedLines(Box(1780, 460, 100, 30).toRec(), 0.5f, 6, 5, BLUE);

    if(grid.mBiomeOffset == Vec2(0, 0))
        DrawRectangleRounded(Box(1540, 100, 80, 80).toRec(), 0.5f, 6, Color{255, 255, 255, 80});
    if(grid.mBiomeOffset == Vec2(0, 7))
        DrawRectangleRounded(Box(1540, 200, 80, 80).toRec(), 0.5f, 6, Color{255, 255, 255, 80});
    if(grid.mBiomeOffset == Vec2(0, 14))
        DrawRectangleRounded(Box(1540, 300, 80, 80).toRec(), 0.5f, 6, Color{255, 255, 255, 80});
    if(grid.mBiomeOffset == Vec2(18, 0))
        DrawRectangleRounded(Box(1640, 100, 80, 80).toRec(), 0.5f, 6, Color{255, 255, 255, 80});
    if(grid.mBiomeOffset == Vec2(18, 7))
        DrawRectangleRounded(Box(1640, 200, 80, 80).toRec(), 0.5f, 6, Color{255, 255, 255, 80});
    if(grid.mBiomeOffset == Vec2(18, 14))
        DrawRectangleRounded(Box(1640, 300, 80, 80).toRec(), 0.5f, 6, Color{255, 255, 255, 80});


    DrawRectangleRoundedLines(selectionBox.toRec(), 0.5f, 8, 3, BLUE);
    
    if(popUpTime > 0)
    {
        DrawRectangleRounded(Box(435, 290, 390, 60).toRec(), 0.5f, 6, RED);
        DrawRectangleRoundedLines(Box(435, 290, 390, 60).toRec(), 0.5f, 6, 5, BLACK);
        DrawText(popUpMessage.c_str(), 450, 300, 40, BLACK);
    }
}

void LevelEditor::DisplayGrid()
{
    for (int i = 0; i < gridWidth; i++)
    {
        for (int j = 0; j < gridHeight; j++)
        {
            if(grid.dataGrid[i][j] >= 2)
            {
                Sprite(Vec2(0, 5) + grid.mBiomeOffset, tileSet,
                    Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)).Draw(collision::Box(i * caseSize + caseSize / 2 + caseSize,
                    j * caseSize + caseSize / 2 + caseSize,
                     caseSize, caseSize), 0);
            }
            grid.spriteGrid[i][j].Draw(collision::Box(i * caseSize + caseSize / 2 + caseSize,
             j * caseSize + caseSize / 2 + caseSize,
             caseSize, caseSize), 0);
            if(debug)
            {
                DrawText(TextFormat("%d", grid.dataGrid[i][j]), i * caseSize + 15 + caseSize,
                 j * caseSize + 10 + caseSize, 20, BLACK);
            }
        }
    }

    
    if(grid.GridCell(GetMouseInGridPos()) >= 0)
    {
        DrawRectangleLines(GetMouseInGridPos().x * caseSize + caseSize, GetMouseInGridPos().y * caseSize + caseSize, caseSize, caseSize, Color{0, 0, 0, 150});
        DrawText(TextFormat("%.f, %.f", GetMouseInGridPos().x, GetMouseInGridPos().y), 10, 40, 20, RED);
    }
}

void LevelEditor::DisplayPath()
{
    if(editionMode == EM_PATH)
    {
        for (int j = 0; j < 4; j++)
        {
            for (size_t i = 0; i < grid.paths[j].size(); i++)
            {
                Color pathColor = Color{180, 180, 180, 110};
                if(j == currentPathEdit)
                {
                    pathColor = IsPathValid(j) ? BLUE : RED;
                    DrawText(TextFormat("%d", i),((grid.paths[j].at(i) * caseSize) + Vec2{caseSize * 1.5f, caseSize * 1.5f}).toVector2().x,
                    ((grid.paths[j].at(i) * caseSize) + Vec2{caseSize * 1.5f, caseSize * 1.5f}).toVector2().y, 18, pathColor);
                }
                DrawCircleV(((grid.paths[j].at(i) * caseSize) + Vec2{caseSize * 1.5f, caseSize * 1.5f}).toVector2(),
                5, pathColor);
                if(i < grid.paths[j].size() - 1)
                {
                    DrawLineV(((grid.paths[j].at(i) * caseSize) + Vec2{caseSize * 1.5f, caseSize * 1.5f}).toVector2(),
                    ((grid.paths[j].at(i + 1) * caseSize) + Vec2{caseSize * 1.5f, caseSize * 1.5f}).toVector2(),
                    pathColor);
                }
            }
        }
    }
}
    
void LevelEditor::DisplayWave()
{
    for(Button* curr : enemyButtons[currentWaveEdit])
        curr->UpdateAndDrawUI();

    for (size_t i = 0; i < grid.waveList[currentWaveEdit].Wave.size(); i++)
    {
        DrawText(TextFormat("%.1f sec", grid.waveList[currentWaveEdit].timeBeforeNextEnemy[i]),( 8 + 150 * i) + waveEditorParent.x, waveEditorParent.y + 2, 15, YELLOW);
        DrawText(TextFormat("path: %d", grid.waveList[currentWaveEdit].pathToFollow[i] + 1),( 70 + 150 * i) + waveEditorParent.x, waveEditorParent.y + 2, 15, YELLOW);
        Texture2D enemyTexture;
        switch(grid.waveList[currentWaveEdit].Wave[i])
        {
            case(ET_SLIME) : enemyTexture = GameTextures::slimeAnim; break;
            case(ET_SPIRIT) : enemyTexture = GameTextures::spiritAnim; break;
            case(ET_CYCLOPE) : enemyTexture = GameTextures::cyclopeAnim; break;
            case(ET_SKELETON) : enemyTexture = GameTextures::skeletonAnim; break;
            case(ET_BEAST) : enemyTexture = GameTextures::beastAnim; break;
            case(ET_KNIGHT) : enemyTexture = GameTextures::KnightAnim; break;
        }
        Sprite(Vec2(0, 0), enemyTexture, Vec2(4, 4),
        Vec2(0, 0)).Draw(collision::Box(30 + 150 * i, 35, 60, 60) + waveEditorParent, 0);
    }
    DrawRectangleRounded(collision::Box(940, 880, 180, 40).toRec(), 0.5f, 8, BLUE);
    DrawRectangleRoundedLines(collision::Box(940, 880, 180, 40).toRec(), 0.5f, 8, 5, DARKBLUE);
    DrawText(TextFormat("%d", currentWaveEdit + 1), 1000, 890, 25, DARKBLUE);
    DrawText(TextFormat("/ %d", grid.waveList.size()), 1020, 890, 25, DARKBLUE);
}

void LevelEditor::GetInput()
{
    if(IsKeyPressed(KEY_A))
    {
        AddEnemy(ET_SLIME);
    }
    if(editionMode == EM_MAP)
    {
        if(IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            if(grid.GridCell(GetMouseInGridPos()) < 0)
                return;

            if(selected == EL_TREE)
            {
                grid.PutTree(GetMouseInGridPos());
                for (int i = -1; i < 3; i++)
                {
                    for (int j = -1; j < 3; j++)
                    {
                        grid.UpdateSprite(GetMouseInGridPos() + Vec2(i, j), false);
                    }
                }
            }
            else
            {
                grid.dataGrid[(int)GetMouseInGridPos().x][(int)GetMouseInGridPos().y] = selected;
                for (int i = -1; i < 2; i++)
                {
                    for (int j = -1; j < 2; j++)
                    {
                        grid.UpdateSprite(GetMouseInGridPos() + Vec2(i, j), false);
                    }
                }
            }
        }
        if(IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
        {
            if(grid.GridCell(GetMouseInGridPos()) < 0)
                return;
            grid.dataGrid[(int)GetMouseInGridPos().x][(int)GetMouseInGridPos().y] = 0;
            for (int i = -1; i < 2; i++)
            {
                for (int j = -1; j < 2; j++)
                {
                    grid.UpdateSprite(GetMouseInGridPos() + Vec2(i, j), false);
                }
            }
        }
    }
    if(editionMode == EM_PATH)
    {
        if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) && grid.GridCell(GetMouseInGridPos()) >= -1 && grid.paths[currentPathEdit].size() != 0)
        {
            grid.paths[currentPathEdit].pop_back();
            return;
        }
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            if(grid.paths[currentPathEdit].size() == 0 && grid.GridCell(GetMouseInGridPos()) == -1)
                grid.paths[currentPathEdit].push_back(GetMouseInGridPos());

            if(grid.paths[currentPathEdit].size() > 0 && grid.GridCell(GetMouseInGridPos()) >= 0)
                grid.paths[currentPathEdit].push_back(GetMouseInGridPos());
            if(grid.paths[currentPathEdit].size() >= 2 && grid.GridCell(GetMouseInGridPos()) == -1 &&

             grid.GridCell(grid.paths[currentPathEdit].at(grid.paths[currentPathEdit].size() - 1)) != -1)
                grid.paths[currentPathEdit].push_back(GetMouseInGridPos());
        }
    }

    if(GetMousePosition().y > 930)
    {
        waveEditorParent.x = Clamp(waveEditorParent.x + GetMouseWheelMove() * 30, 
        (float)((float)grid.waveList[currentWaveEdit].Wave.size() * 150 * -1 + 30), 70.f);
    }
    int i = 0;
    for(Button* curr : enemyButtons[currentWaveEdit])
    {
        int x = i - (i % 4);
        switch(i % 4)
        {
            case(0) : 
            curr->mCollider.min.x = waveEditorParent.x + x * 37.5f;
            curr->mCollider.max.x = curr->mCollider.min.x + 120; break;
            case(1) :
            curr->mCollider.min.x = waveEditorParent.x + x * 37.5f;
            curr->mCollider.max.x = curr->mCollider.min.x + 60; break;
            case(2) :
            curr->mCollider.min.x = waveEditorParent.x + x * 37.5f + 60;
            curr->mCollider.max.x = curr->mCollider.min.x + 60; break;
            case(3) : 
            curr->mCollider.min.x = waveEditorParent.x + x * 37.5f;
            curr->mCollider.max.x = curr->mCollider.min.x + 120; break;
        }
        i++;
    }
        
    
}

void LevelEditor::AddEnemy(EnemyType newEnemy, float _time, int _path)
{
    grid.waveList[currentWaveEdit].Wave.push_back(newEnemy);
    grid.waveList[currentWaveEdit].timeBeforeNextEnemy.push_back(_time);
    grid.waveList[currentWaveEdit].pathToFollow.push_back(_path);


    Button* btn = new Button{
            (collision::Box){150 * (grid.waveList[currentWaveEdit].Wave.size() - 1) + waveEditorParent.x,
             waveEditorParent.y + 25, 100, 80}, 
            [](Button *self){
                ((LevelEditor*)self->mUserPtr)->grid.waveList[((LevelEditor*)self->mUserPtr)->currentWaveEdit].Wave.at(self->intValue)
                 = (EnemyType)((((LevelEditor*)self->mUserPtr)->grid.waveList[((LevelEditor*)self->mUserPtr)->currentWaveEdit].Wave.at(self->intValue) + 1) % 6);
            },
            GameSounds::EventSound,
            Color{255, 255, 255, 100},
            Sprite({240, 128, 1, 1},tileSet, {0, 0}), this, Sprite({240, 128, 1, 1},tileSet, {0, 0}), 
            Sprite({240, 128, 1, 1},tileSet, {0, 0}), false};
    btn->intValue = grid.waveList[currentWaveEdit].Wave.size() - 1;

    enemyButtons[currentWaveEdit].push_back(btn);


    Button* btn2 = new Button{
            (collision::Box){150 * (grid.waveList[currentWaveEdit].Wave.size() - 1) + waveEditorParent.x,
             waveEditorParent.y, 60, 20}, 
            [](Button *self){
                ((LevelEditor*)self->mUserPtr)->grid.waveList[((LevelEditor*)self->mUserPtr)->currentWaveEdit].timeBeforeNextEnemy.at(self->intValue)
                 = fmod(((LevelEditor*)self->mUserPtr)->grid.waveList[((LevelEditor*)self->mUserPtr)->currentWaveEdit].timeBeforeNextEnemy.at(self->intValue) + 0.5f, 6);
            },
            GameSounds::EventSound,
            Color{255, 255, 255, 100},
            Sprite({240, 128, 1, 1},tileSet, {0, 0}), this, Sprite({240, 128, 1, 1},tileSet, {0, 0}), 
            Sprite({240, 128, 1, 1},tileSet, {0, 0}), false};
    btn2->intValue = grid.waveList[currentWaveEdit].Wave.size() - 1;

    enemyButtons[currentWaveEdit].push_back(btn2);

    Button* btn3 = new Button{(collision::Box){150 * (grid.waveList[currentWaveEdit].Wave.size() - 1) + waveEditorParent.x + 60,waveEditorParent.y, 60, 20}, 
    [](Button *self)
    {
        ((LevelEditor*)self->mUserPtr)->grid.waveList[((LevelEditor*)self->mUserPtr)->currentWaveEdit].pathToFollow.at(self->intValue)
            = (((LevelEditor*)self->mUserPtr)->grid.waveList[((LevelEditor*)self->mUserPtr)->currentWaveEdit].pathToFollow.at(self->intValue) + 1) % 4;
    },
    GameSounds::EventSound,
    Color{255, 255, 255, 100},
    Sprite({240, 128, 1, 1},tileSet, {0, 0}), this, Sprite({240, 128, 1, 1},tileSet, {0, 0}), 
    Sprite({240, 128, 1, 1},tileSet, {0, 0}), false};
    btn3->intValue = grid.waveList[currentWaveEdit].Wave.size() - 1;

    enemyButtons[currentWaveEdit].push_back(btn3);

    Button* btn4 = new Button{(collision::Box){150 * (grid.waveList[currentWaveEdit].Wave.size() - 1) + waveEditorParent.x + 60,waveEditorParent.y + 110, 60, 30}, 
    [](Button *self)
    {
        ((LevelEditor*)self->mUserPtr)->DeleteEnemy(self->intValue);
    },
    GameSounds::EventSound,
    Color{255, 13, 13, 255},
    " Delete", this};
    btn4->intValue = grid.waveList[currentWaveEdit].Wave.size() - 1;

    enemyButtons[currentWaveEdit].push_back(btn4);
    
}

void LevelEditor::DeleteEnemy(int index)
{
    grid.waveList[currentWaveEdit].pathToFollow.erase(grid.waveList[currentWaveEdit].pathToFollow.begin() + index);
    grid.waveList[currentWaveEdit].Wave.erase(grid.waveList[currentWaveEdit].Wave.begin() + index);
    grid.waveList[currentWaveEdit].timeBeforeNextEnemy.erase(grid.waveList[currentWaveEdit].timeBeforeNextEnemy.begin() + index);

    for (int i = 0; i < 4; i++)
    {
        delete enemyButtons[currentWaveEdit][index * 4];
        enemyButtons[currentWaveEdit].erase(enemyButtons[currentWaveEdit].begin() + index * 4 );
    }

    for (size_t i = index * 4; i < enemyButtons[currentWaveEdit].size(); i++)
        enemyButtons[currentWaveEdit][i]->intValue --;
    
}

void LevelEditor::InitNavigationButton()
{
    
    UIelements.push_back(new Button{collision::Box{1300, 880, 90, 37},
    [](Button *self)
    {
        ((LevelEditor*)self->mUserPtr)->Save();
    },
    GameSounds::EventSound,GREEN, "Save", this}); 

    UIelements.push_back(new Button(collision::Box(1525, 10, 200, 80),
    [](Button* self)
    {
        Scene::ChangeScene(new Menu());
    }, 
    Sound(GameSounds::ClickSound), Color{0, 0, 0, 0},
    Sprite({0, 0}, GameTextures::QuitTexture, {1, 3}, {0, 0}), this, Sprite({0, 1}, GameTextures::QuitTexture, {1, 3}, {0, 0}), 
    Sprite({0, 2}, GameTextures::QuitTexture, {1, 3}, {0, 0}), true));

    UIelements.push_back(new Button{collision::Box{1780, 20, 100, 30},
    [](Button *self)
    {
        ((LevelEditor*)self->mUserPtr)->mCurrentFile = "save/map1.bin";
        ((LevelEditor*)self->mUserPtr)->Load();
    },
    GameSounds::EventSound, SKYBLUE, "Map 1", this}); 

    UIelements.push_back(new Button{collision::Box{1780, 60, 100, 30},
    [](Button *self)
    {
        ((LevelEditor*)self->mUserPtr)->mCurrentFile = "save/map2.bin";
        ((LevelEditor*)self->mUserPtr)->Load();
    },
    GameSounds::EventSound, SKYBLUE, "Map 2", this}); 

    UIelements.push_back(new Button{collision::Box{1780, 100, 100, 30},
    [](Button *self)
    {
        ((LevelEditor*)self->mUserPtr)->mCurrentFile = "save/map3.bin";
        ((LevelEditor*)self->mUserPtr)->Load();
    },
    GameSounds::EventSound, SKYBLUE, "Map 3", this}); 

    UIelements.push_back(new Button{collision::Box{1780, 140, 100, 30},
    [](Button *self)
    {
        ((LevelEditor*)self->mUserPtr)->mCurrentFile = "save/map4.bin";
        ((LevelEditor*)self->mUserPtr)->Load();
    },
    GameSounds::EventSound, SKYBLUE, "Map 4", this}); 

    UIelements.push_back(new Button{collision::Box{1780, 180, 100, 30},
    [](Button *self)
    {
        ((LevelEditor*)self->mUserPtr)->mCurrentFile = "save/map5.bin";
        ((LevelEditor*)self->mUserPtr)->Load();
    },
    GameSounds::EventSound, SKYBLUE, "Map 5", this}); 

    UIelements.push_back(new Button{collision::Box{1780, 220, 100, 30},
    [](Button *self)
    {
        ((LevelEditor*)self->mUserPtr)->mCurrentFile = "save/map6.bin";
        ((LevelEditor*)self->mUserPtr)->Load();
    },
    GameSounds::EventSound, SKYBLUE, "Map 6", this}); 

    UIelements.push_back(new Button{collision::Box{1780, 260, 100, 30},
    [](Button *self)
    {
        ((LevelEditor*)self->mUserPtr)->mCurrentFile = "save/map7.bin";
        ((LevelEditor*)self->mUserPtr)->Load();
    },
    GameSounds::EventSound, SKYBLUE, "Map 7", this}); 

    UIelements.push_back(new Button{collision::Box{1780, 300, 100, 30},
    [](Button *self)
    {
        ((LevelEditor*)self->mUserPtr)->mCurrentFile = "save/map8.bin";
        ((LevelEditor*)self->mUserPtr)->Load();
    },
    GameSounds::EventSound, SKYBLUE, "Map 8", this}); 

    UIelements.push_back(new Button{collision::Box{1780, 340, 100, 30},
    [](Button *self)
    {
        ((LevelEditor*)self->mUserPtr)->mCurrentFile = "save/map9.bin";
        ((LevelEditor*)self->mUserPtr)->Load();
    },
    GameSounds::EventSound, SKYBLUE, "Map 9", this}); 

    UIelements.push_back(new Button{collision::Box{1780, 380, 100, 30},
    [](Button *self)
    {
        ((LevelEditor*)self->mUserPtr)->mCurrentFile = "save/map10.bin";
        ((LevelEditor*)self->mUserPtr)->Load();
    },
    GameSounds::EventSound, SKYBLUE, "Map 10", this}); 

    UIelements.push_back(new Button{collision::Box{1780, 420, 100, 30},
    [](Button *self)
    {
        ((LevelEditor*)self->mUserPtr)->mCurrentFile = "save/map11.bin";
        ((LevelEditor*)self->mUserPtr)->Load();
    },
    GameSounds::EventSound, SKYBLUE, "Map 11", this}); 

    UIelements.push_back(new Button{collision::Box{1780, 460, 100, 30},
    [](Button *self)
    {
        ((LevelEditor*)self->mUserPtr)->mCurrentFile = "save/map12.bin";
        ((LevelEditor*)self->mUserPtr)->Load();
    },
    GameSounds::EventSound, SKYBLUE, "Map 12", this}); 
}

void LevelEditor::InitThemeButton()
{
    UIelements.push_back(new Button{(collision::Box){1540, 100, 80, 80}, 
    [](Button *self){
        for (int i = 6; i < 17; i++)
        {
            ((Button*)((LevelEditor *)self->mUserPtr)->UIelements[i])->SetSpriteSourceOffset(
                (Vec2(0, 0) - ((LevelEditor *)self->mUserPtr)->grid.mBiomeOffset) * 16);
        }

        ((LevelEditor *)self->mUserPtr)->grid.mBiomeOffset = Vec2{0, 0};
        for (int i = 0; i < gridWidth; i++)
        {
            for (int j = 0; j < gridHeight; j++)
                ((LevelEditor *)self->mUserPtr)->grid.UpdateSprite(Vec2(i, j));
        }   
    },
    GameSounds::EventSound, Color{0, 0, 0, 0},
    Sprite({240, 16, 32, 32},tileSet, {0, 0}), this, Sprite({240, 16, 32, 32},tileSet, {0, 0}), 
    Sprite({240, 16, 32, 32},tileSet, {0, 0}), false});
        

    UIelements.push_back(new Button{(collision::Box){1540, 200, 80, 80}, 
    [](Button *self)
    {
        for (int i = 6; i < 17; i++)
        {
            ((Button*)((LevelEditor *)self->mUserPtr)->UIelements[i])->SetSpriteSourceOffset(
                (Vec2(0, 7) - ((LevelEditor *)self->mUserPtr)->grid.mBiomeOffset) * 16);
        }
        ((LevelEditor *)self->mUserPtr)->grid.mBiomeOffset = Vec2{0, 7};

        for (int i = 0; i < gridWidth; i++)
        {
            for (int j = 0; j < gridHeight; j++)
                ((LevelEditor *)self->mUserPtr)->grid.UpdateSprite(Vec2(i, j));
        }
    },
    GameSounds::EventSound, Color{0, 0, 0, 0},
    Sprite({240, 128, 32, 32},tileSet, {0, 0}), this, Sprite({240, 128, 32, 32},tileSet, {0, 0}), 
    Sprite({240, 128, 32, 32},tileSet, {0, 0}), false});

        UIelements.push_back(new Button{
            (collision::Box){1540, 300, 80, 80}, 
            [](Button *self){
                for (int i = 6; i < 17; i++)
                {
                    ((Button*)((LevelEditor *)self->mUserPtr)->UIelements[i])->SetSpriteSourceOffset(
                        (Vec2(0, 14) - ((LevelEditor *)self->mUserPtr)->grid.mBiomeOffset) * 16);
                }
                ((LevelEditor *)self->mUserPtr)->grid.mBiomeOffset = Vec2{0, 14};
                for (int i = 0; i < gridWidth; i++)
                {
                    for (int j = 0; j < gridHeight; j++)
                    {
                        ((LevelEditor *)self->mUserPtr)->grid.UpdateSprite(Vec2(i, j));
                    }
                }
            },
            GameSounds::EventSound,
            Color{0, 0, 0, 0},
            Sprite({240, 240, 32, 32},tileSet, {0, 0}), this, Sprite({240, 240, 32, 32},tileSet, {0, 0}), 
            Sprite({240, 240, 32, 32},tileSet, {0, 0}), false});


        UIelements.push_back(new Button{
            (collision::Box){1640, 100, 80, 80}, 
            [](Button *self){
                for (int i = 6; i < 17; i++)
                {
                    ((Button*)((LevelEditor *)self->mUserPtr)->UIelements[i])->SetSpriteSourceOffset(
                        (Vec2(18, 0) - ((LevelEditor *)self->mUserPtr)->grid.mBiomeOffset) * 16);
                }
                ((LevelEditor *)self->mUserPtr)->grid.mBiomeOffset = Vec2{18, 0};
                for (int i = 0; i < gridWidth; i++)
                {
                    for (int j = 0; j < gridHeight; j++)
                    {
                        ((LevelEditor *)self->mUserPtr)->grid.UpdateSprite(Vec2(i, j));
                    }
                }
            },
            GameSounds::EventSound,
            Color{0, 0, 0, 0},
            Sprite({528, 16, 32, 32},tileSet, {0, 0}), this, Sprite({528, 16, 32, 32},tileSet, {0, 0}), 
            Sprite({528, 16, 32, 32},tileSet, {0, 0}), false});


        UIelements.push_back(new Button{
            (collision::Box){1640, 200, 80, 80}, 
            [](Button *self){
                for (int i = 6; i < 17; i++)
                {
                    ((Button*)((LevelEditor *)self->mUserPtr)->UIelements[i])->SetSpriteSourceOffset(
                        (Vec2(18, 7) - ((LevelEditor *)self->mUserPtr)->grid.mBiomeOffset) * 16);
                }
                ((LevelEditor *)self->mUserPtr)->grid.mBiomeOffset = Vec2{18, 7};
                for (int i = 0; i < gridWidth; i++)
                {
                    for (int j = 0; j < gridHeight; j++)
                    {
                        ((LevelEditor *)self->mUserPtr)->grid.UpdateSprite(Vec2(i, j));
                    }
                }
            },
            GameSounds::EventSound,
            Color{0, 0, 0, 0},
            Sprite({528, 128, 32, 32},tileSet, {0, 0}), this, Sprite({528, 128, 32, 32},tileSet, {0, 0}), 
            Sprite({528, 128, 32, 32},tileSet, {0, 0}), false});


        UIelements.push_back(new Button{
            (collision::Box){1640, 300, 80, 80}, 
            [](Button *self){
                for (int i = 6; i < 17; i++)
                {
                    ((Button*)((LevelEditor *)self->mUserPtr)->UIelements[i])->SetSpriteSourceOffset(
                        (Vec2(18, 14) - ((LevelEditor *)self->mUserPtr)->grid.mBiomeOffset) * 16);
                }
                ((LevelEditor *)self->mUserPtr)->grid.mBiomeOffset = Vec2{18, 14};
                for (int i = 0; i < gridWidth; i++)
                {
                    for (int j = 0; j < gridHeight; j++)
                    {
                        ((LevelEditor *)self->mUserPtr)->grid.UpdateSprite(Vec2(i, j));
                    }
                }
            },
            GameSounds::EventSound,
            Color{0, 0, 0, 0},
            Sprite({528, 240, 32, 32},tileSet, {0, 0}), this, Sprite({528, 240, 32, 32},tileSet, {0, 0}), 
            Sprite({528, 240, 32, 32},tileSet, {0, 0}), false});
}

void LevelEditor::InitElementButton()
{
    UIelements.push_back(new Button{
            (collision::Box){1540, 530, 50, 50}, 
            [](Button *self){
                ((LevelEditor*)self->mUserPtr)->editionMode = EM_MAP;
                ((LevelEditor *)self->mUserPtr)->selected = EL_ROAD;
            },
            GameSounds::EventSound,
            Color{0, 0, 0, 0},
            Sprite({48 + grid.mBiomeOffset.x * 16, 48 + grid.mBiomeOffset.y * 16, 16, 16}, tileSet, {0, 0}), this,
             Sprite({48 + grid.mBiomeOffset.x * 16, 48 + grid.mBiomeOffset.y * 16, 16, 16},tileSet, {0, 0}), 
            Sprite({48 + grid.mBiomeOffset.x * 16, 48 + grid.mBiomeOffset.y * 16, 16, 16}, tileSet, {0, 0}), false});

    UIelements.push_back(new Button{
        (collision::Box){1540, 450, 50, 50}, 
        [](Button *self){
            ((LevelEditor*)self->mUserPtr)->editionMode = EM_MAP;
            ((LevelEditor *)self->mUserPtr)->selected = EL_BUSH1;
        },
        GameSounds::EventSound,
        Color{255, 255, 255, 150},
        Sprite(Vec2{9, 4} + grid.mBiomeOffset, tileSet, {36, 21}, {0, 0}), this,
            Sprite(Vec2{9, 4} + grid.mBiomeOffset, tileSet, {36, 21}, {0, 0}), 
        Sprite(Vec2{9, 4} + grid.mBiomeOffset, tileSet, {36, 21}, {0, 0}), false});

    UIelements.push_back(new Button{
        (collision::Box){1620, 450, 50, 50}, 
        [](Button *self){
            ((LevelEditor*)self->mUserPtr)->editionMode = EM_MAP;
            ((LevelEditor *)self->mUserPtr)->selected = EL_BUSH2;
        },
        GameSounds::EventSound,
        Color{255, 255, 255, 150},
        Sprite(Vec2{10, 4} + grid.mBiomeOffset, tileSet, {36, 21}, {0, 0}), this,
            Sprite(Vec2{10, 4} + grid.mBiomeOffset, tileSet, {36, 21}, {0, 0}), 
        Sprite(Vec2{10, 4} + grid.mBiomeOffset, tileSet, {36, 21}, {0, 0}), false});

    UIelements.push_back(new Button{
        (collision::Box){1620, 530, 50, 50}, 
        [](Button *self){
            ((LevelEditor*)self->mUserPtr)->editionMode = EM_MAP;
            ((LevelEditor *)self->mUserPtr)->selected = EL_BUSH3;
        },
        GameSounds::EventSound,
        Color{255, 255, 255, 150},
        Sprite(Vec2{11, 4} + grid.mBiomeOffset, tileSet, {36, 21}, {0, 0}), this,
            Sprite(Vec2{11, 4} + grid.mBiomeOffset, tileSet, {36, 21}, {0, 0}), 
        Sprite(Vec2{11, 4} + grid.mBiomeOffset, tileSet, {36, 21}, {0, 0}), false});

    UIelements.push_back(new Button{
        (collision::Box){1700, 450, 50, 50}, 
        [](Button *self){
            ((LevelEditor*)self->mUserPtr)->editionMode = EM_MAP;
            ((LevelEditor *)self->mUserPtr)->selected = EL_BUSH4;
        },
        GameSounds::EventSound,
        Color{255, 255, 255, 150},
        Sprite(Vec2{12, 4} + grid.mBiomeOffset, tileSet, {36, 21}, {0, 0}), this,
            Sprite(Vec2{12, 4} + grid.mBiomeOffset, tileSet, {36, 21}, {0, 0}), 
        Sprite(Vec2{12, 4} + grid.mBiomeOffset, tileSet, {36, 21}, {0, 0}), false});

    UIelements.push_back(new Button{
        (collision::Box){1700, 530, 50, 50}, 
        [](Button *self){
            ((LevelEditor*)self->mUserPtr)->editionMode = EM_MAP;
            ((LevelEditor *)self->mUserPtr)->selected = EL_BUSH5;
        },
        GameSounds::EventSound,
        Color{255, 255, 255, 150},
        Sprite(Vec2{13, 4} + grid.mBiomeOffset, tileSet, {36, 21}, {0, 0}), this,
            Sprite(Vec2{13, 4} + grid.mBiomeOffset, tileSet, {36, 21}, {0, 0}), 
        Sprite(Vec2{13, 4} + grid.mBiomeOffset, tileSet, {36, 21}, {0, 0}), false});

    UIelements.push_back(new Button{
        (collision::Box){1540, 610, 50, 50}, 
        [](Button *self){
            ((LevelEditor*)self->mUserPtr)->editionMode = EM_MAP;
            ((LevelEditor *)self->mUserPtr)->selected = EL_BUSH6;
        },
        GameSounds::EventSound,
        Color{255, 255, 255, 150},
        Sprite(Vec2{14, 4} + grid.mBiomeOffset, tileSet, {36, 21}, {0, 0}), this,
            Sprite(Vec2{14, 4} + grid.mBiomeOffset, tileSet, {36, 21}, {0, 0}), 
        Sprite(Vec2{14, 4} + grid.mBiomeOffset, tileSet, {36, 21}, {0, 0}), false});
    
    UIelements.push_back(new Button{
        (collision::Box){1700, 610, 50, 50}, 
        [](Button *self){
            ((LevelEditor*)self->mUserPtr)->editionMode = EM_MAP;
            ((LevelEditor *)self->mUserPtr)->selected = EL_BUSH7;
        },
        GameSounds::EventSound,
        Color{255, 255, 255, 150},
        Sprite(Vec2{15, 4} + grid.mBiomeOffset, tileSet, {36, 21}, {0, 0}), this,
            Sprite(Vec2{15, 4} + grid.mBiomeOffset, tileSet, {36, 21}, {0, 0}), 
        Sprite(Vec2{15, 4} + grid.mBiomeOffset, tileSet, {36, 21}, {0, 0}), false});

    UIelements.push_back(new Button{
        (collision::Box){1620, 610, 50, 50}, 
        [](Button *self){
            ((LevelEditor*)self->mUserPtr)->editionMode = EM_MAP;
            ((LevelEditor *)self->mUserPtr)->selected = EL_BUSH8;
        },
        GameSounds::EventSound,
        Color{255, 255, 255, 150},
        Sprite(Vec2{16, 4} + grid.mBiomeOffset, tileSet, {36, 21}, {0, 0}), this,
            Sprite(Vec2{16, 4} + grid.mBiomeOffset, tileSet, {36, 21}, {0, 0}), 
        Sprite(Vec2{16, 4} + grid.mBiomeOffset, tileSet, {36, 21}, {0, 0}), false});

    UIelements.push_back(new Button{
        (collision::Box){1540, 690, 50, 50}, 
        [](Button *self){
            ((LevelEditor*)self->mUserPtr)->editionMode = EM_MAP;
            ((LevelEditor *)self->mUserPtr)->selected = EL_BUSH9;
        },
        GameSounds::EventSound,
        Color{255, 255, 255, 150},
        Sprite(Vec2{17, 4} + grid.mBiomeOffset, tileSet, {36, 21}, {0, 0}), this,
            Sprite(Vec2{17, 4} + grid.mBiomeOffset, tileSet, {36, 21}, {0, 0}), 
        Sprite(Vec2{17, 4} + grid.mBiomeOffset, tileSet, {36, 21}, {0, 0}), false});

    UIelements.push_back(new Button{
        (collision::Box){1620, 690, 50, 50}, 
        [](Button *self){
            ((LevelEditor*)self->mUserPtr)->editionMode = EM_MAP;
            ((LevelEditor *)self->mUserPtr)->selected = EL_TREE;
        },
        GameSounds::EventSound,
        Color{255, 255, 255, 150},
        Sprite(Vec2{15, 1} + grid.mBiomeOffset, tileSet, {36, 21}, {0, 0}, 2), this,
            Sprite(Vec2{15, 1} + grid.mBiomeOffset, tileSet, {36, 21}, {0, 0}, 2), 
        Sprite(Vec2{15, 1} + grid.mBiomeOffset, tileSet, {36, 21}, {0, 0}, 2), false});

    UIelements.push_back(new Button{
            collision::Box{20, 880, 200, 40},
            [](Button *self)
            {
                for (int i = 0; i < 4; i++)
                {
                    ((LevelEditor*)self->mUserPtr)->grid.paths[i].clear();
                }
                
                for (int i = 0; i < (int)((LevelEditor*)self->mUserPtr)->grid.waveList.size(); i++)
                {
                    ((LevelEditor*)self->mUserPtr)->grid.waveList[i].pathToFollow.clear();
                    ((LevelEditor*)self->mUserPtr)->grid.waveList[i].timeBeforeNextEnemy.clear();
                    ((LevelEditor*)self->mUserPtr)->grid.waveList[i].Wave.clear();
                    for(Button* curr : ((LevelEditor*)self->mUserPtr)->enemyButtons[i])
                    {
                        delete curr;
                    }
                    ((LevelEditor*)self->mUserPtr)->enemyButtons[i].clear();
                }
                ((LevelEditor*)self->mUserPtr)->enemyButtons.clear();
                ((LevelEditor*)self->mUserPtr)->grid.waveList.clear();
                for (int i = 0; i < gridWidth; i++)
                {
                    for (int j = 0; j < gridHeight; j++)
                    {
                       ((LevelEditor*)self->mUserPtr)->grid.dataGrid[i][j] = 0;
                    }
                }
                for (int i = 0; i < gridWidth; i++)
                {
                    for (int j = 0; j < gridHeight; j++)
                    {
                        ((LevelEditor*)self->mUserPtr)->grid.UpdateSprite(Vec2(i, j));
                    }
                }
                if(((LevelEditor*)self->mUserPtr)->grid.waveList.size() == 0)
                {
                    ((LevelEditor*)self->mUserPtr)->grid.waveList.push_back((EnemyWaveData){});
                    ((LevelEditor*)self->mUserPtr)->enemyButtons.push_back({});
                }
            },
            GameSounds::EventSound,
            BLUE, "Clear Level", this});
}

void LevelEditor::InitPathButton()
{
     UIelements.push_back(new Button{
            collision::Box{1540, 800, 100, 30},
            [](Button *self)
            {
                ((LevelEditor*)self->mUserPtr)->editionMode = EM_PATH;
                ((LevelEditor*)self->mUserPtr)->currentPathEdit = 0;
            },
            GameSounds::EventSound,
            RED, "Path 1", this});

        UIelements.push_back(new Button{
            collision::Box{1660, 800, 100, 30},
            [](Button *self)
            {
                ((LevelEditor*)self->mUserPtr)->editionMode = EM_PATH;
                ((LevelEditor*)self->mUserPtr)->currentPathEdit = 1;
            },
            GameSounds::EventSound,
            RED, "Path 2", this});

        UIelements.push_back(new Button{
            collision::Box{1540, 850, 100, 30},
            [](Button *self)
            {
                ((LevelEditor*)self->mUserPtr)->editionMode = EM_PATH;
                ((LevelEditor*)self->mUserPtr)->currentPathEdit = 2;
            },
            GameSounds::EventSound,
            RED, "Path 3", this});

        UIelements.push_back(new Button{
            collision::Box{1660, 850, 100, 30},
            [](Button *self)
            {
                ((LevelEditor*)self->mUserPtr)->editionMode = EM_PATH;
                ((LevelEditor*)self->mUserPtr)->currentPathEdit = 3;
            },
            GameSounds::EventSound,
            RED, "Path 4", this});
}

void LevelEditor::InitWaveButton()
{
    UIelements.push_back(new Button{
            collision::Box{240, 880, 180, 40},
            [](Button *self)
            {
                ((LevelEditor*)self->mUserPtr)->AddEnemy(ET_SLIME);
            },
            GameSounds::EventSound,
            BLUE, "Add Enemy", this});

        UIelements.push_back(new Button{
            collision::Box{440, 880, 160, 40},
            [](Button *self)
            {
                ((LevelEditor*)self->mUserPtr)->grid.waveList.push_back((EnemyWaveData){});
                ((LevelEditor*)self->mUserPtr)->enemyButtons.push_back({});
            },
            GameSounds::EventSound,
            BLUE, "New Wave", this});

        UIelements.push_back(new Button{
            collision::Box{640, 880, 210, 40},
            [](Button *self)
            {

                if(((LevelEditor*)self->mUserPtr)->grid.waveList.size() > 1)
                {
                    
                    ((LevelEditor*)self->mUserPtr)->grid.waveList.pop_back();
                    for (Button* curr : ((LevelEditor*)self->mUserPtr)->enemyButtons[((LevelEditor*)self->mUserPtr)->enemyButtons.size() - 1])
                    {
                        delete curr;
                    }
                    
                    ((LevelEditor*)self->mUserPtr)->enemyButtons.pop_back();
                    
                    if((size_t)((LevelEditor*)self->mUserPtr)->currentWaveEdit == ((LevelEditor*)self->mUserPtr)->grid.waveList.size())
                    {
                        ((LevelEditor*)self->mUserPtr)->currentWaveEdit  = Clamp(((LevelEditor*)self->mUserPtr)->currentWaveEdit - 1, 0, 999);
                    }
                }
            },
            GameSounds::EventSound,
            BLUE, "Delete Wave", this});

        UIelements.push_back(new Button{(collision::Box){890, 880, 40, 40}, 
        [](Button *self)
        {
            ((LevelEditor*)self->mUserPtr)->currentWaveEdit =
                Clamp( ((LevelEditor*)self->mUserPtr)->currentWaveEdit - 1, 0, 999);
        },
        GameSounds::EventSound,Color{255, 255, 255, 150},
        Sprite({2, 0}, slimeAnim, {4, 4}, {0, 0}), this, Sprite({2, 3}, slimeAnim, {4, 4}, {0, 0}), 
        Sprite({2, 1}, slimeAnim, {4, 4}, {0, 0}), false});

        UIelements.push_back(new Button{
            (collision::Box){1130, 880, 40, 40}, 
            [](Button *self){
                ((LevelEditor*)self->mUserPtr)->currentWaveEdit =
                 Clamp( ((LevelEditor*)self->mUserPtr)->currentWaveEdit + 1,
                  0, ((LevelEditor*)self->mUserPtr)->grid.waveList.size() - 1);
            },
            GameSounds::EventSound,
            Color{255, 255, 255, 150},
            Sprite({3, 0}, slimeAnim, {4, 4}, {0, 0}), this,
             Sprite({3, 3}, slimeAnim, {4, 4}, {0, 0}), 
            Sprite({3, 1}, slimeAnim, {4, 4}, {0, 0}), false});
}

void LevelEditor::Save() 
{
    for (int i = 0; i < 4; i++)
    {
        if(!IsPathValid(i))
        {
            popUpTime = 2;
            popUpMessage = TextFormat("Path %d is not valid", i + 1);
            return;
        }
    }
    

    for (int i = 0; i < 4; i++)
    {
        grid.pathSize[i] = grid.paths[i].size();
    }
    
    FILE* file = fopen(mCurrentFile.c_str(), "wb");
    if(file)
    {
        grid.waveCount = grid.waveList.size();
        fwrite(&grid.dataGrid, sizeof(int[gridWidth][gridHeight]), 1, file);
        fwrite(&grid.mBiomeOffset, sizeof(Vec2), 1, file);
        fwrite(&grid.pathSize, sizeof(int), 4, file);
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < grid.pathSize[i]; j++)
            {
                fwrite(&grid.paths[i][j], sizeof(Vec2), 1, file);
            }
            
        }
        fwrite(&grid.waveCount, sizeof(int), 1, file);
        for (int i = 0; i < grid.waveCount; i++)
        {
            grid.waveList[i].wavesize = grid.waveList[i].Wave.size();
            fwrite(&grid.waveList[i].wavesize, sizeof(int), 1, file);
            for (int j = 0; j < grid.waveList[i].wavesize; j++)
            {
                fwrite(&grid.waveList[i].Wave[j], sizeof(EnemyType), 1, file);
                fwrite(&grid.waveList[i].timeBeforeNextEnemy[j], sizeof(float), 1, file);
                fwrite(&grid.waveList[i].pathToFollow[j], sizeof(int), 1, file);
            }
        }
        fclose(file);
    }
}

void LevelEditor::Load()
{
    Vec2 oldOffset = grid.mBiomeOffset;
    for (int i = 0; i < 4; i++)
    {
        grid.paths[i].clear();
    }
    
    for (int i = 0; i < (int)grid.waveList.size(); i++)
    {
        grid.waveList[i].pathToFollow.clear();
        grid.waveList[i].timeBeforeNextEnemy.clear();
        grid.waveList[i].Wave.clear();
        for(Button* curr : enemyButtons[i])
        {
            delete curr;
        }
        enemyButtons[i].clear();
    }
    enemyButtons.clear();
    grid.waveList.clear();
    FILE* file = fopen(mCurrentFile.c_str(), "rb");
    if(file)
    {
        fread(&grid.dataGrid, sizeof(int[gridWidth][gridHeight]), 1, file);
        fread(&grid.mBiomeOffset, sizeof(Vec2), 1, file);
        fread(&grid.pathSize, sizeof(int), 4, file);
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < grid.pathSize[i]; j++)
            {
                Vec2 wayPoint;
                fread(&wayPoint, sizeof(Vec2), 1, file);
                grid.paths[i].push_back(wayPoint);
            }
            
        }
        fread(&grid.waveCount, sizeof(int), 1, file);
        for (int i = 0; i < grid.waveCount; i++)
        {
            currentWaveEdit = i;
            grid.waveList.push_back({});
            enemyButtons.push_back({});
            fread(&grid.waveList[i].wavesize, sizeof(int), 1, file);
            for (int j = 0; j < grid.waveList[i].wavesize; j++)
            {
                EnemyType newEnemy;
                float timeBeforeNext;
                int pathToFollow;
                fread(&newEnemy, sizeof(EnemyType), 1, file);
                fread(&timeBeforeNext, sizeof(float), 1, file);
                fread(&pathToFollow, sizeof(int), 1, file);
                AddEnemy(newEnemy, timeBeforeNext, pathToFollow);
            }
            
        }
        
        fclose(file);

        for (int i = 0; i < gridWidth; i++)
        {
            for (int j = 0; j < gridHeight; j++)
            {
                grid.UpdateSprite(Vec2(i, j));
            }
        }
        if(UIelements.size()>= 18)
        {
            for (int i = 6; i < 17; i++)
            {
                ((Button*)UIelements[i])->SetSpriteSourceOffset((grid.mBiomeOffset - oldOffset) * 16);
            }
        }
    }
}