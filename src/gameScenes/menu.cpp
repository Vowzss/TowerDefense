#include "../gameScenes/game.hpp"

using namespace GameSounds;
using namespace GameTextures;

void Menu::Start()
{
    PlaySound(AmbiantSound);
    
    switch(rand() % 5)
    {
        case(0) : mBackground = SnowBackground;
        break;

        case(1) : mBackground = DesertBackground;
        break;
        
        case(2) : mBackground = DeadBackground;
        break;

        case(3) : mBackground = PlaineBackground;
        break;

        case(4) : mBackground = JungleBackground;
        break;
        
        case(5) : mBackground = CandyBackground;
        break;       
    }


    UIelements.push_back(new Button{(collision::Box){650, 485, 300, 120}, 
    [](Button* self)
    {
        Scene::ChangeScene(new LevelSelect());
    }, 
    Sound(ClickSound), Color{0, 0, 0, 0},
    Sprite({0, 0}, PlayTexture, {1, 3}, {0, 0}), nullptr, Sprite({0, 1}, PlayTexture, {1, 3}, {0, 0}), 
    Sprite({0, 2}, PlayTexture, {1, 3}, {0, 0}), true});

    UIelements.push_back(new Button{(collision::Box){967, 485, 300, 120},
    [](Button* self)
    {
        Scene::ChangeScene(new LevelEditor());
    }, 
    Sound(ClickSound), Color{0, 0, 0, 0},
    Sprite({0, 0}, EditorTexture, {1, 3}, {0, 0}), nullptr, Sprite({0, 1}, EditorTexture, {1, 3}, {0, 0}), 
    Sprite({0, 2}, EditorTexture, {1, 3}, {0, 0}), true});

    UIelements.push_back(new Button(collision::Box(1713, 1000, 200, 80),
    [](Button* self)
    {
        Scene::ChangeScene(new GameCredits());
    }, 
    Sound(ClickSound), Color{0, 0, 0, 0},
    Sprite({0, 0}, CreditsTexture, {1, 3}, {0, 0}), this, Sprite({0, 1}, CreditsTexture, {1, 3}, {0, 0}), 
    Sprite({0, 2}, CreditsTexture, {1, 3}, {0, 0}), true));

    UIelements.push_back(new Button(collision::Box(1450, 1000, 250, 80),
    [](Button* self)
    {
        Scene::ChangeScene(new HowToPlay());
    }, 
    Sound(ClickSound), Color{0, 0, 0, 0},
    Sprite({0, 0}, HowToPlayTexture, {1, 3}, {0, 0}), this, Sprite({0, 1}, HowToPlayTexture, {1, 3}, {0, 0}), 
    Sprite({0, 2}, HowToPlayTexture, {1, 3}, {0, 0}), true));

    UIelements.push_back(new Button(collision::Box(1235, 1000, 200, 80),
    [](Button* self)
    {
        ((Scene*)self->mUserPtr)->sIsQuitMenu = true;
    }, 
    Sound(QuitSound), Color{0, 0, 0, 0},
    Sprite({0, 0}, QuitTexture, {1, 3}, {0, 0}), this, Sprite({0, 1}, QuitTexture, {1, 3}, {0, 0}), 
    Sprite({0, 2}, QuitTexture, {1, 3}, {0, 0}), true));

}

void Menu::Update() 
{
    Scene::Update();
}

void Menu::GetInput()
{
    Scene::GetInput();
}

void Menu::Render()
{
    DrawTexture(mBackground, 0, 0, WHITE);
    DrawTexture(HUD, GetScreenWidth()/2-325, GetScreenHeight()/2-100, WHITE);
    Scene::Render();
}