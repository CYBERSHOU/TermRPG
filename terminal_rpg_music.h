/*
 * =====================================================================================
 *
 *       Filename:  terminal_rpg_music.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  02/18/2019 02:14:02 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Miguel Fernandes
 *   Organization:
 *
 * =====================================================================================
 */

#ifndef TERMINAL_RPG_MUSIC
#define TERMINAL_RPG_MUSIC


void music_inc_music_volume (void);
void music_dec_music_volume (void);

int music_set_mplayer (void);
int music_quit_mplayer (void);
int music_write_m_volume (const char * filename);
int music_read_m_volume (const char * filename);
int music_return_music_volume (void);


#endif /* ifndef TERMINAL_RPG_MUSIC */
