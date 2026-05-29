#ifndef RENDER_H
#define RENDER_H

#include "maze.h"

void clear_screen();
void render_game(char maze[FIELD_HEIGHT][FIELD_WIDTH], const Position &player);
void render_win();

#endif