// This file is the declaration of all integrators
// going to be used by the simulation
#pragma once
#include <cmath>

#include "ElectrostaticSystem.h"

#define VEL_MAX 600.0f

inline static Vector2 Vector2Clamp(Vector2 v, float min, float max)
{
    float v_length = std::sqrt(v.x * v.x + v.y * v.y);
    if (v_length > max)
    {
        v.x *= max / v_length;
        v.y *= max / v_length;
    }
    if (v_length < min)
    {
        v.x *= min / v_length;
        v.y *= min / v_length;
    }
    return v;
}

// base template for an integrator
class Integrator
{
  public:
    virtual ~Integrator() = default;
    virtual void Step(ElectrostaticSystem& system, float dt) = 0;
};

// most basic and simple form of integration
// literally just does v + dv;
class EulerIntegrator : public Integrator
{
  public:
    void Step(ElectrostaticSystem& system, float dt) override
    {

        auto& charges = system.GetCharges();
        // assume that forces have already been calculated for this frame
        for (auto& c : charges)
        {

            if (c.isStatic)
                continue;

            // semi-implicit Euler
            Vector2 a = {c.force.x / c.mass, c.force.y / c.mass};
            c.vel.x += a.x * dt;
            c.vel.y += a.y * dt;
            // limit velocity for better looking simulation
            c.vel = Vector2Clamp(c.vel, 0, VEL_MAX);

            c.pos.x += c.vel.x * dt;
            c.pos.y += c.vel.y * dt;
        }
    }
};
