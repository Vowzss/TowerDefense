#pragma once

#include <string.h>

#include "menu.hpp"

#include "../System/scene.hpp"

#include "../levelEditor/levelEditor.hpp"

#include "../gameScenes/menu.hpp"

#include "../gameManager/gameSounds.hpp"
#include "../gameManager/gameTextures.hpp"

class LevelSelect : public Scene
{
    public:
        bool ShowInfoBox = false;
        int LevelSelected;
        std::string LevelSelectedNumber[12];
        std::string LevelSelectedName[12];

        myMath::Vec2 LevelTextPosition;

        Grid levelToLoad;
        void Start() override;
        void Update() override;
        void Render() override;
        void LevelMenu();

        void LoadLevelData(std::string FileName);
        void CheckLevelToSetPos();
        
        void InfoBoxManager(int _levelIndex);
        void CheckIfDisplayInfoBox();
        void InfoBoxButtons();

        void SetTextForLevelSelected();
};
