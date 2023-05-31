cmake_minimum_required(VERSION 3.2)
project(App)

# Add the directory paths containing the header files
include_directories(
    ${CMAKE_SOURCE_DIR}/lib/GLAD/include
    ${CMAKE_SOURCE_DIR}/lib/GLFW/include
    ${CMAKE_SOURCE_DIR}/lib
)

# Set the path to main.cpp and all the other directories containing .cpp files
set(MAIN_SRC     ${CMAKE_SOURCE_DIR}/src/main.cpp)
set(GRAPHICS_DIR ${CMAKE_SOURCE_DIR}/src/graphics)
set(UTIL_DIR     ${CMAKE_SOURCE_DIR}/src/util)

# Get a list of all the .cpp files in the previously set directories
file(GLOB GRAPHICS_SOURCES "${GRAPHICS_DIR}/*.cpp")
file(GLOB UTIL_SOURCES     "${UTIL_DIR}/*.cpp")

# Add the executable and include the main.cpp and other .cpp files
add_executable(${PROJECT_NAME} ${MAIN_SRC} ${GRAPHICS_SOURCES} ${UTIL_SOURCES})

# Set OFF these GLFW Option Variables before adding the GLFW subdirectory so it doesn't build useless shit
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
option(GLFW_BUILD_DOCS OFF)

# Add subdirectories containing libraries to build
add_subdirectory(${CMAKE_SOURCE_DIR}/lib/GLFW)
add_subdirectory(${CMAKE_SOURCE_DIR}/lib/GLAD)

# Link all the libraries to the executable
target_link_libraries(${PROJECT_NAME} glfw glad)

