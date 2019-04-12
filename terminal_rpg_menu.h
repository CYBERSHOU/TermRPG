/*
 * =====================================================================================
 *
 *       Filename:  terminal_rpg_menu.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  02/05/2019 08:27:43 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Miguel Fernandes
 *   Organization:
 *
 * =====================================================================================
 */

#ifndef TERMINAL_RPG_MENU
#define TERMINAL_RPG_MENU


int menu_handling (int argc, const char * argv[], int highlight);
int write_menu (int argc, const char * argv[], int highlight);
int menu_handling_expanded (int argc, int argc_div, const char * argv[], int highlight);
int write_menu_expanded (int argc, int argc_div, const char * argv[], int highlight);

#endif /* ifndef TERMINAL_RPG_MENU */
