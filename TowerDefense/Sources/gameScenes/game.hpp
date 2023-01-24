#pragma once

#include <vector>
#include <iostream>
#include <string.h>

#include "gameWinner.hpp"
#include "gameSelector.hpp"

#include "../gameManager/gameSounds.hpp"
#include "../gameManager/gameWaves.hpp"
#include "../gameManager/gameTextures.hpp"
#include "../gameManager/gameEnemies.hpp"
#include "../gameManager/gameTowers.hpp"
#include "../gameManager/gamePlayer.hpp"

#include "../System/scene.hpp"



class Game : public Scene
{
    private:
        const TowerData::TowerStat* mSelectedTowerType;
        std::vector<Tower*> mTowerlist;

        static std::vector<myMath::Vec2> sPath;

        static Player* sPlayer;

        myMath::Vec2 offset;

        Tower mTowerSelected = Tower({0,0}, GameSounds::FlameShotSound, TowerData::Common);
        Tower* mPtrTowerSelected = nullptr;

        int mItStatTower[8];


    public:

        static EnemyWave* sWave;
        static Grid sGridData;

        static float sTimeScale;
        static float sActualVolume;
        static float sBaseVolume;

        Game(Grid _gridData)
        {
            sGridData = _gridData;
        }
        ~Game();

        void Start() override;
        void Update() override;
        void Render() override;
        void GetInput() override;

        void LoadTextureGame();
        void InitButton();
        void InitText();

        bool CheckAvailableTiles(myMath::Vec2 TouretSize);

        static std::vector<myMath::Vec2> GetPath(int index);
        static std::vector<Enemy*> GetEnemies();
        static Player* GetPlayer();

        std::vector<Tower*> GetTowers() const;

        void ActivePauseButton();
        static void GamePause();
        static void GameAcceleration();

        static void CheckAndSetVolume(float gameNewVolume);

        void ActiveStatTower();
        void CheckStatTowerDisplay();
        Tower* FindTowerSelected();
        int FindButtonSelected(Tower _tower);

        void UpgradeTowerSelected();
        void SellTowerSelected();
        void CheckForWin();
};
