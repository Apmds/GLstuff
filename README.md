# OpenGL shenanigans

These are some experiments I'm making to learn [OpenGL](https://www.opengl.org/). I'm currently following the [learnopengl.com](learnopengl.com) book as my main learning tool.

These are using OpenGL (obviously) and [GLFW](https://www.glfw.org/) to abstract OS-specific funcionality (creating window, loading OpenGL functions, getting input...) and [GLAD](https://glad.dav1d.de/) for setting OpenGL function pointers.

## Screenshots

![square](media/screenshot.png)

## Building

`
mkdir build && cd build
cmake ..
make
`

or

`
./run.sh
`
## Running

`
./build/opengl
`

or

`
./run.sh
`

## Controls

- **esc**: quit
- **space**: switch between fill and wireframe modes