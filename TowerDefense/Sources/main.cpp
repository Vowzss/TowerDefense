#include <raylib.h>

#include "Libs/myList.hpp"
#include "gameScenes/menu.hpp"

#include "gameScenes/game.hpp"
#include "gameManager/gameSounds.hpp"
#include "gameManager/gameTextures.hpp"

using namespace myList;

int main(void)
{
    const int screenWidth  = 1920;
    const int screenHeight = 1080;
    
    SetConfigFlags(FLAG_VSYNC_HINT);
    SetConfigFlags(FLAG_MSAA_4X_HINT);

    InitWindow(screenWidth, screenHeight, "Appenzeller Studio - Ninja Defense");

    InitAudioDevice();
    InitSounds();
    InitTextures();

    Scene::ChangeScene(new Menu());
    Game::sTimeScale = 1;

    while (!WindowShouldClose() && !Scene::GetCurrent()->sIsQuitMenu)
    {
        BeginDrawing();
        ClearBackground(BLACK);

        Scene::GetCurrent()->Update();
        Scene::DeleteScenes();

        DrawFPS(10, 10);
        EndDrawing();
    }
    delete Scene::GetCurrent();
    UnloadAllTextures();

    CloseAudioDevice();
    CloseWindow();

    UnloadAllSounds();

    return 0;
}