/*
 * Matriz Ortogonal (Final).cxx
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


#include<iostream>
#include<string>
#include<panel.h>
#include<malloc.h>

using namespace std;

void inicializarM();
void enlazar();

int numero = 50;
int pasa=0;
int posiY=0;
int posiX=0;
char qHay;

typedef struct nodo{
int posY;
int posX;
char dato;
struct nodo *izq;
struct nodo *der;
struct nodo *sup;
struct nodo *inf;
}nodo;

nodo *inicio = 0, *fin, *ini, *temp, *p;

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

	//Consulta Mapa para colisiones [Pared | Fantasmas]
	void cnsMAPA(int pY, int pX){
					
			if(mapa[pY][pX] == 'Y' || mapa[pY][pX] == 'X' || mapa[pY][pX] == 'D' || mapa[pY][pX] == 'A' || mapa[pY][pX] == 'B' || mapa[pY][pX] == 'C'){
				pasa = 1;
				qHay = mapa[pY][pX];
			}else{
				pasa = 0;
				qHay = ' ';
			}

	}

	void llenaMO(struct nodo *a){
			
		if(a!=NULL){
			llenaMO(a->izq);
				if(a!=NULL){
					cnsMAPA(posiY,posiX);
					a->dato = qHay;
				}
			llenaMO(a->der);
				if(a!=NULL){
					cnsMAPA(posiY,posiX);
					a->dato = qHay;
				}
			llenaMO(a->sup);
				if(a!=NULL){
					cnsMAPA(posiY,posiX);
					a->dato = qHay;
				}			
			llenaMO(a->inf);
				if(a!=NULL){
					cnsMAPA(posiY,posiX);
					a->dato = qHay;
				}			
		}
		
	}
	
	void enlazar(int num){
		int cont = 1, cont2 = 0;
			nodo *s, *q;
			q = ini;
			s = inicio;
				
				while(cont < num){
					s->posX = posiX++;
					s->posY = posiY++;
					s = s->inf;
					cont++;
				}
				
				while(cont2 < numero){
					q->posX = posiX++;
					q->posY = posiY++;
					q->sup = s;
					s->inf = q;
					s = s->der;
					q = q->der;
					cont2++;
				}
	}
	
	void inicializarM(){
		nodo *p;
		for(int i = 0; i < numero; i++){
			for(int j = 0; j < numero; j++){
				if(i == 0){
					if(inicio == NULL){
						p = (nodo*)malloc(sizeof(nodo));
							p->posX = posiX++;
							p->posY = posiY++;
							//p->dato = 'P';
							p->izq = NULL;
							p->der = NULL;
							p->sup = NULL;
							p->inf = NULL;
							inicio = p;
							fin = p;
					}else{
						p = (nodo*)malloc(sizeof(nodo));
							p->posX = posiX++;
							p->posY = posiY++;
							//p->dato = 'P';
							p->der = NULL;
							p->inf = NULL;
							p->izq = fin;
							fin->der = p;
							fin = p;
					}
				}else{
					if(ini == NULL){
						p = (nodo*)malloc(sizeof(nodo));
							p->posX = posiX++;
							p->posY = posiY++;
							//p->dato = 'P';
							p->izq = NULL;
							p->der = NULL;
							p->inf = NULL;
							ini = p;
							fin = p;
					}else{
						p = (nodo*)malloc(sizeof(nodo));
							p->posX = posiX++;
							p->posY = posiY++;
							//p->dato = 'P';
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

int main(){
	struct nodo *r=NULL;
	inicializarM();
	llenaMO(r);
	return 0;
}



