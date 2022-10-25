#include "gameWaves.hpp"
#include "../gameScenes/game.hpp"

using namespace myMath;

EnemyWave::EnemyWave(std::vector<EnemyWaveData> data)
: waveData(data)
{}


EnemyWave::~EnemyWave()
{
    for(Enemy* curr : sEnemies)
    {
        delete curr;
    }
    sEnemies.clear();
}

void EnemyWave::Start()
{
    
}

void EnemyWave::SpawnEnemiesWave()
{
    if(mEnemiesNum < waveData[waveIndex].Wave.size()) 
    {
        switch(waveData[waveIndex].Wave.at(mEnemiesNum))
        {
            case (ET_SLIME) : 
                sEnemies.push_back(new CommonEnemy(Game::GetPath(waveData[waveIndex].pathToFollow[mEnemiesNum])[0] *
                 40, sEnemies.size(),
                 waveData[waveIndex].pathToFollow[mEnemiesNum], EnemyData::Slime));
                break;
            case (ET_SPIRIT) : 
                sEnemies.push_back(new HealerEnemy(Game::GetPath(waveData[waveIndex].pathToFollow[mEnemiesNum])[0] *
                 40, sEnemies.size(),
                 waveData[waveIndex].pathToFollow[mEnemiesNum], EnemyData::Spirit));
                break;
            case (ET_CYCLOPE) : 
                sEnemies.push_back(new CommonEnemy(Game::GetPath(waveData[waveIndex].pathToFollow[mEnemiesNum])[0] *
                 40, sEnemies.size(),
                 waveData[waveIndex].pathToFollow[mEnemiesNum], EnemyData::Cyclope));
                break;
            case (ET_SKELETON) : 
                sEnemies.push_back(new CommonEnemy(Game::GetPath(waveData[waveIndex].pathToFollow[mEnemiesNum])[0] *
                 40, sEnemies.size(),
                 waveData[waveIndex].pathToFollow[mEnemiesNum], EnemyData::Skeleton));
                break;
            case (ET_BEAST) : 
                sEnemies.push_back(new CommonEnemy(Game::GetPath(waveData[waveIndex].pathToFollow[mEnemiesNum])[0] *
                 40, sEnemies.size(),
                 waveData[waveIndex].pathToFollow[mEnemiesNum], EnemyData::Beast));
                break;
            case (ET_KNIGHT) : 
                sEnemies.push_back(new CommonEnemy(Game::GetPath(waveData[waveIndex].pathToFollow[mEnemiesNum])[0] *
                 40, sEnemies.size(),
                 waveData[waveIndex].pathToFollow[mEnemiesNum], EnemyData::Knight));
                break;
            break;
        }
        
        mEnemiesNum++;
        

    }
    else
    {
        mEnemiesNum = 0;
        timeBeforeNextEnemy = 10.f;
        waveData[waveIndex].waveIndex++;
        waveIndex++;
        
    }
}

void EnemyWave::Update(float _timeScale)
{
    if (timeBeforeNextEnemy <= 0)
    {
        if(mEnemiesNum != waveData[waveIndex].Wave.size() && waveIndex < waveData.size())
            timeBeforeNextEnemy = waveData[waveIndex].timeBeforeNextEnemy[mEnemiesNum] + 0.1f;
        if(waveIndex < waveData.size())
            SpawnEnemiesWave();
            
    }

    timeBeforeNextEnemy -= GetFrameTime() * _timeScale;
    DrawText(TextFormat("%.3f", timeBeforeNextEnemy), 30 , 60, 30, BLACK);
}

void EnemyWave::Render()
{
    for (int i = 0; i < (int)sEnemies.size(); ++i)
    {
        Enemy* enemy = sEnemies[i];
        enemy->UpdateAndDraw();
    }
}

std::vector<Enemy*> EnemyWave::GetEnemies()
{
    return sEnemies;
}