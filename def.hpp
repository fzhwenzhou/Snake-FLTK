#ifndef DEF_HPP
#define DEF_HPP

enum direction {LEFT = 65361, UP, RIGHT, DOWN};
constexpr int SNAKE_SIZE = 24, FOOD_SIZE = 20;
constexpr int PG_SIZE = 480, PG_X = 10, PG_Y = 50;
constexpr int MAP_NUM = 5;
bool occupied[PG_SIZE / SNAKE_SIZE][PG_SIZE / SNAKE_SIZE];

#endif