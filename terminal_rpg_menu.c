/*
 * =====================================================================================
 *
 *       Filename:  terminal_rpg_menu.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  02/05/2019 08:27:21 PM
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
#include <string.h>

#include "terminal_rpg_menu.h"
#include "terminal_rpg_window_size.h"


int menu_handling (int argc, const char * argv[], int highlight) {
    int c;
    while(1) {
        if(write_menu(argc, argv, highlight) == 1)
            return -2;
        c = getch();
        switch(c) {
            case KEY_UP:
                if(highlight == 1)
                    highlight = argc;
                else
                    highlight--;
                break;
            case KEY_DOWN:
                if(highlight == argc)
                    highlight = 1;
                else
                    highlight++;
                break;
            case 10:
                return highlight;
            default:
                break;
        }
    }

    return -1;
}

int write_menu (int argc, const char * argv[], int highlight) {
    int row, col;
    getmaxyx(stdscr, row, col);
    int dif = 1 + ((row / argc) / 2);
    int row_menu = row * 0.25;
    clear();

    if( window_size_check(row, col, 25, 80) == 1)
        return 1;

    int word_length = 0;
    for(int i = 0; i < argc; i++) {
        if( (strlen(argv[i]) % 2) != 0)
            word_length = strlen(argv[i]) - 1;
        else
            word_length = strlen(argv[i]);
        if(highlight == i + 1) {
            attron(A_REVERSE);
            mvprintw( row_menu, (col - word_length) / 2, "%s <", argv[i] );
            attroff(A_REVERSE);
        }
        else
            mvprintw( row_menu, (col - word_length) / 2, "%s", argv[i] );
        row_menu += dif;
    }

    return 0;
}

int menu_handling_expanded (int argc, int argc_div, const char * argv[], int highlight) {
    if(argc_div == 1)
        return menu_handling(argc, argv, highlight);

    int c = 0;
    int opt_argc = argc - 2;
    int prev_hl = highlight;
    while(1) {
        if(write_menu_expanded(argc, argc_div,  argv, highlight) == 1)
            return -2;
        refresh();
        c = getch();
        switch(c) {
            case KEY_UP:
                if(highlight == argc - 1) {
                    highlight = prev_hl;
                    prev_hl = highlight;
                    break;
                }
                if(highlight == 1) {
                    prev_hl = highlight;
                    highlight = argc - 1;
                    break;
                }
                if(highlight == (opt_argc / argc_div) + 1) {
                    prev_hl = highlight;
                    highlight = argc - 1;
                    break;
                }
                else {
                    prev_hl = highlight;
                    highlight--;
                    break;
                }
            case KEY_DOWN:
                if(highlight == argc - 1) {
                    highlight = prev_hl;
                    prev_hl = highlight;
                    break;
                }
                if(highlight == opt_argc / argc_div) {
                    prev_hl = highlight;
                    highlight = argc - 1;
                    break;
                }
                else {
                    prev_hl = highlight;
                    highlight++;
                    break;
                }
            case KEY_LEFT:
                if(highlight == argc - 1)
                    break;
                if(highlight < opt_argc / argc_div) {
                    prev_hl = highlight;
                    highlight += (opt_argc / argc_div) * (argc_div - 1);
                    break;
                }
                else {
                    prev_hl = highlight;
                    highlight -= opt_argc / argc_div;
                    break;
                }
            case KEY_RIGHT:
                if(highlight == argc - 1)
                    break;
                if(highlight > (opt_argc / argc_div) ) {
                    prev_hl = highlight;
                    highlight -= (opt_argc / argc_div) * (argc_div - 1);
                    break;
                }
                else {
                    prev_hl = highlight;
                    highlight += opt_argc / argc_div;
                    break;
                }
            case 10:
                return highlight;
            default:
                break;
        }
    }
    return -1;
}

int write_menu_expanded (int argc, int argc_div,  const char * argv[], int highlight) {
    int row, col;
    getmaxyx(stdscr, row, col);
    int row_menu_start = row * 0.25;
    int col_menu_start = col * 0.25;
    int row_menu = row * 0.55;
    int col_menu = col * 0.5;
    int row_title = row * 0.20;
    int dif = 2;

    if( window_size_check(row, col, 25, 80) == 1)
        return 1;

    int word_length = 0;
    for(int i = 0; i < argc; i++) {
        if(strlen(argv[i]) > word_length)
            word_length = strlen(argv[i]);
    }

    int max_div = col_menu / (word_length + 5);
    if( max_div < argc_div)
        return 1;

    /* int div_remainder = col_menu % ((word_length + 5) * argc_div); */
    mvprintw( row_title, col_menu - (strlen(argv[0]) / 2), "%s", argv[0]);
    int i_pos = 1;
    int i_div = 1;
    int i_row_menu = row_menu_start;
    int i_col_menu = col_menu_start + ((col_menu / argc_div) * 0.7 );
    int limit = argc / argc_div;
    for(int i = i_pos; i < limit; i++) {
        if(highlight == i) {
            attron(A_REVERSE);
            mvprintw( i_row_menu, i_col_menu, "%s <", argv[i] );
            attroff(A_REVERSE);
        }
        else
            mvprintw( i_row_menu, i_col_menu, "%s  ", argv[i] );
        i_row_menu += dif;
        i_pos++;
    }
    while(i_div < argc_div) {
        limit += argc / argc_div;
        i_row_menu = row_menu_start;
        for(int i = i_pos; i < limit; i++) {
            if(highlight == i) {
                attron(A_REVERSE);
                if(i == limit - 1)
                    mvprintw( row_menu + row_menu_start, col_menu - (strlen(argv[i]) / 2), "%s", argv[i]);
                else
                    mvprintw( i_row_menu, i_col_menu + ((word_length + 5) * i_div), "%s <", argv[i] );
                attroff(A_REVERSE);
            }
            else {
                if(i == limit - 1)
                    mvprintw( row_menu + row_menu_start, col_menu - (strlen(argv[i]) / 2), "%s", argv[i]);
                else
                   mvprintw( i_row_menu, i_col_menu + ((word_length + 5) * i_div), "%s  ", argv[i] );
            }
            i_row_menu += dif;
            i_pos++;
        }
        i_div++;
    }
    return 0;
}



//eof
