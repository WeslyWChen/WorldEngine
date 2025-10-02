//
// Created by 30632 on 2025/10/2.
//

#include "Matrix.h"

#include <cassert>
#include <limits>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

using namespace std;
using namespace WorldEngine;

namespace MatrixUtil
{
    static glm::vec2 convert(const Point& point)  // NOLINT
    {
        return glm::vec2(point.x, point.y);
    }
    static glm::vec3 convert(const Point3& point)  // NOLINT
    {
        return glm::vec3(point.x, point.y, point.z);
    }
    static glm::vec4 convert(const Point4& point)
    {
        return glm::vec4(point.x, point.y, point.z, point.w);
    }
    static glm::mat4 convert(const Matrix& matrix)
    {
        return glm::make_mat4(matrix.mat.data());
    }

    static Point convert(const glm::vec2& point)  // NOLINT
    {
        return Point::Make(point.x, point.y);
    }
    static Point3 convert(const glm::vec3& point)  // NOLINT
    {
        return Point3::Make(point.x, point.y, point.z);
    }
    static Point4 convert(const glm::vec4& point)
    {
        return Point4::Make(point.x, point.y, point.z, point.w);
    }
    static Matrix convert(const glm::mat4& matrix)
    {
        return Matrix::Make(matrix[0][0],
                            matrix[0][1],
                            matrix[0][2],
                            matrix[0][3],
                            matrix[1][0],
                            matrix[1][1],
                            matrix[1][2],
                            matrix[1][3],
                            matrix[2][0],
                            matrix[2][1],
                            matrix[2][2],
                            matrix[2][3],
                            matrix[3][0],
                            matrix[3][1],
                            matrix[3][2],
                            matrix[3][3]);
    }
}  // namespace MatrixUtil

Matrix Matrix::MakeScale(float scale)
{
    Matrix mat;
    mat.setScale(scale);
    return mat;
}

Matrix Matrix::MakeScale(float xScale, float yScale, float zScale)
{
    Matrix mat;
    mat.setScale(xScale, yScale, zScale);
    return mat;
}

Matrix Matrix::MakeTranslate(float x, float y, float z)
{
    Matrix mat;
    mat.setTranslate(x, y, z);
    return mat;
}

Matrix Matrix::MakeTranslate(int x, int y, int z)
{
    return MakeTranslate(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z));
}

Matrix Matrix::MakeTranslate(const Vector3& pt)
{
    return MakeTranslate(pt.x, pt.y, pt.z);
}

Matrix Matrix::MakeRotate(float radians, const Vector3& axis)
{
    Matrix mat;
    mat.setRotate(radians, axis);
    return mat;
}

Matrix Matrix::MakeLookAt(const Vector3& eye, const Vector3& center, const Vector3& up)
{
    auto glmMat = glm::lookAt(glm::vec3(eye.x, eye.y, eye.z), glm::vec3(center.x, center.y, center.z), glm::vec3(up.x, up.y, up.z));
    return MatrixUtil::convert(glmMat);
}

bool Matrix::isFinite() const
{
    return std::all_of(mat.begin(), mat.end(), [](float val) { return std::isfinite(val); });
}

float Matrix::getTranslateX() const
{
    return mat[3];
}

float Matrix::getTranslateY() const
{
    return mat[7];
}

float Matrix::getTranslateZ() const
{
    return mat[11];
}

float Matrix::getTranslateW() const
{
    return mat[15];
}

float Matrix::getScaleX() const
{
    return mat[0];
}

float Matrix::getScaleY() const
{
    return mat[5];
}

float Matrix::getScaleZ() const
{
    return mat[10];
}

float Matrix::getScaleW() const
{
    return mat[15];
}

std::optional<Matrix> Matrix::invMatrix() const
{
    auto glmMat = MatrixUtil::convert(*this);
    float determinant = glm::determinant(glmMat);
    if (std::fabs(determinant) < std::numeric_limits<float>::epsilon())
        return std::nullopt;
    return MatrixUtil::convert(glm::inverse(glmMat));
}

Matrix Matrix::transpose() const
{
    return MatrixUtil::convert(glm::transpose(MatrixUtil::convert(*this)));
}

Vector4 Matrix::mapPt(float x, float y, float z, float w) const
{
    return MatrixUtil::convert(glm::vec4(x, y, z, w) * MatrixUtil::convert(*this));
}

Vector4 Matrix::operator*(const Vector4& v) const
{
    return MatrixUtil::convert(MatrixUtil::convert(*this) * MatrixUtil::convert(v));
}

Vector3 Matrix::operator*(const Vector3& v) const
{
    auto v4 = MatrixUtil::convert(*this) * glm::vec4(v.x, v.y, v.z, 0.f);
    return Vector3(v4.x, v4.y, v4.z);
}

void Matrix::setIdentity()
{
    mat = {1.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 1.f};
}

void Matrix::setScale(float scale)
{
    setScale(scale, scale, scale);
}

void Matrix::setScale(float xScale, float yScale, float zScale)
{
    mat = {xScale, 0.f, 0.f, 0.f, 0.f, yScale, 0.f, 0.f, 0.f, 0.f, zScale, 0.f, 0.f, 0.f, 0.f, 1.f};
}

void Matrix::setTranslate(float x, float y, float z)
{
    mat = {1.f, 0.f, 0.f, x, 0.f, 1.f, 0.f, y, 0.f, 0.f, 1.f, z, 0.f, 0.f, 0.f, 1.f};
}

void Matrix::setRotate(float radians, const Vector3& axis)
{
    auto len = axis.length();
    if (len > std::numeric_limits<float>::epsilon() && std::isfinite(len)) {
        auto glmMat = glm::identity<glm::mat4>();
        *this = MatrixUtil::convert(glm::rotate(glmMat, radians, glm::vec3(axis.x, axis.y, axis.z)));
    } else {
        setIdentity();
    }
}

void Matrix::setConcat(const Matrix& lhs, const Matrix& rhs)
{
    glm::mat4 aMat = MatrixUtil::convert(lhs);
    glm::mat4 bMat = MatrixUtil::convert(rhs);
    mat = std::move(MatrixUtil::convert(aMat * bMat).mat);
}

Matrix& Matrix::preConcat(const Matrix& _mat)
{
    auto glmThis = MatrixUtil::convert(*this);
    auto glmMat = MatrixUtil::convert(_mat);
    *this = MatrixUtil::convert(glmMat * glmThis);
    return *this;
}

Matrix& Matrix::postConcat(const Matrix& _mat)
{
    auto glmThis = MatrixUtil::convert(*this);
    auto glmMat = MatrixUtil::convert(_mat);
    *this = MatrixUtil::convert(glmThis * glmMat);
    return *this;
}

Matrix& Matrix::preTranslate(float x, float y, float z)
{
    return preConcat(MakeTranslate(x, y, z));
}

Matrix& Matrix::postTranslate(float x, float y, float z)
{
    return postConcat(MakeTranslate(x, y, z));
}

Matrix& Matrix::preTranslate(const Vector3& pt)
{
    return preTranslate(pt.x, pt.y, pt.z);
}

Matrix& Matrix::postTranslate(const Vector3& pt)
{
    return postTranslate(pt.x, pt.y, pt.z);
}

Matrix& Matrix::preScale(float scale)
{
    return preScale(scale, scale, scale);
}

Matrix& Matrix::postScale(float scale)
{
    return postScale(scale, scale, scale);
}

Matrix& Matrix::preScale(float xScale, float yScale, float zScale)
{
    return preConcat(MakeScale(xScale, yScale, zScale));
}

Matrix& Matrix::postScale(float xScale, float yScale, float zScale)
{
    return postConcat(MakeScale(xScale, yScale, zScale));
}

void Matrix::operator+=(const Matrix& rhs)
{
    for (int i = 0; i < 16; ++i)
        mat[i] += rhs.mat[i];
}

void Matrix::operator-=(const Matrix& rhs)
{
    for (int i = 0; i < 16; ++i)
        mat[i] -= rhs.mat[i];
}

void Matrix::operator*=(const Matrix& rhs)
{
    setConcat(*this, rhs);
}

Matrix operator+(const Matrix& lhs, const Matrix& rhs)
{
    Matrix mat(lhs);
    for (int i = 0; i < 16; ++i)
        mat.mat[i] += rhs.mat[i];
    return mat;
}

Matrix operator-(const Matrix& lhs, const Matrix& rhs)
{
    Matrix mat(lhs);
    for (int i = 0; i < 16; ++i)
        mat.mat[i] -= rhs.mat[i];
    return mat;
}

Matrix operator*(const Matrix& lhs, const Matrix& rhs)
{
    Matrix mat;
    mat.setConcat(lhs, rhs);
    return mat;
}

Matrix operator-(const Matrix& lhs, float rhs)
{
    Matrix mat(lhs);
    for (int i = 0; i < 16; ++i)
        mat.mat[i] -= rhs;
    return mat;
}

Matrix operator*(const Matrix& lhs, float rhs)
{
    Matrix mat(lhs);
    for (int i = 0; i < 16; ++i)
        mat.mat[i] *= rhs;
    return mat;
}

Matrix operator/(const Matrix& lhs, float rhs)
{
    if (std::fabs(rhs) < std::numeric_limits<float>::epsilon())
        return Matrix::MakeIdentity();
    Matrix mat(lhs);
    for (int i = 0; i < 16; ++i)
        mat.mat[i] /= rhs;
    return mat;
}