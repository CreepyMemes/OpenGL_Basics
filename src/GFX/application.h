#ifndef APPLICATION_H
    #define APPLICATION_H

    #include "window.h"
    #include "renderer.h"

    // Main Application Object Class
    class Application{   

        public:

            // Constructor Method
            Application();

            // Destructor Method
            //~Application();

            // Main Application Loop
            void run();
        
        private:
            // Window Object
            Window window;

            // Rendered Object
            Renderer renderer;
    };

#endif
