#include "math/quaternion.h"

quaternion::quaternion() : q0(0.0f), q1(0.0f), q2(0.0f), q3(0.0f) {}
quaternion::quaternion(float w, float x, float y, float z) : q0(w), q1(x), q2(y), q3(z) {}

quaternion quaternion::multiply(const quaternion& q) const
{
    return quaternion(
        q0*q.q0 - q1*q.q1 - q2*q.q2 - q3*q.q3,
        q0*q.q1 + q1*q.q0 + q2*q.q3 - q3*q.q2,
        q0*q.q2 - q1*q.q3 + q2*q.q0 + q3*q.q1,
        q0*q.q3 + q1*q.q2 - q2*q.q1 + q3*q.q0
    );
}

void quaternion::normalize()
{
    float mag_sqrd = q0*q0 + q1*q1 + q2*q2 + q3*q3;

    float inv_sqr = 1.0f / std::sqrtf(mag_sqrd);
    q0 *= inv_sqr;
    q1 *= inv_sqr;
    q2 *= inv_sqr;
    q3 *= inv_sqr;
}