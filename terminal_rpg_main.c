/*
 * =====================================================================================
 *
 *       Filename:  terminal_rpg_main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  02/05/2019 01:25:25 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Miguel Fernandes
 *   Organization:
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>

#include "terminal_rpg.h"


int main (int argc, char *argv[]) {

    initscr();
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);

    /* while(1) { */
    /* int c = getch(); */
    /* printw("%d,", c); */
    /* } */
    /* getch(); */

    terminal_rpg_menu();

    clear();
    printw("Terminating...");
    refresh();
    sleep(1);
    endwin();

    return 0;
}

//eof
