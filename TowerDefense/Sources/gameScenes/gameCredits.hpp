#pragma once

#include <string.h>

#include "menu.hpp"

#include "../gameManager/gameSounds.hpp"
#include "../gameManager/gameTextures.hpp"

#include "../System/scene.hpp"

class GameCredits : public Scene
{
    private:
        Texture2D mBackground;
        std::string mTextToDisplay[8];
        

    public:
        int PosX = GetScreenWidth()/2-270, PosY = 160;
        
        void Start() override;
        void Update() override;
        void Render() override;
};