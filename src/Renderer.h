#pragma once
#include "ElectrostaticSystem.h"

// responsible for drawing
// right now, just one function inside a class
// Later, each instance might get it's own data,
// that represents what to draw as a bool.
// Hence, putting it into a class in hopes of future expansion
class ChargeRenderer
{
  public:
    void Render(const ElectrostaticSystem& system) const
    {
        for (auto& c : system.GetCharges())
        {
            DrawCircleV(c.pos, c.radius, c.color);
        }
    }
};
