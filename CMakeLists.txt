cmake_minimum_required(VERSION 3.1)

project(SFMLTest)

set(CMAKE_CXX_STANDARD 20)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

## Find OpenGL
# find_package(OpenGL REQUIRED)

## Find SFML 
set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR "C:/Libs/SFML-2.5.1/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS window REQUIRED)

## Find GLEW
# set(GLEW_USE_STATIC_LIBS TRUE)
# set(GLEW_INCLUDE_DIR "C:/Libs/glew-2.1.0/include")
# set(GLEW_LIBRARY "C:/Libs/glew-2.1.0/lib/Release/x64/glew32s.lib")
# find_package(GLEW REQUIRED)

include_directories(include)
include_directories(src)

add_executable(renderer src/main.cpp)
target_link_libraries(renderer sfml-window ${CONAN_LIBS}) 