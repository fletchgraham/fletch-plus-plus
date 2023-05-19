# include "maths.cpp"

class Brick
{
public:
    Brick() {}
    Brick(float x, float y, float w, float h)
    : pos(x, y), w(w), h(h) { }
    Vec2 pos;
    float w;
    float h;
};
