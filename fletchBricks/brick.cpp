#include "maths.cpp"
#include "ball.cpp"

class Brick
{
public:
    Brick() {}
    Brick(float x, float y, float w, float h)
    : pos(x, y), w(w), h(h) { }
    Vec2 pos;
    float w;
    float h;
    bool broken = false;

    void HandleBall(Ball &ball)
    {
        if (broken) {
            return;
        }
        
        BBox ballBBox = ball.getBBox();
        BBox selfBBox = getBBox();

        if (selfBBox.IntersectHorizontal(ballBBox)) {
            ball.BounceVertical();
            broken = true;
        }
        else if (selfBBox.IntersectVertical(ballBBox)) {
            ball.BounceHorizontal();
            broken = true;
        }
    }

    BBox getBBox()
    {
        return BBox(
            Vec2(pos.x - w/2, pos.y - h/2),
            Vec2(pos.x + w/2, pos.y + h/2)
        );
    }
};
