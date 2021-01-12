#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

// orig_termiosは元の状態
struct termios orig_termios;

void disableRawMode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void enableRawMode() {
    struct termios raw;
    atexit(disableRawMode);

    tcgetattr(STDIN_FILENO, &raw);
    orig_termios = raw;
    raw.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

int main() {
    enableRawMode();
    char c;
    while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q');
    return 0;
}
