# OpenGL shenanigans

These are some experiments I'm making to learn [OpenGL](https://www.opengl.org/). I'm currently following the [learnopengl.com](learnopengl.com) book as my main learning tool.

These are using OpenGL (obviously) and [GLFW](https://www.glfw.org/) to abstract OS-specific funcionality (creating window, loading OpenGL functions, getting input...) and [GLAD](https://glad.dav1d.de/) for setting OpenGL function pointers.

There exist multiple parts, each one having their respective `src/partX.c` file and `build/partX` executable. Each part details the sections it covers on the top comment of the C file.

## Screenshots

![square](media/screenshot.png)

## Building

`
mkdir build && cd build
cmake ..
make partX
`

or

`
./run.sh partX
`
## Running

`
./build/partX
`

or

`
./run.sh partX
`

## Controls

Not all parts have these controls because I didn't bother to add them. Only the *quit* keybind is present in all parts.

- **esc**: quit
- **space**: switch between fill and wireframe modes