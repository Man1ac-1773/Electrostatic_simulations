#pragma once

// now everyone will implicitly have both
#include <raylib.h>
// -----
#define RADIUS 5.0f
struct Charge
{
  public:
    float q;
    float mass;
    Vector2 pos;
    Vector2 vel;
    Vector2 force;
    float radius; // in case i want different radii for charges
    Color color;
    bool isStatic;
    Charge(float _q, float _m, float _r, Vector2 _pos, Vector2 _vel = {0}, Vector2 _force = {0})
    {
        q = _q;
        mass = _m;
        radius = _r;
        pos = _pos;
        vel = _vel;
        force = _force;
        isStatic = false; // default config
    }
};

struct Electron : public Charge
{
    Electron(Vector2 _pos, Vector2 _vel = {0}, Vector2 _force = {0}) : Charge(-1, 1, RADIUS, _pos, _vel, _force)
    {
        color = RED;
    }
};

struct Proton : public Charge
{
    Proton(Vector2 _pos, Vector2 _vel = {0}, Vector2 _force = {0}) : Charge(-1, 1836, RADIUS, _pos, _vel, _force)
    {
        color = BLUE;
    }
};
