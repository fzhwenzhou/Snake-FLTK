#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <FL/Fl.H>
#include <FL/Fl_Widget.H>
#include <FL/fl_draw.H>
#include <tuple>
#include "def.hpp"

class food : public Fl_Widget {
    public:
    food() = delete;
    food(int x, int y) : Fl_Widget{x, y, FOOD_SIZE, FOOD_SIZE} {}
    food(std::tuple<int, int> t) : Fl_Widget{std::get<0>(t), std::get<1>(t), FOOD_SIZE, FOOD_SIZE} {}
    virtual void draw() override {
        fl_color(FL_RED);
        fl_begin_polygon();
        fl_arc(x(), y(), FOOD_SIZE / 2, 0, 360);
        fl_end_polygon();
    }

};

class square : public Fl_Widget {
    public:
    square() = delete;
    square(int x, int y, int w, int h, Fl_Color border, Fl_Color fill)
        : border{border}, fill{fill}, Fl_Widget{x, y, w, h} {}
    virtual void draw() override {
        fl_rectf(x(), y(), w(), h(), fill);
        fl_rect(x(), y(), w(), h(), border);
        fl_rect(x() + 1, y() + 1, w() - 2, h() - 2, border);
    }

    private:
    Fl_Color border, fill;
};

class playground : public square {
    public:
    playground() = delete;
    playground(int x, int y, int w, int h)
        : square{x, y, w, h, FL_BLACK, FL_WHITE} {}
};

class snake : public square {
    public:
    snake() = delete;
    snake(int x, int y) : square{x, y, SNAKE_SIZE, SNAKE_SIZE, FL_BLACK, FL_BLACK} {
        occupied[(x - PG_X) / SNAKE_SIZE][(y - PG_Y) / SNAKE_SIZE] = true;
    }
    ~snake() {
        occupied[(x() - PG_X) / SNAKE_SIZE][(y() - PG_Y) / SNAKE_SIZE] = false;
    }
};

class tunnel : public square {
    public:
    tunnel() = delete;
    tunnel(int x, int y) : square{x, y, SNAKE_SIZE, SNAKE_SIZE, FL_BLACK, FL_YELLOW} {
        occupied[(x - PG_X) / SNAKE_SIZE][(y - PG_Y) / SNAKE_SIZE] = true;
    }
    ~tunnel() {
        occupied[(x() - PG_X) / SNAKE_SIZE][(y() - PG_Y) / SNAKE_SIZE] = false;
    }
};

#endif