#pragma once

#include <vector>
#include <list>

#include "gameEnemies.hpp"
#include "gameWaves.hpp"
#include "gameSounds.hpp"

#include "../System/scene.hpp"
#include "../System/UIElement.hpp"
#include "../Libs/myMathLib.hpp"

enum TowerType 
{
    TT_NULL,
    TT_COMMON,
    TT_CRYO,
    TT_BOMB,
    TT_STATUE,
};

namespace TowerData
{
struct TowerStat
{
    char name[22];
    myMath::Vec2 tilePos;
    Texture2D* texture;
    myMath::Vec2 tileSetSize;
    myMath::Vec2 origin;
    int towerSize;
    
    float attackRate = 0.f;
    int damage = 0;
    int cost = 0;
    int range = 0;
    TowerType type;
};

const TowerStat Common = {"Common",
                        myMath::Vec2(19, 10), &GameTextures::enemySet, {23, 13}, {20, 20}, 1,
                            1.5f, 30, 60, 200, TT_COMMON};
const TowerStat Cryo = {"Cryo",
                        myMath::Vec2(20, 9), &GameTextures::enemySet, {23, 13}, {20, 20}, 1,
                        10, 1, 100, 150, TT_CRYO};
const TowerStat Bomb = {"Bomb",
                        myMath::Vec2(22, 8), &GameTextures::enemySet, {23, 13}, {20, 20}, 1,
                        0.7f, 50, 150, 250, TT_BOMB};
const TowerStat Statue = {"Statue",
                        myMath::Vec2(3, 19), &GameTextures::TowerSet, {29, 23}, {40, 40}, 2,
                        0.5f, 250, 250, 350, TT_STATUE};
}

class Projectile
{
    protected:
        float damageRadius;

    public:
        Enemy* target = nullptr;
        int damage;
        myMath::Vec2 position;

        Projectile(Enemy* _target, int _damage, myMath::Vec2 _position, float _radius = 0);
        virtual ~Projectile() {};

        virtual void UpdateAndDraw() {};

        void SetDamageRadius(float _damageRadius);
};

class FireShot : public Projectile
{
    private:
        float mSpeed = 0.f;
        float mRotation = 0.f;

    public:
        Sprite sprite;
        myMath::Vec2 destination;

        FireShot(Sprite _sprite, float _speed, Enemy* _target, int _damage, myMath::Vec2 pos, float radius = 0);
        ~FireShot() override {};

        void UpdateAndDraw() override;
};

class CryoShot : public Projectile
{
    public:
        CryoShot(Enemy* _target, int _damage, myMath::Vec2 _pos, float _radius = 0);
        ~CryoShot() override {}; 

        void UpdateAndDraw() override;
};

class BombShot : public Projectile
{
    private:
        float mSpeed = 0.f;
        float mRotation = 0.f;

    public:
        Sprite sprite;
        myMath::Vec2 destination;
        myMath::Vec2 towerPos;

        BombShot(Sprite _sprite, float _speed, Enemy* _target, int _damage, myMath::Vec2 _pos, float _radius, myMath::Vec2 _towerPos);
        ~BombShot() override {}; 

        void UpdateAndDraw() override;
};

class StatueShot : public Projectile
{
    private:
        float mSpeed = 0.f;
        float mRotation = 0.f;

    public:
        Sprite sprite;
        myMath::Vec2 destination;

        StatueShot(Sprite _sprite, float _speed, Enemy* _target, int _damage, myMath::Vec2 pos, float radius = 0);

        void UpdateAndDraw() override;
};

class Tower
{
    protected:
        Sprite mSprite;
        myMath::Vec2 mPosition = {};
        Sound mSound;

        float mRotation = 0.f;
        std::vector<Enemy> mEnemyInRange;
        Enemy* mEnemyToFollow;
        float mTime = 0.f;
        Projectile* mProjectile = nullptr;

    public:
        float mAttackSpeed = 0.f;
        int mDamage = 0;
        int mCost = 0;
        int mRange = 0;
        int mLevel = 1;
        int size;
        TowerType mType;
        bool isTowerToSell = false;

        Tower(myMath::Vec2 _position, Sound _sound, TowerData::TowerStat _stat);
        virtual ~Tower() {};

        virtual void SelectTarget();
        virtual void UpdateAndDraw();

        virtual void UpgradeTower();

        virtual myMath::Vec2 GetPosition() const;
        float GetAttackSpeed() const;
        int GetDamage() const;
        int GetCost() const;
        int GetRange() const;
};

class CommonTower : public Tower
{
    public:
        CommonTower(myMath::Vec2 _position, Sound _sound);
        ~CommonTower() override {delete mProjectile;}; 

        void UpdateAndDraw() override;
        void UpgradeTower() override;
};

class CryoTower : public Tower
{
    public:
        CryoTower(myMath::Vec2 _position, Sound _sound);
        ~CryoTower() override {delete mProjectile;};

        void UpdateAndDraw() override; 
        void UpgradeTower() override; 
};

class BombTower : public Tower
{
    private:
        float mRadiusExplosion = 90.f;

    public:
        BombTower(myMath::Vec2 _position, Sound _sound);
        ~BombTower() override {delete mProjectile;};

        void UpdateAndDraw() override; 
        void UpgradeTower() override; 
};

class StatueTower : public Tower
{
    private:
        float mRadiusExplosion = 90.f;

    public:
        StatueTower(myMath::Vec2 _position, Sound _sound);
        ~StatueTower() override {delete mProjectile;};

        void UpdateAndDraw() override; 
        void UpgradeTower() override; 
};