/*____________________________________________
* FILE: gioca_tuki_boustrophedon.c
*/

#include "tuki5_modello.h"
#include "libagri.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

rei_genus rivela_rei_genus(oggetto contenuto);

agri_Tabella moveo_Cellam(agri_Tabella * ptab, versus dir);

direzione gioca_tuki(posizioni posi, oggetto **labx){

  labx[16][2]='A';
  labx[16][23]='A';
  labx[14][13]='A';
  labx[14][14]='A';
  
  static int init=0;
  static agri_Tabella g=NULL;
  static agri_Iter p=NULL;
  static agri_Iter l=NULL;
  
  int i = posi.tuki_y;
  int j = posi.tuki_x;
  oggetto s_ = labx[i][j-1];
  oggetto d_ = labx[i][j+1];
  oggetto a_ = labx[i-1][j];
  oggetto b_ = labx[i+1][j];
  
  if(!init)
    {
      init=1;
  
      agri_creo_Tabellam(&g);      
      agri_Tabella fn=(agri_Tabella)malloc(sizeof(agri_Cella));
      g=fn;
      g->d.visitata=1;
      g->d.rei=ALTRO;
  
      agri_creo_Iter(&p);
      agri_addo_Iter(&p,g);
    }
  
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
  
  unsigned char c[4];
  oggetto cx;
  
  g=p->locus;
  if(!g) exit(-1);
  
  cx = a_;
  
  if(g->sursum==NULL)
    {
      agri_Tabella gc=agri_rivela_Cella(p,SU);
      if(gc)
	{
	  agri_colligo_Cellas(g,gc,SU);
	}
      else
	{
	  Attributi d={0,rivela_rei_genus(cx)};
	  agri_Tabella tg=agri_addo_Tabellam(g,d,SU);
	}
    }
  else
    {
      g->sursum->d.rei=rivela_rei_genus(cx);
    }
  
  //Deorsum
  cx = b_;
  if(g->deorsum==NULL)
    {
      agri_Tabella gc=agri_rivela_Cella(p,GIU);
      if(gc)
	{
	  agri_colligo_Cellas(g,gc,GIU);
	}
      else
	{
	  Attributi d={0,rivela_rei_genus(cx)};
	  agri_Tabella tg=agri_addo_Tabellam(g,d,GIU);
	}
    }
  else
    {
      g->deorsum->d.rei=rivela_rei_genus(cx);
    }
  
  //Dextra
  cx = d_;
  if(g->dextra==NULL)
    {
      agri_Tabella gc=agri_rivela_Cella(p,DESTRA);
      if(gc)
	{
	  agri_colligo_Cellas(g,gc,DESTRA);
	}
      else
	{
	  Attributi d={0,rivela_rei_genus(cx)};
	  agri_Tabella tg=agri_addo_Tabellam(g,d,DESTRA);
	}
    }
  else
    {
      g->dextra->d.rei=rivela_rei_genus(cx);
    }
  
  //Sinistra
  cx = s_;
  if(g->sinistra==NULL)
    {
      agri_Tabella gc=agri_rivela_Cella(p,SINISTRA);
      if(gc)
	{
	  
	  agri_colligo_Cellas(g,gc,SINISTRA);
	}
      else
	{
	  Attributi d={0,rivela_rei_genus(cx)};
	  agri_Tabella tg=agri_addo_Tabellam(g,d,SINISTRA);
	}
    }
  else
    {
      g->sinistra->d.rei=rivela_rei_genus(cx);
    }

  if((s_g || d_g || a_g || b_g) && FUGA)
    {

      if(g->sinistra->d.rei!=MURO && !s_g)
        {
	  moveo_Cellam(&g, SINISTRA);
          g->d.visitata=1;
          agri_addo_Iter(&p,g);
          l=p;
          return SINISTRA;
        }

      if(g->sursum->d.rei!=MURO && !a_g)
        {
	  moveo_Cellam(&g, SU);
          g->d.visitata=1;
          agri_addo_Iter(&p,g);
          l=p;
          return SU;
        }

      if(g->dextra->d.rei!=MURO && !d_g)
        {
	  moveo_Cellam(&g, DESTRA);
          g->d.visitata=1;
          agri_addo_Iter(&p,g);
          l=p;
          return DESTRA;
        }

      if(g->deorsum->d.rei!=MURO && !b_g)
        {
	  moveo_Cellam(&g, GIU);
          g->d.visitata=1;
          agri_addo_Iter(&p,g);
          l=p;
          return GIU;
        }
    }

  if(g->sinistra->d.visitata==0&&g->sinistra->d.rei!=MURO)
    {
      g=g->sinistra;
      g->d.visitata=1;
      agri_addo_Iter(&p,g);
      l=p;
      return SINISTRA;
    }

  if(g->sursum->d.visitata==0&&g->sursum->d.rei!=MURO)
    {
      g=g->sursum;
      g->d.visitata=1;
      agri_addo_Iter(&p,g);
      l=p;
      return SU;
    }

  if(g->dextra->d.visitata==0&&g->dextra->d.rei!=MURO)
    {
      g=g->dextra;
      g->d.visitata=1;
      agri_addo_Iter(&p,g);
      l=p;
      return DESTRA;
    }

  if(g->deorsum->d.visitata==0&&g->deorsum->d.rei!=MURO)
    {
      g=g->deorsum;
      g->d.visitata=1;
      agri_addo_Iter(&p,g);
      l=p;
      return GIU;
    }

  l=l->prev;
  if(l==NULL) exit(-1);

  agri_addo_Iter(&p,l->locus);

  direzione nd;
  
  if(g->dextra==l->locus) nd=DESTRA;
  else if(g->sinistra==l->locus) nd=SINISTRA;
  else if(g->sursum==l->locus) nd=SU;
  else if(g->deorsum==l->locus) nd=GIU;
  
  return nd;
}

rei_genus rivela_rei_genus(oggetto code)
{
  if(code != 'J' && code != 'U' && code != 'V')
    {
      return MURO;
    }
  
  return ALTRO;
}

agri_Tabella moveo_Cellam(agri_Tabella * ptab, versus dir)
{
  if (dir == SX)
    *ptab = (*ptab)->sinistra;
  else if (dir == DX)
    *ptab = (*ptab)->dextra;
  else if (dir == DEORSUM)
    *ptab = (*ptab)->deorsum;
  else if (dir == SURSUM)
    *ptab = (*ptab)->sursum;
  return *ptab; 
}
