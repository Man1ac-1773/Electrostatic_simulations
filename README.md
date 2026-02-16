# Electrostatic simulations

A group of files showcasing different things under electrostatic interactions and electric field visualiser. 

Implemented 
- Charge class
- Inheritance into electron and proton class
- Proton being 1836 times heavier than electron
- Charge drawing
- Force interactions
    - Forgot to zero total force after each frame, caused nasty bug that was nearly impossible to pinpoint
    - Coulomb constant required is very large for appreciable forces (visually pleasing). Defined in `src/charge.h` under `#define K` directive. 
- Wall bouncing. Fixed occassional bleeding bug by updating position to be inside bounds. 
- Particle collision. Implemented very roughly inside `ComputeForces()` in `src/charge.h`.

TODO : 
- Refactor particle collision logic into something more stable and more reusable. 
    - Current implementation checks same pair twice in same frame, can cause later bugs. 
    
- ? Neutral particle?? 
- Force direction, arrow, toggle?maybe


