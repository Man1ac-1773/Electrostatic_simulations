# Electrostatic simulations

A group of files showcasing different things under electrostatic interactions and electric field visualiser. 


### TODO : 
- Refactor entire codebase into something more modular that can handle different display/scene modes for different simulations
- Make charge class as just container. Is literally just information, no dependency on any maths or raylib. Let the integrator/dedicated math/physics module handle that
    - This is because we want to demonstrate the difference between seperate math-modes or integration methods, so we need calculations to be seperate. 
    - We also want a isStatic flag inside charge, to know if to keep this charge static or not. 
- Make Individual scenes, that are called once per frame like Outpost zero and handle their own little simulation. 
- Since there are a lot of things to render, it is helpful to make another renderer classes that handle rendering only that specific thing, like Field, charges, Potential etc. It should be stateless, taking input of the current system, and then just drawing it.  
- The physics engine layer must handle all the charges related to that system, integration, motion, physics, and all optional toggle features RELATED TO PHYSICS, then pass rendering onto Renderer classes. 
- Make a scene class that stores information about what type of simulation we are currently displaying. 
