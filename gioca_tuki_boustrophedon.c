#include "tuki5_modello.h"
#include "libagri.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define FUGA 1

/*
  ITA: classifica il contenuto in MURO o ALTRO
  ENG: classify the argument into MURO (i.e. wall) or ALTRO (i.e. non wall)
*/
rei_genus rivela_rei_genus(oggetto contenuto);


/**
 * Tuki algorithm based on The Boustrophedon Cellular Decomposition
 * Choset e Pignon
 */
direzione gioca_tuki(posizioni posi, oggetto **labx){


  //Modifica il labirinto per non imboccare il tunnel 
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
      /* 1)Start with any cell in the decomposition. 
       * Insert it into the agri_Iter list. Mark it as visitata*/
      /* The list of visitata cells*/

      /*the battlefield*/
      agri_creo_Tabellam(&g);      
      agri_Tabella fn=(agri_Tabella)malloc(sizeof(agri_Cella));
      g=fn;
      g->d.visitata=1;
      g->d.rei=ALTRO;
      /*The cell list (agri_Iter in the battlefield)*/
      agri_creo_Iter(&p);
      agri_addo_Iter(&p,g);
    }


  /*
    ITA: cerca un fantasma nelle celle vicine

   */
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

  /*
    ITA: flag di presenza del fantasma
   */
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

  
  
  /*Assigns the neighbors cells */
  unsigned char c[4];
  oggetto cx;
  
  /*This is the cell where Tuki is*/
  g=p->locus;
  if(!g) exit(-1);

  //Sursum
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
    }else
    {
      g->deorsum->d.rei=rivela_rei_genus(cx);
    }

  //Dextra
  cx = d_;
  if(g->dextra==NULL)
    {
      /*check if the cell already exists*/
      agri_Tabella gc=agri_rivela_Cella(p,DESTRA);
      if(gc){
	
	agri_colligo_Cellas(g,gc,DESTRA);

      }else
	{
	  Attributi d={0,rivela_rei_genus(cx)};
	  agri_Tabella tg=agri_addo_Tabellam(g,d,DESTRA);

	}
    }else
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
	}else
	{
	  Attributi d={0,rivela_rei_genus(cx)};
	  agri_Tabella tg=agri_addo_Tabellam(g,d,SINISTRA);
	}
    }else
    {
      g->sinistra->d.rei=rivela_rei_genus(cx);
    }
    
  /*
    2)Go to the rst unvisitata cell in the neighbor list of
    the current cell (i.e., go to the rst clockwise
    unvisitata cell). Insert this cell into the beginniing of
    the agri_Iter list and mark it as visitata.
   */


/* Se un fantasma è nelle vicinanze prendo la prima cella buona */
  if((s_g || d_g || a_g || b_g) && FUGA)
    {
      if(g->sinistra->d.rei!=MURO && !s_g)
        {
          g=g->sinistra;
          g->d.visitata=1;
          agri_addo_Iter(&p,g);
          l=p;
          return SINISTRA;
        }
      
      /* chekcs U */
      
      if(g->sursum->d.rei!=MURO && !a_g)
        {
          g=g->sursum;
          g->d.visitata=1;
          agri_addo_Iter(&p,g);
          l=p;
          return SU;
        }
      
      
      
      /* chekcs R */
      
      if(g->dextra->d.rei!=MURO && !d_g)
        {
          g=g->dextra;
          g->d.visitata=1;
          agri_addo_Iter(&p,g);
          l=p;
          return DESTRA;
        }
      /* chekcs D */
      
      if(g->deorsum->d.rei!=MURO && !b_g)
        {
          g=g->deorsum;
          g->d.visitata=1;
          agri_addo_Iter(&p,g);
          l=p;
          return GIU;
        }
      
    }
  
 //chekcs L
  //if(g->sinistra->d.rei==MURO)g->sinistra->d.visitata=1;
  if(g->sinistra->d.visitata==0&&g->sinistra->d.rei!=MURO)
    {
      g=g->sinistra;
      g->d.visitata=1;
      agri_addo_Iter(&p,g);
      l=p;
      return SINISTRA;
    }

  //chekcs U
  //if(g->sursum->d.rei==MURO)g->sursum->d.visitata=1;
  if(g->sursum->d.visitata==0&&g->sursum->d.rei!=MURO)
    {
      g=g->sursum;
      g->d.visitata=1;
      agri_addo_Iter(&p,g);
      l=p;
      return SU;
    }
      


 //chekcs R
  //if(g->destra->d.rei==MURO)g->destra->d.visitata=1;
  if(g->dextra->d.visitata==0&&g->dextra->d.rei!=MURO)
    {
      g=g->dextra;
      g->d.visitata=1;
      agri_addo_Iter(&p,g);
      l=p;
      return DESTRA;
    }
  //chekcs D
  //if(g->deorsum->d.rei==MURO)g->deorsum->d.visitata=1;
  if(g->deorsum->d.visitata==0&&g->deorsum->d.rei!=MURO)
    {
      g=g->deorsum;
      g->d.visitata=1;
      agri_addo_Iter(&p,g);
      l=p;
      return GIU;
    }
 
  

  /*
    3) At this point, back track until a cell with unvis-
    ited neighbors is encountered. This back tracking is
    achieved by walking forward through the agri_Iter list,
    inserting each element that is visitata to the front
    of the agri_Iter list, until an element with an unvisied
    neighbor is encountered. Insert this element to the
    front of the agri_Iter list and repeat the above procedure
    (i.e., goto step 2).
   */
 
  /*back to previous cell*/
  l=l->prev;
  if(l==NULL) exit(-1);
  /*Add it to the agri_Iter list*/
  agri_addo_Iter(&p,l->locus);
  
  /*get the diretion*/
  direzione nd;//next step direzione

  if(g->dextra==l->locus) nd=DESTRA;
  else
  if(g->sinistra==l->locus) nd=SINISTRA;
  else
  if(g->sursum==l->locus) nd=SU;
  else
  if(g->deorsum==l->locus) nd=GIU;

  /*Set as the online cell*/
  //g=l->locus;
  /*move to the previous one*/
  
  return nd;
  
}


rei_genus rivela_rei_genus(oggetto code){
  if(code != 'J' && code != 'U' && code != 'V'){
    return MURO;
  }
  
  return ALTRO;
}



