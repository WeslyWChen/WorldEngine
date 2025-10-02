//
// Created by 30632 on 2025/10/2.
//

#ifndef WORLDENGINE_POINT3_H
#define WORLDENGINE_POINT3_H

#include <cmath>

#include "Point.h"

namespace WorldEngine
{
    struct Point3 final {
        float x = 0.f;
        float y = 0.f;
        float z = 0.f;

        Point3() = default;
        ~Point3() = default;
        Point3(const Point3&) = default;
        Point3& operator=(const Point3&) = default;
        Point3(Point3&&) = default;
        Point3& operator=(Point3&&) = default;

        Point3(float x, float y, float z) { set(x, y, z); }
        Point3(Point pt2, float z) { set(pt2.x, pt2.y, z); }

        static constexpr Point3 Make(float x, float y, float z) { return Point3 {x, y, z}; }

        static float Distance(const Point3& lhs, const Point3& rhs) { return (lhs - rhs).length(); }
        static float DotProduct(const Point3& lhs, const Point3& rhs) { return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z; }
        static Point3 CrossProduct(const Point3& lhs, const Point3& rhs)
        {
            return Point3::Make(lhs.y * rhs.z - lhs.z * rhs.y, lhs.z * rhs.x - lhs.x * rhs.z, lhs.x * rhs.y - lhs.y * rhs.x);
        }
        static Point3 Normalize(const Point3& pt)
        {
            Point3 ret = pt;
            ret.normalize();
            return ret;
        }

        bool isZero() const { return x == 0.f && y == 0.f && z == 0.f; }
        bool isFinite() const { return std::isfinite(x) && std::isfinite(y) && std::isfinite(z); }

        float length() const
        {
            float magSq = x * x + y * y + z * z;
            if (std::isfinite(magSq))
                return std::sqrt(magSq);

            double xx = x;
            double yy = y;
            double zz = z;
            return std::sqrt(xx * xx + yy * yy + zz * zz);
        }

        float distanceToOrigin() const { return length(); }

        void set(float _x, float _y, float _z)
        {
            this->x = _x;
            this->y = _y;
            this->z = _z;
        }

        void set(int _x, int _y, int _z)
        {
            this->x = static_cast<float>(_x);
            this->y = static_cast<float>(_y);
            this->z = static_cast<float>(_z);
        }

        void setAbs(const Point3& pt)
        {
            this->x = std::abs(pt.x);
            this->y = std::abs(pt.y);
            this->z = std::abs(pt.z);
        }

        void offset(float _x, float _y, float _z)
        {
            this->x += _x;
            this->y += _y;
            this->z += _z;
        }

        void offset(const Point3& pt) { offset(pt.x, pt.y, pt.z); }

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
            z *= scale;

            return true;
        }

        Point3 operator-() const { return Point3(-x, -y, -z); }

        void operator+=(const Point3& pt)
        {
            x += pt.x;
            y += pt.y;
            z += pt.z;
        }

        void operator-=(const Point3& pt)
        {
            x -= pt.x;
            y -= pt.y;
            z -= pt.z;
        }

        void operator*=(float scale)
        {
            x *= scale;
            y *= scale;
            z *= scale;
        }

        void operator/=(float scale)
        {
            if (std::fabs(scale) < std::numeric_limits<float>::epsilon()) {
                x = 0.f;
                y = 0.f;
                z = 0.f;
            } else {
                x /= scale;
                y /= scale;
                z /= scale;
            }
        }

        friend bool operator==(const Point3& lhs, const Point3& rhs) = default;
        friend bool operator!=(const Point3& lhs, const Point3& rhs) = default;

        friend Point3 operator+(const Point3& lhs, const Point3& rhs) { return Point3::Make(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z); }
        friend Point3 operator-(const Point3& lhs, const Point3& rhs) { return Point3::Make(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z); }

        friend Point3 operator+(const Point3& lhs, float rhs) { return Point3::Make(lhs.x + rhs, lhs.y + rhs, lhs.z + rhs); }
        friend Point3 operator-(const Point3& lhs, float rhs) { return Point3::Make(lhs.x - rhs, lhs.y - rhs, lhs.z - rhs); }
        friend Point3 operator*(const Point3& lhs, float rhs) { return Point3::Make(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs); }
        friend Point3 operator/(const Point3& lhs, float rhs) { return Point3::Make(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs); }
    };
}  // namespace WorldEngine

#endif  // WORLDENGINE_POINT3_H
