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

    void Update(float deltaTime)
    {
        if (direction != 0)
        {
            pos.x += direction * 300.0f * deltaTime;
            ClampX();
        }

    }

    bool isBallCollide(Ball ball)
    {
        float alignment = Alignment(ball);

        return (
            abs(alignment) <= 1 &&
            // We are in the correct y-position
            ball.pos.y <= pos.y + 5.0f && ball.pos.y >= pos.y - 5.0f &&
            // The ball is moving down
            ball.vel.y > 0.0f
        );
    }

    float Alignment(Ball ball)
    // -1 to 1 along the width, 0 is centered
    {
        return (pos.x - ball.pos.x) / (width / 2);
    }

private:
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
