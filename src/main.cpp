#include "GFX/application.h"

#include <iostream>

/* TODO: 

Make renderer define multiple attributes automatically
Combine setVBO and setEBO into one setBuffer in renderer.h
Make the various classes have an init function instead of initializing them from constructor


*/


// Main Function
int main(){

    // Create a Application Object
    Application game;

    // Run the Application Loop
    game.run();

    return 0;
}

