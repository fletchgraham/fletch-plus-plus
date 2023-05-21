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
    Vec2 max;
    Vec2 min;

    Vec2 Dimensions() {
        dimensions = max - min;
        return dimensions;
    }

    bool isPossible() {
        return (
            Dimensions().x >= 0 &&
            Dimensions().y >= 0
        );
    }

    bool IntersectHorizontal(BBox &other) {

        BBox intersection = IntersectionBox(other);

        if (!intersection.isPossible()) {
            return false;
        }

        return (
            intersection.Dimensions().y >=
            intersection.Dimensions().x
        );
    }

    bool IntersectVertical(BBox &other) {

        BBox intersection = IntersectionBox(other);

        if (!intersection.isPossible()) {
            return false;
        }

        return (
            intersection.Dimensions().x >=
            intersection.Dimensions().y
        );
    }

    BBox IntersectionBox(BBox &other) {
        Vec2 newMin = Vec2(
            std::max(min.x, other.min.x),
            std::max(min.y, other.min.y)
        );
        Vec2 newMax = Vec2(
            std::min(max.x, other.max.x),
            std::min(max.y, other.max.y)
        );
        return BBox(newMin, newMax);
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
