#pragma once
#include "../System/scene.hpp"
#include "vector"
#include "../gameManager/gameEnemies.hpp"
#include "../gameManager/gameTextures.hpp"
#include "../gameManager/gameSounds.hpp"

class Grid
{
    public:
        int pathSize[4];
        std::vector<myMath::Vec2> paths[4];
        int waveCount;
        std::vector<EnemyWaveData> waveList;
        myMath::Vec2 mBiomeOffset;
        Grid() {};
        int dataGrid[gridWidth][gridHeight];
        Sprite spriteGrid[gridWidth][gridHeight];

        void UpdateSprite(myMath::Vec2 pos, bool randomizeGrass = true);
        void PutTree(myMath::Vec2 pos);
        int GridCell(myMath::Vec2 pos);

};

