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

//CONTROLS - Strings
char * controls_msg [] =    {
                                "CONTROLS",
                                "- ARROWS : For movement and selection like usual;",
                                "- ENTER : To confirm selection and interact;",
                                "- M : To show the map;",
                                "- OTHER STUFF",
                                "Press any key to return."
                            };

//OPTIONS - Strings
char * options_msg [] =  {
                            "OPTIONS",
                            "- MUSIC VOLUME - ",
                        };

char * options_music_volume [] =  {
                                "<",
                                "[",
                                "|", // 10 of these for 100% / music_volume = 10; [2]
                                ".", // or 10 of these for 0% / music_volume = 0; [3]
                                "]",
                                ">"
                            };
//Options - Variables
int music_volume = 10;

//QUIT - Strings
char * quit_msg = "Do you really want to quit?";

char * error_msg = "An error occurred !!! - quit() returned -1 ";

char * quit_choice[] =  {
                            "YES",
                            "NO"
                        };

int controls() {
    int row, col;
    getmaxyx(stdscr, row, col);
    clear();
    mvprintw((row / 4), (col - strlen(controls_msg[0])) / 2, "%s", controls_msg[0]); //title
    for(int i = 1; i < 6; i++){
        mvprintw((row / 4) + 2 + i, (col - strlen(controls_msg[i])) / 2, "%s", controls_msg[i]);
    }
    refresh();
    getch();
    return 0;
}

int options() {
    int row, col;
    getmaxyx(stdscr, row, col);
    clear();
    mvprintw((row / 4), (col - strlen(options_msg[0])) / 2, "%s", options_msg[0]); //title
    for(int i = 1; i < 2; i++){
        mvprintw((row / 4) + 2 + i, (col - strlen(options_msg[i])) / 2, "%s", options_msg[i]);
    }
    refresh();
    getch();
    return 0;
}

int quit() {
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

int quit_write(const int highlight) {
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
