/*
 * Fantasmas.cpp
 * 
 * Copyright 2014 Victor <victor@VMorales>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#include <ncurses.h>
#include <unistd.h>

#define DELAY 30000
	int ERROR = 0;
/*    
    //Crear el Mapa
    char mapa[50][100] = {
        //"                                                      ",
        "                  AXXXXXXXXXXXXXXXXXXXB AXXXXXXXXXXXXXXXXXXXB",
        "                  YM__________________Y Y__________________MY",
        "                  Y_AXXXXXB_AXXXXXXXB_Y Y_AXXXXXXXB_AXXXXXB_Y",
        "                  Y_Y     Y_Y       Y_Y Y_Y       Y_Y     Y_Y",
        "                  Y_DXXXXXC_DXXXXXXXC_DXC_DXXXXXXXC_DXXXXXC_Y",
        "                  Y________|_________|___|_________|________Y",
        "                  Y_AXXXXXB_AXB_AXXXXXXXXXXXXXB_AXB_AXXXXXB_Y",
        "                  Y_DXXXXXC_Y Y_DXXXXB   AXXXXC_Y Y_DXXXXXC_Y",
        "                  Y_________Y Y______Y   Y______Y Y_________Y",
        "                  DXXXXXXXB_Y DXXXXB_Y   Y_AXXXXC Y_AXXXXXXXC",
        "                          Y_Y AXXXXC_DXXXC_DXXXXB Y_Y        ",
        "                          Y_Y Y_________________Y Y_Y        ",
        "                  XXXXXXXXC_DXC_AXXXXXX XXXXXXB_DXC_DXXXXXXXX",
        "                  _________|____Y      *      Y____|_________",
        "                  XXXXXXXXB_AXB_DXXXXXXXXXXXXXC_AXB_AXXXXXXXX",
        "                          Y_Y Y_________________Y Y_Y        ",
        "                          Y_Y Y_AXXXXXXXXXXXXXB_Y Y_Y        ",
        "                  AXXXXXXXC_DXC_DXXXXB   AXXXXC_DXC_DXXXXXXXB",
        "                  Y________|_________Y   Y_________|________Y",
        "                  Y_AXXXXXB_AXXXXXXB_Y   Y_AXXXXXXB_AXXXXXB_Y",
        "                  Y_DXXXB Y_DXXXXXXC_DXXXC_DXXXXXXC_Y AXXXC_Y",
        "                  Y_____Y Y_________|_____|_________Y Y_____Y",
        "                  DXXXB_Y Y_AXB_AXXXXXXXXXXXXXB_AXB_Y Y_AXXXC",
        "                  AXXXC_DXC_Y Y_DXXXXB   AXXXXC_Y Y_DXC_DXXXB",
        "                  Y_________Y Y______Y   Y______Y Y_________Y",
        "                  Y_AXXXXXXXC DXXXXB_Y   Y_AXXXXC DXXXXXXXB_Y",
        "                  Y_DXXXXXXXXXXXXXXC_DXXXC_DXXXXXXXXXXXXXXC_Y",
        "                  YM________________|_____|________________MY",
        "                  DXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXC",
        "                                                      ",
   };

    //Pinta el Mapa
    void pintar_mapa(){                                                   

        for(int i = 0 ; i < 78 ; i++){
            for(int j = 0 ; j < 30 ; j++){
                   
                  move(j,i);
  
                  if(mapa[j][i] == 'X') {printw("=");}
                  if(mapa[j][i] == '_') {attron(COLOR_PAIR(2)|A_BOLD);printw(".");attroff(COLOR_PAIR(2)|A_BOLD);}
                  else if(mapa[j][i] == 'Y') {printw("|");}
                  else if(mapa[j][i] == 'A') {attron(A_BOLD);printw("*");attroff(A_BOLD);}
                  else if(mapa[j][i] == 'B') {attron(A_BOLD);printw("*");attroff(A_BOLD);}
                  else if(mapa[j][i] == 'C') {attron(A_BOLD);printw("*");attroff(A_BOLD);}
                  else if(mapa[j][i] == 'D') {attron(A_BOLD);printw("*");attroff(A_BOLD);}
                  else if(mapa[j][i] == 'M') {attron(COLOR_PAIR(3));printw("@");attroff(COLOR_PAIR(3));}
            }
       }
   }

    //Consulta Mapa para colisiones [Pacman]
    void cnsMAPA(int pY, int pX){
                      
            if(mapa[pY][pX] == 'Y' || mapa[pY][pX] == 'X' || mapa[pY][pX] == 'D' || mapa[pY][pX] == 'A' || mapa[pY][pX] == 'B' || mapa[pY][pX] == 'C'){
                ERROR = 1;
            }else{
                ERROR = 0;
            }
	}

int main(int argc, char *argv[]) {
	int x = 35, y = 13;
	int max_y = 0, max_x = 0;
	int next_x = 0;
	int next_y = 0;
	int direction = 1;


	initscr();
	noecho();
	start_color();
	curs_set(FALSE);
	// Global var `stdscr` is created by the call to `initscr()`
	getmaxyx(stdscr, max_y, max_x);
	pintar_mapa();

		while(1) {
			mvprintw(y, x-1, " ");
			mvprintw(y, x, "G");
			refresh();
			usleep(DELAY);
			next_x = x + direction;
			next_y = y;
			cnsMAPA(next_y,next_x);
			if (ERROR==0) {
			direction*= -1;
			} else {
			x+= direction;
			}
		}
	endwin();
}*/
   #include <ncurses.h>
    #include <unistd.h>
    #define DELAY 30000
    int main(int argc, char *argv[]) {
    int x = 0, y = 0;
    int max_y = 0, max_x = 0;
    int next_x = 0;
    int direction = 1;
    initscr();
    noecho();
    curs_set(FALSE);
    // Global var `stdscr` is created by the call to `initscr()`
    getmaxyx(stdscr, max_y, max_x);
    while(1) {
    //clear();
    mvprintw(y, x-1, " ");
    mvprintw(y, x, "o");
    refresh();
    usleep(DELAY);
    next_x = x + direction;
    if (next_x >= max_x || next_x < 0) {
    direction*= -1;
    } else {
    x+= direction;
    }
    }
    endwin();
    }
