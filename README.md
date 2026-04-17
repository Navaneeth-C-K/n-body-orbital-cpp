# n-body-orbital-cpp

A custom 2D N-body gravity with collision engine built in C++.

An object-oriented 2D physics engine built entirely from scratch in C++.

*(I built this engine out of curiosity to explore vector calculus and numerical integration in C++. It is a straightforward, ground-up implementation of Newtonian gravity and elastic mass-based collisions.)*

## Current Architecture 
Currently, this is a very simple and straightforward implementation hardcoded for 3 specific bodies, meaning the collision checks are manually paired.

## Important Context
* The fully functioning C++ code is the file `3-body-code.cpp`. 
* The MATLAB script for the visualization of the data is also given here. *(Note: I used AI to help generate this visualization script so I could focus my afternoon entirely on building the C++ architecture, though I am actively working on understanding the MATLAB plotting logic!)*

## EXTRA
This is more of a code for 3 bodies because if you want to increase the number of particles you will have to write the collision check again.. it can be easily be made into a proper N body solver if the collision check is made into a function and I just use vector to store the particles (will make that update whenever I have time)
