#include "lorenz.h"
Vector3 lorenz(float &x, float &y, float &z, float rho, float beta, float sigma, float dt)
{
    float dxdt = sigma * (y - x);
    float dydt = x * (rho - z) - y;
    float dzdt = x * y - beta * z;

    x += dxdt * dt;
    y += dydt * dt;
    z += dzdt * dt;

    Vector3 point = {x, z - 25.0f, y};
    return point;
}