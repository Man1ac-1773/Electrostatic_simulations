#pragma once
// A minimal vector implementation
// To reduce the dependency of physics and math layers
// of my simulator on raylib.

#include <cmath>
#include <ostream>
class Vec2
{
  public:
    float x;
    float y;
    Vec2(float _x = 0, float _y = 0) : x(_x), y(_y) {}
    // cout overload
    friend std::ostream& operator<<(std::ostream& os, const Vec2& sub)
    {
        os << "{" << sub.x << "," << sub.y << "}";
        return os;
    }

    // ======== arithmetic overloads ===========
    Vec2& operator+=(const Vec2& rhs)
    {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

    friend Vec2 operator+(Vec2 lhs, const Vec2& rhs)
    {
        lhs += rhs;
        return lhs;
    }
    Vec2& operator-=(const Vec2& rhs)
    {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }

    friend Vec2 operator-(Vec2 lhs, const Vec2& rhs)
    {
        lhs -= rhs;
        return lhs;
    }
    Vec2& operator/=(const double& s)
    {
        x /= s;
        y /= s;
        return *this;
    }
    friend Vec2 operator/(Vec2 lhs, const double& rhs)
    {
        lhs /= rhs;
        return lhs;
    }

    Vec2& operator*=(const double& s)
    {
        x *= s;
        y *= s;
        return *this;
    }
    friend Vec2 operator*(Vec2 lhs, const double& rhs)
    {
        lhs *= rhs;
        return lhs;
    }
    // =========== ============
    // ====== Vector functionality =======
    void Normalise()
    {
        double len = Length();
        x /= len;
        y /= len;
    }
    double LengthSqr()
    {
        double len = x * x + y * y;
        return len;
    }
    double Length()
    {
        double len = LengthSqr();
        return sqrt(len);
    }
    double DotProduct(const Vec2& b)
    {
        double dot = x * b.x + y * b.y;
        return dot;
    }
    // =========== =========
};
