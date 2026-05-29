#ifndef MAZE_H
#define MAZE_H

#include "config.h"

struct Position {
    unsigned short x;
    unsigned short y;
};

void generate_maze(char maze[FIELD_HEIGHT][FIELD_WIDTH]);
bool is_walkable(char maze[FIELD_HEIGHT][FIELD_WIDTH], unsigned short x, unsigned short y);

#endif