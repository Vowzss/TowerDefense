#pragma once

#include <raylib.h>

#include "../libs/myMathLib.hpp"

#include "../gameManager/gameTextures.hpp"

class Sprite
{
    private:
        Texture2D mTexture;
        myMath::Vec2 mOrigin;
        collision::Box mSource;

    public:
        Sprite(myMath::Vec2 _tilePos, Texture2D _texture,
         myMath::Vec2 _tileSize, myMath::Vec2 _origin, int _size = 1); 

        Sprite(collision::Box _source, Texture2D _texture, myMath::Vec2 _origin);

        Sprite() {};

        void Draw(collision::Box _dest, float _rotation, Color _tint = WHITE);

        collision::Box GetSource() const;
        void SetSource(collision::Box _source);
        void SetTexture(Texture2D _texture);
};

class UIElement
{
    public:
        bool isActive = true;

        UIElement() {};
        virtual ~UIElement() {};

        virtual void UpdateAndDrawUI() {};
        virtual void SetText(std::string text) {};
        virtual collision::Box GetCollider() const {return {0,0,0,0};};

        virtual void DisplayTowerStat(int _damage = 0, int _attackSpeed = 0, int _range = 0) {};
};

class Button : public UIElement
{
    typedef void(*Event)(Button*);

    private:
        Event mOnClick;
        Sound mSound;
        Color mColor;
        bool mOnReleased;

        std::string mText;

        bool mIsText;

    public:
        Sprite mSprite;
        Sprite mHoverSprite;
        Sprite mPressedSprite;
        
        collision::Box mCollider;
        void* mUserPtr;
        union
        {
            int intValue;
            float floatValue;
        };
        
        Button(collision::Box _box, Event _event, Sound _sound, Color _color, std::string _text, void* _userPtr, bool _isActive = true);
        Button(collision::Box _box, Event _event, Sound _sound, Color _color, Sprite _sprite, void* _userPtr, Sprite _hoverSprite, Sprite _pressedSprite, bool _onReleased, bool _isActive = true);

        void operator=(Button a) const;
        void UpdateAndDrawUI() override;


        void SetSpriteSourceOffset(myMath::Vec2 offset);
        void SetText(std::string _text) override;
        collision::Box GetCollider() const override;

        void CallEvent()
        {
            mOnClick(this);
        }
};

class UIText : public UIElement
{
    typedef void(*Event)(void*);
    
    private:
        collision::Box mBox;
        Color mColor;
        const char* mText;
        bool mIsInt;
        union
        {
            const float* mFloatValue;
            const int* mIntValue;
        };
        

    public:
        UIText(collision::Box _box, Color _color, const char* _text, const int* _value, bool _isActive = true);
        UIText(collision::Box _box, Color _color, const char* _text, const float* _value, bool _isActive = true);

        void UpdateAndDrawUI() override;

        collision::Box GetCollider() const override;

        void SetIntValue(const int* _value);
        void SetFloatValue(const float* _value);
};