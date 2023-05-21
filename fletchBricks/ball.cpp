#pragma once
#include "maths.cpp"

class Ball
{
public:
    Vec2 pos;
    Vec2 vel;
    float radius;

    void Update(float deltaTime)
    {
        pos = pos + vel * deltaTime;
    }

    BBox getBBox()
    {
        return BBox(
            Vec2(pos - radius),
            Vec2(pos + radius)
        );
    }

    void BounceVertical() {
        vel.y *= -1.0f;
    }

    void BounceHorizontal() {
        vel.x *= -1.0f;
    }
};
