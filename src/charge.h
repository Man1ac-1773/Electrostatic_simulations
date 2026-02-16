#pragma once
#include <cmath>
#include <memory>
#include <raylib.h>
#include <raymath.h>
#include <vector>
// Convention assumes mass of electron is 1;
// mass of proton is therefore 1836
#define RADIUS 5.0f  // assume same radius for both proton and electron
#define K 1000000.0f // coulomb law constant
#define EPSI 0.01f   // force softening
#define MAX_SPEED 500.0f

class Charge
{
  public:
    float q;
    float mass;
    Vector2 pos;
    Vector2 vel;
    Vector2 force;
    float radius;
    Color color;
    Charge(float _q, float _m, float _r, Vector2 _pos, Vector2 _vel = {0}, Vector2 _force = {0})
    {
        q = _q;
        mass = _m;
        radius = _r;
        pos = _pos;
        vel = _vel;
        force = _force;
    }
    void Draw()
    {
        DrawCircleV(pos, radius, color);
    }
    void Update(float deltaTime)
    {
        // semi-implicit euler
        vel += (force / mass) * (deltaTime);
        vel = Vector2ClampValue(vel, 0, MAX_SPEED); // limit speed from blowing up
        pos += vel * deltaTime;
        // borders collision
        if (pos.y + RADIUS > GetScreenHeight())
        {
            pos.y = GetScreenHeight() - RADIUS;
            vel.y *= -1;
        }
        if (pos.y < RADIUS)
        {
            pos.y = 2 * RADIUS;
            vel.y *= -1;
        }
        if (pos.x + RADIUS > GetScreenWidth())
        {
            pos.x = GetScreenWidth() - RADIUS;
            vel.x *= -1;
        }
        if (pos.x < RADIUS)
        {
            pos.x = 2 * RADIUS;
            vel.x *= -1;
        }
        // to check collision with other particles
    }
    void ComputeForces(std::vector<std::unique_ptr<Charge>>& charges)
    {
        ResetForce(); // forgot to reset every frame on initial iteration

        for (auto& c : charges)
        {
            if (c.get() == this) // prevent self check
                continue;
            if (Vector2DistanceSqr(c->pos, pos) <= 4 * RADIUS * RADIUS)
            {
                // the charges are colliding
                Vector2 normal = Vector2Normalize(c->pos - pos);
                Vector2 rv = c->vel - vel;
                float rvAlongNormal = Vector2DotProduct(rv, normal);
                if (rvAlongNormal > 0)
                    continue;
                float e = 1.0f; // restitution
                float j = -(1 + e) * rvAlongNormal;
                j /= (1 / mass + 1 / c->mass);
                Vector2 impulse = normal * j;
                vel -= impulse / mass;
                c->vel += impulse / c->mass;
            }
            force += Vector2Normalize(pos - c->pos) * (K / (Vector2DistanceSqr(c->pos, pos) + EPSI)) * (q * c->q);
        }
    }

  protected:
    void ResetForce()
    {
        force = {0, 0};
    }
};

class Electron : public Charge
{
  public:
    Electron(Vector2 _pos, Vector2 _vel = {0}, Vector2 _force = {0}) : Charge(-1, 1, RADIUS, _pos, _vel, _force)
    {
        color = RED;
    }
};

class Proton : public Charge
{
  public:
    Proton(Vector2 _pos, Vector2 _vel = {0}, Vector2 _force = {0}) : Charge(1, 1800, RADIUS, _pos, _vel, _force)
    {
        color = BLUE;
    }
};
