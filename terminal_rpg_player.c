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

#define NAME "NAME:"
#define RACE "RACE:"
#define CLASS "CLASS:"
#define BGROUND "BACKGROUND:"

player_t * create_player(void) {
    player_t * player = malloc(sizeof(player_t));
    player->name = malloc(sizeof(char) * 32);
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
    mvwprintw(win_player, 1, 1, "%s %s", NAME, player->name);
    mvwprintw(win_player, 2, 1, "%s %d", RACE, player->race);
    mvwprintw(win_player, 3, 1, "%s %d Level %d", CLASS, player->class_[0], player->class_[1]);
    mvwprintw(win_player, 4, 1, "%s %d", BGROUND, player->background);
    box(win_player, 0, 0);
    refresh();
    wrefresh(win_player);
    return 0;
}



//end
