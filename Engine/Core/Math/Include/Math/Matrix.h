//
// Created by 30632 on 2025/10/2.
//

#ifndef WORLDENGINE_MATRIX_H
#define WORLDENGINE_MATRIX_H

#include <array>
#include <optional>

#include "MathApi.h"
#include "Vector.h"

namespace WorldEngine
{
    class WEMATH_API Matrix final {
    public:
        std::array<float, 16> mat {};

    public:
        static constexpr Matrix MakeIdentity() { return Matrix {}; }

        static constexpr Matrix Make(float m00,
                                     float m01,
                                     float m02,
                                     float m03,
                                     float m10,
                                     float m11,
                                     float m12,
                                     float m13,
                                     float m20,
                                     float m21,
                                     float m22,
                                     float m23,
                                     float m30,
                                     float m31,
                                     float m32,
                                     float m33)
        {
            return Matrix {std::array {m00, m01, m02, m03, m10, m11, m12, m13, m20, m21, m22, m23, m30, m31, m32, m33}};
        }

        static constexpr Matrix Make(const std::array<float, 16>& mat) { return Matrix(mat); }

        static constexpr Matrix Make(const Vector4& v0, const Vector4& v1, const Vector4& v2, const Vector4& v3)
        {
            return Make(std::array {v0.x, v0.y, v0.z, v0.w, v1.x, v1.y, v1.z, v1.w, v2.x, v2.y, v2.z, v2.w, v3.x, v3.y, v3.z, v3.w});
        }

        static Matrix MakeScale(float scale);

        static Matrix MakeScale(float xScale, float yScale, float zScale);

        static Matrix MakeTranslate(float x, float y, float z);

        static Matrix MakeTranslate(int x, int y, int z);

        static Matrix MakeTranslate(const Vector3& pt);

        static Matrix MakeRotate(float radians, const Vector3& axis);

        static Matrix MakeLookAt(const Vector3& eye, const Vector3& center, const Vector3& up);

    public:
        constexpr Matrix() { mat = {1.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 1.f}; }
        constexpr explicit Matrix(const std::array<float, 16>& mat) { this->mat = mat; }
        ~Matrix() = default;
        Matrix(const Matrix&) = default;
        Matrix& operator=(const Matrix&) = default;
        Matrix(Matrix&&) = default;
        Matrix& operator=(Matrix&&) = default;

    public:
        bool isFinite() const;

        float getTranslateX() const;
        float getTranslateY() const;
        float getTranslateZ() const;
        float getTranslateW() const;
        float getScaleX() const;
        float getScaleY() const;
        float getScaleZ() const;
        float getScaleW() const;

        std::optional<Matrix> invMatrix() const;
        Matrix transpose() const;

        Vector4 mapPt(float x, float y, float z, float w) const;
        Vector4 operator*(const Vector4& v) const;
        Vector3 operator*(const Vector3& v) const;

    public:
        void setIdentity();
        void setScale(float scale);
        void setScale(float xScale, float yScale, float zScale);
        void setTranslate(float x, float y, float z);
        void setRotate(float radians, const Vector3& axis);
        void setConcat(const Matrix& lhs, const Matrix& rhs);

    public:
        Matrix& preConcat(const Matrix& _mat);
        Matrix& postConcat(const Matrix& _mat);
        Matrix& preTranslate(float x, float y, float z);
        Matrix& postTranslate(float x, float y, float z);
        Matrix& preTranslate(const Vector3& pt);
        Matrix& postTranslate(const Vector3& pt);
        Matrix& preScale(float scale);
        Matrix& postScale(float scale);
        Matrix& preScale(float xScale, float yScale, float zScale);
        Matrix& postScale(float xScale, float yScale, float zScale);

    public:
        void operator+=(const Matrix& rhs);
        void operator-=(const Matrix& rhs);
        void operator*=(const Matrix& rhs);

        friend Matrix operator+(const Matrix& lhs, const Matrix& rhs);
        friend Matrix operator-(const Matrix& lhs, const Matrix& rhs);
        friend Matrix operator*(const Matrix& lhs, const Matrix& rhs);

        friend Matrix operator+(const Matrix& lhs, float rhs);
        friend Matrix operator-(const Matrix& lhs, float rhs);
        friend Matrix operator*(const Matrix& lhs, float rhs);
        friend Matrix operator/(const Matrix& lhs, float rhs);

        friend bool operator==(const Matrix&, const Matrix&) = default;
        friend bool operator!=(const Matrix&, const Matrix&) = default;
    };
}  // namespace WorldEngine

#endif  // WORLDENGINE_MATRIX_H
