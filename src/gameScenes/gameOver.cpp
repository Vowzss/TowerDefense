#include "gameOver.hpp"

using namespace GameTextures;
using namespace GameSounds;

GameOver::GameOver(Game& _game)
:mGame(_game)
{}

void GameOver::Start()
{
    UIelements.push_back(new Button{(collision::Box){855, 540, 200, 80}, 
    [](Button* self)
    {
        Scene::ChangeScene(new Menu());
    }, 
    Sound(QuitSound), Color{0, 0, 0, 0},
    Sprite({0, 0}, QuitTexture, {1, 3}, {0, 0}), nullptr, Sprite({0, 1}, QuitTexture, {1, 3}, {0, 0}), 
    Sprite({0, 2}, QuitTexture, {1, 3}, {0, 0}), true});
}

void GameOver::Update() 
{
    Scene::Update();
}

void GameOver::Render()
{
    PlaySound(GameOverSound);
    DrawTexture(GameOverBackground, 0, 0, WHITE);
    DrawTexture(HUD, GetScreenWidth()/2-325, GetScreenHeight()/2-100, WHITE);
    DrawTexture(GameOverScreen, 0, 0, WHITE);
    DrawText(TextFormat("Wave : %d", mGame.sWave->waveIndex), GetScreenWidth()/2 - 130, GetScreenHeight()/2 - 70, 60, WHITE);

    Scene::Render();
}