#pragma once

#include <cmath>

struct quaternion
{
    float q0, q1, q2, q3;
    quaternion();
    quaternion(float w, float x, float y, float z); // Corresponds to q0 .. q3

    quaternion multiply(const quaternion& q) const;
    void normalize();
};