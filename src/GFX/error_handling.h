#pragma once

#include "gfx.h"

#include <iostream>
#include <string>
#include <cassert>

// Function that checks if there any errors, then returns their code if any are found
bool glErrorCode();

// Easy macro to automatically kill the execution if an OpenGL errors is found
#define glCheckError() assert(glErrorCode())