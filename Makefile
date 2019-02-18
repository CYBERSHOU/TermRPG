CMP = gcc
OPT = -Wall -lncurses

MAIN = terminal_rpg_main
FILE = terminal_rpg
MENU = terminal_rpg_menu
START = terminal_rpg_start
OPTIONS = terminal_rpg_options
WINSIZE = terminal_rpg_window_size
MUSIC = terminal_rpg_music
AUDIO_LOG = audio_tracks/log.txt

DEBUG = debug

all: file
	$(CMP) $(OPT) $(FILE).o $(MENU).o $(START).o $(OPTIONS).o $(WINSIZE).o \
	$(MUSIC).o $(DEBUG).o $(MAIN).c -o $(MAIN).exe

file: dependencies
	$(CMP) $(FILE).c -c $(OPT)

dependencies:
	$(CMP) $(MENU).c $(START).c $(OPTIONS).c $(WINSIZE).c $(MUSIC).c $(DEBUG).c -c $(OPT)

run: all
	./$(MAIN).exe

clean:
	rm *.o $(MAIN).exe $(AUDIO_LOG)

