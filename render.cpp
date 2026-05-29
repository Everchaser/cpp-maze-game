#include "render.h"

#include <cstdio>
#include <cstdlib>

void clear_screen() {
#ifdef _WIN32
    system("cls");
#else
    printf(CLEAR_SYMBOL);
#endif
}

void render_game(char maze[FIELD_HEIGHT][FIELD_WIDTH], const Position &player) {
    clear_screen();

    for (unsigned short y = 0; y < FIELD_HEIGHT; y++) {
        for (unsigned short x = 0; x < FIELD_WIDTH; x++) {
            if (player.x == x && player.y == y)
                putchar(PLAYER_SYMBOL);
            else
                putchar(maze[y][x]);
        }

        putchar('\n');
    }
}

void render_win() {
    clear_screen();
    puts("you win!");
}