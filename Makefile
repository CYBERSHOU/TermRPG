CC = gcc
CCF = -Wall -lncurses

MAIN = terminal_rpg_main
FILE = terminal_rpg
MENU = terminal_rpg_menu
START = terminal_rpg_start
OPTIO = terminal_rpg_options
WINSZ = terminal_rpg_window_size
MUSIC = terminal_rpg_music
PLAYE = terminal_rpg_player
A_LOG = audio_tracks/log.txt

#Only for debug purposes.
DEBUG = debug/debug

.PHONY: clean debug debug_clean debug_make

all: files
	$(CC) $(CCF) $(FILE).o $(MENU).o $(START).o $(OPTIO).o $(WINSZ).o \
	$(MUSIC).o $(PLAYE).o $(MAIN).c -o $(MAIN).exe

run: all
	./$(MAIN).exe

files:
	$(CC) $(FILE).c $(MENU).c $(START).c $(OPTIO).c $(WINSZ).c \
	$(MUSIC).c $(PLAYE).c -c $(CCF)

clean:
	rm -vf *.o $(MAIN).exe $(A_LOG)

#Debug

debug: debug_make files
	$(CC) $(CCF) $(FILE).o $(MENU).o $(START).o $(OPTIO).o $(WINSZ).o \
	$(MUSIC).o $(DEBUG).o $(MAIN).c -o $(MAIN).exe

debug_make:
	cd debug/ ; make

debug_clean: clean
	cd debug/ ; make clean

#EOF
