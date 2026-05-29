#include "maze.h"

#include <cstdlib>
#include <ctime>

static void shuffle_dirs(int dirs[4]) {
    for (int i = 3; i > 0; i--) {
        int j = rand() % (i + 1);

        int tmp = dirs[i];
        dirs[i] = dirs[j];
        dirs[j] = tmp;
    }
}

static void carve(char maze[FIELD_HEIGHT][FIELD_WIDTH], int x, int y) {
    maze[y][x] = EMPTY_SYMBOL;

    int dirs[4] = {0, 1, 2, 3};
    shuffle_dirs(dirs);

    for (int i = 0; i < 4; i++) {
        int dx = 0;
        int dy = 0;

        switch (dirs[i]) {
            case 0: dy = -2; break;
            case 1: dy =  2; break;
            case 2: dx = -2; break;
            case 3: dx =  2; break;
        }

        int nx = x + dx;
        int ny = y + dy;

        if (nx <= 0 || nx >= FIELD_WIDTH - 1)
            continue;

        if (ny <= 0 || ny >= FIELD_HEIGHT - 1)
            continue;

        if (maze[ny][nx] == WALL_SYMBOL) {
            maze[y + dy / 2][x + dx / 2] = EMPTY_SYMBOL;
            carve(maze, nx, ny);
        }
    }
}

void generate_maze(char maze[FIELD_HEIGHT][FIELD_WIDTH]) {
    srand(static_cast<unsigned int>(time(nullptr)));

    for (int y = 0; y < FIELD_HEIGHT; y++) {
        for (int x = 0; x < FIELD_WIDTH; x++) {
            maze[y][x] = WALL_SYMBOL;
        }
    }

    carve(maze, 1, 1);

    maze[FIELD_HEIGHT - 2][FIELD_WIDTH - 2] = EXIT_SYMBOL;
}

bool is_walkable(char maze[FIELD_HEIGHT][FIELD_WIDTH], unsigned short x, unsigned short y) {
    return maze[y][x] == EMPTY_SYMBOL || maze[y][x] == EXIT_SYMBOL;
}