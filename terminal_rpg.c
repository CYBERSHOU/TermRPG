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
#include <stdlib.h>

#include "terminal_rpg.h"
#include "terminal_rpg_start.h"
#include "terminal_rpg_options.h"
#include "terminal_rpg_menu.h"
#include "terminal_rpg_music.h"

const char * menu_word [] =  {
                                "Start",
                                "Controls",
                                "Options",
                                "Quit"
                            };


int terminal_rpg_menu () {
    int q; //holds quit() function's result;
    int option = 1; //sets the starting highlighted option, and keeps track of which was last highlighted.
    options_def_longest_str(); //defines which element of options is the longest string.
    music_set_mplayer();
    while(1) {
        if(option == -2)
            option = 1;
        option = menu_handling(4, menu_word, option);
        switch(option) {
            case -2:
                mvprintw(0,0, "Change window size to proceed.");
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
                if( q == 0 ) {
                    if(music_quit_mplayer() == 1) {
                        mvprintw(0,0, "Error quitting mplayer !!! Press any key to continue.");
                        getch();
                    }
                    return 0;
                }
                if( q == -1)
                    return -1;
                else
                    break;
        }
    }
}


//eof
