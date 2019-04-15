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


//defines create_character_prompts
#define CRTR "Character Creator"
#define CRTR_NAME "Name your character.", "Name:"
#define CRTR_RACE "Choose your character's race.", "Race:"


const char * start_menu_msg [] =    {
                                    "New Game",
                                    "Continue",
                                    "Load Save",
                                    "Return",
                                    };
const int start_menu_size = 4;

const char * character_variables [] =   {
                                        "Character Creator",
                                        "Name",
                                        "Race",
                                        "Class",
                                        "Background",
                                        "Return"
                                        };
const int character_variables_size = 6;


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
    char buff[32];
    getmaxyx(stdscr, row, col);
    clear();
    //Show a little info on the right side for each variable(name, race, strength, etc..);
    //While on the left the characters current settings are shown.
    int option = 1;
    while(1) {
        if(option == -2)
            option = 1;
        set_win_player(player, 10, 20, row/4, col/4);
        option = menu_handling_expanded(character_variables_size, 2, character_variables, option);
        if(character_variables_size == option + 1)
            return 0;
        switch(option) {
            case -2:
                mvprintw(0,0, "Change window size to proceed.");
                getch();
                break;
            case 1:
                clear();
                set_win_player(player, 10, 20, row/4, col/4);
                create_character_prompts(row, col, CRTR, CRTR_NAME, buff);
                for(int i = 0; i < 18; i++) player->name[i] = buff[i];
                clear();
                break;
            case 2:
                clear();
                set_win_player(player, 10, 20, row/4, col/4);
                create_character_prompts(row, col, CRTR, CRTR_RACE, buff);
                player->race = buff[0];
                clear();
                break;
            case 3:
                clear();
                create_character_prompts(row, col, CRTR, CRTR_RACE, buff);
                player->race = buff[0];
                set_win_player(player, 10, 20, row/4, col/4);
                break;
            case 4:
                clear();
                create_character_prompts(row, col, CRTR, CRTR_RACE, buff);
                player->race = buff[0];
                set_win_player(player, 10, 20, row/4, col/4);
                break;
            case 5:
                clear();
                create_character_prompts(row, col, CRTR, CRTR_RACE, buff);
                player->race = buff[0];
                set_win_player(player, 10, 20, row/4, col/4);
                break;
            case 6:
                clear();
                create_character_prompts(row, col, CRTR, CRTR_RACE, buff);
                player->race = buff[0];
                set_win_player(player, 10, 20, row/4, col/4);
                break;
            case 7:
                clear();
                create_character_prompts(row, col, CRTR, CRTR_RACE, buff);
                player->race = buff[0];
                set_win_player(player, 10, 20, row/4, col/4);
                break;
            case 8:
                clear();
                create_character_prompts(row, col, CRTR, CRTR_RACE, buff);
                player->race = buff[0];
                set_win_player(player, 10, 20, row/4, col/4);
                break;
            case 9:
                clear();
                create_character_prompts(row, col, CRTR, CRTR_RACE, buff);
                player->race = buff[0];
                set_win_player(player, 10, 20, row/4, col/4);
                break;
            case 10:
                clear();
                create_character_prompts(row, col, CRTR, CRTR_RACE, buff);
                player->race = buff[0];
                set_win_player(player, 10, 20, row/4, col/4);
                break;
            case 11:
                clear();
                create_character_prompts(row, col, CRTR, CRTR_RACE, buff);
                player->race = buff[0];
                set_win_player(player, 10, 20, row/4, col/4);
                break;
            case 12:
                clear();
                create_character_prompts(row, col, CRTR, CRTR_RACE, buff);
                player->race = buff[0];
                set_win_player(player, 10, 20, row/4, col/4);
                break;
        }
    }
    /* clear(); */
    /* create_character_prompts(row, col, CRTR, CRTR_NAME, buff); */
    /* for(int i = 0; i < 18; i++) player->name[i] = buff[i]; */
    /* set_win_player(player, 10, 20, row/4, col/4); */
    //little menu for selecting what to change in the Character
    create_character_prompts(row, col, CRTR, CRTR_RACE, buff);
    set_win_player(player, 10, 20, row/4, col/4);

    return 0;
}

int create_character_prompts(int row, int col, char * prompt, char * prompt2, char * prompt3, char buff[32]) {
    mvprintw(row/4, (col - strlen(prompt))/2, "%s", prompt);
    mvprintw(row/4 + 3, (col - strlen(prompt2))/2, "%s", prompt2);
    mvprintw(row/4 + 5, (col - 18)/2 - strlen(prompt3), prompt3);
    echo();
    curs_set(1);
    WINDOW * win_input = newwin(1, 18, row/4 + 5, (col - 18)/2 );
    wrefresh(win_input);
    refresh();
    wgetnstr(win_input, buff, 18);
    noecho();
    curs_set(0);
    return 0;
}



//eof
