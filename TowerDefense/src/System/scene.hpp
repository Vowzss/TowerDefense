#pragma once

#include <raylib.h>
#include <iostream>
#include <vector>

#include "UIElement.hpp"
#include "gameAnimator.hpp"

constexpr int gridHeight = 27;
constexpr int gridWidth = 48;
constexpr int caseSize = 30;

class Scene
{
    public:
        std::vector<UIElement*> UIelements;
        FXManager fx;

        Scene();
        virtual ~Scene();
        
        virtual void Start() {};
        virtual void Update();
        virtual void Render();
        virtual void GetInput();


    public:
        static void ChangeScene(Scene* _next);
        static Scene* GetCurrent() { return sCurrentScene; }
        static void DeleteScenes();
        bool sIsQuitMenu = false;

    private:
        static Scene* sCurrentScene;
        static std::vector<Scene*> sScenesToDelete;
};
