// simple_interactions.cpp
// It just throws a bunch of charges on the screen and let's
// coloumbic force handle forces on them

#include <iostream>
#include <memory>

#include "src/charge.h" // includes vector, raylib, raymath

using namespace std;
#define WIDTH 1000
#define HEIGHT 700
int main()
{
    InitWindow(WIDTH, HEIGHT, "Coulombic force");
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
            cout << "Vel magnitude : " << Vector2LengthSqr(c->vel) << endl;
        }
        BeginDrawing();
        ClearBackground(BLACK);
        for (auto& c : charges)
        {
            c->Draw();
        }
        EndDrawing();
    }
    CloseWindow();
}
