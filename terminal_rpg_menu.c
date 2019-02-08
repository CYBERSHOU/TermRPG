/*
 * =====================================================================================
 *
 *       Filename:  terminal_rpg_menu.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  02/05/2019 08:27:21 PM
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
#include <string.h>

#include "terminal_rpg_menu.h"
#include "terminal_rpg_window_size.h"


int menu_handling (int argc, const char * argv[], int highlight) {
    int c;
    while(1) {
        if(write_menu(argc, argv, highlight) == 1)
            return -2;
        c = getch();
        switch(c) {
            case KEY_UP:
                if(highlight == 1)
                    highlight = argc;
                else
                    highlight--;
                break;
            case KEY_DOWN:
                if(highlight == argc)
                    highlight = 1;
                else
                    highlight++;
                break;
            case 10:
                return highlight;
            default:
                break;
        }
    }

    return -1;
}

int write_menu (int argc, const char * argv[], int highlight) {
    int row, col;
    getmaxyx(stdscr, row, col);
    int dif = 1 + ((row / argc) / 2);
    int row_menu = row * 0.25;
    clear();
    if( window_size_check(row, col, 25, 80) == 1)
        return 1;

    for(int i = 0; i < argc; i++) {
        if(highlight == i + 1) {
            attron(A_REVERSE);
            mvprintw( row_menu, (col - strlen(argv[i])) / 2, "%s <", argv[i] );
            attroff(A_REVERSE);
        }
        else
            mvprintw( row_menu, (col - strlen(argv[i])) / 2, "%s", argv[i] );
        row_menu += dif;
    }

    return 0;
}


//eof
