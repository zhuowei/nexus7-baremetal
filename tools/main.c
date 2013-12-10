#include <ncurses.h>

extern const char console_font[];

extern const char console_font_widths[];

#define FONT_WIDTH 8

int drawCharacter(char mychar, int screenr, int screenc) {
    int index = ((int) mychar) * FONT_WIDTH;
    int rr, cc;
    for (rr = 0; rr < FONT_WIDTH; rr++) {
        int myrow = console_font[index + rr];
        for (cc = 0; cc < FONT_WIDTH; cc++) {
            int thisPixel = (myrow >> (FONT_WIDTH - 1 - cc)) & 0x1;
            char myChar = ' ';
            if (thisPixel) myChar = '@';
            mvaddch(screenr + rr, screenc + cc, myChar);
        }
    }
    return console_font_widths[mychar] + 1;
}

void drawString(char* myStr, int screenr, int screenc) {
    char myChar;
    while ((myChar = *(myStr++)) != 0) {
        int width = drawCharacter(myChar, screenr, screenc);
        screenc += width;
    }
}

int main(int argc, char* argv[]) {
    char* myStr = "No input";
    if (argc > 1) {
        myStr = argv[1];
    }
    initscr();
    drawString(myStr, 0, 0);
    refresh();
    getch();
    endwin();
    return 0;
}
