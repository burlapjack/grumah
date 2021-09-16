/* grumah.c
 * by burlapjack 
 * 2021
 */
#include <time.h>
#include <ncurses.h>
#include <locale.h>
#include <signal.h>
#include "../include/grumah.h"


void grumah_init(){
	
	setlocale(LC_ALL,"");		
	time_t t;
	srand((unsigned) time(&t));
	 
	//init ncurses	
	initscr();
	cbreak();
	keypad(stdscr,TRUE);	
	noecho();
	curs_set(0);

}

