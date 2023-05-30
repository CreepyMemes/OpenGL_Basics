#include "opengl.h"

#include <iostream>
#include <string>

// Macro that checks for error codes, if one is found prints in which file and line it was called
#define glCheckError() getErrorCode(__FILE__, __LINE__) 

GLenum getErrorCode(const char *file, int line);