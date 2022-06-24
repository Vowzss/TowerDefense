#include "gameAnimator.hpp"

#include "../gameScenes/game.hpp"

Animation::Animation(float _frameRate)
: frameRate(_frameRate)
, currentTime(0)
, loop(true)
{
};

Animation::Animation(Texture2D _FX, int _size, myMath::Vec2 _pos, float _scale, Color _tint)
: frameRate(11)
, currentTime(0)
, position(_pos)
, scale(_scale)
, tint(_tint)
{
    for (int i = 0; i < _size; i++)
    {
        frames.push_back(Sprite({i, 0}, _FX, {_size, 1}, {scale / 2, scale / 2}));
    }
}

Animator::Animator(Texture2D _model4x4, float _frameRate, Sprite* _sprite, int _start) 
: currentAnimation(_start)
, sprite(_sprite)
{
    for ( int i = 0; i < 4; i++)
    {
        Animation* curr = new Animation(_frameRate);
        for (int j = 0; j < 4; j++)
        {
            curr->frames.push_back(Sprite(myMath::Vec2(i, j),
             _model4x4, myMath::Vec2(4, 4), myMath::Vec2(20, 20)));
        }
        animations.push_back(curr);
    }
}

Animator::~Animator()
{
    for(Animation* curr : animations)
    {
        delete curr;
    }
    animations.clear();
}

void Animator::Update()
{
    Animation* curr = animations.at(currentAnimation);  
    curr->currentTime += GetFrameTime() * Game::sTimeScale;
    if(curr->loop)
        curr->currentTime = fmodf(curr->currentTime, ((float)curr->frames.size() * (1.f / curr->frameRate)));
    *sprite = curr->frames[myMath::Clamp((int)(curr->currentTime * curr->frameRate), 0, curr->frames.size() - 1)];
}

FXManager::~FXManager()
{
    for(Animation* curr : animations)
    {
        delete curr;
    }
    animations.clear();
}

void FXManager::Update()
{
    for (size_t i = 0; i < animations.size(); i++)
    {
        animations[i]->currentTime += GetFrameTime()* Game::sTimeScale;
        animations[i]->frames.at(myMath::Clamp((int)(animations[i]->currentTime * animations[i]->frameRate), 0, 
        animations[i]->frames.size() - 1)).Draw(collision::Box(animations[i]->position,
        animations[i]->position + myMath::Vec2{animations[i]->scale, animations[i]->scale}), 0, animations[i]->tint);
        
        if(animations[i]->currentTime >= (float)animations[i]->frames.size() * (1.f / animations[i]->frameRate))
        {
            delete animations[i];
            animations.erase(animations.begin() + i);
        }
    }
}
