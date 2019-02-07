/*
 * =====================================================================================
 *
 *       Filename:  terminal_rpg_options.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  02/05/2019 08:31:09 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Miguel Fernandes
 *   Organization:
 *
 * =====================================================================================
 */
#ifndef TERMINAL_RPG_OPTIONS
#define TERMINAL_RPG_OPTIONS

int controls();
int options();
int options_handling();
int options_write();
signed int quit();
signed int quit_handling(signed int highlight);
signed int quit_write(const signed int highlight);

#endif /* ifndef  TERMINAL_RPG_OPTIONS */
