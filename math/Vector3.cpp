#include "Vector3.h"

Vector3 Vector3::operator*(const Vector3& v)
{
    Vector3 temp(*this);
    temp.x *= v.x;
    temp.y *= v.y;
    temp.z *= v.z;
    return temp;
}

Vector3 Vector3::operator*(float s)
{
    Vector3 temp(*this);
    temp.x *= s;
    temp.y *= s;
    temp.z *= s;
    return temp;
}
