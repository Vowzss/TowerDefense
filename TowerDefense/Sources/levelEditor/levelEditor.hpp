#pragma once

#include <vector>

#include "../System/scene.hpp"

#include "../gameManager/gameEnemies.hpp"
#include "../gameManager/gameTextures.hpp"
#include "../gameManager/gameSounds.hpp"
#include "grid.hpp"

enum Element
{
    EL_TERRAIN,
    EL_ROAD,
    EL_BUSH1,
    EL_BUSH2,
    EL_BUSH3,
    EL_BUSH4,
    EL_BUSH5,
    EL_BUSH6,
    EL_BUSH7,
    EL_BUSH8,
    EL_BUSH9,
    EL_TREE
};

enum EditionMode
{
    EM_MAP,
    EM_PATH
};



class LevelEditor : public Scene
{
    private:
        std::string mCurrentFile;
        std::string popUpMessage;
        float popUpTime;


    public:
        Element selected = EL_ROAD;
        EditionMode editionMode;
        Grid grid;
        myMath::Vec2 waveEditorParent;
        int currentPathEdit = 0;
        int currentWaveEdit = 0;

        std::vector<std::vector<Button*>> enemyButtons;

        bool debug = false;

        ~LevelEditor();

        void Start() override;
        void Update() override;
        void Render() override;
        void GetInput() override;

        void DisplayGrid();
        void DisplayPath();
        void DisplayWave();
        
        void InitNavigationButton();
        void InitThemeButton();
        void InitElementButton();
        void InitPathButton();
        void InitWaveButton();

        myMath::Vec2 GetMouseInGridPos();
        bool IsPathValid(int i);
        void AddEnemy(EnemyType newEnemy, float _time = 0, int _path = 0);
        void DeleteEnemy(int index);

        void Save();
        void Load();
};