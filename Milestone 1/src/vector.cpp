#include "../include/vector.h"
#include <cmath> // sqrt, sin, cos

float Vector::getX(){
    return x;
}
float Vector::getY(){
    return y;
}

void Vector::setX(float _x){
    x = _x;
}

void Vector::setY(float _y){
    y = _y;
}

Vector Vector::operator+(Vector& v) {
    return Vector(x + v.x, y + v.y);
}

Vector Vector::operator-(Vector& v) {
    return Vector(x + v.x, y + v.y);
}

Vector Vector::operator*(float n) {
    return Vector(x * n, y * n);
}

void Vector::operator+=( const Vector& v ) {
    x += v.x;
    y += v.y;
}
void Vector::operator-=( const Vector& v ) {
    x -= v.x;
    y -= v.y;
}

void Vector::operator*=( const Vector& v ) {
    x *= v.x;
    y *= v.y;
}

void Vector::operator+=( const float n ) {
    x += n;
    y += n;
}

void Vector::operator-=( const float n ) {
    x -= n;
    y -= n;
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

bool Vector::operator==( const Vector& v ) const {
    return (v.x == x and v.y == y);
}

bool Vector::operator!=( const Vector& v ) const {
    return !(*this == v);
}

float dot(const Vector& v1, const Vector& v2) {
    return (v1.x * v2.x) + (v1.y * v2.y);
}

float Vector::length() const {
    return sqrt((x * x) + (y * y));
}

void Vector::normalize() {
    float len = length();
    x /= len;
    y /= len;
}

void Vector::rotate(float theta){
    float _x = x * cos(theta) - y * sin(theta);
    float _y = x * sin(theta) + y * cos(theta);
    x = _x;
    y = _y;
}
