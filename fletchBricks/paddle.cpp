#include "maths.cpp"

class Paddle
{
public:
    Paddle(){};

    Vec2 pos;
    int direction;

    float width = 100.0f;

    float leftLimit;
    float rightLimit;

    float speed = 500.f;
    float tipFactor = 200.f;

    void Update(float deltaTime)
    {
        if (direction != 0)
        {
            pos.x += direction * speed * deltaTime;
            ClampX();
        }

    }

    void HandleBall(Ball& ball)
    {
        float alignmentX = AlignmentX(ball);

        if (abs(alignmentX) > 1)
        {
            return;
        }

        else if (isAlignedY(ball))
        {
            ball.vel.y *= -1.0f;
            ball.vel.x += alignmentX * tipFactor;
        }

    }

private:

    bool isAlignedY(Ball& ball)
    {
        return (
            // We are in the correct y-position
            ball.pos.y <= pos.y + 5.0f && ball.pos.y >= pos.y - 5.0f &&
            // The ball is moving down
            ball.vel.y > 0.0f
        );
    }

    float AlignmentX(Ball& ball)
    // -1 to 1 along the width, 0 is centered
    {
        return (ball.pos.x - pos.x) / (width / 2);
    }

    void ClampX()
    {
        float leftExtremePos = leftLimit + width/2;
        float rightExtremePos = rightLimit - width/2;

        if (pos.x < leftExtremePos) 
        {
            pos.x = leftExtremePos;
        }
        else if (pos.x > rightExtremePos) 
        {
            pos.x = rightExtremePos;
        }
    }
};
