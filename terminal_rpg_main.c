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
#include <pulse/pulseaudio.h>

#include "terminal_rpg.h"


int main (int argc, char *argv[]) {

    initscr();
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);

    // system("mplayer -shuffle -loop 0 ~/Documents/project_terminal_rpg/GIT/TermRPG/audio_tracks/*.mp3 &> audio_tracks/log.txt & -- ");

    terminal_rpg_menu();
    clear();
    printw("Exiting...");
    refresh();
    sleep(1);
    endwin();

    return 0;
}

//eof
