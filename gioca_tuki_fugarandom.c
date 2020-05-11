#include "tuki5_modello.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


int si_passa(char s)
{
  if(s == 'J' || s == 'U' || s == 'V')
    return 1;
  else
    return 0;
}

direzione gioca_tuki(posizioni p, oggetto **labx){
  static int init = 0;
  if(!init)
    {
      srand(time(0));
      init = 1;
    }
  
  static int nodi[33];
  static direzione ld=SINISTRA;
  int i = p.tuki_y;
  int j = p.tuki_x;
  oggetto s = labx[i][j-1];
  oggetto d = labx[i][j+1];
  oggetto a = labx[i-1][j];
  oggetto b = labx[i+1][j];


  //Gestione ostacoli
  char bloccato = 1;
  char appenadeciso = 0;
  while(bloccato)
    {
      
      if( !si_passa(s) && ld == SINISTRA)
        {
          ld = rand()%2;
          if(ld==0)
            ld = SU;
          else
            ld = GIU;
          appenadeciso = 1;
        }
      else
        
        if(!si_passa(d) && ld == DESTRA)
          {
            
            ld = rand()%2;
            if(ld==0) ld = SU;
            else
              ld = GIU;
            appenadeciso = 1;
          }
        else
          
          if(!si_passa(a) && ld == SU)
            {
              ld = rand()%2;
              if(ld==0) ld = SINISTRA;
              else
                ld = DESTRA;
              appenadeciso = 1;
            }
          else
            if(!si_passa(b) && ld == GIU)
             {
                ld = rand()%2;
                if(ld==0) ld = SINISTRA;
                else
                  ld = DESTRA;
                appenadeciso = 1;
             }
            else
              bloccato = 0;
    }  

  if(appenadeciso) return ld;
  
  //Cambi voluti
  
  if(si_passa(a) && ld !=SU && ld!=GIU)
    {
      int sv = rand()%10;
      if(sv>=5)
        ld = SU;
    }
   if(si_passa(b) && ld !=GIU && ld!=SU)
    {
      int sv = rand()%10;
      if(sv>=5)
        ld = GIU;
    }
   if(si_passa(s) && ld !=SINISTRA && ld!=DESTRA)
    {
      int sv = rand()%10;
      if(sv>=5)
        ld = SINISTRA;
    }
    if(si_passa(d) && ld !=DESTRA && ld!=SINISTRA)
    {
      int sv = rand()%10;
      if(sv>=5)
        ld = DESTRA;
    }

      
  return ld;
 

}
/*
A = 'A', //ANGOLO ALTO SIN BORDO
   B = 'B', //ANGOLO ALTO DES BORDO
   C = 'C', //ANGOLO BASSO SIN BORDO 
   D = 'D', //ANGOLO BASSO DES BORDO
   E = 'E', //MURO ORR BORDO
   F = 'F', //MURO VER BORDO
   G = 'G', //ANGOLO ALTO SIN 
   H = 'H', //ANGOLO ALTO DES
   I = 'I', //ANGOLO ALTO DES
   J = 'J', //SPAZIO
   K = 'K',
   L = 'L', //ANGOLO ALTO SIN
   M = 'M', //ANGOLO BASSO DES
   N = 'N', //ANGOLO BASSO SIN
   O = 'O', //ANGOLO BASSO SIN
   P = 'P', //ANGOLO ALTO SIN
   Q = 'Q', //ANGOLO BASSO DES
   R = 'R', //ANGOLO ALTO DES
   S = 'S', //MURO VER
   T = 'T', //MURO ORR
   U = 'U', //PUNTINO
   V = 'V', //PILLOLA
   X = 'X', //MURO VER BORDO
   Y = 'Y', //ANGOLO BASSO DES
   W = 'W', //ANGOLO BASSO SIN
   Z = 'Z', //MURO ORZZ BORDO
*/
