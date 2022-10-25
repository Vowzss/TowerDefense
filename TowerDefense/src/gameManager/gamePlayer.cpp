#include "gamePlayer.hpp"

using namespace GameSounds;

Player::Player(int _gold, int _life)
: mGold(_gold)
, mLife(_life)
{}

void Player::TakeDamage(int _damage)
{
    PlaySound(CastleAttackedSound);
    if(mLife - _damage <= 0) 
    {
        mLife = 0;
    }
    else
    {
        mLife -= _damage;
    }
}

bool Player::BuyTower(int _cost)
{
    if(mGold - _cost < 0)
        return false;
    else
    {
        mGold -= _cost;
        PlaySound(TouretBuyingSound);
        return true;
    }
}

void Player::WinGold(const int _gold)
{
    mGold += _gold;
}

int& Player::GetGold() 
{
    return mGold;
}

int& Player::GetLife() 
{
    return mLife;
}