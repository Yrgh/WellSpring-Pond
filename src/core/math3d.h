#include <glm/mat3x3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

class Vec2 {
private:
    glm::vec2 internal;
public: 
    Vec2(float x) : internal(x, x) {}
    Vec2(float x, float y) : internal(x, y) {}
    Vec2(const Vec2 &other) : internal(other.internal) {}

    Vec2 &operator=(const Vec3 2other) {
        internal = other.internal;
        return *this;
    }

    Vec2 operator+(const Vec2 &other) const {
        return internal + other.internal;
    }

    Vec2 operator-(const Vec2 &other) const {
        return internal - other.internal;
    }

    Vec2 operator*(const Vec2 &other) const {
        return internal * other.internal;
    }

    Vec2 operator/(const Vec2 &other) const {
        return internal / other.internal;
    }

    Vec2 operator+(float x) const {
        return *this + Vec2(x);
    }

    Vec2 operator-(float x) const {
        return *this - Vec2(x);
    }

    Vec2 operator*(float x) const {
        return *this * Vec2(x);
    }

    Vec2 operator/(float x) const {
        return *this / Vec2(x);
    }

    Vec2 &operator+=(const Vec2 &other) { return *this = (*this + other); }
    Vec2 &operator-=(const Vec2 &other) { return *this = (*this - other); }
    Vec2 &operator*=(const Vec2 &other) { return *this = (*this * other); }
    Vec2 &operator/=(const Vec2 &other) { return *this = (*this / other); }

    Vec2 &operator+=(float x) { return *this = (*this + x); }
    Vec2 &operator-=(float x) { return *this = (*this - x); }
    Vec2 &operator*=(float x) { return *this = (*this * x); }
    Vec2 &operator/=(float x) { return *this = (*this / x); }

    operator glm::vec2() const { return internal; }

    float &x() { return internal.x; }
    float &y() { return internal.y; }

    Vec2 yx() const { return Vec2(y(), x()); }

    static float dot(const Vec2 &a, const Vec2 &b) {
        return a.x() * b.x() + a.y() * b.y();
    }

    float dot(const Vec2 &other) const {
        return dot(*this, other);
    }

    float length() const {
        return sqrt(dot(*this, *this));
    }

    Vec2 normalized() const {
        return *this / length();
    }
};

class Vec3 {
private:
    glm::vec3 internal;
public:
    Vec3(float x) : internal(x, x, x) {}
    Vec3(float x, float y, float z) : internal(x, y, z) {}
    Vec3(const Vec3 &other) : internal(other.internal) {}
    Vec3(float x, const Vec2 &yz) : intenal(x, yz.y(), yz.z()) {}
    Vec3(const Vec2 &xy, float z) : intenal(xy.x(), xy.y(), z) {}

    Vec3 &operator=(const Vec3 &other) {
        internal = other.internal;
        return *this;
    }

    Vec3 operator+(const Vec3 &other) const {
        return internal + other.internal;
    }

    Vec3 operator-(const Vec3 &other) const {
        return internal - other.internal;
    }

    Vec3 operator*(const Vec3 &other) const {
        return internal * other.internal;
    }

    Vec3 operator/(const Vec3 &other) const {
        return internal / other.internal;
    }

    Vec3 operator+(float x) const {
        return *this + Vec3(x);
    }

    Vec3 operator-(float x) const {
        return *this - Vec3(x);
    }

    Vec3 operator*(float x) const {
        return *this * Vec3(x);
    }

    Vec3 operator/(float x) const {
        return *this / Vec3(x);
    }

    Vec3 &operator+=(const Vec3 &other) { return *this = (*this + other); }
    Vec3 &operator-=(const Vec3 &other) { return *this = (*this - other); }
    Vec3 &operator*=(const Vec3 &other) { return *this = (*this * other); }
    Vec3 &operator/=(const Vec3 &other) { return *this = (*this / other); }

    Vec3 &operator+=(float x) { return *this = (*this + x); }
    Vec3 &operator-=(float x) { return *this = (*this - x); }
    Vec3 &operator*=(float x) { return *this = (*this * x); }
    Vec3 &operator/=(float x) { return *this = (*this / x); }

    operator glm::vec3() const { return internal; }

    float &x() { return internal.x; }
    float &y() { return internal.y; }
    float &z() { return internal.z; }

    Vec2 xy() const { return Vec2(x(), y()); }
    Vec2 xz() const { return Vec2(x(), z()); }

    static float dot(const Vec3 &a, const Vec3 &b) {
        return a.x() * b.x() + a.y() * b.y() + a.z() * b.z();
    }

    float dot(const Vec3 &other) const {
        return dot(*this, other);
    }

    float length() const {
        return sqrt(dot(*this, *this));
    }

    Vec3 normalized() const {
        return *this / length();
    }
};