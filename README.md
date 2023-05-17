# My CMake OpenGL C++ Notes (_cross-platform_)


### First of all clone this repo with this command:
```
git clone https://github.com/CreepyMemes/OpenGL_Basics.git
```
### Before building with CMake clone the the GLFW submodule with the following commands from the root:
```
git submodule init
git submodule update
```

### From the root directory to generate the cmake configuration run this command:

- #### If on Linux just run this command:
```
cmake -S . -B build/
```

- #### If on Windows install MinGW from [here](https://www.msys2.org/) then run this command:
```
cmake -S . -B build/ -G "MinGW Makefiles"
```

### Finally to generate the executable file run this command:
    cmake --build build