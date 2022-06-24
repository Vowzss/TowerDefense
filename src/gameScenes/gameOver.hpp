#pragma once

#include "game.hpp"
#include "gameSelector.hpp"
#include "menu.hpp"

#include "../System/scene.hpp"

#include "../gameManager/gameTextures.hpp"
#include "../gameManager/gameSounds.hpp"

class GameOver : public Scene
{
    private:
        Game& mGame;

    public:
        GameOver(Game& _game);

        void Start() override;
        void Update() override;
        void Render() override;
};
