#include "../gameScenes/game.hpp"

using namespace collision;

using namespace GameSounds;

Projectile::Projectile(Enemy* _target, int _damage, myMath::Vec2 _position, float _radius)
: damageRadius(_radius)
, target(_target)
, damage(_damage)
, position(_position)
{}

void Projectile::SetDamageRadius(float _damageRadius)
{
    damageRadius = _damageRadius;
}

FireShot::FireShot(Sprite _sprite, float _speed, Enemy* _target, int _damage, myMath::Vec2 _pos, float _radius)
: Projectile(_target, _damage, _pos, _radius)
, mSpeed(_speed)
, sprite(_sprite)
{}

void FireShot::UpdateAndDraw()
{
    if(target)
    {
        destination = target->GetPos();
        position += (destination - position).Normalized().Normalized() 
            * mSpeed * GetFrameTime() * Game::sTimeScale;

        mRotation = atan2f((destination - position).y, 
            (destination - position).x) * (180 / myMath::mPI);

        sprite.Draw(collision::Box(position, position + myMath::Vec2{40, 40}), mRotation - 90);
        if(collision::Collision(position, 7, destination, 7))
        {
            if(target->GetLife() > 0)
            {
                if(damageRadius > 0)
                {
                    Scene::GetCurrent()->fx.animations.push_back(new Animation(smokeFX, 6, position, 150, ORANGE));

                    for (Enemy* curr : EnemyWave::GetEnemies())
                    {
                        if(Distance(position, curr->GetPos()) <= damageRadius)
                            curr->TakeDamage(damage);
                    }
                }
                else
                    target->TakeDamage(damage);
            }
            target = nullptr;
        }
    }
}

CryoShot::CryoShot(Enemy* _target, int _damage, myMath::Vec2 _pos, float _radius)
: Projectile(_target, _damage, _pos, _radius)
{}

void CryoShot::UpdateAndDraw()
{
    if(target)
    {
        DrawLineEx(position.toVector2(), target->GetPos().toVector2(), 6, DARKBLUE);
        DrawLineEx(position.toVector2(), target->GetPos().toVector2(), 3, BLUE);
        DrawCircleV(target->GetPos().toVector2(), 5, BLUE);
    }
}

BombShot::BombShot(Sprite _sprite, float _speed, Enemy* _target, int _damage, myMath::Vec2 _pos, float _radius, Vec2 _towerPos)
: Projectile(_target, _damage, _pos, _radius)
, mSpeed(_speed)
, sprite(_sprite)
, towerPos(_towerPos)
{
}

void BombShot::UpdateAndDraw()
{
    if(target)
        destination = target->GetPos();

    if(target || position != towerPos)
    position += (destination - position).Normalized().Normalized() 
        * mSpeed * GetFrameTime() * Game::sTimeScale;

    mRotation = atan2f((destination - position).y, 
        (destination - position).x) * (180 / myMath::mPI);

    sprite.Draw(collision::Box(position, position + myMath::Vec2{40, 40}), mRotation + 90);

    if(collision::Collision(position, 7, destination, 7))
    {
        Scene::GetCurrent()->fx.animations.push_back(new Animation(smokeFX, 6, position, 150, ORANGE));
        for (Enemy* curr : EnemyWave::GetEnemies())
        {
            if(Distance(position, curr->GetPos()) <= damageRadius)
                curr->TakeDamage(damage);
        }
    
        target = nullptr;
        position = towerPos;
    }
}

StatueShot::StatueShot(Sprite _sprite, float _speed, Enemy* _target, int _damage, myMath::Vec2 _pos, float _radius)
: Projectile(_target, _damage, _pos, _radius)
, mSpeed(_speed)
, sprite(_sprite)
{}

void StatueShot::UpdateAndDraw()
{
    if(target)
    {
        destination = target->GetPos();
        position += (destination - position).Normalized().Normalized() 
            * mSpeed * GetFrameTime() * Game::sTimeScale;

        mRotation = atan2f((destination - position).y, 
            (destination - position).x) * (180 / myMath::mPI);

        sprite.Draw(collision::Box(position, position + myMath::Vec2{40, 40}), mRotation + 90);
        if(collision::Collision(position, 7, destination, 7))
        {
            if(target->GetLife() > 0)
            {
                Scene::GetCurrent()->fx.animations.push_back(new Animation(circleFX, 4, position, 100, SKYBLUE)); 
                target->TakeDamage(damage);
            }
            target = nullptr;
        }
    }
}

Tower::Tower(myMath::Vec2 _position, Sound _sound, TowerData::TowerStat _stat)
: mSprite(Sprite(_stat.tilePos, *_stat.texture, _stat.tileSetSize, _stat.origin, _stat.towerSize))
, mPosition(_position)
, mSound(_sound)
, mRotation(rand() % 360)
, mAttackSpeed(1.f / _stat.attackRate)
, mDamage(_stat.damage)
, mCost(_stat.cost)
, mRange(_stat.range)
, size(_stat.towerSize)
{
    mEnemyToFollow = nullptr;
}

void Tower::UpdateAndDraw()
{
    mProjectile->UpdateAndDraw();
    mSprite.Draw(Box(mPosition.x + 0, mPosition.y + 0, size * 40, size * 40), mRotation + 90);

    if(mEnemyToFollow)
        mRotation = atan2f(mEnemyToFollow->GetPos().y - mPosition.y, mEnemyToFollow->GetPos().x - mPosition.x)* (180 / mPI);
}

void Tower::SelectTarget()
{
    int farthestEnemy = -99999;
    float shortestDistance = -99999;
    mEnemyToFollow = nullptr;
    for(Enemy* curr : EnemyWave::GetEnemies())
    {
        if(curr->GetPathIndex() >= farthestEnemy && Distance(mPosition, curr->GetPos()) <= (float)mRange &&
        Distance(curr->GetPos(), Game::GetPath(curr->pathToFollow)[curr->GetPathIndex()]) > shortestDistance)
        {
            mEnemyToFollow = curr;
            farthestEnemy = curr->GetPathIndex();
            shortestDistance = Distance(curr->GetPos(), Game::GetPath(curr->pathToFollow)[curr->GetPathIndex()]);
        }
    }
}
void Tower::UpgradeTower()
{
    mLevel++;
}

myMath::Vec2 Tower::GetPosition() const
{
    return mPosition;
}
float Tower::GetAttackSpeed() const
{
    return mAttackSpeed;
}
int Tower::GetDamage() const
{
    return mDamage;
}
int Tower::GetCost() const
{
    return mCost;
}
int Tower::GetRange() const
{
    return mRange;
}

CommonTower::CommonTower(myMath::Vec2 _position, Sound _sound) 
: Tower(_position, FlameShotSound, TowerData::Common)
{
    mProjectile = new FireShot(Sprite(Vec2(21, 12), enemySet,
     Vec2(23, 13), Vec2(20, 20)), 950, nullptr, mDamage, mPosition);
}

void CommonTower::UpdateAndDraw()
{
    Tower::SelectTarget();
    Tower::UpdateAndDraw();

    if(mTime <= 0)
    {
        if(mEnemyToFollow) 
        {
            mProjectile->target = mEnemyToFollow;
            mProjectile->position = mPosition;
            PlaySound(mSound);
        }
        mTime = mAttackSpeed;
    }
    else 
        mTime -= GetFrameTime() * Game::sTimeScale;
}
void CommonTower::UpgradeTower()
{
    if(mLevel == 1)
    {
        myMath::Vec2 spriteSize = myMath::Vec2{(float)TowerData::Common.texture->width / TowerData::Common.tileSetSize.x,
        (float)TowerData::Common.texture->height / TowerData::Common.tileSetSize.y};
        mSprite.SetSource(Box{20 * spriteSize.x,
        10 * spriteSize.y, (int)spriteSize.x, (int)spriteSize.y});

        mDamage += 20;
        mProjectile->damage = mDamage;
        mRange += 60;
        mAttackSpeed -= .4f;
    }
    Tower::UpgradeTower();
}

CryoTower::CryoTower(myMath::Vec2 _position, Sound _sound) 
: Tower(_position, CryoShotSound, TowerData::Cryo)
{
    mProjectile = new CryoShot(nullptr, mDamage, mPosition);
}

void CryoTower::UpdateAndDraw()
{
    Tower::SelectTarget();
    Tower::UpdateAndDraw();
    
    if(mTime <= 0)
    {
        if(mEnemyToFollow) 
        {
            mEnemyToFollow->TakeDamage(mDamage);
            PlaySound(mSound);
        }
        mTime = mAttackSpeed;
    }
    else 
        mTime -= GetFrameTime() * Game::sTimeScale;

    mProjectile->target = mEnemyToFollow;

    if(mEnemyToFollow)
    {
        if(!mEnemyToFollow->debufList.Contain(Status(DT_FREEZE)))
            mEnemyToFollow->debufList.Add(Status(DT_FREEZE, 0.2f));
    }
}
void CryoTower::UpgradeTower()
{
    if(mLevel == 1)
    {
        myMath::Vec2 spriteSize = myMath::Vec2{(float)TowerData::Cryo.texture->width / TowerData::Cryo.tileSetSize.x,
        (float)TowerData::Cryo.texture->height / TowerData::Cryo.tileSetSize.y};
        mSprite.SetSource(Box{19 * spriteSize.x,
        9 * spriteSize.y, (int)spriteSize.x, (int)spriteSize.y});

        mRange += 80;
        mDamage += 1;
        mProjectile->damage = mDamage;
    }
    Tower::UpgradeTower();
}

BombTower::BombTower(myMath::Vec2 _position, Sound _sound)
: Tower(_position, BombShotSound, TowerData::Bomb)
{
    mProjectile = new BombShot(Sprite(Vec2(22, 10), enemySet,
     Vec2(23, 13), Vec2(20, 20)), 500, nullptr, mDamage, mPosition, mRadiusExplosion, _position);

}

void BombTower::UpdateAndDraw()
{
    Tower::SelectTarget();
    Tower::UpdateAndDraw();

    if(mTime <= 0)
    {
        if(mEnemyToFollow) 
        {
            mProjectile->target = mEnemyToFollow;
            mProjectile->position = mPosition;
            PlaySound(mSound);
        }
        mTime = mAttackSpeed;
    }
    else 
        mTime -= GetFrameTime() * Game::sTimeScale;
}
void BombTower::UpgradeTower()
{
    if(mLevel == 1)
    {
        myMath::Vec2 spriteSize = myMath::Vec2{(float)TowerData::Bomb.texture->width / TowerData::Bomb.tileSetSize.x,
        (float)TowerData::Bomb.texture->height / TowerData::Bomb.tileSetSize.y};
        mSprite.SetSource(Box{21 * spriteSize.x,
        8 * spriteSize.y, (int)spriteSize.x, (int)spriteSize.y});

        mDamage += 25;
        mProjectile->damage = mDamage;
        mRange += 40;

        if(mAttackSpeed > .5f)
            mAttackSpeed -= .2f;

        mRadiusExplosion += 30.f;
        mProjectile->SetDamageRadius(mRadiusExplosion);
    }
    Tower::UpgradeTower();
}

StatueTower::StatueTower(myMath::Vec2 _position, Sound _sound) 
: Tower(_position, FlameShotSound, TowerData::Statue)
{
    mType = TT_STATUE;
    mProjectile = new StatueShot(Sprite(Vec2(13, 19), TowerSet,
     Vec2(29, 22), Vec2(20, 20)), 680, nullptr, mDamage, mPosition);
}

void StatueTower::UpdateAndDraw()
{
    Tower::SelectTarget();

    mProjectile->UpdateAndDraw();
    mSprite.Draw(Box(mPosition.x + 0, mPosition.y + 0, 80, 80), 0);

    if(mTime <= 0)
    {
        if(mEnemyToFollow) 
        {
            mProjectile->target = mEnemyToFollow;
            mProjectile->position = mPosition;
            PlaySound(mSound);
        }
        mTime = mAttackSpeed;
    }
    else 
        mTime -= GetFrameTime() * Game::sTimeScale;
}
void StatueTower::UpgradeTower()
{

    mSprite.SetSource(Box{48, 240, 32, 32});

    mDamage += 80;
    mProjectile->damage = mDamage;
    mRange += 40;
    mAttackSpeed -= .2f;

    Tower::UpgradeTower();
}
