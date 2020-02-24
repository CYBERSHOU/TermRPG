/*
 * =====================================================================================
 *
 *       Filename:  terminal_rpg_window_size.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  02/07/2019 06:22:27 PM
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

#include "terminal_rpg_window_size.h"

char * size_check_error_msg = "Window size too small!! Recomended is ";

int window_size_check(int row, int col, int min_row, int min_col) {
    if(row < min_row || col < min_col) {
        mvprintw(row / 2, (col - (strlen(size_check_error_msg) + 5)) / 2, "%s%dx%d.", size_check_error_msg, min_col, min_row);
        refresh();
        return 1;
    }
    return 0;
}

int window_size_change_check(int row, int col) {
    int current_row, current_col;
    getmaxyx(stdscr, current_row, current_col);
    if(current_row != row || current_col != col)
        return 1;
    return 0;
}


//eof
