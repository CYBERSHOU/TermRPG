/*
 * =====================================================================================
 *
 *       Filename:  terminal_rpg_options.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  02/05/2019 08:30:15 PM
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

#include "terminal_rpg_options.h"
#include "terminal_rpg_window_size.h"
#include "terminal_rpg_music.h"

//CONTROLS - Strings
char * controls_msg [] =    {
                                "CONTROLS",
                                "- ARROWS : For movement and selection like usual;",
                                "- ENTER : To confirm selection and interact;",
                                "- BACKSPACE : To return, when option is not available;",
                                "- M : To show the map (just a placeholder);",
                                "Press any key to return."
                            };
//CONTROLS - Variables
int controls_msg_size = 6;

//OPTIONS - Strings
char * options_msg [] =  {
                            "OPTIONS",
                            "- MUSIC VOLUME -",
                            "- Return -",
                        };

char * options_music_volume [] =  {
                                "<",
                                " ",
                                "[",
                                "!", // 10 of these for 100% / music_volume = 10; [2]
                                ".", // or 10 of these for 0% / music_volume = 0; [3]
                                "]",
                                " ",
                                ">"
                            };

//OPTIONS - Variables
int options_msg_size = 3;
int options_longest_str = 0;
int options_music_volume_size = 8;

//QUIT - Strings
char * quit_msg = "Do you really want to quit?";

char * error_msg = "An error occurred !!! - quit() returned -1 ";

char * quit_choice [] =  {
                            "YES",
                            "NO"
                        };

int controls () {
    int row, col;
    getmaxyx(stdscr, row, col);
    clear();
    mvprintw((row / 4), (col - strlen(controls_msg[0])) / 2, "%s", controls_msg[0]); //title
    int longest_str = 0;
    for (int i = 1; i < controls_msg_size; i++) {
        if(strlen(controls_msg[i]) > longest_str)
            longest_str = strlen(controls_msg[i]);
    }
    for(int i = 1; i < controls_msg_size; i++){
        if(i == controls_msg_size - 1 )
            mvprintw((row / 4) + 3 + i, (col - strlen(controls_msg[i])) / 2, "%s", controls_msg[i]);
        else
            mvprintw((row / 4) + 2 + i, (col - longest_str) / 2, "%s", controls_msg[i]);
    }
    refresh();
    getch();
    return 0;
}

int options () {

    while(1) {
        int c = options_handling(options_msg_size, 1);
        switch(c) {
            case 1:
                // first arg is the starting highlight inside the function, second is equal to the switch case;
                options_handling_music(options_msg_size, 0, 1);
                break;
            case 2:
                return 0;
                break;
            default:
                break;
        }
    }
    return 0;
}

int options_def_longest_str () {
    for(int i = 1; i < options_msg_size; i++) {
        if(strlen(options_msg[i]) > options_longest_str)
            options_longest_str = strlen(options_msg[i]);
    }

    return 0;
}

int options_handling (int argc, int highlight) {

    while(1) {
        if(options_write(argc, highlight) == 1)
            continue;
        int c = getch();
        switch(c) {
            case KEY_UP:
                if(highlight == 1)
                    highlight = argc - 1;
                else
                    highlight--;
                break;
            case KEY_DOWN:
                if(highlight == argc - 1)
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

int options_handling_music (int argc, int highlight, int option) {
    int music_volume = music_return_music_volume();
    while(1) {
        options_write_music(argc, highlight, option);
        int c = getch();
        switch(c) {
            case KEY_LEFT:
                if(highlight == 0)
                    highlight = 1;
                else
                    highlight = 0;
                break;
            case KEY_RIGHT:
                if(highlight == 1)
                    highlight = 0;
                else
                    highlight = 1;
                break;
            case 10:
                if(highlight == 0 && music_volume > 0) {
                    music_volume--;
                    music_dec_music_volume();
                }
                if(highlight == 1 && music_volume < 10) {
                    music_volume++;
                    music_inc_music_volume();
                }
                break;
            case 127:
                return 0;
            default:
                break;
        }
    }

    return -1;
}

int options_write (int argc, const int highlight) {
    int row, col;
    getmaxyx(stdscr, row, col);
    if(window_size_check(row, col, 25, 80) == 1) {
        return 1;
    }
    clear();
    mvprintw((row / 4), (col - strlen(options_msg[0])) / 2, "%s", options_msg[0]); //title
    for(int i = 1; i < argc; i++){
        if(highlight == i) {
            attron(A_REVERSE);
            mvprintw((row / 4) + 2 + i, (col - options_longest_str) / 3, "%s", options_msg[i]);
            attroff(A_REVERSE);
        }
        else
            mvprintw((row / 4) + 2 + i, (col - options_longest_str) / 3, "%s", options_msg[i]);
        if(i == 1)
            options_write_music_volume(2, row, col);
    }
    return 0;
}

int options_write_music (int argc, const int highlight, int option) {
    int row, col;
    getmaxyx(stdscr, row, col);
    if(window_size_check(row, col, 25, 80) == 1) {
        return 1;
    }
    clear();
    mvprintw((row / 4), (col - strlen(options_msg[0])) / 2, "%s", options_msg[0]); //title
    for(int i = 1; i < argc; i++){
        mvprintw((row / 4) + 2 + i, (col - options_longest_str) / 3, "%s", options_msg[i]);
    }
    if(highlight == 0) {
        options_write_music_volume(0, row, col);
    }
    else {
        options_write_music_volume(1, row, col);
    }
    return 0;
}

int options_write_music_volume (const int highlight, int row, int col) {
    int music_volume = music_return_music_volume();
    mvprintw((row / 4) + 3, col / 2, "  ");
    for(int i = 0; i < options_music_volume_size; i++) {

        if(highlight == 0 && i == 0) {
            attron(A_REVERSE);
            printw("%s", options_music_volume[i]);
            attroff(A_REVERSE);
            continue;
        }
        if(highlight == 1 && i == options_music_volume_size - 1) {
            attron(A_REVERSE);
            printw("%s", options_music_volume[i]);
            attroff(A_REVERSE);
            continue;
        }
        if(i == (options_music_volume_size / 2) - 1)  {
            for(int c = 0; c < music_volume; c++) {
                printw("%s", options_music_volume[i]);
            }
            continue;
        }
        if(i == (options_music_volume_size / 2) ) {
            for(int c = 10; c > music_volume; c--) {
                printw("%s", options_music_volume[i]);
            }
            continue;
        }

        printw("%s", options_music_volume[i]);
    }
    return 0;
}

int quit () {
    int highlight = quit_handling(0);
    if( highlight == 0)
        return 0;
    if( highlight == 1)
        return 1;
    if( highlight == -1)
        clear();
        int row, col;
        getmaxyx(stdscr, row, col);
        mvprintw(row /2, (col - strlen(error_msg)) / 2, "%s", error_msg);
        return -1;
}

int quit_handling (int highlight) {

    while(1) {
        int c;
        quit_write(highlight);
        switch(c = getch()) {
            case KEY_LEFT:
                if(highlight == 0)
                    highlight = 1;
                else
                    highlight = 0;
                break;
            case KEY_RIGHT:
                if(highlight == 1)
                    highlight = 0;
                else
                    highlight = 1;
                break;
            case 10:
                return highlight;
            default:
                break;
        }
    }
    return -1;
}

int quit_write (const int highlight) {
    clear();
    int row, col;
    getmaxyx(stdscr, row, col);
    mvprintw(row / 2 - 1, (col - strlen(quit_msg)) / 2, "%s", quit_msg);
    if(highlight == 0) {
        attron(A_REVERSE);
        mvprintw( (row / 2) + 1, (col - 8) / 2, "%s", quit_choice[0], quit_choice[0]);
        attroff(A_REVERSE);
        printw("   %s", quit_choice[1]);
    } else {
        mvprintw( (row / 2) + 1, (col - 8) / 2, "%s   ", quit_choice[0], quit_choice[0]);
        attron(A_REVERSE);
        printw("%s", quit_choice[1]);
        attroff(A_REVERSE);
    }
    return 0;
}


//eof
