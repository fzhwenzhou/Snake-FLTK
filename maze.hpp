#ifndef MAZE_HPP
#define MAZE_HPP

#include <FL/Fl.H>
#include <FL/fl_draw.H>

#include <fstream>

#include "object.hpp"

class maze {
    public:
    maze(int level) {
        char buf[20];
        snprintf(buf, 20, "%d.txt", level);
        std::ifstream f{buf};
        int cnt;
        f >> cnt;

    }
    ~maze() {

    }
    private:
    
};

#endif