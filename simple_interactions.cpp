// simple_interactions.cpp
// It just throws a bunch of charges on the screen and let's
// coloumbic force handle forces on them

#include <raylib.h>

#include "src/Scenes.h" // includes everything lmao

using namespace std;
#define WIDTH 1000
#define HEIGHT 700
int main()
{
    InitWindow(WIDTH, HEIGHT, "Coulombic force");
    SetTargetFPS(60);
    unique_ptr<Scene> currentScene = make_unique<ParticleScene>();
    currentScene->Init();
    while (!WindowShouldClose())
    {
        ClearBackground(BLACK);
        // update of Scene handles input
        currentScene->Update(GetFrameTime());
        BeginDrawing();
        currentScene->Render();
        DrawFPS(0, 0);
        EndDrawing();
    }
    currentScene->Unload();
    CloseWindow();
}
