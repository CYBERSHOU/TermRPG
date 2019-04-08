/*
 * =====================================================================================
 *
 *       Filename:  terminal_rpg_start.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  02/05/2019 06:24:59 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Miguel Fernandes
 *   Organization:
 *
 * =====================================================================================
 */

#ifndef TERMINAL_RPG_START
#define TERMINAL_RPG_START

#include "terminal_rpg_player.h"

int start (void);
int new_game(void);
int continue_game(void);
int load_game(void);
int create_character(player_t * player);

#endif /* ifndef TERMINAL_RPG_START */
