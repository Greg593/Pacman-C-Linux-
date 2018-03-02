/*
 * Matriz Ortogonal.cpp
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


#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>

#define FARRIBA 21
#define FABAJO 22
#define FIZQ 23
#define FDER 24
#define MAX_SCREEN_AREA 100

void primercolumnas(struct campo **A,struct campo **B);
void restcolumnas(struct campo **A,struct campo **B);
void construir(struct campo **A,struct campo **B);

struct campo{
	int arb;
	int aba;
	int der;
	int izq;
	struct campo *izquierda;
	struct campo *derecha;
	struct campo *arriba;
	struct campo *abajo;
};

struct tabla{
	struct campo *dato;
	};
	
struct campo *nivel;
struct campo *temp1;
struct tabla temp2[54];
int columnas=0;
int filas=0;

int gotoxy(int x, int y){
char essq[MAX_SCREEN_AREA]={0}; // String variable to hold the escape sequence
sprintf(essq,"\033[%d;%df",y,x);
printf("%s",essq);
return 0;
}

int getch(){
      
   struct termios oldt, newt;
   int ch;
   tcgetattr( STDIN_FILENO, &oldt );
   newt = oldt;
   newt.c_lflag &= ~( ICANON | ECHO );
   tcsetattr( STDIN_FILENO, TCSANOW, &newt );
   do{
      ch = getchar();
   }while(ch==10);
   if(ch==27){
      getchar();
      ch = getchar();
      switch(ch){
         case 'A':
            ch=21;
         break;
         case 'B':
            ch=22;
         break;
         case 'C':
            ch=23;
         break;
         case 'D':
            ch=24;   
         break;
      }
   }
   tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
   return ch; 
}

char leeDirecto(unsigned opc){
   char ch;
   ch=getch();
   switch(opc){
      case 1:
         printf("%c", ch);
      break;
      case 2:
         printf("%c\n", ch);
      break;
      case 3:
         printf("%c\n", ch);
      break;
   }
   return ch;
}

void construir(struct campo **A,struct campo **B){
	
	if(filas == 0){
		
		primercolumnas(&(*A),&(*B));
		construir(&(*A)->abajo,&(*B));
		}else{
			
			restcolumnas(&(*A),&(*B));
			if(filas < 20){
				construir(&(*A)->abajo,&(*B));
				}
			}
	
	}

void primercolumnas(struct campo **A,struct campo **B){
	
	if((*A)==NULL && columnas < 54 ){
		(*A)=(struct campo *)malloc(sizeof(struct campo));
		(*A)->arriba = NULL;
		(*A)->abajo = NULL;
		(*A)->derecha = NULL;
		if(columnas == 0){
			(*A)->izquierda = NULL;
			}else{
				(*A)->izquierda = (*B);
				}
		
		(*A)->arb = 0;
		(*A)->aba = 0;
		(*A)->izq = 0;
		(*A)->der = 0;
		(*B)=(*A);
		temp2[columnas].dato = (*A);
		columnas = columnas+1;
		primercolumnas(&(*A)->derecha,&(*B));
		}
	if(columnas == 54){
		filas = filas + 1;
		columnas = 0;
		} 
}

void restcolumnas(struct campo **A,struct campo **B){
	
	if((*A)==NULL && columnas < 54){
		(*A)=(struct campo *)malloc(sizeof(struct campo));
		(*A)->arriba = temp2[columnas].dato;
		(*A)->abajo = NULL;
		if(columnas > 0){
			temp2[columnas].dato->abajo = (*A);
			}
		(*A)->derecha = NULL;
		if(columnas == 0){
			(*A)->izquierda = NULL;
			}else{
				(*A)->izquierda = (*B);
				}
		
		(*A)->arb = 0;
		(*A)->aba = 0;
		(*A)->izq = 0;
		(*A)->der = 0;
		(*B)=(*A);
		temp2[columnas].dato = (*A);
		columnas = columnas + 1;
		restcolumnas(&(*A)->derecha,&(*B));
		}
	if(columnas == 54){
		filas = filas + 1 ;
		columnas = 0;
		} 
	}


int main(int argc, char **argv)
{
	nivel = NULL;
	temp1 = NULL;
	construir(&nivel,&temp1);
	
	return 0;
}


