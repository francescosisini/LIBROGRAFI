/*___________________________________________________________
 * 
 * FILE: gioca_tuki_random.c
 */
#include "tuki5_modello.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

bool oggetto_accessibile(oggetto s)
{
  if(s == 'J' || s == 'U' || s == 'V')
    return true;
  else
    return false;
}

direzione gioca_tuki(posizioni posi, oggetto **labx)
{
  static direzione ld = SINISTRA; 
  static bool init = false;
  if(!init)
    {
      srand(time(0));
      init = true;
    }

  int i = posi.tuki_y;
  int j = posi.tuki_x;

  oggetto s,d,a,b;
  s = labx[i][j-1]; //sinistra, left
  d = labx[i][j+1]; //destra, right
  a = labx[i-1][j]; //su, up
  b = labx[i+1][j]; //giu, down

  int x = posi.tuki_x;
  int y = posi.tuki_y;
  int x_g[4];
  int y_g[4];
  x_g[0] = posi.blinky_x;
  x_g[1] = posi.pinky_x;
  x_g[2] = posi.inky_x;
  x_g[3] = posi.clyde_x;
  
  y_g[0] = posi.blinky_y;
  y_g[1] = posi.pinky_y;
  y_g[2] = posi.inky_y;
  y_g[3] = posi.clyde_y;
  
  char s_g = 0, d_g = 0,a_g = 0,b_g = 0;
  for (int ig = 0; ig<4; ig++)
    {
      s_g = s_g || ( x_g[ig] < x) && ( x - x_g[ig] <=2 )  && (y == y_g[ig]);
      s_g = s_g || ((x_g[ig] == x-1) &&  (y_g[ig] == y+1));
      s_g = s_g || ((x_g[ig] == x-1) &&  (y_g[ig] == y-1));
      d_g = d_g || ( x_g[ig] > x) && (x_g[ig] - x <= 2) && (y == y_g[ig]);
      d_g = d_g || ((x_g[ig] == x+1) &&  (y_g[ig] == y+1));
      d_g = d_g || ((x_g[ig] == x+1) &&  (y_g[ig] == y-1));
      a_g = a_g || (x == x_g[ig]) && ( y >  y_g[ig]) && ( y - y_g[ig] <=2);
      a_g = a_g || ((y == y_g[ig] + 1) && (x_g[ig] == x+1));
      a_g = a_g || ((y == y_g[ig] + 1) && (x_g[ig] == x-1));
      b_g = b_g || (x == x_g[ig]) && ( y <  y_g[ig]) && ( y_g[ig]- y <=2);
      b_g = b_g || ((y == y_g[ig] - 1) && (x_g[ig] == x+1));
      b_g = b_g || ((y == y_g[ig] - 1) && (x_g[ig] == x-1));
    }
  
  if((s_g || d_g || a_g || b_g) && FUGA)
    {
      direzione esc[4];
      for(int i=0;i<4;i++) esc[i]=FERMO;
      int ki = 0; //direzioni buone, good directions
      
      if(oggetto_accessibile(s) && !s_g)
	{
	  esc[ki] = SINISTRA;
	  ki++;
	}
      if(oggetto_accessibile(a) && !a_g)
	{
	  esc[ki] = SU;
	  ki++;
	}
      if(oggetto_accessibile(d) && !d_g)
	{
	  esc[ki] = DESTRA;
	  ki++;
	}
      if(oggetto_accessibile(b) && !b_g)
	{
	  esc[ki] = GIU;
	  ki++;
	}
      if(ki == 0)
	{
	  return FERMO;
	}
      ld = esc[rand()%ki];
      
      return ld;
    }

  bool trovata_direzione = false;

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
      else if(!oggetto_accessibile(d) && ld == DESTRA)
	{ 
	  ld = rand()%2;
	  if(ld == 0) ld = SU;
	  else
	    ld = GIU;
	  aleatorio = true;
	}
      else if(!oggetto_accessibile(a) && ld == SU)
	{
	  ld = rand()%2;
	  if(ld == 0) ld = SINISTRA;
	  else
	    ld = DESTRA;
	  aleatorio = true;
	}
      else if(!oggetto_accessibile(b) && ld == GIU)
	{
	  ld = rand()%2;
	  if(ld == 0) ld = SINISTRA;
	  else
	    ld = DESTRA;
	  aleatorio = true;
	}
      else trovata_direzione = true;
    }
  
  if(aleatorio) return ld;

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
