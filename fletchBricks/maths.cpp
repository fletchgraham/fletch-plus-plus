class Vec2
{
public:
    float x;
    float y;
    void Add(Vec2 other)
    {
        x = x + other.x;
        y = y + other.y;
    }
};
