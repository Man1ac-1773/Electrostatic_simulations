#pragma once
#include <raylib.h>

#include "ElectrostaticSystem.h"
// responsible for drawing
// right now, just one function inside a class
// Later, each instance might get it's own data,
// that represents what to draw as a bool.
// Hence, putting it into a class in hopes of future expansion
//
//
// Everything except my rendering and my input handling should work without raylib
class ChargeRenderer
{
  public:
    void Render(const ElectrostaticSystem& system) const
    {
        for (auto& c : system.GetCharges())
        {
            Color C = BLUE;
            if (c.q > 0)
                C = BLUE;
            else
                C = RED;
            DrawCircleV(Vector2{c.pos.x, c.pos.y}, c.radius, C);
        }
    }
};
