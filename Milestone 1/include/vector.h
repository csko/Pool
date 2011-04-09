#ifndef _VECTOR_H_
#define _VECTOR_H_
#include <cmath> // sqrt, sin, cos

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

        void operator+=(const float n);
        void operator-=(const float n);
        void operator*=(const float n );
        void operator/=(const float n );

        float length() const;

        void normalize();
        void rotate(float theta);

        friend float dot(const Vector& left, const Vector& right);

        float getX();
        float getY();
        void setX(float _x);
        void setY(float _y);

    private:
        float x, y;
};

#endif
