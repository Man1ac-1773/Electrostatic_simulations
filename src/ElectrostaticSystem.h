#pragma once
#include <memory>
#include <vector>

#include "Charge.h"
#include "core/ForceLaw.h"

// the system that each scene might have multiple of.
// It stores charge, and is responsible only for
// computing Forces, field, and potential due to those charges.
// It might be expanded later to demonstrate how two different systems interact
//
class ElectrostaticSystem
{
  public:
    explicit ElectrostaticSystem(float k = 1000000.0f, float softening = 0.01f)
    {
        interaction = new CoulombInteraction(k, softening);
    }

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
    // reset all forces on all charges
    void ResetForces()
    {
        for (auto& c : charges)
        {
            c.force = {0, 0};
        }
    }
    // re-evaluate forces on all charges of system
    void ComputeForces()
    {
        ResetForces();

        const size_t n = charges.size();

        for (size_t i = 0; i < n; ++i)
        {
            for (size_t j = i + 1; j < n; ++j)
            {

                Vec2 force = interaction->ComputeForce(charges[i], charges[j]);
                charges[i].force -= force;
                charges[j].force += force;
            }
        }
    }
    // Return vector of Electric Field at a point due to system
    Vec2 ComputeFieldAt(Vec2 point) const
    {
        Vec2 E = {0, 0};

        for (const auto& c : charges)
        {
            E += interaction->ComputeField(c, point);
        }

        return E;
    }
    // Return potential at a point due to system
    float ComputePotentialAt(Vec2 point) const
    {
        float V = 0.0f;

        for (const auto& c : charges)
        {
            V += interaction->ComputePotential(c, point);
        }

        return V;
    }

  private:
    std::vector<Charge> charges;
    InteractionLaw* interaction;
};
