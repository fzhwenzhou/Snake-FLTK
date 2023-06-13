#ifndef MAZE_HPP
#define MAZE_HPP

#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/fl_draw.H>

#include <fstream>
#include <queue>

#include "object.hpp"
#include "snake.hpp"

#define relative(x) (int((x + 0.001) * PG_SIZE / SNAKE_SIZE) * SNAKE_SIZE)

class barrier : public Fl_Widget {
    public:
    barrier() = delete;
    barrier(int x, int y, int w, int h) 
        : Fl_Widget{x, y, w, h} {
        for (int i = (x - PG_X) / SNAKE_SIZE; i < (x + w - PG_X) / SNAKE_SIZE; ++i) {
            for (int j = (y - PG_Y) / SNAKE_SIZE; j < (y + h - PG_Y) / SNAKE_SIZE; ++j) {
                occupied[i][j] = true;
            }
        }
    }
    ~barrier() {
        for (int i = (x() - PG_X) / SNAKE_SIZE; i < (x() + w() - PG_X) / SNAKE_SIZE; ++i) {
            for (int j = (y() - PG_Y) / SNAKE_SIZE; j < (y() + h() - PG_Y) / SNAKE_SIZE; ++j) {
                occupied[i][j] = false;
            }
        }
    }
    virtual void draw() override {
        fl_rectf(x(), y(), w(), h(), FL_DARK_YELLOW);
    }
};

class maze {
    public:
    maze() = delete;
    maze(int level, Fl_Double_Window* window) {
        char buf[20];
        snprintf(buf, 20, "maze/%d.txt", level);
        auto f = fopen(buf, "r");
        int cnt;
        fscanf(f, "%d", &cnt);
        while (cnt--) {
            double st_x, st_y, ed_x, ed_y;
            fscanf(f, "%lf%lf%lf%lf", &st_x, &st_y, &ed_x, &ed_y);
            int x = relative(st_x) + PG_X, y = relative(st_y) + PG_Y;
            int w = relative(ed_x - st_x), h = relative(ed_y - st_y);
            w = w == 0 ? SNAKE_SIZE : w, h = h == 0 ? SNAKE_SIZE : h;
            x = x == PG_X + PG_SIZE ? x - SNAKE_SIZE : x;
            y = y == PG_Y + PG_SIZE ? y - SNAKE_SIZE : y;
            printf("%d, %d, %d, %d\n", x, y, w, h);
            barriers.emplace(x, y, w, h);
            window->add(barriers.back());
        }
        fclose(f);
    }
    private:
    std::queue<barrier> barriers;
};

#endif