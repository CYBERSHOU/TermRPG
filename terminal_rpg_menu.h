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

int w_menu_handling (WINDOW * win, int argc, const char * argv[], int highlight);
int w_write_menu (WINDOW * win, int argc, const char * argv[], int highlight);
int w_menu_handling_expanded (WINDOW * win, int argc, int argc_div, const char * argv[], int highlight);
int w_write_menu_expanded (WINDOW * win, int argc, int argc_div, const char * argv[], int highlight);

int w_menu_handling_expanded_KEY_UP(int opt_argc, int opt_argc_div, int opt_argc_exc, int prev_hl, int highlight);
int w_menu_handling_expanded_KEY_DOWN(int opt_argc, int opt_argc_div, int opt_argc_exc, int prev_hl, int highlight);
int w_menu_handling_expanded_KEY_LEFT(int opt_argc, int opt_argc_div, int opt_argc_exc, int highlight);
int w_menu_handling_expanded_KEY_RIGHT(int opt_argc, int opt_argc_div, int opt_argc_exc, int highlight);

#endif /* ifndef TERMINAL_RPG_MENU */
