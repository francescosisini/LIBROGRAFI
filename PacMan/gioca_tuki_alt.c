#include "tuki5_modello.h"
#include <stdio.h>
#include <unistd.h>



direzione gioca_tuki(posizioni p, oggetto **labx){
  static int turno = 0;
  static direzione ld=SINISTRA;
  
  int r = p.tuki_y;
  int c = p.tuki_x;
  if( ld == SINISTRA)
    {
      if(labx[r][c-1] !=J && labx[r][c-1] !=U && labx[r][c-1] != V)
        {
          if(labx[r+1][c] == J || labx[r+1][c] == U || labx[r+1][c] == V)
            ld = GIU;
          else
            if(labx[r][c+1] == J || labx[r][c+1] == U || labx[r][c+1] == V)
              ld = DESTRA;
            else
              ld = SU;
        }
      return ld;
    }

  if( ld == SU)
    {
      if(labx[r-1][c] !=J && labx[r-1][c] !=U && labx[r-1][c] != V)
        {
          if(labx[r][c+1] == J || labx[r][c+1] == U || labx[r][c+1] == V)
            ld = DESTRA;
          else
            if(labx[r+1][c] == J || labx[r+1][c] == U || labx[r+1][c] == V)
              ld = GIU;
            else
              ld = SINISTRA;
        }
      return ld;
    }
  
  if( ld == DESTRA)
    {
      if(labx[r][c+1] !=J && labx[r][c+1] !=U && labx[r][c+1] != V)
        {
          if(labx[r-1][c] == J || labx[r-1][c] == U || labx[r-1][c] == V)
            ld = SU;
          else
            if(labx[r+1][c] == J || labx[r+1][c] == U || labx[r+1][c] == V)
              ld = GIU;
            else
              ld = SINISTRA;
        }
      return ld;
    }

  if( ld == GIU)
    {
      if(labx[r+1][c] !=J && labx[r+1][c] !=U && labx[r+1][c] != V)
        {
          if(labx[r][c+1] == J || labx[r][c+1] == U || labx[r][c+1] == V)
            ld = DESTRA;
          else
            if(labx[r-1][c] == J || labx[r-1][c] == U || labx[r-1][c] == V)
              ld = SU;
          
            else
              ld = SINISTRA;
        }
      return ld;
    }
  
  
}
