// This file is the declaration of all integrators
// going to be used by the simulation
#pragma once
#include "ElectrostaticSystem.h"

#define VEL_MAX 600.0f

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
            Vec2 a = c.force / c.mass;
            c.vel += a * dt;

            // limit velocity for better looking simulation
            c.vel.Clamp(0, VEL_MAX);
            c.pos += c.vel * dt;
        }
    }
};
