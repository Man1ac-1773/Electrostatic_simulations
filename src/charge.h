#pragma once
#include <memory>
#include <raylib.h>
#include <raymath.h>
#include <vector>
// Convention assumes mass of electron is 1;
// mass of proton is therefore 1836
#define RADIUS 5.0f // assume same radius for both proton and electron
#define K 100.0f    // coulomb law constant
#define EPSI 0.01f  // force softening
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
    }
    void ComputeForces(std::vector<std::unique_ptr<Charge>>& charges)
    {
        for (auto& c : charges)
        {
            if (c.get() == this) // prevent self check
                continue;
            force += Vector2Normalize(pos - c->pos) * (K / (Vector2DistanceSqr(c->pos, pos) + EPSI)) * (q * c->q);
        }
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
    Proton(Vector2 _pos, Vector2 _vel = {0}, Vector2 _force = {0}) : Charge(1, 1, RADIUS, _pos, _vel, _force)
    {
        color = BLUE;
    }
};
