# Game Engine

Doom like game engine

<br>

## OpenGL setup (Arch)

1. install stuff
> yay -S mesa-utils // install utilities to show OpenGL version
> glxinfo | grep "OpenGL" // show OpenGL version e.g. core profile version string: 4.6 (Core Profile)
> sudo pacman -S glfw-x11 // install GLFW3
> yay -S libglvnd // to link the program with -lGL

2. Download glad files
- go to https://glad.dav1d.de/  specify the version (4.6) and download the zip
- copy glad.c from zip into project folder
- copy glad.h from zip into /usr/include/glad (glad directory need to be created manually)

3. Includes
#include <GLFW/glfw3.h>
// #include <glad/glad.h> -> this will be included by the glad.c file

<br>

## Compile file

> gcc main.c -lglfw -lGL - main
