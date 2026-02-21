#pragma once
#include <vector>

#include "Charge.h"

// the system that each scene might have multiple of.
// It stores charge, and is responsible only for
// computing Forces, field, and potential due to those charges.
// It might be expanded later to demonstrate how two different systems interact
//
class ElectrostaticSystem
{
  public:
    explicit ElectrostaticSystem(float k = 1000000.0f, float softening = 0.01f) : K(k), epsilon(softening) {}

    // add a new charge
    void AddCharge(const Charge& c)
    {
        charges.push_back(c);
    }

    // clear existing charges
    void Clear()
    {
        charges.clear();
    }

    std::vector<Charge>& GetCharges()
    {
        return charges;
    }

    const std::vector<Charge>& GetCharges() const
    {
        return charges;
    }

    void ResetForces()
    {
        for (auto& c : charges)
        {
            c.force = {0, 0};
        }
    }

    void ComputeForces()
    {
        ResetForces();

        const size_t n = charges.size();

        for (size_t i = 0; i < n; ++i)
        {
            for (size_t j = i + 1; j < n; ++j)
            {

                Vec2 r = charges[j].pos - charges[i].pos;
                float distSqr = r.x * r.x + r.y * r.y + epsilon * epsilon;
                float invDist = 1.0f / std::sqrt(distSqr);

                float forceMagnitude = K * charges[i].q * charges[j].q * invDist * invDist * invDist;

                Vec2 force = r * forceMagnitude;

                charges[i].force -= force;
                charges[j].force += force;
            }
        }
    }
    // return vector of electric field at a point due to system
    Vec2 ComputeFieldAt(Vec2 point) const
    {
        Vec2 E = {0, 0};

        for (const auto& c : charges)
        {
            Vec2 r = point - c.pos;

            float distSqr = r.x * r.x + r.y * r.y + epsilon * epsilon;
            float invDist = 1.0f / std::sqrt(distSqr);

            float coeff = K * c.q * invDist * invDist * invDist;

            E += r * coeff;
        }

        return E;
    }
    // return potential at a point due to system
    float ComputePotentialAt(Vec2 point) const
    {
        float V = 0.0f;

        for (const auto& c : charges)
        {
            Vec2 r = point - c.pos;

            float dist = std::sqrt(r.x * r.x + r.y * r.y + epsilon * epsilon);

            V += K * c.q / dist;
        }

        return V;
    }

  private:
    std::vector<Charge> charges;

    float K;       // Coulomb constant
    float epsilon; // softening parameter
};
