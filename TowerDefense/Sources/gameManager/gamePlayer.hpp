#pragma once

#include <raylib.h>

#include "gameSounds.hpp"

class Player
{
private:
    int mGold = 0;
    int mLife = 20;
    
public:
    Player(int _gold = 0, int _life = 0);

    void TakeDamage(int _damage);
    bool BuyTower(int _cost);

    void WinGold(const int _gold);

    int& GetGold();
    int& GetLife();
};