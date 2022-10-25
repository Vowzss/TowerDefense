#pragma once

#include <vector>
#include <raylib.h>

#include "UIElement.hpp"

#include "../libs/myMathLib.hpp"

class Animation
{
    public:
        std::vector<Sprite> frames;
        float frameRate;
        float currentTime;
        bool loop;
        union 
        {
            myMath::Vec2 position;
            myMath::Vec2* positionPtr;
        };
        float scale;
        Color tint;
        bool ptr;

        Animation(float _frameRate);
        Animation(Texture2D _FX, int _size, myMath::Vec2 _pos,
         float _scale = 1, Color _tint = WHITE);
         ~Animation() {};
};

class Animator
{
    public:
        std::vector<Animation*> animations;
        int currentAnimation;
        Sprite* sprite;
        Animator(){};
        Animator(Texture2D _model4x4, float _frameRate, Sprite* _sprite, int _start);
        ~Animator();

        void Update();
};

class FXManager
{
    public:
        std::vector<Animation*> animations;

        FXManager(){};
        ~FXManager();

        void Update();
};

