//
// Created by 30632 on 2025/10/2.
//

#ifndef WORLDENGINE_POINT4_H
#define WORLDENGINE_POINT4_H

#include <cmath>

#include "Point3.h"

namespace WorldEngine
{
    struct Point4 final {
        float x = 0.f;
        float y = 0.f;
        float z = 0.f;
        float w = 0.f;

        Point4() = default;
        ~Point4() = default;
        Point4(const Point4&) = default;
        Point4& operator=(const Point4&) = default;
        Point4(Point4&&) = default;
        Point4& operator=(Point4&&) = default;

        constexpr Point4(float x, float y, float z, float w) { set(x, y, z, w); }
        constexpr Point4(Point3 pt3, float w) { set(pt3.x, pt3.y, pt3.z, w); }

        static constexpr Point4 Make(float x, float y, float z, float w) { return Point4 {x, y, z, w}; }

        static float Distance(const Point4& lhs, const Point4& rhs) { return (lhs - rhs).length(); }
        static float DotProduct(const Point4& lhs, const Point4& rhs) { return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w; }
        static Point4 Normalize(const Point4& pt)
        {
            Point4 ret = pt;
            ret.normalize();
            return ret;
        }

        bool isZero() const { return x == 0.f && y == 0.f && z == 0.f && w == 0.f; }
        bool isFinite() const { return std::isfinite(x) && std::isfinite(y) && std::isfinite(z) && std::isfinite(w); }

        float length() const
        {
            float magSq = x * x + y * y + z * z + w * w;
            if (std::isfinite(magSq))
                return std::sqrt(magSq);

            double xx = x;
            double yy = y;
            double zz = z;
            double ww = w;
            return std::sqrt(xx * xx + yy * yy + zz * zz + ww * ww);
        }

        float distanceToOrigin() const { return length(); }

        constexpr void set(float _x, float _y, float _z, float _w)
        {
            this->x = _x;
            this->y = _y;
            this->z = _z;
            this->w = _w;
        }

        constexpr void set(int _x, int _y, int _z, int _w)
        {
            this->x = static_cast<float>(_x);
            this->y = static_cast<float>(_y);
            this->z = static_cast<float>(_z);
            this->w = static_cast<float>(_w);
        }

        void setAbs(const Point4& pt)
        {
            this->x = std::abs(pt.x);
            this->y = std::abs(pt.y);
            this->z = std::abs(pt.z);
            this->w = std::abs(pt.w);
        }

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
            w *= scale;

            return true;
        }

        Point4 operator-() const { return Point4(-x, -y, -z, -w); }

        void operator+=(const Point4& pt)
        {
            x += pt.x;
            y += pt.y;
            z += pt.z;
            w += pt.w;
        }

        void operator-=(const Point4& pt)
        {
            x -= pt.x;
            y -= pt.y;
            z -= pt.z;
            w -= pt.w;
        }

        void operator*=(float scale)
        {
            x *= scale;
            y *= scale;
            z *= scale;
            w *= scale;
        }

        void operator/=(float scale)
        {
            if (std::fabs(scale) < std::numeric_limits<float>::epsilon()) {
                x = 0.f;
                y = 0.f;
                z = 0.f;
                w = 0.f;
            } else {
                x /= scale;
                y /= scale;
                z /= scale;
                w /= scale;
            }
        }

        friend bool operator==(const Point4& lhs, const Point4& rhs) = default;
        friend bool operator!=(const Point4& lhs, const Point4& rhs) = default;

        friend Point4 operator+(const Point4& lhs, const Point4& rhs) { return Point4 {lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w}; }

        friend Point4 operator-(const Point4& lhs, const Point4& rhs) { return Point4 {lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w}; }

        friend Point4 operator+(const Point4& lhs, float rhs) { return Point4 {lhs.x + rhs, lhs.y + rhs, lhs.z + rhs, lhs.w + rhs}; }
        friend Point4 operator-(const Point4& lhs, float rhs) { return Point4 {lhs.x - rhs, lhs.y - rhs, lhs.z - rhs, lhs.w - rhs}; }
        friend Point4 operator*(const Point4& lhs, float rhs) { return Point4 {lhs.x * rhs, lhs.y * rhs, lhs.z * rhs, lhs.w * rhs}; }
        friend Point4 operator/(const Point4& lhs, float rhs) { return Point4 {lhs.x / rhs, lhs.y / rhs, lhs.z / rhs, lhs.w / rhs}; }
    };
}  // namespace WorldEngine

#endif  // WORLDENGINE_POINT4_H
