#pragma once
#include <cmath>
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

                Vector2 r = {charges[j].pos.x - charges[i].pos.x, charges[j].pos.y - charges[i].pos.y};
                float distSqr = r.x * r.x + r.y * r.y + epsilon * epsilon;
                float invDist = 1.0f / std::sqrt(distSqr);

                float forceMagnitude = K * charges[i].q * charges[j].q * invDist * invDist * invDist;

                Vector2 force = {r.x * forceMagnitude, r.y * forceMagnitude};

                charges[i].force.x += force.x;
                charges[i].force.y += force.y;

                charges[j].force.x -= force.x;
                charges[j].force.y -= force.y;
            }
        }
    }
    // return vector of electric field at a point due to system
    Vector2 ComputeFieldAt(Vector2 point) const
    {
        Vector2 E = {0, 0};

        for (const auto& c : charges)
        {
            Vector2 r = {point.x - c.pos.x, point.y - c.pos.y};

            float distSqr = r.x * r.x + r.y * r.y + epsilon * epsilon;
            float invDist = 1.0f / std::sqrt(distSqr);

            float coeff = K * c.q * invDist * invDist * invDist;

            E.x += r.x * coeff;
            E.y += r.y * coeff;
        }

        return E;
    }
    // return potential at a point due to system
    float ComputePotentialAt(Vector2 point) const
    {
        float V = 0.0f;

        for (const auto& c : charges)
        {
            Vector2 r = {point.x - c.pos.x, point.y - c.pos.y};

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
