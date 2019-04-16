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
#include "terminal_rpg_window_size.h"


//defines create_character_prompts
#define CRTR "Character Creator"
#define CRTR_NAME "Name your character.", "Name:"
#define CRTR_RACE "Choose your character's race."
#define CRTR_CLASS "Choose your character's class."
#define CRTR_BGROUND "Choose your character's background."

//Error
#define ERROR_1 "Insert Only Numbers!!"

const char * races [] = {
                        CRTR_RACE,
                        "Human",
                        "Orc",
                        "Nordener",
                        "Frog",
                        "Return"
                        };
const int races_size = 6;

const char * classes [] =   {
                            CRTR_CLASS,
                            "Knight",
                            "Assasin",
                            "Ranger",
                            "Mage",
                            "Bard",
                            "Return"
                            };
const int classes_size = 7;

const char * backgrounds [] =   {
                                CRTR_BGROUND,
                                "Commoner",
                                "Noble",
                                "Burgeoise",
                                "Religious",
                                "Criminal",
                                "Return"
                                };
const int backgrounds_size = 7;


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
    /* int row, col; */
    /* getmaxyx(stdscr, row, col); */
    /* set_win_player(new_player, 10, 20, (row/4), (col/4) ); */
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
    int option = 1;
    while(1) {
        if(option == -2)
            option = 1;
        set_win_player(player, 10, 26, row/4, (col/4) - 13);
        option = menu_handling_expanded(character_variables_size, 2, character_variables, option);
        switch(option) {
            case -2:
                window_size_check(row, col, 25, 80);
                break;
            case 1:
                set_win_player(player, 10, 26, row/4, (col/4) - 13);
                create_character_prompts(row, col, CRTR_NAME, buff);
                for(int i = 0; i < 18; i++) player->name[i] = buff[i];
                break;
            case 2:
                set_win_player(player, 10, 26, row/4, (col/4) - 13);
                player->race = create_character_select_menu(row, col, CRTR_RACE, races, races_size);
                break;
            case 3:
                set_win_player(player, 10, 26, row/4, (col/4) - 13);
                player->class_[0] = create_character_select_menu(row, col, CRTR_CLASS, classes, classes_size);
                player->class_[1] = 1;
                break;
            case 4:
                set_win_player(player, 10, 26, row/4, (col/4) - 13);
                player->background = create_character_select_menu(row, col, CRTR_BGROUND, backgrounds, backgrounds_size);
                break;
            case 5:
                return 0;
        }
    }
    return 0;
}

int create_character_prompts(int row, int col, char * prompt, char * prompt2, char buff[32]) {
    int prompt_row = 10;
    int prompt_col = 40;
    int prompt2_col_pos;
    prompt2_col_pos = (prompt_col - 19 - strlen(prompt2)) / 2;

    WINDOW * win_prompt = newwin(prompt_row, prompt_col, (row * 0.4) - (prompt_row / 2), (col * 0.5) - (prompt_col / 2));
    mvwprintw(win_prompt, prompt_row * 0.2, (prompt_col / 2) - (strlen(prompt)/2), prompt);
    mvwprintw(win_prompt, prompt_row * 0.5, prompt2_col_pos , prompt2);
    box(win_prompt, 0,0);
    wrefresh(win_prompt);
    echo();
    curs_set(1);
    wgetnstr(win_prompt, buff, 18);
    noecho();
    curs_set(0);
    wclear(win_prompt);
    wrefresh(win_prompt);
    delwin(win_prompt);
    refresh();
    return 0;
}

int create_character_select_menu(int row, int col, char * prompt, const char * selection[], const int selection_size) {
    int prompt_row = 15;
    int prompt_col = 60;

    WINDOW * win_prompt = newwin(prompt_row, prompt_col, (row * 0.4) - (prompt_row / 2), (col * 0.5) - (prompt_col / 2));
    /* mvwprintw(win_prompt, prompt_row * 0.2, (prompt_col / 2) - (strlen(prompt)/2), prompt); */
    box(win_prompt, 0,0);
    /* wrefresh(win_prompt); */
    int option = 1;
    option = w_menu_handling_expanded(win_prompt, selection_size, 2, selection, option);
    wclear(win_prompt);
    wrefresh(win_prompt);
    delwin(win_prompt);
    refresh();
    return option;
}



//eof
