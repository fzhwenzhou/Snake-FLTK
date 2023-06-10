#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>
#include <FL/fl_message.H>
#include <FL/fl_draw.H>

#include <string_view>
#include <fstream>
#include <filesystem>
#include <queue>
#include <random>
#include <tuple>

#include "maze.hpp"
#include "object.hpp"

using namespace std::chrono_literals;

#include "def.hpp"

class snake_window : public Fl_Double_Window {
    public:
    snake_window(std::string_view username) 
        : Fl_Double_Window{400, 150, 500, 550}, username{username} {
        this->copy_label("Snake Game");
        if (!std::filesystem::exists(username)) {
            std::ofstream f{username};
            f << 0 << std::endl;
        }
        std::ifstream f{username};
        f >> high_score;
        char buf[20];
        snprintf(buf, 20, "High Score: %d", high_score);
        high_score_board.labelsize(20);
        score_board.labelsize(20);
        high_score_board.copy_label(buf);
        // Generate a three-knot snake
        for (int i = 0; i < 3; ++i) {
            snakes.emplace(250, 314 - SNAKE_SIZE * i);
        }
        Fl::scheme("plastic");
        Fl::add_timeout(0.5, run_snake, this);
    }

    static bool reach_edge(int x, int y) {
        return x < PG_X || y < PG_Y || x >= PG_X + PG_SIZE || y >= PG_Y + PG_SIZE;
    }

    static std::tuple<int, int> gen_random_pos() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(0, PG_SIZE / SNAKE_SIZE - 1);
        int x, y;
        while (occupied[x = distrib(gen)][y = distrib(gen)]);
        return std::make_tuple(x * SNAKE_SIZE + PG_X + FOOD_SIZE / 2,
            y * SNAKE_SIZE + PG_Y + FOOD_SIZE / 2);
    }

    static double gen_timeout(int score) {
        if (score < 6) {
            return 0.5;
        }
        else if (score < 12) {
            return 0.4;
        }
        else if (score < 16) {
            return 0.3;
        }
        return 0.2;  
    }

    static auto next_pos(direction d, snake* cur) {
        int x, y;
        switch (d) {
            case LEFT:
                x = cur->x() - SNAKE_SIZE, y = cur->y();
                break;
            case UP:
                x = cur->x(), y = cur->y() - SNAKE_SIZE;
                break;
            case RIGHT:
                x = cur->x() + SNAKE_SIZE, y = cur->y();
                break;
            case DOWN:
                x = cur->x(), y = cur->y() + SNAKE_SIZE;
        }
        return std::make_tuple(x, y);
    }

    static void run_snake(void* window) {
        auto w = reinterpret_cast<snake_window*>(window);
        if (w->run) {
            auto cur = &w->snakes.back();
            auto [x, y] = next_pos(w->d, cur);
            if (reach_edge(x, y) || occupied[(x - PG_X) / SNAKE_SIZE][(y - PG_Y) / SNAKE_SIZE]) {
                fl_message_title("Game Over");
                fl_message("Game over. Your score is %d.", w->score);
                exit(0);
            }
            if (x + FOOD_SIZE / 2 == w->foods->x() && y + FOOD_SIZE / 2 == w->foods->y()) {
                ++(w->score);
                delete w->foods;
                w->foods = new food{gen_random_pos()};
                w->add(w->foods);
                char buf[20];
                snprintf(buf, 20, "Score: %d", w->score);
                w->score_board.copy_label(buf);
                if (w->score > w->high_score) {
                    w->high_score = w->score;
                    snprintf(buf, 20, "High Score: %d", w->high_score);
                    w->high_score_board.copy_label(buf);
                    std::ofstream f{w->username};
                    f << w->high_score;
                }
            }
            else {
                w->snakes.pop();
            }
            w->snakes.emplace(x, y);
            w->add(w->snakes.back());
        }
        w->redraw();
        Fl::repeat_timeout(gen_timeout(w->score), run_snake, w);
    }

    int handle(int event) override {
        if (event == FL_KEYDOWN) {
            int key_ascii = Fl::event_key();
            switch (key_ascii) {
                case LEFT:
                    d = d == RIGHT ? d : LEFT;
                    break;
                case UP:
                    d = d == DOWN ? d : UP;
                    break;
                case RIGHT:
                    d = d == LEFT ? d : RIGHT;
                    break;
                case DOWN:
                    d = d == UP ? d : DOWN;
            }
            if (!run) {
                run = true;
            }
        }
        return Fl_Window::handle(event);
    }

    // private:
    bool run;
    direction d;
    std::string_view username;
    Fl_Box high_score_board{40, 10, 60, 20}, score_board{220, 10, 60, 20, "Score: 0"};
    playground pg{PG_X, PG_Y, PG_SIZE, PG_SIZE};
    std::queue<snake> snakes;
    food* foods = new food{gen_random_pos()};  
    int high_score, score = 0, level = 1;
};

#endif