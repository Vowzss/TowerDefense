#include "../gameScenes/game.hpp"

using namespace collision;

void Game::ActiveStatTower()
{  
    for(int i = 0; i < 7; i++)
        UIelements[mItStatTower[i]]->isActive = !UIelements[mItStatTower[i]]->isActive;
    
    if(mPtrTowerSelected->mLevel == 2)
    {
        UIelements[mItStatTower[0]]->isActive = false; // Button upgade
        UIelements[mItStatTower[2]]->isActive = false; // Text upgade
    }
    else if(mPtrTowerSelected->mLevel == 1 && UIelements[mItStatTower[1]]->isActive)
    {
        UIelements[mItStatTower[0]]->isActive = true; // Button upgade
        UIelements[mItStatTower[2]]->isActive = true; // Text upgade
    }
    else if(mPtrTowerSelected->mLevel == 1 && !UIelements[mItStatTower[1]]->isActive)
    {
        UIelements[mItStatTower[0]]->isActive = false; // Button upgade
        UIelements[mItStatTower[2]]->isActive = false; // Text upgade
    }
}

void Game::CheckStatTowerDisplay()
{
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) 
    && UIelements[mItStatTower[1]]->isActive
    && !collision::Collision(UIelements[mItStatTower[0]]->GetCollider(), myMath::toVec2(GetMousePosition()))
    && !collision::Collision(UIelements[mItStatTower[1]]->GetCollider(), myMath::toVec2(GetMousePosition()))
    && !collision::Collision(UIelements[FindButtonSelected(*mPtrTowerSelected)]->GetCollider(), myMath::toVec2(GetMousePosition())))
        ActiveStatTower();
}

Tower* Game::FindTowerSelected()
{
    for(Tower* curr : mTowerlist)
    {
        if(collision::Collision((Box){curr->GetPosition().x - curr->size * 20,
         curr->GetPosition().y - curr->size * 20, curr->size * 40, curr->size * 40},
          myMath::toVec2(GetMousePosition())))
        {
            mTowerSelected = *curr;
            return curr;
        }
    }
    return nullptr;
}

int Game::FindButtonSelected(Tower _tower)
{
    for(int i = 0; i < (int)UIelements.size(); i++)
    {
        if(collision::Collision(UIelements[i]->GetCollider(), _tower.GetPosition()))
            return i;
    }
    return -1;
}

void Game::UpgradeTowerSelected()
{
    if(mPtrTowerSelected)
    {
        mPtrTowerSelected->UpgradeTower();
        ActiveStatTower();
    }
    
}

void Game::SellTowerSelected()
{
    for(int i = 0; i < (int)mTowerlist.size(); i++)
    {
        if(mPtrTowerSelected == mTowerlist[i])
        {
            sPlayer->WinGold(mTowerlist[i]->GetCost());
            mTowerlist[i]->isTowerToSell = true;
            ActiveStatTower();
        }
    }
}
