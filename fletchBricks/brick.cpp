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
    float hitRadius;

    void HandleBall(Ball &ball)
    {
        if (broken) {
            return;
        }
        
        if (GetHitBoxTop().Contains(ball.pos) && ball.vel.y <= 0) {
            ball.BounceVertical();
            broken = true;
        }
        else if (GetHitBoxBottom().Contains(ball.pos) && ball.vel.y >= 0) {
            ball.BounceVertical();
            broken = true;
        }
        else if (GetHitBoxLeft().Contains(ball.pos) && ball.vel.x >= 0) {
            ball.BounceHorizontal();
            broken = true;
        }
        else if (GetHitBoxRight().Contains(ball.pos) && ball.vel.x <= 0) {
            ball.BounceHorizontal();
            broken = true;
        }
    }

    BBox GetHitBoxTop(){
        BBox selfBox = getBBox();
        return BBox(
            selfBox.min.x,
            selfBox.max.y - hitRadius,
            selfBox.max.x,
            selfBox.max.y + hitRadius
        );
    }
    BBox GetHitBoxBottom(){
        BBox selfBox = getBBox();
        return BBox(
            selfBox.min.x,
            selfBox.min.y - hitRadius,
            selfBox.max.x,
            selfBox.min.y + hitRadius
        );
    }
    BBox GetHitBoxLeft(){
        BBox selfBox = getBBox();
        return BBox(
            selfBox.min.x - hitRadius,
            selfBox.min.y,
            selfBox.min.x + hitRadius,
            selfBox.max.y
        );
    }
    BBox GetHitBoxRight(){
        BBox selfBox = getBBox();
        return BBox(
            selfBox.max.x - hitRadius,
            selfBox.min.y,
            selfBox.max.x + hitRadius,
            selfBox.max.y
        );
    }

    BBox getBBox()
    {
        return BBox(
            Vec2(pos.x - w/2, pos.y - h/2),
            Vec2(pos.x + w/2, pos.y + h/2)
        );
    }
};
