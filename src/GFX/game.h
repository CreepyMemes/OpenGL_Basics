#ifndef GAME_H
    #define GAME_H

    #include "window.h"
    #include "renderer.h"

    // Main Game Object Class
    class Game{   

        public:

            // Constructor Method
            Game();

            // Destructor Method
            //~Game();

            // Main Game Loop
            void run();
        
        private:
            // Window Object
            Window window;

            // Rendered Object
            Renderer renderer;
    };

#endif
