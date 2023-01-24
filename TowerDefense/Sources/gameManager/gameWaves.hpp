#pragma once

#include <vector>

#include "../gameManager/gameEnemies.hpp"
#include "../System/scene.hpp"

class EnemyWave
{
    private:
        long unsigned int mEnemiesNum = 0;

    public:
        EnemyWave(std::vector<EnemyWaveData> data);
        ~EnemyWave();

        void Start();
        void Update(float _timeScale);
        void Render();
        
        void SpawnEnemiesWave();
        
        float timeBeforeNextEnemy = 2;
        long unsigned int waveIndex = 0;
        std::vector<EnemyWaveData> waveData;

        static std::vector<Enemy*> sEnemies;
        static std::vector<Enemy*> GetEnemies();
};