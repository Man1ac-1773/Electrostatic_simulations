// force abstraction to switch out laws in case required
// Makes experimentation with different force laws easy
// Can switch out to gravity later, or have multiple force systems
//
#pragma once
#include <cmath>

#include "../Charge.h"

class InteractionLaw
{
  public:
    virtual Vec2 ComputeForce(const Charge& q1, const Charge& q2) = 0;
    virtual Vec2 ComputeField(const Charge& q, const Vec2& point) = 0;
    virtual float ComputePotential(const Charge& q, const Vec2& point) = 0;
    virtual ~InteractionLaw() = default;
};

class CoulombInteraction : public InteractionLaw
{
    // kQq/r^2
  public:
    CoulombInteraction(float _k = 1000000.0f, float softening = 0.01f) : k(_k), epsilon(softening * softening) {}
    // compute field at a point due to one charge
    virtual Vec2 ComputeField(const Charge& q, const Vec2& point) override
    {
        Vec2 r = point - q.pos;
        float distSqr = r.LengthSqr() + epsilon;
        float invDist = 1.0f / sqrt(distSqr);
        float coeff = k * q.q * invDist * invDist * invDist;
        Vec2 field = r * coeff;
        return field;
    }
    // compute potential at a point due to one charge
    virtual float ComputePotential(const Charge& q, const Vec2& point) override
    {
        Vec2 r = point - q.pos;
        float dist = sqrt(r.LengthSqr() + epsilon);
        return (k * q.q) / dist;
    }
    // compute force between two charges
    virtual Vec2 ComputeForce(const Charge& q1, const Charge& q2) override
    {
        Vec2 field = ComputeField(q1, q2.pos);
        Vec2 force = field * q2.q;
        return force;
    }

  private:
    float k;
    float epsilon; // stores the squared value
};
