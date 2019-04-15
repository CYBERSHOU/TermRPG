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
#define CRTR_RACE "Choose your character's race.", "Race:"
#define CRTR_CLASS "Choose your character's class.", "Class:"
#define CRTR_BGROUND "Choose your character's background.", "Background:"

//Error
#define ERROR_1 "Insert Only Numbers!!"

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
                /* clear(); */
                set_win_player(player, 10, 26, row/4, (col/4) - 13);
                create_character_prompts(row, col, CRTR_NAME, buff, 1);
                for(int i = 0; i < 18; i++) player->name[i] = buff[i];
                /* clear(); */
                break;
            case 2:
                /* clear(); */
                set_win_player(player, 10, 26, row/4, (col/4) - 13);
                create_character_prompts(row, col, CRTR_RACE, buff, 0);
                if(buff[0] < 48 || buff[0] > 58)
                    mvprintw(0,0, ERROR_1);
                else
                    player->race = (buff[0] - 48);
                /* clear(); */
                break;
            case 3:
                /* clear(); */
                set_win_player(player, 10, 26, row/4, (col/4) - 13);
                create_character_prompts(row, col, CRTR_CLASS, buff, 0);
                if(buff[0] < 48 || buff[0] > 58)
                    mvprintw(0,0, ERROR_1);
                else {
                    player->class_[0] = (buff[0] - 48);
                    player->class_[1] = 1;
                }
                /* clear(); */
                break;
            case 4:
                /* clear(); */
                set_win_player(player, 10, 26, row/4, (col/4) - 13);
                create_character_prompts(row, col, CRTR_BGROUND, buff, 0);
                if(buff[0] < 48 || buff[0] > 58)
                    mvprintw(0,0, ERROR_1);
                else
                    player->background = (buff[0] - 48);
                /* clear(); */
                break;
            case 5:
                return 0;
        }
    }
    return 0;
}

int create_character_prompts(int row, int col, char * prompt, char * prompt2, char buff[32], int case_) {
    int prompt_row = 10;
    int prompt_col = 40;
    int prompt2_col_pos;
    if(case_)
        prompt2_col_pos = (prompt_col - 19 - strlen(prompt2)) / 2;
    else
        prompt2_col_pos = (prompt_col / 2) - 2 - strlen(prompt2);

    WINDOW * win_prompt = newwin(prompt_row, prompt_col, (row * 0.4) - (prompt_row / 2), (col * 0.5) - (prompt_col / 2));
    mvwprintw(win_prompt, prompt_row * 0.2, (prompt_col / 2) - (strlen(prompt)/2), prompt);
    mvwprintw(win_prompt, prompt_row * 0.5, prompt2_col_pos , prompt2);
    box(win_prompt, 0,0);
    wrefresh(win_prompt);
    echo();
    curs_set(1);
    if(case_)
        wgetnstr(win_prompt, buff, 18);
    else
        wgetnstr(win_prompt, buff, 1);
    noecho();
    curs_set(0);
    wclear(win_prompt);
    wrefresh(win_prompt);
    delwin(win_prompt);
    refresh();
    return 0;
}



//eof
