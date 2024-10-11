#include <iostream>
#include <ncurses.h>
#include "BoothAlg.h"


int main()
{
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    //nodelay(stdscr, TRUE);
    BoothAlg k;
    k.run(); 
    echo();
    refresh();
    endwin();
}
