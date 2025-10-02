//
// Created by 30632 on 2025/10/2.
//

#ifndef WORLDENGINE_POINT_H
#define WORLDENGINE_POINT_H

#include <cmath>

namespace WorldEngine
{
    struct Point final {
        float x = 0.f;
        float y = 0.f;

        static constexpr Point Make(float x, float y) { return Point {x, y}; }

        static float Distance(const Point& lhs, const Point& rhs) { return (lhs - rhs).length(); }
        static float DotProduct(const Point& lhs, const Point& rhs) { return lhs.x * rhs.x + lhs.y * rhs.y; }
        static float CrossProduct(const Point& lhs, const Point& rhs) { return lhs.x * rhs.y - lhs.y * rhs.x; }
        static Point Normalize(const Point& pt)
        {
            Point ret = pt;
            ret.normalize();
            return ret;
        }

        bool isZero() const { return x == 0.f && y == 0.f; }
        bool isFinite() const { return std::isfinite(x) && std::isfinite(y); }

        float length() const
        {
            float mag2 = x * x + y * y;
            if (std::isfinite(mag2))
                return std::sqrt(x * x + y * y);

            double xx = x;
            double yy = y;
            return std::sqrt(xx * xx + yy * yy);
        }

        float distanceToOrigin() const { return length(); }

        void set(float _x, float _y)
        {
            this->x = _x;
            this->y = _y;
        }

        void set(int _x, int _y)
        {
            this->x = static_cast<float>(_x);
            this->y = static_cast<float>(_y);
        }

        void setAbs(const Point& pt)
        {
            this->x = std::fabs(pt.x);
            this->y = std::fabs(pt.y);
        }

        void offset(float _x, float _y)
        {
            this->x += _x;
            this->y += _y;
        }

        void offset(const Point& pt) { offset(pt.x, pt.y); }

        bool normalize()
        {
            if (isZero())
                return false;

            auto len = length();
            if (len < std::numeric_limits<float>::epsilon())
                return false;

            float scale = 1.f / len;
            x *= scale;
            y *= scale;

            return true;
        }

        Point operator-() const { return Point {-x, -y}; }

        void operator+=(const Point& point)
        {
            x += point.x;
            y += point.y;
        }

        void operator-=(const Point& point)
        {
            x -= point.x;
            y -= point.y;
        }

        void operator*=(float scale)
        {
            x *= scale;
            y *= scale;
        }

        void operator/=(float scale)
        {
            if (std::fabs(scale) < std::numeric_limits<float>::epsilon()) {
                x = 0.f;
                y = 0.f;
            } else {
                x /= scale;
                y /= scale;
            }
        }

        friend bool operator==(const Point&, const Point&) = default;
        friend bool operator!=(const Point&, const Point&) = default;

        friend Point operator+(const Point& lhs, const Point& rhs) { return Point {lhs.x + rhs.x, lhs.y + rhs.y}; }
        friend Point operator-(const Point& lhs, const Point& rhs) { return Point {lhs.x - rhs.x, lhs.y - rhs.y}; }

        friend Point operator+(const Point& lhs, float rhs) { return Point {lhs.x + rhs, lhs.y + rhs}; }
        friend Point operator-(const Point& lhs, float rhs) { return Point {lhs.x - rhs, lhs.y - rhs}; }
        friend Point operator*(const Point& lhs, float rhs) { return Point {lhs.x * rhs, lhs.y * rhs}; }
        friend Point operator/(const Point& lhs, float rhs) { return Point {lhs.x / rhs, lhs.y / rhs}; }
    };
}  // namespace WorldEngine

#endif  // WORLDENGINE_POINT_H
