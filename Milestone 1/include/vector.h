#ifndef _VECTOR_H
#define _VECTOR_H
#include <cmath> // sqrt

// 2D vector mostly for handling the balls
class Vector{
    public:
        Vector(float _x, float _y) : x(_x), y(_y){}
        Vector() : x(0), y(0){}
        Vector(const Vector& v) : x(v.x), y(v.y) {}

        Vector& operator=(const Vector& v);

        Vector operator+(Vector& v);
        Vector operator-(Vector& v);
        Vector operator*(float n);

        bool operator==(const Vector& v) const;
        bool operator!=(const Vector& v) const;

        void operator+=(const Vector& v);
        void operator-=(const Vector& v);
        void operator*=(const Vector& v);
        void operator/=(const Vector& v);

        void operator*=(const float n );
        void operator/=(const float n );

        float length() const;

        void normalize();

        friend float dot(const Vector& left, const Vector& right);

        float getX(){
            return x;
        }
        float getY(){
            return y;
        }

    private:
        float x, y;
};

Vector Vector::operator+(Vector& v) {
    return Vector(x + v.x, y + v.y);
}

Vector Vector::operator-(Vector& v) {
    return Vector(x + v.x, y + v.y);
}

Vector Vector::operator*(float n) {
    return Vector(x * n, y * n);
}

void Vector::operator*=( const Vector& v ) {
  x *= v.x;
  y *= v.y;
}

void Vector::operator*=( const float n ) {
  x *= n;
  y *= n;
}

void Vector::operator/=( const float n ) {
  x /= n;
  y /= n;
}

void Vector::operator/=( const Vector& v ) {
  x /= v.x;
  y /= v.y;
}

inline bool Vector::operator==( const Vector& v ) const {
  return (v.x == x and v.y == y);
}

inline bool Vector::operator!=( const Vector& v ) const {
  return !(*this == v);
}

inline float dot(const Vector& v1, const Vector& v2) {
  return (v1.x * v2.x) + (v1.y * v2.y);
}

inline float Vector::length() const {
  return sqrt((x * x) + (y * y));
}

inline void Vector::normalize() {
  float len = length();
  x /= len;
  y /= len;
}

#endif
