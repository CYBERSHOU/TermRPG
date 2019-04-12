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
#include <string.h>
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

player_t * create_player(void) {
    player_t * player = malloc(sizeof(player_t));
    player->name = malloc(sizeof(char) * 20);
    return player;
}



int set_struct_player(player_t player, char * name, int class_ [2], int race, int background) {
    player.race = race;
    player.class_[0] = class_[0];
    player.class_[1] = class_[1];
    player.background = background;
    return 0;
}

int set_struct_player_name(player_t * player, char * name) {
    strcpy(player->name, name);

    return 0;
}

int set_struct_player_race(player_t * player, int race) {
    player->race = race;
    return 0;
}


int set_win_player(player_t * player, int size_x, int size_y, int pos_x, int pos_y) {
    WINDOW * win_player = newwin(size_x, size_y, pos_x, pos_y);
    mvwprintw(win_player, 1, 1, "%s\n", player->name);
    box(win_player, 0, 0);
    refresh();
    wrefresh(win_player);
    return 0;
}



//end
