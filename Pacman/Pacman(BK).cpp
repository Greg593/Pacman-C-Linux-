/*
 * PacMan.cpp
 *
 * Copyright 2014 Victor <victor@VMorales>
 * 
 * Universidad "Mariano Galvez de Guatemala"
 * Ingenieria en Sistemas de la Computación
 * Estructura de Datos - Año 2014
 *    
 */


#include <iostream>
#include <ncurses.h>
#include <string.h>
#include <math.h>
#include <cstdlib>
#include <stdio.h>
#include <pthread.h>

using namespace std;

/*Definiciones*/
    #define MAX_SCREEN_AREA 100
    #define DELAY 80000

/*Estructuras*/
    /**Estructura Principal**/
	typedef struct nodo{
		char *dato;
		struct nodo *izq;
		struct nodo *der;
		struct nodo *sup;
		struct nodo *inf;
	}nodo;

/*Variables Globales*/
    int vida = 3;
    int puntos = 0;
    int ERRORf = 0;
    int ERROR = 0;
    int x=39;
    int y=21;
    int yT,xT;
    int columnas=0;
    int filas=0;
    int gO = 0;
    int ch;
    /******YX para Fantasmas*******/
    int yy1=11; int xx1=35; int yy1T, xx1T; int mover1=0; int tmpMOV1 = 0;
    int yy2=13; int xx2=37; int yy2T, xx2T; int mover2=0; int tmpMOV2 = 0;
    int yy3=13; int xx3=39; int yy3T, xx3T; int mover3=0; int tmpMOV3 = 0;
    int yy4=13; int xx4=41; int yy4T, xx4T; int mover4=0; int tmpMOV4 = 0;
    int yy5=13; int xx5=43; int yy5T, xx5T; int mover5=0; int tmpMOV5 = 0;
    /******************************/
    
    int numero = 50; 
    nodo *inicio = 0, *fin, *ini, *temp, *p;
   
/*Declaración de Funciones*/

    void pruebas();
    void pacman(int Sy, int Sx);
    void cuadro();
    void gameOVER();
    void txtMOS();
    void HELPkeys();
    void mundo();
    void cnsMAPA(int pY, int pX);
    void fantasma();
    void iniMO();
	void enlazar(int num);
	void inicializarM();
	void colision(int cY, int cX);
	void limpiaFANTASMA();
	void HELPkeysFIN();

/*Funciones*/

    void pruebas(){
        mvprintw(1,1,"%d,%d",y,x);
    }

    //Arma la estructura principal de la Matriz Ortogonal
	void inicializarM(){
		nodo *p;
		for(int i = 0; i < numero; i++){
			for(int j = 0; j < numero; j++){
				if(i == 0){
					if(inicio == NULL){
						p = (nodo*)malloc(sizeof(nodo));
							p->izq = NULL;
							p->der = NULL;
							p->sup = NULL;
							p->inf = NULL;
							inicio = p;
							fin = p;
					}else{
						p = (nodo*)malloc(sizeof(nodo));
						p->der = NULL;
						p->inf = NULL;
						p->izq = fin;
						fin->der = p;
						fin = p;
					}
				}else{
					if(ini == NULL){
						p = (nodo*)malloc(sizeof(nodo));
						p->izq = NULL;
						p->der = NULL;
						p->inf = NULL;
						ini = p;
						fin = p;
					}else{
						p = (nodo*)malloc(sizeof(nodo));
						p->inf = NULL;
						fin->der = p;
						p->izq = fin;
						fin = p;
					}
				}
			}
			if(i > 0){
				enlazar(i);
			}
			ini = NULL;
		}
	}

	//Crea enlaces de la Matriz Ortogonal	
	void enlazar(int num){
		int cont = 1, cont2 = 0;
			nodo *s, *q;
			q = ini;
			s = inicio;
				
				while(cont < num){
					s = s->inf;
					cont++;
				}
				
				while(cont2 < numero){
					q->sup = s;
					s->inf = q;
					s = s->der;
					q = q->der;
					cont2++;
				}
	}

    //Inicializa Matriz Ortogonal
    void iniMO(){
		inicializarM();   
    }
    
    void recorreMO(struct nodo *a){
		
		
		
	}

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
        "                  _________|____Y  G G G G G  Y____|_________",
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

    //Dibuja por primera vez en Pacman
    void pacman(int Sy, int Sx){
        attron(COLOR_PAIR(2));
        mvprintw(Sy,Sx,"0");   
        attroff(COLOR_PAIR(2));
        move(Sy,Sx--);
    }
   
    //Pinta VIDA y PUNTOS
    void cuadro(){

        //move(7,0); printw("**************");
        move(12,0); printw("  Vidas:       ");
        move(13,0); printw("  Puntos:      ");
        //move(10,0);printw("*            *");
        //move(11,0);printw("**************");
    }
   
    //Muestra Pantalla de GAMEOVER
    void gameOVER(){
       
        int fila,colu;
        //system("clear");
        char msg[]= "¡¡¡¡¡GAME OVER!!!!!";
        getmaxyx(stdscr,fila,colu);
        for(int u=0;u<100;u++){
			int z=u;
			int e=0;
			move(z,e);
			printw("                                                                            ");
		}
		
		clear();
		HELPkeysFIN();
        attron(COLOR_PAIR(3)|A_BOLD);
        mvprintw(fila/2,(colu-strlen(msg))/2,"%s",msg);
        attroff(COLOR_PAIR(3)|A_BOLD);
        while((ch=getch())!= KEY_F(12)){
			switch(ch){
				case KEY_F(5):
					vida = 3;
					mundo();
				break;		
			}
		}
        //KEY_F(12) = 1;
        endwin();
    }
   
    //Muestra VIDA y PUNTOS
    void txtMOS(){

        if (vida < 0){
            gameOVER();
        }else{
            attron(COLOR_PAIR(2)|A_BOLD);
            move(12,10);printw("%d",vida);
            move(13,10);printw("%d",puntos);
            attroff(COLOR_PAIR(2)|A_BOLD);
        }   
    }
   
    //Muestra las teclas de Ayuda
    void HELPkeys(){
        char keys[]= "Movimiento: Flechas de Dirección. || F5= Reiniciar. || F12= Salir.";
        attron(COLOR_PAIR(3)|A_BOLD);
        mvprintw(29,(COLS-strlen(keys))/2,"%s",keys);
        printw(" ");
        attroff(COLOR_PAIR(3)|A_BOLD);  
    }
    
    //Muestra las teclas de Ayuda en el GAMEOVER
    void HELPkeysFIN(){
        char keys[]= "F5= Reiniciar. || F12= Salir.";
        attron(COLOR_PAIR(3)|A_BOLD);
        mvprintw(29,(COLS-strlen(keys))/2,"%s",keys);
        printw(" ");
        attroff(COLOR_PAIR(3)|A_BOLD);
     } 
        
   
    //Pinta todo lo gráfico del Juego
    void mundo(){
       
        ERROR = 0;
        ERRORf = 0;
        puntos = 0;
        /*****Pacman*****/
        x=39;
        y=21;
        
		/******YX para Fantasmas*******/
		yy1=11; xx1=35;
		yy2=13; xx2=37;
		yy3=13; xx3=39;
		yy4=13; xx4=41;
		yy5=13; xx5=43;
		
		mover1=0; tmpMOV1=0;
		mover2=0; tmpMOV2=0;
		mover3=0; tmpMOV3=0;
		mover4=0; tmpMOV4=0;						

		/******************************/
       
        pintar_mapa();
        cuadro();
        HELPkeys();
        txtMOS();
        limpiaFANTASMA();
        fantasma();
        pacman(y,x);       

       
    }
   
    //Consulta Mapa para colisiones [Pared | Pacman]
    void cnsMAPA(int pY, int pX){
            pruebas();
           
            if(mapa[pY][pX] == 'G'){
                gO = 1;
            }else{
				gO = 0;
			}
            
            if(mapa[pY][pX] == '_'){
                ERROR = 0;
                puntos += 5;   
            }
           
            if(mapa[pY][pX]=='M'){
                ERROR = 0;
                puntos += 25;
            }
           
            if(mapa[pY][pX] == 'Y' || mapa[pY][pX] == 'X' || mapa[pY][pX] == 'D' || mapa[pY][pX] == 'A' || mapa[pY][pX] == 'B' || mapa[pY][pX] == 'C'){
                ERROR = 1;
            }else{
                ERROR = 0;
            }

    }
   
	//Consulta Mapa para colisiones [Pared | Fantasmas]
	void cnsMAPAf(int pY, int pX){
			pruebas();
					
			if(mapa[pY][pX] == 'Y' || mapa[pY][pX] == 'X' || mapa[pY][pX] == 'D' || mapa[pY][pX] == 'A' || mapa[pY][pX] == 'B' || mapa[pY][pX] == 'C'){
				ERRORf = 1;
			}else{
				ERRORf = 0;
			}

	}
	   
    //Pinta Fantasmas
    void fantasma(){
        attron(A_BOLD);
        attron(COLOR_PAIR(4));
        mvprintw(13,35,"G");
        attroff(COLOR_PAIR(4));
       
        attron(COLOR_PAIR(5));
        mvprintw(13,37,"G");
        attroff(COLOR_PAIR(5));
       
        attron(COLOR_PAIR(6));
        mvprintw(13,39,"G");
        attroff(COLOR_PAIR(6));
       
        attron(COLOR_PAIR(7));
        mvprintw(13,41,"G");
        attroff(COLOR_PAIR(7));
    }
   
	void limpiaFANTASMA(){
		mvprintw(13,33,"            ");
	}
	/***Mueve Fantasmas***/
	/*Pinky*/
	void mvFantasma1(){
		
		mvprintw(13,35," ");
		
		if(ERRORf != OK){
			mover1 =rand()%4;
				while(tmpMOV1 == mover1){mover1 =rand()%4;}
					if(mover1 == 0){tmpMOV1 = 1;}
					if(mover1 == 1){tmpMOV1 = 0;}
					if(mover1 == 2){tmpMOV1 = 3;}
					if(mover1 == 3){tmpMOV1 = 2;}
			ERRORf = 0;
		}
		
		switch(mover1){
				case 0:
					if(yy1==13 && xx1==18){	
						yy1T = yy1; 
						xx1T = xx1;
						attron(COLOR_PAIR(2)|A_BOLD); 
						mvprintw(yy1T,yy1T,"."); 
						attroff(COLOR_PAIR(2)|A_BOLD);
						xx1=61;
						attron(COLOR_PAIR(4)|A_BOLD);						 
						mvprintw(yy1,xx1,"G");
						attroff(COLOR_PAIR(4)|A_BOLD);
					}					
					cnsMAPAf(yy1,xx1-1);
					if (ERRORf == OK){
						
						attron(COLOR_PAIR(2)|A_BOLD);
						mvprintw(yy1,xx1--,".");
						attroff(COLOR_PAIR(2)|A_BOLD);
						attron(COLOR_PAIR(4)|A_BOLD);						 
						mvprintw(yy1,xx1,"G");
						attroff(COLOR_PAIR(4)|A_BOLD);
						move(yy1,xx1);						
					}
				break;
				case 1:
					if(yy1==13 && xx1==60){
						yy1T = yy1; 
						xx1T = xx1;
						attron(COLOR_PAIR(2)|A_BOLD); 
						mvprintw(yy1T,yy1T,"."); 
						attroff(COLOR_PAIR(2)|A_BOLD);						
						xx1=17;
						attron(COLOR_PAIR(4)|A_BOLD);						 
						mvprintw(yy1,xx1,"G");
						attroff(COLOR_PAIR(4)|A_BOLD);
					}
					cnsMAPAf(yy1,xx1+1);
					if(ERRORf == OK){
						attron(COLOR_PAIR(2)|A_BOLD);
						mvprintw(yy1,xx1++,".");
						attroff(COLOR_PAIR(2)|A_BOLD);
						attron(COLOR_PAIR(4)|A_BOLD);						 
						mvprintw(yy1,xx1,"G");
						attroff(COLOR_PAIR(4)|A_BOLD);
						move(yy1,xx1);
					}
				break;
				case 2:
					cnsMAPAf(yy1+1,xx1);
					if(ERRORf == OK){						
						attron(COLOR_PAIR(2)|A_BOLD);
						mvprintw(yy1++,xx1,".");
						attroff(COLOR_PAIR(2)|A_BOLD);
						attron(COLOR_PAIR(4)|A_BOLD);						 
						mvprintw(yy1,xx1,"G");
						attroff(COLOR_PAIR(4)|A_BOLD);
						move(yy1,xx1);
					}
				break;
				case 3:
					cnsMAPAf(yy1-1,xx1);
					if(ERRORf == OK){				
						attron(COLOR_PAIR(2)|A_BOLD);
						mvprintw(yy1--,xx1,".");
						attroff(COLOR_PAIR(2)|A_BOLD);
						attron(COLOR_PAIR(4)|A_BOLD);						 
						mvprintw(yy1,xx1,"G");
						attroff(COLOR_PAIR(4)|A_BOLD);
						move(yy1,xx1);
					}
				break;
				
					
			}		
	}

	/*Clyde*/
	void mvFantasma2(){
		
		mvprintw(13,37," ");
		
		if(ERRORf != OK){
			mover2 =rand()%4;
				while(tmpMOV2 == mover2){mover2 =rand()%4;}
					if(mover2 == 0){tmpMOV2 = 1;}
					if(mover2 == 1){tmpMOV2 = 0;}
					if(mover2 == 2){tmpMOV2 = 3;}
					if(mover2 == 3){tmpMOV2 = 2;}
			ERRORf = 0;
		}
		
		switch(mover2){
				case 0:
					if(yy2==13 && xx2==18){	
						yy2T = yy2; 
						xx2T = xx2;
						attron(COLOR_PAIR(2)|A_BOLD); 
						mvprintw(yy2T,yy2T,"."); 
						attroff(COLOR_PAIR(2)|A_BOLD);
						xx2=61;
						attron(COLOR_PAIR(5)|A_BOLD);						 
						mvprintw(yy2,xx2,"G");
						attroff(COLOR_PAIR(5)|A_BOLD);
					}					
					cnsMAPAf(yy2,xx2-1);
					if (ERRORf == OK){
						
						attron(COLOR_PAIR(2)|A_BOLD);
						mvprintw(yy2,xx2--,".");
						attroff(COLOR_PAIR(2)|A_BOLD);
						attron(COLOR_PAIR(5)|A_BOLD);						 
						mvprintw(yy2,xx2,"G");
						attroff(COLOR_PAIR(5)|A_BOLD);
						move(yy2,xx2);						
					}
				break;
				case 1:
					if(yy2==13 && xx2==60){
						yy2T = yy2; 
						xx2T = xx2;
						attron(COLOR_PAIR(2)|A_BOLD); 
						mvprintw(yy2T,yy2T,"."); 
						attroff(COLOR_PAIR(2)|A_BOLD);						
						xx2=17;
						attron(COLOR_PAIR(5)|A_BOLD);						 
						mvprintw(yy2,xx2,"G");
						attroff(COLOR_PAIR(5)|A_BOLD);
					}
					cnsMAPAf(yy2,xx2+1);
					if(ERRORf == OK){
						attron(COLOR_PAIR(2)|A_BOLD);
						mvprintw(yy2,xx2++,".");
						attroff(COLOR_PAIR(2)|A_BOLD);
						attron(COLOR_PAIR(5)|A_BOLD);						 
						mvprintw(yy2,xx2,"G");
						attroff(COLOR_PAIR(5)|A_BOLD);
						move(yy2,xx2);
					}
				break;
				case 2:
					cnsMAPAf(yy2+1,xx2);
					if(ERRORf == OK){						
						attron(COLOR_PAIR(2)|A_BOLD);
						mvprintw(yy2++,xx2,".");
						attroff(COLOR_PAIR(2)|A_BOLD);
						attron(COLOR_PAIR(5)|A_BOLD);						 
						mvprintw(yy2,xx2,"G");
						attroff(COLOR_PAIR(5)|A_BOLD);
						move(yy2,xx2);
					}
				break;
				case 3:
					cnsMAPAf(yy2-1,xx2);
					if(ERRORf == OK){				
						attron(COLOR_PAIR(2)|A_BOLD);
						mvprintw(yy2--,xx2,".");
						attroff(COLOR_PAIR(2)|A_BOLD);
						attron(COLOR_PAIR(5)|A_BOLD);						 
						mvprintw(yy2,xx2,"G");
						attroff(COLOR_PAIR(5)|A_BOLD);
						move(yy2,xx2);
					}
				break;
				
					
			}		
	}
     
	/*Inky*/
	void mvFantasma3(){
		
		mvprintw(13,39," ");		
		
		if(ERRORf != OK){
			mover3 =rand()%4;
				while(tmpMOV3 == mover3){mover3 =rand()%4;}
					if(mover3 == 0){tmpMOV3 = 1;}
					if(mover3 == 1){tmpMOV3 = 0;}
					if(mover3 == 2){tmpMOV3 = 3;}
					if(mover3 == 3){tmpMOV3 = 2;}
			ERRORf = 0;
		}
		
		switch(mover3){
				case 0:
					if(yy1==13 && xx3==18){	
						yy3T = yy3; 
						xx3T = xx3;
						attron(COLOR_PAIR(2)|A_BOLD); 
						mvprintw(yy3T,yy3T,"."); 
						attroff(COLOR_PAIR(2)|A_BOLD);
						xx3=61;
						attron(COLOR_PAIR(6)|A_BOLD);						 
						mvprintw(yy3,xx3,"G");
						attroff(COLOR_PAIR(6)|A_BOLD);
					}					
					cnsMAPAf(yy3,xx3-1);
					if (ERRORf == OK){
						
						attron(COLOR_PAIR(2)|A_BOLD);
						mvprintw(yy3,xx3--,".");
						attroff(COLOR_PAIR(2)|A_BOLD);
						attron(COLOR_PAIR(6)|A_BOLD);						 
						mvprintw(yy3,xx3,"G");
						attroff(COLOR_PAIR(6)|A_BOLD);
						move(yy3,xx3);						
					}
				break;
				case 1:
					if(yy3==13 && xx3==60){
						yy3T = yy3; 
						xx3T = xx3;
						attron(COLOR_PAIR(2)|A_BOLD); 
						mvprintw(yy3T,yy3T,"."); 
						attroff(COLOR_PAIR(2)|A_BOLD);						
						xx3=17;
						attron(COLOR_PAIR(6)|A_BOLD);						 
						mvprintw(yy3,xx3,"G");
						attroff(COLOR_PAIR(6)|A_BOLD);
					}
					cnsMAPAf(yy3,xx3+1);
					if(ERRORf == OK){
						attron(COLOR_PAIR(2)|A_BOLD);
						mvprintw(yy3,xx3++,".");
						attroff(COLOR_PAIR(2)|A_BOLD);
						attron(COLOR_PAIR(6)|A_BOLD);						 
						mvprintw(yy3,xx3,"G");
						attroff(COLOR_PAIR(6)|A_BOLD);
						move(yy3,xx3);
					}
				break;
				case 2:
					cnsMAPAf(yy3+1,xx3);
					if(ERRORf == OK){						
						attron(COLOR_PAIR(2)|A_BOLD);
						mvprintw(yy3++,xx3,".");
						attroff(COLOR_PAIR(2)|A_BOLD);
						attron(COLOR_PAIR(6)|A_BOLD);						 
						mvprintw(yy3,xx3,"G");
						attroff(COLOR_PAIR(6)|A_BOLD);
						move(yy3,xx3);
					}
				break;
				case 3:
					cnsMAPAf(yy3-1,xx3);
					if(ERRORf == OK){				
						attron(COLOR_PAIR(2)|A_BOLD);
						mvprintw(yy3--,xx3,".");
						attroff(COLOR_PAIR(2)|A_BOLD);
						attron(COLOR_PAIR(6)|A_BOLD);						 
						mvprintw(yy3,xx3,"G");
						attroff(COLOR_PAIR(6)|A_BOLD);
						move(yy3,xx3);
					}
				break;
				
					
			}		
	}

	/*Blinky*/
	void mvFantasma4(){
		
		mvprintw(13,41," ");		
		
		if(ERRORf != OK){
			mover4 =rand()%4;
				while(tmpMOV4 == mover4){mover4 =rand()%4;}
					if(mover4 == 0){tmpMOV4 = 1;}
					if(mover4 == 1){tmpMOV4 = 0;}
					if(mover4 == 2){tmpMOV4 = 3;}
					if(mover4 == 3){tmpMOV4 = 2;}
			ERRORf = 0;
		}
		
		switch(mover4){
				case 0:
					if(yy4==13 && xx4==18){	
						yy4T = yy4; 
						xx4T = xx4;
						attron(COLOR_PAIR(2)|A_BOLD); 
						mvprintw(yy4T,yy4T,"."); 
						attroff(COLOR_PAIR(2)|A_BOLD);
						xx4=61;
						attron(COLOR_PAIR(7)|A_BOLD);						 
						mvprintw(yy4,xx4,"G");
						attroff(COLOR_PAIR(7)|A_BOLD);
					}					
					cnsMAPAf(yy4,xx4-1);
					if (ERRORf == OK){
						
						attron(COLOR_PAIR(2)|A_BOLD);
						mvprintw(yy4,xx4--,".");
						attroff(COLOR_PAIR(2)|A_BOLD);
						attron(COLOR_PAIR(7)|A_BOLD);						 
						mvprintw(yy4,xx4,"G");
						attroff(COLOR_PAIR(7)|A_BOLD);
						move(yy4,xx4);						
					}
				break;
				case 1:
					if(yy4==13 && xx4==60){
						yy4T = yy4; 
						xx4T = xx4;
						attron(COLOR_PAIR(2)|A_BOLD); 
						mvprintw(yy4T,yy4T,"."); 
						attroff(COLOR_PAIR(2)|A_BOLD);						
						xx4=17;
						attron(COLOR_PAIR(7)|A_BOLD);						 
						mvprintw(yy4,xx4,"G");
						attroff(COLOR_PAIR(7)|A_BOLD);
					}
					cnsMAPAf(yy4,xx4+1);
					if(ERRORf == OK){
						attron(COLOR_PAIR(2)|A_BOLD);
						mvprintw(yy4,xx4++,".");
						attroff(COLOR_PAIR(2)|A_BOLD);
						attron(COLOR_PAIR(7)|A_BOLD);						 
						mvprintw(yy4,xx4,"G");
						attroff(COLOR_PAIR(7)|A_BOLD);
						move(yy4,xx4);
					}
				break;
				case 2:
					cnsMAPAf(yy4+1,xx4);
					if(ERRORf == OK){						
						attron(COLOR_PAIR(2)|A_BOLD);
						mvprintw(yy4++,xx4,".");
						attroff(COLOR_PAIR(2)|A_BOLD);
						attron(COLOR_PAIR(7)|A_BOLD);						 
						mvprintw(yy4,xx4,"G");
						attroff(COLOR_PAIR(7)|A_BOLD);
						move(yy4,xx4);
					}
				break;
				case 3:
					cnsMAPAf(yy4-1,xx4);
					if(ERRORf == OK){				
						attron(COLOR_PAIR(2)|A_BOLD);
						mvprintw(yy4--,xx4,".");
						attroff(COLOR_PAIR(2)|A_BOLD);
						attron(COLOR_PAIR(7)|A_BOLD);						 
						mvprintw(yy4,xx4,"G");
						attroff(COLOR_PAIR(7)|A_BOLD);
						move(yy4,xx4);
					}
				break;
				
					
			}		
	}
            
	//Consulta Colision [Pacman | Fantasma]
	void colision(int cY, int cX){
		if(cY == yy1 && cX == xx1){	gO = 1;	}else{ gO = 0; }
		if(cY == yy2 && cX == xx2){	gO = 1;	}else{ gO = 0; }
		if(cY == yy3 && cX == xx3){	gO = 1;	}else{ gO = 0; }
		if(cY == yy4 && cX == xx4){	gO = 1;	}else{ gO = 0; }						
	}
	
    //Menú Principal
    int main(int argc, char **argv){

        initscr();
        iniMO();
        start_color();
        /***************COLORES******************/
        //Fondo
        init_pair(0,COLOR_BLUE,COLOR_BLACK);
        init_pair(1,COLOR_WHITE,COLOR_BLACK);
        //PACMAN
        init_pair(2,COLOR_YELLOW,COLOR_BLACK);
        //Teclas de Ayuda
        init_pair(3,COLOR_RED,COLOR_BLACK);
        //Fantasmas
        init_pair(4,COLOR_MAGENTA,COLOR_BLACK);
        init_pair(5,COLOR_CYAN,COLOR_BLACK);
        init_pair(6,COLOR_GREEN,COLOR_BLACK);
        init_pair(7,COLOR_WHITE,COLOR_BLACK);
        init_pair(8,COLOR_BLUE,COLOR_BLACK);       
        /*****************************************/
       
        bkgd(COLOR_PAIR(0));    
        keypad(stdscr, TRUE);
        curs_set(FALSE);
        noecho();
        refresh();
       
        //Pinta el Mundo
        mundo();
        /******Reconocimiento de Teclas**********/
        while((ch = getch()) != KEY_F(12)){
			//Fantasmas
			mvFantasma1();
			mvFantasma2();
			mvFantasma3();
			mvFantasma4();

            switch(ch){
                case KEY_LEFT:                    
                    if(y==13 && x==18){
                        yT = y;
                        xT = x;
                        mvprintw(yT,xT," ");
                        x=61;
                        attron(COLOR_PAIR(2));
                        mvprintw(y,x,"0");
                        attroff(COLOR_PAIR(2));
                    }                   
                    cnsMAPA(y,x-1);
                    colision(y,x);
					if(gO == OK){                    
						if (ERROR == OK){
							txtMOS();
							mvprintw(y,x--," ");
							attron(COLOR_PAIR(2));
							mvprintw(y,x,"0");
							attroff(COLOR_PAIR(2));
							move(y,x);                       
						}
					}else{
						mvprintw(y,x," ");
						vida--;
						mundo();
					}                     
                break;
                case KEY_RIGHT:					
                    if(y==13 && x==60){
                        yT = y;
                        xT = x;
                        mvprintw(yT,xT," ");                       
                        x=17;
                        attron(COLOR_PAIR(2));
                        mvprintw(y,x,"0");
                        attroff(COLOR_PAIR(2));
                    }
                    cnsMAPA(y,x+1);
                    colision(y,x);
                    if(gO == OK){                    
						if(ERROR == OK){
							txtMOS();
							mvprintw(y,x++," ");
							attron(COLOR_PAIR(2));
							mvprintw(y,x,"0");
							move(y,x);
							attroff(COLOR_PAIR(2));
						}
					}else{
						mvprintw(y,x," ");
						vida--;
						mundo();
					}                    
                    attroff(COLOR_PAIR(2));
                break;
                case KEY_DOWN:
                    cnsMAPA(y+1,x);
                    colision(y,x);
                    if(gO == OK){
						if(ERROR == OK){                       
							txtMOS();
							mvprintw(y++,x," ");
							attron(COLOR_PAIR(2));
							mvprintw(y,x,"0");
							move(y,x);
							attroff(COLOR_PAIR(2));
						}
					}else{
						mvprintw(y,x," ");
						vida--;
						mundo();
					}
					
                break;
                case KEY_UP:
                    cnsMAPA(y-1,x);
                    colision(y,x);
                    if(gO == OK){                    
						if(ERROR == OK){               
							txtMOS();
							mvprintw(y--,x," ");
							attron(COLOR_PAIR(2));
							mvprintw(y,x,"0");
							move(y,x);
							attroff(COLOR_PAIR(2));
						}
					}else{
						mvprintw(y,x," ");
						vida--;
						mundo();
					}                    
                break;
               
                case KEY_F(5):
                    vida--;
                    mundo();
                break;
                   
            }
       
        }
              
        endwin();           
       
        return 0;
    }
