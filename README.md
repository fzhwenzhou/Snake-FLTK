# Simple Snake Game Implemented in C++ and FLTK

## Environment Pre-requisite
- A C++17 compatible compiler (tested on clang 14.0.3)
- FLTK installed (tested on version 1.3.8)

## Compile Guide
- GCC
```sh
g++ main.cpp -o main --std=c++17 $(/path/to/fltk-config --cxxflags --ldflags --libs)
```

- Clang
```sh
clang++ main.cpp -o main --std=c++17 $(/path/to/fltk-config --cxxflags --ldflags --libs)
```

- MSVC

Create a Visual Studio solution and copy all the files into the solution folder. Set the IncludePath and add "fltk.lib" to the linker dependencies. Then build the solution.

## Usage

Run the executable the compiler generates. Use the arrow keys to adjust the direction the snake moves. The highest score will be stored in a file with the same name of the username. After each 8 scores, there will be a tunnel allowing the snake to get to another level. Different levels may have different mazes.

## Development

Mazes are in the "maze" folder. Each maze is a text file. For each file, the first line is the number of barriers. Each of the following lines contains 4 floats implying the ratio starting x, starting y, ending x, and ending y. Thus, the number should between 0 and 1. The number of maps is defined in "def.hpp."
