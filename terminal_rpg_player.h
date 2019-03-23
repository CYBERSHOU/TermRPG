/*
 * =====================================================================================
 *
 *       Filename:  terminal_rpg_player.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  03/01/2019 10:50:23 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Miguel Fernandes
 *   Organization:
 *
 * =====================================================================================
 */
#ifndef TERMINAL_RPG_PLAYER
#define TERMINAL_RPG_PLAYER


struct PLAYER {
    char * name; //Max size of 18 char;
    int class_ [2];
    int race;
    int background;
    int dex;
    int str_;
    int con;
    int int_;
    int wis;
    int cha;
    int hp;
    int armor;
} player;

int set_win_player(struct PLAYER player, size_t size_x, size_t size_y, size_t pos_x, size_t pos_y);


#endif /* ifndef TERMINAL_RPG_PLAYER */
