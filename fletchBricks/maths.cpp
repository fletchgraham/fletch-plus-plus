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
    BBox(Vec2 mMin, Vec2 mMax) : mMin(mMin), mMax(mMax) { }
    Vec2 mMax;
    Vec2 mMin;

    Vec2 Dimensions() {
        dimensions = mMax - mMin;

        // is this creating a new Vec2 every time? or returning 
        // a reference to dimensions?
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
            std::max(mMin.x, other.mMin.x),
            std::max(mMin.y, other.mMin.y)
        );
        Vec2 newMax = Vec2(
            std::min(mMax.x, other.mMax.x),
            std::min(mMax.y, other.mMax.y)
        );
        return BBox(newMin, newMax);
    }

    bool Intersects(BBox &other)
    {
        return (
            other.mMin.x < mMin.x && mMin.x < other.mMax.x &&
            other.mMin.y < mMin.y && mMin.y < other.mMax.y ||
            other.mMin.x < mMax.x && mMax.x < other.mMax.x &&
            other.mMin.y < mMax.y && mMax.y < other.mMax.y
        );
    }

private:
    Vec2 dimensions;

};
