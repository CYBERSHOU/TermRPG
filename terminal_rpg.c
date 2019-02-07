/*
 * ============================================================================
 *
 *       Filename:  terminal_rpg.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  01/28/2019 02:12:06 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Miguel Fernandes
 *   Organization:
 *
 * ============================================================================
 */

#include <ncurses.h>
#include <stdio.h>
//#include <unistd.h>

#include "terminal_rpg.h"
#include "terminal_rpg_start.h"
#include "terminal_rpg_options.h"
#include "terminal_rpg_menu.h"


const char * menu_word[] =  {
                                "Start",
                                "Controls",
                                "Options",
                                "Quit"
                            };



int terminal_rpg_menu () {
    signed int q;
    while(1) {
        int option = menu_handling(4, menu_word);
        switch(option) {
            case -2:
                mvprintw(0,0, "Window size not enough! Recomended size is 80x25.");
                getch();
                break;
            case 1:
                start();
                break;
            case 2:
                controls();
                break;
            case 3:
                options();
                break;
            case 4:
                q = quit();
                if( q == 0 )
                    return 0;
                if( q == -1)
                    return -1;
                else
                    break;
        }
    }
}



//eof
