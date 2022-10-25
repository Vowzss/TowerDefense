#pragma once

#include "../System/scene.hpp"

class HowToPlay : public Scene
{
    private:
        Texture2D mBackground;
        std::string mTextToDisplay[12];


    public:
        int PosX = GetScreenWidth()/2-270, PosY = 160;
        
        void Start() override;
        void Update() override;
        void Render() override;
};