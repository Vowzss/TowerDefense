#pragma once

#include "gameTextures.hpp"
#include "gameSounds.hpp"

#include "../System/gameAnimator.hpp"
#include "../System/scene.hpp"
#include "../System/UIElement.hpp"

#include "../Libs/myMathLib.hpp"
#include "../Libs/myList.hpp"

enum EnemyType
{
    ET_SLIME,
    ET_SPIRIT,
    ET_CYCLOPE,
    ET_SKELETON,
    ET_BEAST,
    ET_KNIGHT
};

class EnemyWaveData
{
    public:
    int waveIndex;
    int wavesize;
    std::vector<EnemyType> Wave;
    std::vector<int> pathToFollow;
    std::vector<float> timeBeforeNextEnemy;

    EnemyWaveData(std::vector<EnemyType> _wave, std::vector<int> _pathToFollow, std::vector<float> _timeBeforeNextEnemy)
    : Wave(_wave)
    , pathToFollow(_pathToFollow)
    , timeBeforeNextEnemy(_timeBeforeNextEnemy)
    {
        wavesize = 0;
    };

    EnemyWaveData() {};
};

namespace EnemyData
{
struct EnemyStat
{
    char name[22];
    Texture2D* animation;

    float speed;
    int damage;
    int gain;
    int life;
};

const EnemyStat Spirit = {"Spirit", &GameTextures::spiritAnim,         60.f, 15, 15, 220};
const EnemyStat Slime = {"Slime", &GameTextures::slimeAnim,            112.f, 5, 10, 60};
const EnemyStat Skeleton = {"Skeleton", &GameTextures::skeletonAnim,   45.f, 20, 35, 640};
const EnemyStat Cyclope = {"Cyclope", &GameTextures::cyclopeAnim,      50.f, 35, 20, 270};
const EnemyStat Beast = {"Beast", &GameTextures::beastAnim,            60.f, 10, 40, 800};
const EnemyStat Knight = {"Knight", &GameTextures::KnightAnim,         62.f, 35 ,100, 1600};
};


enum StatusType 
{
    DT_POISON,
    DT_FREEZE
};

class Status
{
    public:
        StatusType status;
        float time = 0.f;
        float effectTime = 0.f;
        float effectRate = 0.f;

        Status(StatusType _status, float _time = 0, float _effect = 0);
        Status() {};

        bool operator==(Status _status)
        {
            return (status == _status.status);
        }
};

class Enemy
{
    private:
        void DrawHealthBar();
        void DebufEffect();
        float CalculSpeed();

    protected:
        Sprite mSprite;
        Animator mAnimator;
        myMath::Vec2 mPosition = {};

        float mSpeed = 0.f;
        int mDamage = 0;
        int mGain = 0;
        float mLife = 0.f;
        float mMaxLife = 0.f;

        long unsigned int sPathIndex = 1;
        int mListIndex = 0;

        float animationDamage = 0.f;
    public:
        myList::List<Status> debufList;
        int pathToFollow;

        Enemy(myMath::Vec2 _position, EnemyData::EnemyStat _enemyStat, int _path, int _listIndex = 0);
        virtual ~Enemy() {debufList.Clean();};

        virtual void UpdateAndDraw();

        void TakeDamage(float _damage);
        void HealEnemy(float _healing);

        myMath::Vec2 GetPos() const;
        int GetIndex() const;
        int GetPathIndex() const;
        int GetLife() const;

        void SetIndex(int _index);
};

class CommonEnemy : public Enemy
{
    public:
        CommonEnemy(myMath::Vec2 _position, int _listIndex, int _path, EnemyData::EnemyStat _stat);
        void UpdateAndDraw() override;
};

class HealerEnemy : public Enemy
{
    private:
        float mHeal = 25.0f;
        float mRange = 120.f;
        int mFarthestEnemy = -99999;
        int mCurr = 0;
        float mTime = 0.;
        float mHealSpeed = 1.f;
        Enemy* mEnemyToFollow;

    public:
        HealerEnemy(myMath::Vec2 _position, int _listIndex, int _path, EnemyData::EnemyStat _stat);

        void UpdateAndDraw() override;

        void CheckEnemiesForHealing();
        void Healing(Enemy* _target, float _healing);
};
