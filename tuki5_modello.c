/*
  Tuki5: il pacman - A C-Language coding game based on  pacman game
  
  Copyright (C) 2018  Francesco Sisini (scuolaSisini)
  
  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
  
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */



#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tuki5_modello.h"

/* stato di Tuki */
char sppc = 0;
int conto_rovescia = 10;

/* punti */
int punti = 0;

/* il campo di battaglia */
oggetto  campo[ALTEZZA][LARGHEZZA]={
  {J,J,J,J,J,J,J,J,J,J,J,J,J,J,J,J,J,J,J,J,J,J,J,J,J,J,J,J},
  {J,J,J,J,J,J,J,J,J,J,J,J,J,J,J,J,J,J,J,J,J,J,J,J,J,J,J,J},
  {A,E,E,E,E,E,E,E,E,E,E,E,E,I,L,E,E,E,E,E,E,E,E,E,E,E,E,B},
  {F,U,U,U,U,U,U,U,U,U,U,U,U,S,S,U,U,U,U,U,U,U,U,U,U,U,U,X},
  {F,U,G,T,T,H,U,G,T,T,T,H,U,S,S,U,G,T,T,T,H,U,G,T,T,H,U,X},
  {F,V,S,J,J,S,U,S,J,J,J,S,U,S,S,U,S,J,J,J,S,U,S,J,J,S,V,X},
  {F,U,W,T,T,Y,U,W,T,T,T,Y,U,W,Y,U,W,T,T,T,Y,U,W,T,T,Y,U,X},
  {F,U,U,U,U,U,U,U,U,U,U,U,U,U,U,U,U,U,U,U,U,U,U,U,U,U,U,X},
  {F,U,G,T,T,H,U,G,H,U,G,T,T,T,T,T,T,H,U,G,H,U,G,T,T,H,U,X},
  {F,U,W,T,T,Y,U,S,S,U,W,T,T,H,G,T,T,Y,U,S,S,U,W,T,T,Y,U,X},
  {F,U,U,U,U,U,U,S,S,U,U,U,U,S,S,U,U,U,U,S,S,U,U,U,U,U,U,X},
  {C,Z,Z,Z,Z,B,U,S,W,T,T,H,J,S,S,J,G,T,T,Y,S,U,A,Z,Z,Z,Z,D},
  {J,J,J,J,J,F,U,S,G,T,T,Y,J,W,Y,J,W,T,T,H,S,U,X,J,J,J,J,J},
  {J,J,J,J,J,F,U,S,S,J,J,J,J,J,J,J,J,J,J,S,S,U,X,J,J,J,J,J},
  {J,J,J,J,J,F,U,S,S,J,A,E,E,J,J,E,E,B,J,S,S,U,X,J,J,J,J,J},
  {Z,Z,Z,Z,Z,D,U,W,Y,J,F,J,J,J,J,J,J,X,J,W,Y,U,C,E,E,E,E,E},
  {J,J,J,J,J,J,U,J,J,J,F,J,J,J,J,J,J,X,J,J,J,U,J,J,J,J,J,J},
  {E,E,E,E,E,B,U,G,H,J,F,J,J,J,J,J,J,X,J,G,H,U,A,Z,Z,Z,Z,Z},
  {J,J,J,J,J,F,U,S,S,J,C,E,E,E,E,E,E,D,J,S,S,U,X,J,J,J,J,J},
  {J,J,J,J,J,F,U,S,S,J,J,J,J,J,J,J,J,J,J,S,S,U,X,J,J,J,J,J},
  {J,J,J,J,J,F,U,S,S,J,G,T,T,T,T,T,T,H,J,S,S,U,X,J,J,J,J,J},
  {A,E,E,E,E,D,U,W,Y,J,W,T,T,H,G,T,T,Y,J,W,Y,U,C,E,E,E,E,B},
  {F,U,U,U,U,U,U,U,U,U,U,U,U,S,S,U,U,U,U,U,U,U,U,U,U,U,U,X},
  {F,U,G,T,T,H,U,G,T,T,T,H,U,S,S,U,G,T,T,T,H,U,G,T,T,H,U,X},
  {F,U,W,T,H,S,U,W,T,T,T,Y,U,W,Y,U,W,T,T,T,Y,U,S,G,T,Y,U,X},
  {F,V,U,U,S,S,U,U,U,U,U,U,U,J,J,U,U,U,U,U,U,U,S,S,U,U,V,X},
  {O,T,H,U,S,S,U,G,H,U,G,T,T,T,T,T,T,H,U,G,H,U,S,S,U,G,T,Q},
  {P,T,Y,U,W,Y,U,S,S,U,W,T,T,H,G,T,T,Y,U,S,S,U,W,Y,U,W,T,R},
  {F,U,U,U,U,U,U,S,S,U,U,U,U,S,S,U,U,U,U,S,S,U,U,U,U,U,U,X},
  {F,U,G,T,T,T,T,Y,W,T,T,H,U,S,S,U,G,T,T,Y,W,T,T,T,T,H,U,X},
  {F,U,W,T,T,T,T,T,T,T,T,Y,U,W,Y,U,W,T,T,T,T,T,T,T,T,Y,U,X},
  {F,U,U,U,U,U,U,U,U,U,U,U,U,U,U,U,U,U,U,U,U,U,U,U,U,U,U,X},
  {C,Z,Z,Z,Z,Z,Z,Z,Z,Z,Z,Z,Z,Z,Z,Z,Z,Z,Z,Z,Z,Z,Z,Z,Z,Z,Z,D},
  {J,J,J,J,J,J,J,J,J,J,J,J,J,J,J,J,J,J,J,J,J,J,J,J,J,J,J,J},
  {J,J,J,J,J,J,J,J,J,J,J,J,J,J,J,J,J,J,J,J,J,J,J,J,J,J,J,J}                                    
};
oggetto **copia_campo;

/* Numero di trifogli attivi */
int n_trifogli;

/* Posizione giocatori */
posizioni g;

int mangia()
{
  punti+=1;
  return punti;
}

void superpacman(char si_no)
{
  if(si_no)
    {
      conto_rovescia=30;
      sppc=1;
    }
  else
    sppc=0;
}

/*_____________________________________________________
 *|
 *| Se inverso=1, ogni direzione è inverita
 *| srrve ad eseguire il rollback di un movimento
 */
void muovi(direzione d, int *x,int *y,char inverso)
{
  if(!inverso)
    {
      if(d==SU) (*y)=*y-1;
      if(d==GIU) (*y)=*y+1;
      if(d==SINISTRA) (*x)=*x-1;
      if(d==DESTRA) (*x)=*x+1;
    }
  else
    {
      if(d==SU) (*y)=*y+1;
      if(d==GIU) (*y)=*y-1;
      if(d==SINISTRA) (*x)=*x+1;
      if(d==DESTRA) (*x)=*x-1;
    }
}

char mdl_superpacman()
{
  return sppc;
}


/*____________________________________________________
 *|
 *| Verifica se riga e colonna di pacman e di uno dei
 *| fantasmi coincido. Non abilitato se pacman è in
 *| modalità superpacman (pillola)
 */
int rileva_collisione()
{
  if(sppc == 1) return 0;
  
  //-verifica collisione tuki-fantasma
  if(g.tuki_x == g.blinky_x && g.tuki_y == g.blinky_y)
    {
      return 1;
    }
  if(g.tuki_x == g.inky_x && g.tuki_y == g.inky_y)
    {
      return 1;
    }
  if(g.tuki_x == g.pinky_x && g.tuki_y == g.pinky_y)
    {
      return 1;
    }
  if(g.tuki_x == g.clyde_x && g.tuki_y == g.clyde_y)
    {
      return 1;
    }

  return 0;
  
}

int mdl_passo
(direzione tuki,
 direzione blinky,
 direzione inky,
 direzione pinky,
 direzione clyde)
{
  //-verifica se la pillola è attiva
  char sp=mdl_superpacman();
  if(sp)
    {
      if(conto_rovescia==0)
        superpacman(0);
      else
        conto_rovescia-=1;
    }

  int collisione=0;
  
  //-Modifica le coordinate
  muovi(tuki,&g.tuki_x,&g.tuki_y,0);
  
  collisione = rileva_collisione();
  
  muovi(blinky,&g.blinky_x,&g.blinky_y,0);

  collisione = collisione || rileva_collisione();

  muovi(inky,&g.inky_x,&g.inky_y,0);

  collisione = collisione || rileva_collisione();

  muovi(pinky,&g.pinky_x,&g.pinky_y,0);

  collisione = collisione || rileva_collisione();

  muovi(clyde,&g.clyde_x,&g.clyde_y,0);

  collisione = collisione || rileva_collisione();
  
  //-Verifica collisione muro
  if(campo[g.tuki_y][g.tuki_x] != J && campo[g.tuki_y][g.tuki_x] != U && campo[g.tuki_y][g.tuki_x] != V)
    {
      muovi(tuki,&g.tuki_x,&g.tuki_y,1);
      collisione = collisione || rileva_collisione();
    }
  
  if(campo[g.blinky_y][g.blinky_x] != J && campo[g.blinky_y][g.blinky_x] != U && campo[g.blinky_y][g.blinky_x] != V)
    {
      muovi(blinky,&g.blinky_x,&g.blinky_y,1);
    }

   if(campo[g.inky_y][g.inky_x] != J && campo[g.inky_y][g.inky_x] != U && campo[g.inky_y][g.inky_x] != V)
    {
      muovi(inky,&g.inky_x,&g.inky_y,1);
    }

    if(campo[g.pinky_y][g.pinky_x] != J && campo[g.pinky_y][g.pinky_x] != U && campo[g.pinky_y][g.pinky_x] != V)
    {
      muovi(pinky,&g.pinky_x,&g.pinky_y,1);
    }

    if(campo[g.clyde_y][g.clyde_x] != J && campo[g.clyde_y][g.clyde_x] != U && campo[g.clyde_y][g.clyde_x] != V)
    {
      muovi(clyde,&g.clyde_x,&g.clyde_y,1);
    }

  //-verifica imbocco tunnel
    if(g.tuki_x == 23 && g.tuki_y==16)
      {
        g.tuki_x = 3;
        muovi(DESTRA,&g.tuki_x,&g.tuki_y,0);
      }

     if(g.tuki_x == 2 && g.tuki_y==16)
      {
        g.tuki_x = 22;
        muovi(DESTRA,&g.tuki_x,&g.tuki_y,0);
      }
  
  //-verifica consumo trifogli
  if(campo[g.tuki_y][g.tuki_x] == U)
    {
      mangia();
      campo[g.tuki_y][g.tuki_x] = J;
      copia_campo[g.tuki_y][g.tuki_x] = J;
    }

  //-verifica consumo pillola
   if(campo[g.tuki_y][g.tuki_x] == V)
    {
      mangia();
      campo[g.tuki_y][g.tuki_x] = J;
      copia_campo[g.tuki_y][g.tuki_x] = J;
      superpacman(1);
    }
   else
     {
       if(collisione) return 0;
     }

   
   
  return 1;
}

oggetto ** mdl_campo(){

  return copia_campo;
}

posizioni mdl_posizioni()
{
  return g;
}

int mdl_genera_campo(){
  int level=1;
  int l=1,i;
  int h=ALTEZZA;
  int w=LARGHEZZA;

  /** inizializza la posizione dei giocatori */
  g.tuki_y = 25;
  g.tuki_x = 14;
  g.blinky_y = 17;
  g.blinky_x = 14;
  g.inky_y = 17;
  g.inky_x = 14;
  g.pinky_y = 17;
  g.pinky_x = 14;
  g.clyde_y = 17;
  g.clyde_x = 14;
  
  /** Alloca memoria per il campo */
  copia_campo=(oggetto**)malloc(h*sizeof(oggetto*));
  
  if(!copia_campo)return 1;

  for(int in=0;in<h;in++)
    {
      *(copia_campo+in)=malloc(w*sizeof(oggetto));
      if(!(*(copia_campo+in)))return 1;
    }
  
  /*Copia il campo in campo*/
  for(int i=0;i<h;i+=1)
    {
      for(int j=0;j<w;j+=1)
	{
          copia_campo[i][j]=campo[i][j];
	}
    }

  
  /*Conto i fiori rimasti nel campo*/
  for(int i=0;i<h;i+=1)
    for(int j=0;j<w;j+=1){
      if(campo[i][j]==TRIFOGLIO) n_trifogli++;
    }
  
  return 1;
}

void mdl_libera_campo()
{
  
  for(int in=0;in<ALTEZZA;in++)
    {
      free(*(copia_campo+in));
    }
  
  
  free(copia_campo);
}

int mdl_punteggio(){
  
  return punti;

}

