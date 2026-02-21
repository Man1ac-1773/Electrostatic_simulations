#pragma once

#include "core/Vec2.h"
#define RADIUS 5.0f
struct Charge
{
  public:
    float q;
    float mass;
    Vec2 pos;
    Vec2 vel;
    Vec2 force;
    float radius; // in case i want different radii for charges
    bool isStatic;
    Charge(float _q, float _m, float _r, Vec2 _pos, Vec2 _vel = {0}, Vec2 _force = {0})
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
    Electron(Vec2 _pos, Vec2 _vel = {0}, Vec2 _force = {0}) : Charge(-1, 1, RADIUS, _pos, _vel, _force) {}
};

struct Proton : public Charge
{
    Proton(Vec2 _pos, Vec2 _vel = {0}, Vec2 _force = {0}) : Charge(1, 1836, RADIUS, _pos, _vel, _force) {}
};
