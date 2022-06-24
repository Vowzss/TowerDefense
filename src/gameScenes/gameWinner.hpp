#include "../gameManager/gameSounds.hpp"
#include "../gameManager/gameTextures.hpp"

#include "../gameScenes/menu.hpp"
#include "../gameScenes/gameSelector.hpp"

using namespace GameTextures;

class WinScreen : public Scene
{
    private:
        int mScore;

    public :
        WinScreen(int score);
        void Start() override;
        void Update() override;
        void Render() override;
};
