#include "maths.cpp"

class Ball
{
public:
    Vec2 pos;
    Vec2 vel;

    void Update(float deltaTime)
    {
        pos = pos + vel * deltaTime;
    }
};
