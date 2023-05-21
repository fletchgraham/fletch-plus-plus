#pragma once
#include <algorithm>

struct Vec2
{
    float x;
    float y;

    Vec2(float x, float y) : x(x), y(y) { }
    Vec2() : x(0), y(0) { }

    Vec2 operator+ (const Vec2& other) const {
        return Vec2(x + other.x, y + other.y);
    }

    Vec2 operator- (const Vec2& other) const {
        return Vec2(x - other.x, y - other.y);
    }

    Vec2 operator+ (const float& other) const {
        return Vec2(x + other, y + other);
    }

    Vec2 operator- (const float& other) const {
        return Vec2(x - other, y - other);
    }

    Vec2 operator* (const Vec2& other) const {
        return Vec2(x * other.x, y * other.y);
    }

    Vec2 operator* (const float other) const {
        return Vec2(x * other, y * other);
    }
};

struct BBox
{
    BBox(Vec2 min, Vec2 max) : min(min), max(max) { }
    BBox(float minX, float minY, float maxX, float maxY)
    : min(minX, minY), max(maxX, maxY) { }
    Vec2 max;
    Vec2 min;

    Vec2 Dimensions() {
        dimensions = max - min;
        return dimensions;
    }

    bool Contains(Vec2 point) {
        return (
            point.x > min.x &&
            point.x < max.x &&
            point.y > min.y &&
            point.y < max.y
        );
    }

    bool Intersects(BBox &other)
    {
        return (
            other.min.x < min.x && min.x < other.max.x &&
            other.min.y < min.y && min.y < other.max.y ||
            other.min.x < max.x && max.x < other.max.x &&
            other.min.y < max.y && max.y < other.max.y
        );
    }

private:
    Vec2 dimensions;

};
