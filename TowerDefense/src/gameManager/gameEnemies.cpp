#include "gameWaves.hpp"
#include "../gameScenes/game.hpp"

using namespace collision;
using namespace myMath;
using namespace EnemyData;

std::vector<myMath::Vec2> Game::sPath = {};
std::vector<Enemy*> EnemyWave::sEnemies = {};
Player* Game::sPlayer = nullptr;

Status::Status(StatusType _status, float _time, float _effect)
: status(_status)
, time(_time)
, effectTime(_effect)
, effectRate(_effect)
{}


Enemy::Enemy(myMath::Vec2 _position, EnemyStat _enemyStat, int _path, int _listIndex)
: mSprite(Sprite())
, mAnimator(Animator(*_enemyStat.animation, 6, &mSprite, 3))
, mPosition(_position)
, mSpeed(_enemyStat.speed)
, mDamage(_enemyStat.damage)
, mGain(_enemyStat.gain)
, mLife(_enemyStat.life)
, mMaxLife(_enemyStat.life)
, mListIndex(_listIndex)
, pathToFollow(_path)
{
    float X = (Game::GetPath(pathToFollow).at(sPathIndex) * 40 - (mPosition)).x;
    float Y = (Game::GetPath(pathToFollow).at(sPathIndex) * 40 - (mPosition)).y;

    if(X > Y)
    {
        if(-X > Y)
        {
            mAnimator.currentAnimation = 1;
        }else
        {
            mAnimator.currentAnimation = 3;
        }
    }else
    {
        if(-X > Y)
        {
            mAnimator.currentAnimation = 2;
        }else
        {
            mAnimator.currentAnimation = 0;
        }
    }
}

void Enemy::DrawHealthBar()
{
    if(mLife < mMaxLife)
    {
        Color healthColor = GREEN;
        if(mLife < mMaxLife / 2)
            healthColor = YELLOW;
        if(mLife < mMaxLife / 4)
            healthColor = ORANGE;
        if(mLife < mMaxLife / 10)
            healthColor = RED;
        DrawRectangleLines(mPosition.x - 22, mPosition.y - 25, 40, 6, BLACK);
        DrawRectangleV((mPosition - Vec2{22, 25}).toVector2(),
        Vec2{(mLife * 40) / (float)mMaxLife, 6.f}.toVector2(), healthColor);
    }
}

void Enemy::DebufEffect()
{
    for (int i = 0; i < debufList.size; i++)
    {
        debufList[i]->time -= GetFrameTime() * Game::sTimeScale;
        debufList[i]->effectTime -= GetFrameTime() * Game::sTimeScale;
        if(debufList[i]->status == DT_POISON && debufList[i]->effectTime <= 0)
        {   
            TakeDamage((mMaxLife / 50) + 2);
            debufList[i]->effectTime = debufList[i]->effectRate;
        }
        if(debufList[i]->time <= 0)
            debufList.Remove(*debufList[i]);
    }
}

float Enemy::CalculSpeed()
{
    if(debufList.Contain(Status(DT_FREEZE)))
    {
        return mSpeed * 0.4f;
        mAnimator.animations[mAnimator.currentAnimation]->frameRate = 3;
    }
    else
    {
        return mSpeed;
        mAnimator.animations[mAnimator.currentAnimation]->frameRate = 6;
    }
}

void Enemy::UpdateAndDraw()
{
    float currSpeed = CalculSpeed();
    
    mAnimator.Update();
    if(animationDamage > 0)
    {
        animationDamage -= GetFrameTime() * Game::sTimeScale;
        mSprite.Draw(Box(mPosition, mPosition+(Vec2){40,40}), 0, (Color){255,100,100,255});
    }
    else
    {
        mSprite.Draw(Box(mPosition, mPosition+(Vec2){40,40}), 0);
    }
    mPosition += (Game::GetPath(pathToFollow).at(sPathIndex) * 40 - (mPosition)).Normalized().Normalized() * currSpeed * GetFrameTime() * Game::sTimeScale;

    DebufEffect();
    DrawHealthBar();

    if(Distance(mPosition, Game::GetPath(pathToFollow).at(sPathIndex) * 40) <= 3.0f) 
    {
        if(sPathIndex + 1 >= Game::GetPath(pathToFollow).size())
        {
            
            for (Enemy* curr : EnemyWave::GetEnemies())
            {
                if(curr->GetIndex() > mListIndex)
                    curr->SetIndex(curr->GetIndex() - 1);
            }
            Game::GetPlayer()->TakeDamage(mDamage);
            mLife = 0;
            return;
        }
        sPathIndex++;

        float X = (Game::GetPath(pathToFollow).at(sPathIndex) * 40 - (mPosition)).x;
        float Y = (Game::GetPath(pathToFollow).at(sPathIndex) * 40 - (mPosition)).y;

        if(X > Y)
        {
            if(-X > Y)
                mAnimator.currentAnimation = 1;
            else
                mAnimator.currentAnimation = 3;
        }
        else
        {
            if(-X > Y)
                mAnimator.currentAnimation = 2;
            else
                mAnimator.currentAnimation = 0;
        }
    }

}

void Enemy::TakeDamage(float _damage)
{
    if(mLife - _damage <= 0)
    {
        mLife = 0;
        for (Enemy* curr : EnemyWave::GetEnemies())
        {
            if(curr->GetIndex() > mListIndex)
            {
                curr->SetIndex(curr->GetIndex() - 1);
                PlaySound(GameSounds::DeadSound);
            }

        }
        Scene::GetCurrent()->fx.animations.push_back(new Animation(sparkFX, 5, mPosition, 50, YELLOW));
        mLife = 0;
        Game::GetPlayer()->WinGold(mGain);
    }
    else
        mLife -= _damage;

    animationDamage = 0.3f;
}

void Enemy::HealEnemy(float _healing)
{
    if(mLife != mMaxLife)
    {
        mLife += _healing;

        if(mLife > mMaxLife)
            mLife = mMaxLife;
    }
    else
        return;
}

myMath::Vec2 Enemy::GetPos() const
{
    return mPosition;
}

int Enemy::GetIndex() const
{
    return mListIndex;
}

int Enemy::GetPathIndex() const
{
    return sPathIndex;
}

int Enemy::GetLife() const
{
    return mLife;
}

void Enemy::SetIndex(int _index)
{
    mListIndex = _index;
}

CommonEnemy::CommonEnemy(myMath::Vec2 _position, int _listIndex, int _path, EnemyStat _stat) 
: Enemy(_position, _stat, _path, _listIndex)
{} 

void CommonEnemy::UpdateAndDraw()
{
    Enemy::UpdateAndDraw();
}

HealerEnemy::HealerEnemy(myMath::Vec2 _position, int _listIndex, int _path, EnemyStat _stat) 
: Enemy(_position, _stat, _path, _listIndex) 
{}

void HealerEnemy::UpdateAndDraw()
{ 
    Enemy::UpdateAndDraw();
    mTime -= GetFrameTime() * Game::sTimeScale;
    if(mTime <= 0)
    {
        CheckEnemiesForHealing();
        mTime = mHealSpeed;
    }
}

void HealerEnemy::CheckEnemiesForHealing()
{
    std::vector<Enemy*> enemyRange;

    for(Enemy* curr : EnemyWave::GetEnemies())
    {
        if(Distance(mPosition, curr->GetPos()) <= mRange)
        {
            enemyRange.push_back(curr);
        }
    }

    if(enemyRange.size() > 0)
    {
        for(Enemy* curr : enemyRange)
        {
            Healing(curr, mHeal);
        }
    }     
}

void HealerEnemy::Healing(Enemy* _target, float _healing)
{
    _target->HealEnemy(_healing);
}
