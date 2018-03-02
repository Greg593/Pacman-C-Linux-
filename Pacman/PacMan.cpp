/*
 * PacMan.cpp
 * 
 * Copyright 2014 Victor <victor@VMorales>
 * 	
 * 
 */


#include <iostream>
#include <ncurses.h>
#include <string.h>
#include <math.h>
#include <cstdlib>
#include <stdio.h>
	
	char mapa[50][100] = {
        "                                                      ",
        "                  AXXXXXXXXXXXXXXXXXXB AXXXXXXXXXXXXXXXXXXXB",
        "                  Y___________________Y Y___________________Y",
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
        "                  Y_________________|_____|_________________Y",
        "                  DXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXC",
   };
   
	void pintar_mapa(){													

        for(int i = 0 ; i < 78 ; i++){
            for(int j = 0 ; j < 30 ; j++){
					
                  move(j,i);
   
                  if(mapa[j][i] == 'X') {attron(COLOR_PAIR(1) | A_BOLD);printw("_");attroff(COLOR_PAIR(1) | A_BOLD);}
                  if(mapa[j][i] == '_') {attron(COLOR_PAIR(0) | A_BOLD); printw(".");attroff(COLOR_PAIR(0) | A_BOLD);}
                  else if(mapa[j][i] == 'Y') {attron(COLOR_PAIR(1) | A_BOLD);printw("|");attroff(COLOR_PAIR(1) | A_BOLD);}
                  else if(mapa[j][i] == 'A') {attron(COLOR_PAIR(1) | A_BOLD);printw("*");attroff(COLOR_PAIR(1) | A_BOLD);}
                  else if(mapa[j][i] == 'B') {attron(COLOR_PAIR(1) | A_BOLD);printw("*");attroff(COLOR_PAIR(1) | A_BOLD);}
                  else if(mapa[j][i] == 'C') {attron(COLOR_PAIR(1) | A_BOLD);printw("*");attroff(COLOR_PAIR(1) | A_BOLD);}
                  else if(mapa[j][i] == 'D') {attron(COLOR_PAIR(1) | A_BOLD);printw("*");attroff(COLOR_PAIR(1) | A_BOLD);}
            }
       }
   }

	void dibujar_marco(){
		int i;
		attron(A_BOLD | A_REVERSE);
			for(i=0;i<LINES;i++) //Pintamos las paredes: LINES indica el numero de lineas de la terminal y COLS el de columnas (proporcionados por la librería ncurses).
			{
				move(i,0);
				printw(" ");
				move(i,COLS - 1);
				printw(" ");
			}
 
			for(i=0;i<COLS-1;i++)
			{
				move(0,i);
				printw(" ");
				move(LINES -1,i);
				printw(" ");
			}
		attroff(A_BOLD | A_REVERSE);
	}
	
	void pacman(int Sy, int Sx){
		attron(COLOR_PAIR(2));
		mvprintw(Sy,Sx,"C");	
		attroff(COLOR_PAIR(2));
	}
	

	int main(int argc, char **argv){
		int fila, colu;

		int x=(39);
		int y=(22);

		initscr();
		start_color();
		init_pair(0,COLOR_BLACK,COLOR_BLACK);
		init_pair(1,COLOR_WHITE,COLOR_BLACK);
		init_pair(2,COLOR_YELLOW,COLOR_BLACK);
		bkgd(COLOR_PAIR(1)); 	
		keypad(stdscr, TRUE);
		noecho();

		refresh();
		//dibujar_marco();
		pintar_mapa();
		pacman(y,x);
		do{

		}while(getch()!=KEY_F(2));
		refresh();			
		getch();			
		endwin();			
		
		return 0;
	}

