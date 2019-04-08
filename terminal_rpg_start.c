/*
 * =====================================================================================
 *
 *       Filename:  terminal_rpg_start.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  02/05/2019 06:25:03 PM
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

#include "terminal_rpg_start.h"
#include "terminal_rpg_menu.h"
#include "terminal_rpg_player.h"




const char * start_menu_msg [] =    {
                                    "New Game",
                                    "Continue",
                                    "Load Save",
                                    "Return",
                                    };
const int start_menu_size = 4;


int start () {
    int option = 1;
    while(1) {
        if(option == -2)
            option = 1;
        option = menu_handling(start_menu_size, start_menu_msg, option);
        switch(option) {
            case -2:
                mvprintw(0,0, "Change window size to proceed.");
                getch();
                break;
            case 1:
                new_game();
                break;
            case 2:
                continue_game();
                break;
            case 3:
                load_game();
                break;
            case 4:
                return 0;
        }
    }
}

int new_game() {
    player_t * new_player = create_player();
    create_character(new_player);
    int row, col;
    getmaxyx(stdscr, row, col);
    set_win_player(new_player, 10, 20, (row/4), (col/4) );
    mvprintw(0,0, "%s\n", new_player->name);
    getch();
    free(new_player);
    return 0;
}

int continue_game() {

    return 0;
}

int load_game() {

    return 0;
}

int create_character(player_t * player) {
    int row, col;
    getmaxyx(stdscr, row, col);
    clear();

    const char * ng_new_character = "Character Creator";
    mvprintw(row/4, (col - strlen(ng_new_character))/2, "%s", ng_new_character);
    const char * name_char = "Name your character...";
    mvprintw(row/4 + 3, (col - strlen(name_char))/2, "%s", name_char );
    mvprintw(row/4 + 5, (col - 18)/2 - 5, "Name:");
    refresh();
    echo();
    curs_set(1);
    WINDOW * win_input = newwin(1, 18, row/4 + 5, (col - 18)/2 );
    wrefresh(win_input);
    refresh();
    char buff [18] = "";
    wscanw(win_input, "%s", buff);
    noecho();
    curs_set(0);
    for(int i = 0; i < 18; i++) {
        player->name[i] = buff[i];
    }

    return 0;
}



//eof
