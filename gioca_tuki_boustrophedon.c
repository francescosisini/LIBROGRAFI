#include "tuki5_modello.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

enum tipo {MURO,ALTRO};
typedef enum tipo tipo_oggetto;

/*
  ITA: Attributi della cella
  ENG: Cell attributes
 */
typedef struct dato
{
  int visitata;
  tipo_oggetto t_o;
} Attributi;

/*
  ITA: vicini di ogni cella
  ENG: cell's neighbords
 */
typedef struct cella {
  Attributi d;
  struct cella* destra;
  struct cella* basso;
  struct cella* sinistra;
  struct cella* alto;
} Cella;

/*
  ITA: Grafo composto da celle
  ENG: Graph composed by cells
 */
typedef Cella* Grafo;

/*
  ITA: elementi della lista dei passi
  ENG: elements of the step list
 */
typedef struct nodo{
  Grafo pcell;
  struct nodo * next;
  struct nodo * prev;
}Nodo;

/*
  ITA: lista dei passi
  ENG: step list
 */
typedef Nodo* Cammino;  

/*
  ITA: classifica il contenuto in MURO o ALTRO
  ENG: classify the argument into MURO (i.e. wall) or ALTRO (i.e. non wall)
*/
tipo_oggetto rivela_tipo_oggetto(oggetto contenuto);
/*
  ITA: inizializza un grafo vuoto
  ENG: initialize an empty graph
 */
void crea_Grafo(Grafo* g);
/*
  ITA: Aggiunge al grafo una nuova cella con attributi d, collegandola alla direzione
  dir cella corrente
  ENG: Adds a new cell, with the attributes d, to the graph, linking it to the
  direction dir of the current cell
 */
Grafo aggiungi_al_Grafo(Cella * p_corrente,Attributi d,direzione dir);
/*
  ITA: inizializza una lista di passo puntata da p_camm cammimo vuoto
  ENG: initialize an empty list of steps
 */
void crea_Cammino(Cammino* p_camm);
/*
  ITA: aggiunge una Cella nella lista puntata da p_camm dei passi compiuti
  ENG: adds a cell in the list pointed to by p_camm of the steps performed
 */
void aggiungi_in_testa(Cammino * p_camm, Cella * p_cella);
/*
  ITA:
 */
Cella* rivela_vicini(Cammino ap,direzione inquired_dir);

int nn=0;
int moves=0;

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
  static Grafo g=NULL;
  static Cammino p=NULL;
  static Cammino l=NULL;

  int i = posi.tuki_y;
  int j = posi.tuki_x;
  oggetto s_ = labx[i][j-1];
  oggetto d_ = labx[i][j+1];
  oggetto a_ = labx[i-1][j];
  oggetto b_ = labx[i+1][j];
  
  moves++;
  if(!init)
    {
      init=1;
      /* 1)Start with any cell in the decomposition. 
       * Insert it into the Cammino list. Mark it as visitata*/
      /* The list of visitata cells*/

      /*the battlefield*/
      crea_Grafo(&g);      
      Grafo fn=(Grafo)malloc(sizeof(Cella));
      g=fn;
      g->d.visitata=1;
      g->d.t_o=ALTRO;
      /*The cell list (Cammino in the battlefield)*/
      crea_Cammino(&p);
      aggiungi_in_testa(&p,g);
    }
  
  /*Assigns the neighbors cells */
  unsigned char c[4];
  oggetto cx;
  
  /*This is the cell where Tuki is*/
  g=p->pcell;
  if(!g) exit(-1);

  //Alto
  cx = a_;
  
  if(g->alto==NULL)
    {
      Grafo gc=rivela_vicini(p,SU);
      if(gc)
	{
	  g->alto=gc;
	  gc->basso=g;
	}
      else
	{
	  Attributi d={0,rivela_tipo_oggetto(cx)};
	  Grafo tg=aggiungi_al_Grafo(g,d,SU);
	}
    }
  else
    {
      g->alto->d.t_o=rivela_tipo_oggetto(cx);
    }
  
  //Basso
  cx = b_;
  if(g->basso==NULL)
    {
      Grafo gc=rivela_vicini(p,GIU);
      if(gc)
	{
	  g->basso=gc;
	  gc->alto=g;
	}
      else
	{
	  Attributi d={0,rivela_tipo_oggetto(cx)};
	  Grafo tg=aggiungi_al_Grafo(g,d,GIU);
	}
    }else
    {
      g->basso->d.t_o=rivela_tipo_oggetto(cx);
    }

  //Destra
  cx = d_;
  if(g->destra==NULL)
    {
      /*check if the cell already exists*/
      Grafo gc=rivela_vicini(p,DESTRA);
      if(gc){
	g->destra=gc;
	gc->sinistra=g;

      }else
	{
	  Attributi d={0,rivela_tipo_oggetto(cx)};
	  Grafo tg=aggiungi_al_Grafo(g,d,DESTRA);

	}
    }else
    {
      g->destra->d.t_o=rivela_tipo_oggetto(cx);
    }
  
  //Sinistra
  cx = s_;
  if(g->sinistra==NULL)
    {
      Grafo gc=rivela_vicini(p,SINISTRA);
      if(gc)
	{
	  g->sinistra=gc;
	  gc->destra=g;
	}else
	{
	  Attributi d={0,rivela_tipo_oggetto(cx)};
	  Grafo tg=aggiungi_al_Grafo(g,d,SINISTRA);
	}
    }else
    {
      g->sinistra->d.t_o=rivela_tipo_oggetto(cx);
    }
    
  /*
    2)Go to the rst unvisitata cell in the neighbor list of
    the current cell (i.e., go to the rst clockwise
    unvisitata cell). Insert this cell into the beginniing of
    the Cammino list and mark it as visitata.
   */
 
 //chekcs L
  //if(g->sinistra->d.t_o==MURO)g->sinistra->d.visitata=1;
  if(g->sinistra->d.visitata==0&&g->sinistra->d.t_o!=MURO)
    {
      g=g->sinistra;
      g->d.visitata=1;
      aggiungi_in_testa(&p,g);
      l=p;
      return SINISTRA;
    }

  //chekcs U
  //if(g->alto->d.t_o==MURO)g->alto->d.visitata=1;
  if(g->alto->d.visitata==0&&g->alto->d.t_o!=MURO)
    {
      g=g->alto;
      g->d.visitata=1;
      aggiungi_in_testa(&p,g);
      l=p;
      return SU;
    }
      


 //chekcs R
  //if(g->destra->d.t_o==MURO)g->destra->d.visitata=1;
  if(g->destra->d.visitata==0&&g->destra->d.t_o!=MURO)
    {
      g=g->destra;
      g->d.visitata=1;
      aggiungi_in_testa(&p,g);
      l=p;
      return DESTRA;
    }
  //chekcs D
  //if(g->basso->d.t_o==MURO)g->basso->d.visitata=1;
  if(g->basso->d.visitata==0&&g->basso->d.t_o!=MURO)
    {
      g=g->basso;
      g->d.visitata=1;
      aggiungi_in_testa(&p,g);
      l=p;
      return GIU;
    }
 
  

  /*
    3) At this point, back track until a cell with unvis-
    ited neighbors is encountered. This back tracking is
    achieved by walking forward through the Cammino list,
    inserting each element that is visitata to the front
    of the Cammino list, until an element with an unvisied
    neighbor is encountered. Insert this element to the
    front of the Cammino list and repeat the above procedure
    (i.e., goto step 2).
   */
 
  /*back to previous cell*/
  l=l->prev;
  if(l==NULL) exit(-1);
  /*Add it to the Cammino list*/
  aggiungi_in_testa(&p,l->pcell);
  
  /*get the diretion*/
  direzione nd;//next step direzione

  if(g->destra==l->pcell) nd=DESTRA;
  else
  if(g->sinistra==l->pcell) nd=SINISTRA;
  else
  if(g->alto==l->pcell) nd=SU;
  else
  if(g->basso==l->pcell) nd=GIU;

  /*Set as the online cell*/
  //g=l->pcell;
  /*move to the previous one*/
  
  return nd;
  
}

Cella* rivela_vicini(Cammino ap,direzione dir){
  int R=0,U=0;
  int found=0;
  
  while(ap->prev){
    if(ap->pcell->destra==ap->prev->pcell) R++;
    if(ap->pcell->sinistra==ap->prev->pcell) R--;
    if(ap->pcell->alto==ap->prev->pcell) U++;
    if(ap->pcell->basso==ap->prev->pcell) U--;
    /*check neighbor condition*/
    //DESTRA
    if(dir==DESTRA&&R==1&&U==0)
      {
	return ap->prev->pcell;
      }
    //R-U
    if(dir==DESTRA&&(R==1)&&U==+1)
      {
	return ap->prev->pcell->basso;
      }
    //R-D
    if(dir==DESTRA&&(R==1)&&U==-1)
      {
	return ap->prev->pcell->alto;
      }


    if(dir==DESTRA&&R==2&&U==0)
      {
	//return ap->prev->pcell->sinistra;
      }



    
    //L
    if(dir==SINISTRA&&R==-1&&(U==0))
      {
	return ap->prev->pcell;
      }
    //L-U
    if(dir==SINISTRA&&(R==-1)&&U==+1)
      {
	return ap->prev->pcell->basso;
      }
    //L-D
    if(dir==SINISTRA&&(R==-1)&&U==-1)
      {
	return ap->prev->pcell->alto;
      }


    if(dir==SINISTRA&&R==-2&&U==0)
      {
	//return ap->prev->pcell->destra;
      }
    //SU
    if(dir==SU&&R==0&&U==1)
      {
	return ap->prev->pcell;
      }
    //U-L
    if(dir==SU&&(R==-1)&&U==+1)
      {
	return ap->prev->pcell->destra;
      }
    //U-R
    if(dir==SU&&(R==1)&&U==+1)
      {
	return ap->prev->pcell->sinistra;
      }

    
    if(dir==SU&&R==0&&U==2)
      {
	//return ap->prev->pcell->basso;
      }
    // D
    if(dir==GIU&&R==0&&U==-1)
      {
	return ap->prev->pcell;
      }
    //D-L
    if(dir==GIU&&(R==-1)&&U==-1)
      {
	return ap->prev->pcell->destra;
      }
    //D-R
    if(dir==GIU&&(R==1)&&U==-1)
      {
	return ap->prev->pcell->sinistra;
      }

    if(dir==GIU&&R==0&&U==-2)
      {

	//return ap->prev->pcell->alto;
      }
    ap=ap->prev;
  }
  return NULL;
}



tipo_oggetto rivela_tipo_oggetto(oggetto code){
  if(code != 'J' && code != 'U' && code != 'V'){
    return MURO;
  }
  
  return ALTRO;
}

void crea_Grafo(Grafo* g)
{
  *g = NULL;
}


/**
 *Add a cell to the Grafo after checking that a cell
 *was already present at the same poistion.
 *For each cell of the actual Tuki Cammino is saltoposed
 *to exist another 4 cells at the ajacent direzione
 *This functions.
 *The existence of a possible unlinked cell in the 'd' 
 *direzione is tested scann2ing the Cammino_list untill a
 *cell 
 */
Grafo aggiungi_al_Grafo(Grafo pcell,Attributi d,direzione dir){
  nn++;
  Cella* n=(Cella*)malloc(sizeof(Cella));
  n->d=d;
 
  switch(dir)
    {
    case SU:
      pcell->alto=n;
      n->basso=pcell;
      break;
    case GIU:
      pcell->basso=n;
      n->alto=pcell;
      break;
    case DESTRA:
      pcell->destra=n;
      n->sinistra=pcell;
      break;
    case SINISTRA:
      pcell->sinistra=n;
      n->destra=pcell;
      break;
    }
  return n;
}

void crea_Cammino(Cammino* p){
  *p=0;
}
void aggiungi_in_testa(Cammino* l, Grafo g) {
  Nodo* aux = (Nodo*)malloc(sizeof(Nodo));
  
  aux->prev = *l;
  aux->next = NULL;  
  aux->pcell = g;
  if(*l)
    (*l)->next=aux;
  *l = aux;
}





