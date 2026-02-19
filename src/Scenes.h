#pragma once

// parent scene template
#include <memory>
#include <raylib.h>

#include "Charge.h"
#include "ElectrostaticSystem.h"
#include "Integrator.h"
#include "Renderer.h"
class Scene
{
  public:
    virtual ~Scene() = default;

    virtual void Init() = 0;
    virtual void Update(float dt) = 0;
    virtual void Render() = 0;
    virtual void Unload() = 0;
};

// particle only scene.
// Draws simple particles on screen and
// deals with their interactions,
// only in terms of vel and forces.

class ParticleScene : public Scene
{
  public:
    ParticleScene() : system(), integrator(std::make_unique<EulerIntegrator>()) {}
    void Init() override
    {

        system.Clear();
    }
    /* Responsible for updating the entire system;
     * Handles input, computes forces, integrates motion
     * and handles collisions;
     */
    void Update(float dt) override
    {
        HandleInput();
        system.ComputeForces();
        integrator->Step(system, dt);

        HandleScreenBounds();
    }

    void Render() override
    {

        renderer.Render(system);
    }

    void Unload() override
    {
        system.Clear();
    }

  private:
    ElectrostaticSystem system;
    std::unique_ptr<Integrator> integrator;
    ChargeRenderer renderer;

    void HandleInput()
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            // electron
            Charge c = Electron(GetMousePosition());
            system.AddCharge(c);
        }
        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
        {
            // proton
            Charge c = Proton(GetMousePosition());
            system.AddCharge(c);
        }
    }
    void HandleScreenBounds()
    {
        auto& charges = system.GetCharges();

        for (auto& c : charges)
        {

            if (c.isStatic)
                continue;

            float r = c.radius;

            if (c.pos.x < r)
            {
                c.pos.x = r;
                c.vel.x *= -1;
            }
            if (c.pos.x > GetScreenWidth() - r)
            {
                c.pos.x = GetScreenWidth() - r;
                c.vel.x *= -1;
            }

            if (c.pos.y < r)
            {
                c.pos.y = r;
                c.vel.y *= -1;
            }
            if (c.pos.y > GetScreenHeight() - r)
            {
                c.pos.y = GetScreenHeight() - r;
                c.vel.y *= -1;
            }
        }
    }
};
