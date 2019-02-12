/*
 * =====================================================================================
 *
 *       Filename:  terminal_rpg_main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  02/05/2019 01:25:25 PM
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
#include <unistd.h>
#include <signal.h>

#include "terminal_rpg.h"


int main (int argc, char *argv[]) {

    pid_t pid = fork();
    if(pid < 0)
        return 1;

    if(pid > 0) {
        initscr();
        keypad(stdscr, TRUE);
        noecho();
        curs_set(0);
        terminal_rpg_menu();
        clear();
        printw("Exiting...");
        refresh();
        kill(pid+2,SIGHUP);
        sleep(1);
        endwin();

        return 0;
    }
    else {
        system("mplayer -shuffle -loop 0 audio_tracks/*.mp3 &> audio_tracks/log.txt &");
        exit(0);
    }
}

//eof
