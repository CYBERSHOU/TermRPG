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


typedef struct PLAYER {
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
} player_t;

player_t *create_player(void);

int set_struct_player(player_t player, char * name, int class_ [2], int race, int background);
int set_struct_player_name(player_t * player, char * name);
int set_struct_player_race(player_t * player, int race);
int set_win_player(player_t * player, int size_x, int size_y, int pos_x, int pos_y);


#endif /* ifndef TERMINAL_RPG_PLAYER */
