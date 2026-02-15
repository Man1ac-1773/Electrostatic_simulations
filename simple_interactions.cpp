// simple_interactions.cpp
// It just throws a bunch of charges on the screen and let's
// coloumbic force handle forces on them

#include <memory>
#include <raylib.h>

#include "src/charge.h" // includes vector, raylib, raymath

using namespace std;
#define WIDTH 1000
#define HEIGHT 700
int main()
{
    InitWindow(WIDTH, HEIGHT, "Coulombic force");
    Charge::LoadTextures();
    SetTargetFPS(60);
    vector<unique_ptr<Charge>> charges;
    while (!WindowShouldClose())
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            charges.push_back(make_unique<Electron>(GetMousePosition()));
        }
        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
        {
            charges.push_back(make_unique<Proton>(GetMousePosition()));
        }
        for (auto& c : charges)
        {
            c->ComputeForces(charges);
            c->Update(GetFrameTime());
        }
        BeginDrawing();
        ClearBackground(BLACK);
        for (auto& c : charges)
        {
            c->Draw();
        }
        DrawFPS(0, 0);
        EndDrawing();
    }
    CloseWindow();
}
