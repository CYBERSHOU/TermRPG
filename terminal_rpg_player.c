/*
 * =====================================================================================
 *
 *       Filename:  terminal_rpg_player.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  03/01/2019 10:50:31 AM
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

#include "terminal_rpg_player.h"


/* int handle_player(void) { */
/*     int x, y; */
/*     getmaxyx(stdscr, y, x); */
/*     set_win_player(player, x/2, y/2, x/4, y/4); */
/*     while(1){ */
/*         if (1) */
/*             return 0; */
/*     } */
/* } */

int set_win_player(struct PLAYER player, size_t size_x, size_t size_y, size_t pos_x, size_t pos_y) {
    WINDOW * win_player = newwin(10, 25, 15, 10);
    box(win_player, 0, 0);
    wrefresh(win_player);
    getchar();
    return 0;
}



//end
