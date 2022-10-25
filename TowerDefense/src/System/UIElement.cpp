#include "UIElement.hpp"

Sprite::Sprite(myMath::Vec2 _tilePos, Texture2D _texture, myMath::Vec2 _tileSize, myMath::Vec2 _origin, int _size)
: mTexture(_texture)
, mOrigin(_origin)
{
    myMath::Vec2 spriteSize = myMath::Vec2{(float)_texture.width / _tileSize.x,
        (float)_texture.height / _tileSize.y};
    mSource = collision::Box(_tilePos.x * spriteSize.x,
        _tilePos.y * spriteSize.y, spriteSize.x * _size, spriteSize.y * _size);
}

Sprite::Sprite(collision::Box _source, Texture2D _texture, myMath::Vec2 _origin)
: mTexture(_texture)
, mOrigin(_origin)
, mSource(_source)
{}



void Sprite::Draw(collision::Box _dest, float _rotation, Color _tint)
{
    DrawTexturePro(mTexture, mSource.toRec(),
        _dest.toRec(), mOrigin.toVector2(), _rotation, _tint);
}

collision::Box Sprite::GetSource() const
{
    return mSource;
}

void Sprite::SetSource(collision::Box _source)
{
    mSource = _source;
}

void Sprite::SetTexture(Texture2D _texture)
{
    mTexture = _texture;
}

Button::Button(collision::Box _box, Event _event, Sound _sound, Color _color, std::string _text, void* _userPtr, bool _isActive)
: mOnClick(_event)
, mSound(_sound)
, mColor(_color)
, mText(_text)
, mIsText(true)
, mCollider(_box)
, mUserPtr(_userPtr)
{
    isActive = _isActive;
}

Button::Button(collision::Box _box, Event _event, Sound _sound, Color _color, Sprite _sprite, void* _userPtr,
 Sprite _hoverSprite, Sprite _pressedSprite, bool _onReleased, bool _isActive)
: mOnClick(_event)
, mSound(_sound)
, mColor(_color)
, mOnReleased(_onReleased)
, mIsText(false)
, mSprite(_sprite)
, mHoverSprite(_hoverSprite)
, mPressedSprite(_pressedSprite)
, mCollider(_box)
, mUserPtr(_userPtr)
{
    isActive = _isActive;
}

void Button::UpdateAndDrawUI()
{
    if(mIsText)
    {
        int font = myMath::sqrt(mCollider.max.y - mCollider.min.y) * 5;
        DrawRectangleRounded(mCollider.toRec(), 0.5f, 8, mColor);
        //DrawRectangleRoundedLines(mCollider.toRec(), 0.5f, 8, 5, BLACK);
        DrawText(mText.c_str(), mCollider.min.x + font / 4, mCollider.min.y + font / 15,
            font, BLACK);
    }else
    {
        if(collision::Collision(mCollider, myMath::toVec2(GetMousePosition())))
        {
            if(IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            {
                DrawRectangleRounded(mCollider.toRec(), 0.5, 8, mColor);
                mPressedSprite.Draw(mCollider, 0);
            }else
            {
                DrawRectangleRounded(mCollider.toRec(), 0.5, 8, mColor);
                mHoverSprite.Draw(mCollider, 0);
            }
        }else
        {
            DrawRectangleRounded(mCollider.toRec(), 0.5, 8, mColor);
            mSprite.Draw(mCollider, 0);
        }
    }

    if(mOnReleased)
    {
        if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {
            if(collision::Collision(mCollider, myMath::toVec2(GetMousePosition())))
            {
                PlaySound(mSound);
                mOnClick(this);
            }
        }
    }else
    {
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            if(collision::Collision(mCollider, myMath::toVec2(GetMousePosition())))
            {
                PlaySound(mSound);
                mOnClick(this);
            }
        }
    }
}

void Button::SetText(std::string _text)
{
    mText = _text;
}

void Button::SetSpriteSourceOffset(myMath::Vec2 offset)
{
    mHoverSprite.SetSource(mHoverSprite.GetSource() + offset);
    mSprite.SetSource(mSprite.GetSource() + offset);
    mPressedSprite.SetSource(mPressedSprite.GetSource() + offset);
}

collision::Box Button::GetCollider() const
{
    return mCollider;
}

UIText::UIText(collision::Box _box, Color _color, const char* _text, const int* _value, bool _isActive)
: mBox(_box)
, mColor(_color)
, mText(_text)
, mIsInt(true)
, mIntValue(_value)
{
    isActive = _isActive;
}

UIText::UIText(collision::Box _box, Color _color, const char* _text, const float* _value, bool _isActive)
: mBox(_box)
, mColor(_color)
, mText(_text)
, mIsInt(false)
, mFloatValue(_value)
{
    isActive = _isActive;
}

void UIText::UpdateAndDrawUI()
{
    int font = mBox.max.y - mBox.min.y;
    DrawRectangleRounded(mBox.toRec(), 0.5f, 8, mColor);
    DrawRectangleRoundedLines(mBox.toRec(), 0.5f, 8, 5, BLACK);
    if(mIsInt)
        DrawText(TextFormat("%.d%s", *mIntValue, mText), mBox.min.x + font / 4, mBox.min.y + font / 15, font, BLACK);
    else
        DrawText(TextFormat("%.1f%s", *mFloatValue, mText), mBox.min.x + font / 4, mBox.min.y + font / 15, font, BLACK);
}

collision::Box UIText::GetCollider() const
{
    return mBox;
}

void UIText::SetIntValue(const int* _value)
{
    mIntValue = _value;
}

void UIText::SetFloatValue(const float* _value)
{
    mFloatValue = _value;
}