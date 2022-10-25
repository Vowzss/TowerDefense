#include "scene.hpp"

Scene* Scene::sCurrentScene = nullptr;
std::vector<Scene*> Scene::sScenesToDelete;

Scene::Scene() {}

Scene::~Scene()
{
    for(UIElement* curr : UIelements)
        delete curr;
    
    UIelements.clear();
}

void Scene::Update()
{
    Render();
    GetInput();
    int i = 0;
    for(UIElement* curr : UIelements)
    {
        if(curr->isActive)
            curr->UpdateAndDrawUI();
        i++;
    }
    GetInput();
    
    fx.Update();
}

void Scene::Render() {}

void Scene::GetInput() {}

void Scene::DeleteScenes()
{
    for(Scene* curr : sScenesToDelete)
        delete curr;
    
    sScenesToDelete.clear();

}

void Scene::ChangeScene(Scene* _next)
{
    if (sCurrentScene)
        sScenesToDelete.push_back(sCurrentScene);

    sCurrentScene = _next;
    sCurrentScene->Start();
}
