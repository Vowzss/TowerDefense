#include "gameWinner.hpp"

using namespace GameSounds;

WinScreen::WinScreen(int score) 
: mScore(score)
{}

void WinScreen::Start()
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

void WinScreen::Update()
{
    Scene::Update();
}

void WinScreen::Render()
{
    PlaySound(GameWinSound);
    DrawTexture(JungleBackground, 0, 0, WHITE);
    DrawTexture(HUD, GetScreenWidth()/2-325, GetScreenHeight()/2-100, WHITE);
    DrawTexture(YouWonScreen, 0, 0, WHITE);
    DrawText(TextFormat("Wave : %d", mScore), GetScreenWidth()/2 - 127, GetScreenHeight()/2 - 70, 60, WHITE);

    Scene::Render();
}
