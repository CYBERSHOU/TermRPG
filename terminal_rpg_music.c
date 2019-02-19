/*
 * =====================================================================================
 *
 *       Filename:  terminal_rpg_music.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  02/18/2019 02:13:37 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Miguel Fernandes
 *   Organization:
 *
 * =====================================================================================
 */

#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>

#include "terminal_rpg_music.h"


int music_volume = 10; //0-10, 0 = 0%, 5 = 50%, 10 = 100%, volume increases and decreases by 10%.

const char * fifo = "/tmp/mplayercontrol";
const char * audio_tracks = "audio_tracks/*.mp3";
const char * log_file = "audio_tracks/log.txt";

//Using mkfifo to create a file onto which to echo commands to mplayer;
const char * mkfifo = "mkfifo %s &> %s"; //First (%s) is 'fifo' and second is 'log_file';
//First (%s) is 'fifo', then (%d) is '(music_volume * 10)', the last two (%s) are 'audio_tracks' and 'log_file';
const char * mplayer = "mplayer -slave -input file=%s -softvol -volstep 10 -volume %d -loop 0 %s &>> %s &";
const char * volume_dec = "echo 'volume -1 0' >> %s"; //(%s) is 'fifo' for each.
const char * volume_inc = "echo 'volume 1 0' >> %s";
const char * quit_mplayer = "echo 'quit 0' >> %s";

const char * error_closing_file = "There was an error closing the file %s !!!";


void music_inc_music_volume () {
    music_volume++;
    char temp [128];
    sprintf(temp, volume_inc, fifo);
    system(temp);
}

void music_dec_music_volume () {
    music_volume--;
    char temp [128];
    sprintf(temp, volume_dec, fifo);
    system(temp);
}

int music_set_mplayer () {
    if((music_volume = music_read_m_volume(log_file)) == -1)
        music_volume = 10;

    if(music_volume == -2) {
        mvprintw(0,0, error_closing_file, log_file);
        getch();
    }

    int m_vol = (10 * music_volume);
    char temp [256];
    sprintf(temp, mkfifo, fifo, log_file);
    system(temp);
    sprintf(temp, mplayer, fifo, m_vol, audio_tracks, log_file);
    system(temp);

    return 0;
}

int music_quit_mplayer () {
    char temp [128];
    sprintf(temp, quit_mplayer, fifo);
    system(temp);
    if(music_write_m_volume(log_file) == 1)
        return 1;
    return 0;
}

int music_write_m_volume (const char * filename) {
    FILE * fs;
    fs = fopen(filename, "w");
    fprintf(fs, "%d\n", music_volume);
    if(fclose(fs) == EOF) {
        mvprintw(0,0, error_closing_file, log_file);
        getch();
    }
    return 0;
}

int music_read_m_volume (const char * filename) {
    FILE * fs;
    fs = fopen(filename, "a+");
    int i = fgetc(fs);
    int mvol = -1;
    if(i >= '\x30' && i <= '\x39') {
        mvol = i - 48;
        if(i == '\x31') {
            i = fgetc(fs);
            if(i == '\n') {
                if(fclose(fs) == EOF)
                    return -2;
                return mvol;
            }
            if(i == '\x30') {
                i = fgetc(fs);
                if(i == '\n') {
                    mvol = 10;
                    if(fclose(fs) == EOF)
                        return -2;
                    return mvol;
                }
            }
            else {
                if(fclose(fs) == EOF)
                    return -2;
                return -1;
            }
        }
        else {
            i = fgetc(fs);
            if(i != '\n')
                mvol = -1;
        }
    }
    if(fclose(fs) == EOF)
        return -2;
    return mvol;
}

int music_return_music_volume () {
    return music_volume;
}


//eof
