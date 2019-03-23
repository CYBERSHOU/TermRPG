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


const char * start_menu_msg [] = {
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

    return 0;
}

int continue_game() {

    return 0;
}

int load_game() {

    return 0;
}

//eof
