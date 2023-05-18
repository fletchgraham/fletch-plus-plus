#include "maths.cpp"

class Paddle
{
public:
    Paddle(){};

    Vec2 pos;
    int direction;
    float width = 100.0f;

    void Update(float deltaTime)
    {
        pos.x += direction * 300.0f * deltaTime;
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
