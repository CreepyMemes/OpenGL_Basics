# My CMake OpenGL C++ Notes (_cross-platform_)


### First of all clone this repo (and it's submodules automatically) with this command:
```
git clone https://github.com/CreepyMemes/OpenGL_Basics --recursive
```

### From the _root directory_, to generate the cmake configuration run this command:

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

### Then run the previously generated executable with this command:
```
build/OpenGL-Basics
```