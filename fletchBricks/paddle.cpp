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

    bool isBallCollide(Ball ball)
    {

	float diff = pos.x - ball.pos.x;

	// Take absolute value of difference
	diff = (diff > 0.0f) ? diff : -diff;

	return (
		// Our x-difference is small enough
		diff <= width / 2.0f &&
		// We are in the correct y-position
		ball.pos.y <= pos.y + 5.0f && ball.pos.y >= pos.y - 5.0f &&
		// The ball is moving down
		ball.vel.y > 0.0f
        );
    }
};
