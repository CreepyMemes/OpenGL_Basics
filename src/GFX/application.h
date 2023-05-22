#ifndef APPLICATION_H
    #define APPLICATION_H

    #include "window.h"

    class Application{   

        public:
            Application();

            void run();
        
        private:
            Window window;
    };

#endif
