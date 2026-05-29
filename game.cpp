#include "game.h"

#include "input.h"
#include "maze.h"
#include "render.h"

static void move_player(char key, Position &player, char maze[FIELD_HEIGHT][FIELD_WIDTH]) {
    short nx = player.x;
    short ny = player.y;

    switch (key) {
        case 'w': ny--; break;
        case 's': ny++; break;
        case 'a': nx--; break;
        case 'd': nx++; break;
    }

    if (nx < 0 || nx >= FIELD_WIDTH)
        return;

    if (ny < 0 || ny >= FIELD_HEIGHT)
        return;

    if (is_walkable(maze, static_cast<unsigned short>(nx), static_cast<unsigned short>(ny))) {
        player.x = static_cast<unsigned short>(nx);
        player.y = static_cast<unsigned short>(ny);
    }
}

void run_game() {
    char maze[FIELD_HEIGHT][FIELD_WIDTH];

    generate_maze(maze);

    Position player = {1, 1};
    Position finish = {FIELD_WIDTH - 2, FIELD_HEIGHT - 2};

    render_game(maze, player);

    while (true) {
        const char key = read_key();

        if (key == 'q')
            break;

        move_player(key, player, maze);

        if (player.x == finish.x && player.y == finish.y) {
            render_win();
            break;
        }

        render_game(maze, player);
    }
}