# Electrostatic simulations

A group of files showcasing different things under electrostatic interactions and electric field visualiser. 

## Current design
- `src/` has 5 files, Integrator, Scenes, Charge, Renderer, ElectrostaticSystem.
- Each of them have been distributed responsibilities for easily scaling and debugging. 

### Charge
- `Charge.h` provides just a container struct for storing information related to a charge. 
- It has charge, mass radius, pos, velocity, force, color, and isStatic. 
    - Radius is current same for all
- It has two sub-structs, Electron and Proton for modularity purposes. 
- It's only purpose is to hold information. It does not do anything else, and has no knowledge about other charges and doesn't draw itself ever.
- Includes raylib, no raymath

### Electrostatic System
- The parent container of any simulation. It owns all the charges used for the simulation
- It is designed to be only initialised as a single object per simulation. 
- It stores information related to constants, like Coulomb constant and softening factor
- Provides public functions for 
    - adding charges
    - getting the vector of charges
    - clearing all charges
    - Computing forces on all charges
    - Resetting forces if required
    - Returning Electric field due to itself (system) at a point
    - Returning Potential in the same fashion
- Inherits raylib from Charge, and does not use raymath for vector works

### Integrator
- A class used for mathematical purpose of integration. 
- Right now, since I'm only integrating motion, it is not very prominent, but later when integrating fields and potentials I might use RK4.
- Also want to reflect the difference between two different integration methods, and how they deviate from reality over time. 
- It is initialised as an object in a simulation, and can be changed inside the simulation itself, if required.

#### NOTE : 
- Had to implement `Vector2Clamp` by myself, since inclusion of `raymath.h` was causing linker issues. 
- Please help if you know how to debug.

### Scene
- The functional container for a 'simulation'. 
- Responsible for frame-wise update, initialising ElectrostaticSystem, and using the integrator to calculate necessary variables.
- Owns a ElectrostaticSystem variable, and an Integrator. 
- Currently only one scene implemented, plan to expand it further for more simulations. 

- It is also responsible for all of the physics that is not to be done using integration. Collisions, out-of-bounds, etc, are all handled by it. 

- It also handles input for now

### Renderer
- Handles rendering everything related to a specific system. 
- In a very elementary state right now, will expand later.
- Might later include flags depending on user input of what to draw (interactive simulation)and is therefore a class, not just a function

## TODO :
- Implement charge collision
- Include raylib as submodule
- Expand on scenes available and simulations
