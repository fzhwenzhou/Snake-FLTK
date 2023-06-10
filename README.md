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