# opengl-stuff

## Requirements

- Conan - <https://conan.io/> - to install the other dependencies
- CMake - <https://cmake.org/> - to build the project
- Microsoft Visual C++ 2019 compiler

## Dependencies

- OpenGL
- glew
- glm
- SFML 2.5.1 <https://www.sfml-dev.org/download/sfml/2.5.1/>

## Building

SFML has to be installed manualy. Edit the SFML_DIR variable in CMakeLists.txt with the full path to "SFML-2.5.1/lib/cmake/SFML"

From the root folder

`> cd build`

`> conan install ..`

`> cmake .. -G "Visual Studio 16 2019"`

`> cd ..`

`> cmake --build build --config Debug --target renderer -- /maxcpucount:10`

## Running

From the root folder


`> .\build\bin\renderer.exe`
