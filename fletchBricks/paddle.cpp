#include "maths.cpp"

class Paddle
{
public:
    Paddle(){};

    Vec2 pos;
    int direction;

    void Update(float deltaTime)
    {
        pos.x += direction * 300.0f * deltaTime;
    }

};
