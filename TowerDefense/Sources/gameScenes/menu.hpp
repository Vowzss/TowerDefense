#pragma once

#include "menu.hpp"

#include "../System/scene.hpp"

#include "../levelEditor/levelEditor.hpp"

#include "../gameManager/gameSounds.hpp"
#include "../gameManager/gameTextures.hpp"

#include "../gameScenes/gameHowToPlay.hpp"
#include "../gameScenes/gameSelector.hpp"
#include "../gameScenes/gameCredits.hpp"

class Menu : public Scene
{
    private:
        Texture2D mBackground;

    public:
        void Start() override;
        void Update() override;
        void Render() override;
        void GetInput() override;
};