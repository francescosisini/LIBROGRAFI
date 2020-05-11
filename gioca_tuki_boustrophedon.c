#include "tuki5_modello.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>




enum chartype {MURO,ALTRO};
typedef enum chartype char_type;

/**
 *Battlefield cells graph representation
 */
typedef struct data
{
  int readed;
  int visitata;
  char_type cell_type;
  int cont;
} Data;

typedef struct cell {
  Data d;
  struct cell* destra;
  struct cell* basso;
  struct cell* sinistra;
  struct cell* alto;
} Cell;
typedef Cell* graph;

/**
 *Cell path list
 */
typedef struct node{
  graph pcell;
  struct node * next;
  struct node * prev;
}Node;
typedef Node* path;  



/*Functions*/

char_type get_cell_type(oggetto code);
direzione symmetry(direzione d);
void new_graph(graph* g);
graph add_to_graph(graph pcell,Data d,direzione dir);
void new_path(path* p);
void add_head(path* l, graph g);
Cell* get_neighbor(path ap,direzione inquired_dir);
oggetto controller_leggi_oggetto(direzione dir);

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
  static graph g=NULL;
  static path p=NULL;
  static path l=NULL;

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
       * Insert it into the path list. Mark it as visitata*/
      /* The list of visitata cells*/

      /*the battlefield*/
      new_graph(&g);      
      graph fn=(graph)malloc(sizeof(Cell));
      g=fn;
      g->d.visitata=1;
      g->d.cell_type=ALTRO;
      g->d.cont=-1;
      /*The cell list (path in the battlefield)*/
      new_path(&p);
      add_head(&p,g);
    }else
    {
      
    }
  
  /*Assigns the neighbors cells */
  unsigned char c[4];
  oggetto cx;
  
  /*This is the cell where Tuki is*/
  g=p->pcell;
  if(!g) exit(-1);

  //Alto
  cx = a_;
  //fprintf(f,"dir SU readed %d ",cx);
  if(g->alto==NULL)
    {
      graph gc=get_neighbor(p,SU);
      if(gc){
	g->alto=gc;
	gc->basso=g;
      }else
	{
          
	  Data d={1,0,get_cell_type(cx)};
	  graph tg=add_to_graph(g,d,SU);
	}
    }else
    {
      g->alto->d.readed=1;
      g->alto->d.cell_type=get_cell_type(cx);
    }
  
  //Basso
  cx = b_;
  //fprintf(f,"dir GIU readed %d ",cx);
  if(g->basso==NULL)
    {
      graph gc=get_neighbor(p,GIU);
      if(gc)
	{
	  g->basso=gc;
	  gc->alto=g;
	}
      else
	{
	  Data d={1,0,get_cell_type(cx)};
	  graph tg=add_to_graph(g,d,GIU);
	}
    }else
    {
      g->basso->d.readed=1;
      g->basso->d.cell_type=get_cell_type(cx);
    }

  //Destra
  cx = d_;
  //fprintf(f,"dir DESTRA readed %d ",cx);
  if(g->destra==NULL)
    {
      /*check if the cell already exists*/
      graph gc=get_neighbor(p,DESTRA);
      if(gc){
	g->destra=gc;
	gc->sinistra=g;

      }else
	{
	  Data d={1,0,get_cell_type(cx)};
	  graph tg=add_to_graph(g,d,DESTRA);

	}
    }else
    {
      g->destra->d.readed=1;
      g->destra->d.cell_type=get_cell_type(cx);
    }
  
  //Sinistra
  cx = s_;
  //fprintf(f,"dir SINISTRA readed %d ",cx);
  if(g->sinistra==NULL)
    {
      graph gc=get_neighbor(p,SINISTRA);
      if(gc)
	{
	  g->sinistra=gc;
	  gc->destra=g;
	}else
	{
	  Data d={1,0,get_cell_type(cx)};
	  graph tg=add_to_graph(g,d,SINISTRA);
	}
    }else
    {
      g->sinistra->d.readed=1;
      g->sinistra->d.cell_type=get_cell_type(cx);
    }
    
  /*
    2)Go to the rst unvisitata cell in the neighbor list of
    the current cell (i.e., go to the rst clockwise
    unvisitata cell). Insert this cell into the beginniing of
    the path list and mark it as visitata.
   */
 
 //chekcs L
  //if(g->sinistra->d.cell_type==MURO)g->sinistra->d.visitata=1;
  if(g->sinistra->d.visitata==0&&g->sinistra->d.cell_type!=MURO)
    {
      g=g->sinistra;
      g->d.visitata=1;
      add_head(&p,g);
      l=p;
      return SINISTRA;
    }

  //chekcs U
  //if(g->alto->d.cell_type==MURO)g->alto->d.visitata=1;
  if(g->alto->d.visitata==0&&g->alto->d.cell_type!=MURO)
    {
      g=g->alto;
      g->d.visitata=1;
      add_head(&p,g);
      l=p;
      return SU;
    }
      


 //chekcs R
  //if(g->destra->d.cell_type==MURO)g->destra->d.visitata=1;
  if(g->destra->d.visitata==0&&g->destra->d.cell_type!=MURO)
    {
      g=g->destra;
      g->d.visitata=1;
      add_head(&p,g);
      l=p;
      return DESTRA;
    }
  //chekcs D
  //if(g->basso->d.cell_type==MURO)g->basso->d.visitata=1;
  if(g->basso->d.visitata==0&&g->basso->d.cell_type!=MURO)
    {
      g=g->basso;
      g->d.visitata=1;
      add_head(&p,g);
      l=p;
      return GIU;
    }
 
  

  /*
    3) At this point, back track until a cell with unvis-
    ited neighbors is encountered. This back tracking is
    achieved by walking forward through the path list,
    inserting each element that is visitata to the front
    of the path list, until an element with an unvisied
    neighbor is encountered. Insert this element to the
    front of the path list and repeat the above procedure
    (i.e., goto step 2).
   */
 
  /*back to previous cell*/
  l=l->prev;
  if(l==NULL) exit(-1);
  /*Add it to the path list*/
  add_head(&p,l->pcell);
  
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

Cell* get_neighbor(path ap,direzione dir){
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



char_type get_cell_type(oggetto code){
  if(code != 'J' && code != 'U' && code != 'V'){
    return MURO;
  }
  
  return ALTRO;
}
direzione symmetry(direzione d){
  direzione sd=FERMO;
  switch(d){
  case SINISTRA:
    sd=DESTRA;
    break;
  case DESTRA:
    sd=SINISTRA;
    break;
  case SU:
    sd=GIU;
    break;
   case GIU:
    sd=SU;
    break;
  }
  return sd;
  
}

void new_graph(graph* g)
{
  *g = NULL;
}


/**
 *Add a cell to the graph after checking that a cell
 *was already present at the same poistion.
 *For each cell of the actual Tuki path is saltoposed
 *to exist another 4 cells at the ajacent direzione
 *This functions.
 *The existence of a possible unlinked cell in the 'd' 
 *direzione is tested scann2ing the path_list untill a
 *cell 
 */
graph add_to_graph(graph pcell,Data d,direzione dir){
  nn++;
  Cell* n=(Cell*)malloc(sizeof(Cell));
  n->d=d;
  n->d.cont=nn;
 
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

void new_path(path* p){
  *p=0;
}
void add_head(path* l, graph g) {
  Node* aux = (Node*)malloc(sizeof(Node));
  
  aux->prev = *l;
  aux->next = NULL;  
  aux->pcell = g;
  if(*l)
    (*l)->next=aux;
  *l = aux;
}





