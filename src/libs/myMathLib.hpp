#pragma once
#include <math.h>
#include <iostream> 
#include <raylib.h>  

namespace myMath
{
    const float mPI = 3.141592653589793;

    inline float sqrt(float x)
    {
        if(x == 0) 
            return 0;
        float result = x / 4;
        for(int i = 0; i < 10; i++)
        {
            result = (result + x / result) / 2;
        }
        return result;
    }

    inline float pow (float x, int p)
    {
        float result = 1;
        for (int i = 0; i < p; i++)
        {
            result *= x;
        }
        return result;
    }

    inline float Clamp(float value, float min, float max)
    {
        if(value < min)
            return min;
        if(value > max)
            return max;
        return value;
    }

    inline int Clamp(int value, int min, int max)
    {
        if(value < min)
            return min;
        if(value > max)
            return max;
        return value;
    }

    template<typename T>
    inline T Min(T a, T b)
    {
        return a < b ? a : b;
    }

    template<typename T>
    inline T Max(T a, T b)
    {
        return a > b ? a : b;
    }

    template<typename T>
    inline T Abs(T a)
    {
        return a < 0 ? -a : a;
    }

    class Vec2
    {
        public: 
            float x;
            float y;

            Vec2(float _x = 0, float _y = 0)
            {
                x = _x; y = _y;
            }

            Vec2(int _x, int _y)
            {
                x = (float)_x; y = (float)_y;
            }

            ~Vec2() {};

            float GetNorm()
            {
                return sqrt((x * x) + (y * y));
            }

            inline Vec2 operator+(Vec2 b)
            {
                return (Vec2){this->x + b.x, this->y + b.y};
            }

            inline Vec2 operator+=(Vec2 b)
            {
                *this = *this + b;
                return *this;
            }

            inline Vec2 operator-(Vec2 b)
            {
                return (Vec2){this->x - b.x, this->y - b.y};
            }

            inline Vec2 operator-=(Vec2 b)
            {
                *this = *this - b;
                return *this;
            }

            inline Vec2 operator*(float b)
            {
                return (Vec2){x * b, y * b};
            }

            inline Vec2 operator*=(float b)
            {
                *this = *this * b;
                return *this;
            }

            inline Vec2 operator/(float b)
            {
                return (Vec2){this->x / b, this->y / b};
            }

            inline float operator*(Vec2 b)
            {
                return (float){this->x * b.x + this->y * b.y};
            }

            friend std::ostream& operator << (std::ostream& stream, const Vec2& a)
            {
                return stream << "(" << a.x << ", " << a.y << ")";
            }

            inline Vec2 Normalized()
            {
                return (Vec2){x / GetNorm(), y / GetNorm()};
            }

            inline float operator^(Vec2 b)
            {
                return this->x * b.y - this->y * b.x;
            }

            inline bool operator==(Vec2 b)
            {
                return (this->x == b.x && this->y == b.y);
            }

            inline bool operator!=(Vec2 b)
            {
                return (this->x != b.x && this->y != b.y);
            }

            inline Vec2 Rotate(Vec2 origin, float angle)
            {
                Vec2 op = *this - origin;
                Vec2 opP;
                opP.x = cos(angle) * op.x - sin(angle) * op.y;
                opP.y = sin(angle) * op.x + cos(angle) * op.y; 
                return opP + origin;
            }

            inline static Vec2 Vec2Zero()
            {
                return (Vec2){0, 0};
            }

            inline Vec2 Projection (Vec2 b, Vec2 c)
            {
                Vec2 axis = c - b;
                Vec2 point = *this - b;

                return axis * ((point * axis) / (axis * axis)) + b;
            }

            inline Vector2 toVector2()
            {
                return {x, y};
            }

            inline Vec2 floor(int i)
            {
                return {(int)x - ((int)x % i), (int)y - ((int)y % i)};
            }

            inline Vec2 Abs()
            {
                return {abs(x), abs(y)};
            }

            explicit operator Vector2() 
            {
                return toVector2();
            }
    };
    inline Vec2 toVec2(Vector2 v)
    {
        return {v.x, v.y};
    }

    inline float Distance (Vec2 a, Vec2 b)
    {
        return (sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2)));
    }
}

namespace collision
{
    using namespace myMath;
    
    class Box
    {
        public:
            Vec2 min;
            Vec2 max;

            Box(){};

            Box(Vec2 _min, Vec2 _max)
            {
                min = _min; max = _max;
            }

            Box(float x, float y, int width, int height)
            {
                min = (Vec2){x, y};
                max = (Vec2){x + width, y + height};
            }

            Rectangle toRec()
            {
                return (Rectangle){min.x, min.y, max.x - min.x, max.y - min.y};
            }

            inline Box operator+(Vec2 b)
            {
                return (Box){min + b, max + b};
            }
    };

    inline bool Collision(Box box, Vec2 point)
    {
        return (point.x > box.min.x && point.x < box.max.x &&
                point.y > box.min.y && point.y < box.max.y);
    }

    inline bool Collision(Vec2 c1, float r1, Vec2 c2, float r2)
    {
        return (Distance(c1, c2) <= r1 + r2);
    }
}