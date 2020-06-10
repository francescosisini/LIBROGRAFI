/*___________________________________________________________
 * 
 * FILE: gioca_tuki_random.c
 */
#include "tuki5_modello.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* 
   ITA: Controlla se l'oggetto nella cella non è un muro
   ENG: In order to be accessible, a cell must not contain 
   a piece of wall
*/
bool oggetto_accessibile(oggetto s)
{
  if(s == 'J' || s == 'U' || s == 'V')
    return true;
  else
    return false;
}

/*
  ITA: Questa funzione contiene la logica dell'agente Pac-Man.
  Viene chiamata da tuki5_controllo ad ogni ciclo di gioco
  ENG: This function contains the Pac-Man agent's logic. 
  It is called by  tuki5_controllo every game cycle
 */
direzione gioca_tuki(posizioni posi, oggetto **labx)
{
  static direzione ld = SINISTRA; 
  static bool init = false;
  if(!init)
    {
      srand(time(0));
      init = true;
    }
  
  /* 
     ITA: Riga e colonna della cella di Pac-Man
     ENG: Row and column of Pac-Man's cell 
     into the labyrinth
  */
  int i = posi.tuki_y;
  int j = posi.tuki_x;
  
  /* 
     ITA: Celle confinanti 
     ENG: Neighboring cells
  */
  oggetto s,d,a,b;
  s = labx[i][j-1]; //sinistra, left
  d = labx[i][j+1]; //destra, right
  a = labx[i-1][j]; //su, up
  b = labx[i+1][j]; //giu, down
  
  /* 
     ITA: Vera quando la cella nella direzione scelta
     è accessibile
     ENG: The variable is set true when the cell 
     in the chosen direction is available 
     (doesn't contain walls)
  */
  bool trovata_direzione = false;
  
  /* 
     ITA: Vera quando la scelta della direzione ha avuto
     una componente random
     ENG: The variable is set true when the choice of the direction
     has been randomly generated
  */
  bool aleatorio = false;
  
  while(!trovata_direzione)
    {
      if(!oggetto_accessibile(s) && ld == SINISTRA)
        {
          ld = rand()%2;
          if(ld == 0)
            ld = SU;
          else
            ld = GIU;
          aleatorio = true;
        }
      else
	if(!oggetto_accessibile(d) && ld == DESTRA)
          {
	    
            ld = rand()%2;
            if(ld == 0) ld = SU;
            else
              ld = GIU;
            aleatorio = true;
          }
        else
	  if(!oggetto_accessibile(a) && ld == SU)
            {
              ld = rand()%2;
              if(ld == 0) ld = SINISTRA;
              else
                ld = DESTRA;
              aleatorio = true;
            }
          else
            if(!oggetto_accessibile(b) && ld == GIU)
	      {
                ld = rand()%2;
                if(ld == 0) ld = SINISTRA;
                else
                  ld = DESTRA;
                aleatorio = true;
	      }
            else
              trovata_direzione = true;
    }
    
  if(aleatorio) return ld;
    
  /* 
     ITA:Se la direzione non è aleatoria
     qui viene data un'altra chance alla fortuna.
     Questo per evitare loop nel labirinto
     ENG: If the direction has not been randomly generated, 
     here it is forced to be randomly changed in an available 
     direction
   */
  if(oggetto_accessibile(a) && ld !=SU && ld!=GIU)
    {
      int sv = rand()%10;
	if(sv>=5)
	  ld = SU;
      }
    if(oggetto_accessibile(b) && ld !=GIU && ld!=SU)
      {
	int sv = rand()%10;
	if(sv>=5)
	  ld = GIU;
      }
    if(oggetto_accessibile(s) && ld !=SINISTRA && ld!=DESTRA)
      {
	int sv = rand()%10;
	if(sv>=5)
	  ld = SINISTRA;
      }
    if(oggetto_accessibile(d) && ld !=DESTRA && ld!=SINISTRA)
      {
	int sv = rand()%10;
	if(sv>=5)
	  ld = DESTRA;
      }
    
    return ld;
  
}
