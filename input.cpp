#include "input.h"

#ifdef _WIN32
    #include <conio.h>
#else
    #include <cstdio>
    #include <unistd.h>
    #include <termios.h>
#endif

static char getch_crossplatform() {
#ifdef _WIN32
    return static_cast<char>(_getch());
#else
    termios oldt{}, newt{};

    tcgetattr(STDIN_FILENO, &oldt);

    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);

    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    const char ch = static_cast<char>(getchar());

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return ch;
#endif
}

char read_key() {
    char ch = getch_crossplatform();

#ifdef _WIN32
    if (ch == 0 || ch == -32) {
        ch = getch_crossplatform();

        switch (ch) {
            case 72: return 'w';
            case 80: return 's';
            case 77: return 'd';
            case 75: return 'a';
        }
    }
#else
    if (ch == 27) {
        getch_crossplatform();
        ch = getch_crossplatform();

        switch (ch) {
            case 'A': return 'w';
            case 'B': return 's';
            case 'C': return 'd';
            case 'D': return 'a';
        }
    }
#endif

    return ch;
}