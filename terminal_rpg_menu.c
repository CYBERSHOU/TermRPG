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
    int row_menu_start = row * 0.3;
    int col_menu_start = col * 0.25;
    int row_menu = row * 0.55;
    int col_menu = col * 0.5;
    int row_title = row * 0.20;
    int dif = 2;

    if( window_size_check(row, col, 25, 80) == 1)
        return 1;

    int word_length = 0;
    for(int i = 1; i < argc; i++) {
        if(strlen(argv[i]) > word_length)
            word_length = strlen(argv[i]);
    }

    int max_div = col_menu / (word_length + 5);
    if( max_div < argc_div)
        return 1;

    mvprintw( row_title, col_menu - (strlen(argv[0]) / 2), "%s", argv[0]);
    int i_pos = 1;
    int i_div = 1;
    int i_row_menu = row_menu_start;
    int i_col_menu = col_menu_start + ((col_menu / argc_div) - (word_length) + 3);
    int limit = argc / argc_div;
    word_length = 0;
    for(int i = i_pos; i < limit; i++) {
        if(strlen(argv[i]) > word_length)
            word_length = strlen(argv[i]);
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
        int i_word_length = 0;
        for(int i = i_pos; i < limit; i++) {
            if(highlight == i) {
                attron(A_REVERSE);
                if(i == limit - 1)
                    mvprintw( row_menu + row_menu_start, col_menu - (strlen(argv[i]) / 2), "%s <", argv[i]);
                else
                    mvprintw( i_row_menu, i_col_menu + ((word_length + 5) * i_div), "%s <", argv[i] );
                attroff(A_REVERSE);
            }
            else {
                if(i == limit - 1)
                    mvprintw( row_menu + row_menu_start, col_menu - (strlen(argv[i]) / 2), "%s  ", argv[i]);
                else
                   mvprintw( i_row_menu, i_col_menu + ((word_length + 5) * i_div), "%s  ", argv[i] );
            }
            i_row_menu += dif;
            i_pos++;
            if(i_word_length < strlen(argv[i]))
                i_word_length = strlen(argv[i]);
        }
        word_length = i_word_length;
        i_div++;
    }
    return 0;
}

int w_menu_handling (WINDOW * win, int argc, const char * argv[], int highlight) {
    int c;
    while(1) {
        if(w_write_menu(win, argc, argv, highlight) == 1)
            return -2;
        wrefresh(win);
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

int w_write_menu (WINDOW * win, int argc, const char * argv[], int highlight) {
    int row, col;
    getmaxyx(stdscr, row, col);
    if( window_size_check(row, col, 25, 80) == 1)
        return 1;

    getmaxyx(win, row, col);
    int dif = 1 + ((row / argc) / 2);
    int row_menu = row * 0.25;
    /* wclear(win); */


    int word_length = 0;
    for(int i = 0; i < argc; i++) {
        if( (strlen(argv[i]) % 2) != 0)
            word_length = strlen(argv[i]) - 1;
        else
            word_length = strlen(argv[i]);
        if(highlight == i + 1) {
            wattron(win, A_REVERSE);
            mvwprintw(win, row_menu, (col - word_length) / 2, "%s <", argv[i] );
            wattroff(win, A_REVERSE);
        }
        else
            mvwprintw(win, row_menu, (col - word_length) / 2, "%s  ", argv[i] );
        row_menu += dif;
    }

    return 0;
}

int w_menu_handling_expanded (WINDOW * win, int argc, int argc_div, const char * argv[], int highlight) {
    if(argc_div == 1)
        return menu_handling(argc, argv, highlight);

    int c = 0;
    int opt_argc = argc - 2;
    int opt_argc_div = opt_argc / argc_div;
    int opt_argc_exc = opt_argc % argc_div;
    int prev_hl = highlight;
    while(1) {
        if(w_write_menu_expanded(win, argc, argc_div,  argv, highlight) == 1)
            return -2;
        wrefresh(win);
        c = getch();
        switch(c) {
            case KEY_UP:
                if(highlight != opt_argc + 1)
                    prev_hl = highlight;
                highlight = w_menu_handling_expanded_KEY_UP(opt_argc, opt_argc_div, opt_argc_exc, prev_hl, highlight);
                break;
            case KEY_DOWN:
                if(highlight != opt_argc + 1)
                    prev_hl = highlight;
                highlight = w_menu_handling_expanded_KEY_DOWN(opt_argc, opt_argc_div, opt_argc_exc, prev_hl, highlight);
                break;
            case KEY_LEFT:
                if(highlight != opt_argc + 1)
                    prev_hl = highlight;
                highlight = w_menu_handling_expanded_KEY_LEFT(opt_argc, opt_argc_div, opt_argc_exc, highlight);
                break;
            case KEY_RIGHT:
                if(highlight != opt_argc + 1)
                    prev_hl = highlight;
                highlight = w_menu_handling_expanded_KEY_RIGHT(opt_argc, opt_argc_div, opt_argc_exc, highlight);
                break;
            case 10:
                return highlight;
            default:
                break;
        }
    }
    return -1;
}

int w_write_menu_expanded (WINDOW * win, int argc, int argc_div,  const char * argv[], int highlight) {
    int row, col;
    getmaxyx(stdscr, row, col);
    if( window_size_check(row, col, 25, 80) == 1)
        return 1;
    getmaxyx(win, row, col);
    int row_menu_start = row * 0.3;
    int col_menu_start = col * 0.25;
    int row_menu = row * 0.55;
    int col_menu = col * 0.5;
    int row_title = row * 0.15;
    int dif = 2;

    int word_length = 0;
    for(int i = 1; i < argc; i++) {
        if(strlen(argv[i]) > word_length)
            word_length = strlen(argv[i]);
    }

    int max_div = col / (word_length + 5);
    if( max_div < argc_div)
        return 1;

    mvwprintw(win, row_title, col_menu - (strlen(argv[0]) / 2), "%s", argv[0]);
    int i_pos = 1;
    int i_div = 1;
    int i_row_menu = row_menu_start;
    int i_col_menu = col_menu_start + ((col_menu / argc_div) * 0.25 );
    int limit = argc / argc_div;
    if( (argc % argc_div) != 0)
        limit += argc % argc_div;
    word_length = 0;
    for(int i = i_pos; i < limit; i++) {
        if(word_length < strlen(argv[i]))
            word_length = strlen(argv[i]);
        if(highlight == i) {
            wattron(win, A_REVERSE);
            mvwprintw(win, i_row_menu, i_col_menu, "%s <", argv[i] );
            wattroff(win, A_REVERSE);
        }
        else
            mvwprintw(win, i_row_menu, i_col_menu, "%s  ", argv[i] );
        i_row_menu += dif;
        i_pos++;
    }
    while(i_div < argc_div) {
        limit += argc / argc_div;
        i_row_menu = row_menu_start;
        for(int i = i_pos; i < limit; i++) {
            if(highlight == i) {
                wattron(win, A_REVERSE);
                if(i == limit - 1)
                    mvwprintw(win, row_menu + row_menu_start, col_menu - (strlen(argv[i]) / 2), "%s <", argv[i]);
                else
                    mvwprintw(win, i_row_menu, i_col_menu + ((word_length + 5) * i_div), "%s <", argv[i] );
                wattroff(win, A_REVERSE);
            }
            else {
                if(i == limit - 1)
                    mvwprintw(win, row_menu + row_menu_start, col_menu - (strlen(argv[i]) / 2), "%s  ", argv[i]);
                else
                   mvwprintw(win, i_row_menu, i_col_menu + ((word_length + 5) * i_div), "%s  ", argv[i] );
            }
            i_row_menu += dif;
            i_pos++;
        }
        i_div++;
    }
    return 0;
}

int w_menu_handling_expanded_KEY_UP(int opt_argc, int opt_argc_div, int opt_argc_exc, int prev_hl, int highlight) {
    if(highlight == opt_argc + 1)
        return prev_hl;
    if(highlight > (opt_argc_div + 1) * opt_argc_exc) {
        int i_hl = 0;
        for(i_hl = highlight - opt_argc_exc; i_hl > 1; i_hl -= opt_argc_div);
        if(i_hl == 1)
            return highlight = opt_argc + 1;
        else
            return highlight -= 1;
    }
    else {
        int i_hl = 0;
        for(i_hl = highlight; i_hl > 1; i_hl -= (opt_argc_div + 1));
        if(i_hl == 1)
            return highlight = opt_argc + 1;
        else
            return highlight -= 1;
    }
}

int w_menu_handling_expanded_KEY_DOWN(int opt_argc, int opt_argc_div, int opt_argc_exc, int prev_hl, int highlight) {
    if(highlight == opt_argc + 1)
        return 1;
    if(highlight > (opt_argc_div + 1) * opt_argc_exc) {
        int i_hl = 0;
        for(i_hl = highlight - opt_argc_exc; i_hl > 1; i_hl -= opt_argc_div);
        if(i_hl == 0)
            return highlight = opt_argc + 1;
        else
            return highlight += 1;
    }
    else {
        int i_hl = 0;
        for(i_hl = highlight; i_hl > 1; i_hl -= (opt_argc_div + 1));
        if(i_hl == 0)
            return highlight = opt_argc + 1;
        else
            return highlight += 1;
    }
}

int w_menu_handling_expanded_KEY_LEFT(int opt_argc, int opt_argc_div, int opt_argc_exc, int highlight) {
    if(highlight == opt_argc + 1)
        return highlight;
    if(highlight > (opt_argc_div + 1) * opt_argc_exc) {
        if(highlight - opt_argc_div <= 0)
            return highlight += opt_argc_exc + (opt_argc_div * ((opt_argc / opt_argc_div) - 1));
        if(highlight - opt_argc_div <= (opt_argc_div + 1) * opt_argc_exc)
            return highlight -= opt_argc_div + 1;
        else
            return highlight -= opt_argc_div;
    }
    else {
        if(highlight - opt_argc_div <= 0)
            return highlight += opt_argc_exc + (opt_argc_div * ((opt_argc / opt_argc_div) - 1));
        if(highlight - (opt_argc_div + 1) == 0)
            return highlight += (opt_argc_exc - 1) * (opt_argc_div + 1);
        else
            return highlight -= opt_argc_div + 1;
    }
}

int w_menu_handling_expanded_KEY_RIGHT(int opt_argc, int opt_argc_div, int opt_argc_exc, int highlight) {
    if(highlight == opt_argc + 1)
        return highlight;
    if(highlight > (opt_argc_div + 1) * opt_argc_exc) {
        if(highlight + opt_argc_div > opt_argc)
            return highlight -= opt_argc_exc + (opt_argc_div * ((opt_argc / opt_argc_div) - 1));
        else
            return highlight += opt_argc_div;
    }
    else {
        int i_hl = 0;
        for(i_hl = highlight; i_hl > 1; i_hl -= opt_argc_div + 1);
        if( (i_hl == 0) && ((highlight + opt_argc_div + 1) > (opt_argc_div + 1) * opt_argc_exc) )
            return highlight -= (opt_argc_exc - 1) * (opt_argc_div + 1);
        else
            return highlight += opt_argc_div + 1;
    }
}



//eof
