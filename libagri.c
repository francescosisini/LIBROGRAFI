#include "libagri.h"
#include <stdlib.h>



void agri_creo_Tabellam(agri_Tabella* g)
{
  *g = NULL;
}


/**
 *Add a cell to the agri_Tabella after checking that a cell
 *was already present at the same poistion.
 *For each cell of the actual Tuki agri_Iter is ssursumposed
 *to exist another 4 cells at the ajacent direzione
 *This functions.
 *The existence of a possible unlinked cell in the 'd' 
 *direzione is tested scann2ing the agri_Iter_list untill a
 *cell 
 */
agri_Tabella agri_addo_Tabellam(agri_Tabella tabella,Attributi d,versus dir)
{
  agri_Cella* n=(agri_Cella*)malloc(sizeof(agri_Cella));
  n->d=d;
 
  switch(dir)
    {
    case DEORSUM:
      tabella->sursum=n;
      n->deorsum=tabella;
      break;
    case SURSUM:
      tabella->deorsum=n;
      n->sursum=tabella;
      break;
    case DX:
      tabella->dextra=n;
      n->sinistra=tabella;
      break;
    case SX:
      tabella->sinistra=n;
      n->dextra=tabella;
      break;
    }
  return n;
}

void agri_colligo_Cellas
(agri_Cella * da, agri_Cella * a, versus da_a)
{
  switch(da_a)
    {
    case DEORSUM:
      da->sursum=a;
      a->deorsum=da;
      break;
    case SURSUM:
      da->deorsum=a;
      a->sursum=da;
      break;
    case DX:
      da->dextra=a;
      a->sinistra=da;
      break;
    case SX:
      da->sinistra=a;
      a->dextra=da;
      break;
    }

}

void agri_creo_Iter(agri_Iter* p){
  *p=0;
}
void agri_addo_Iter(agri_Iter* l, agri_Tabella g)
{
  agri_Passo* aux = (agri_Passo*)malloc(sizeof(agri_Passo));  
  aux->prev = *l;
  aux->next = NULL;  
  aux->locus = g;
  if(*l)
    (*l)->next=aux;
  *l = aux;
}

/*
  Cerca una eventuale cella nella direzione dir che sia già stata esplorata
  lungo il cammino ma che non sia ancora stata connessa alla cella corrente
  del cammino
 */
agri_Cella* agri_rivela_Cella(agri_Iter ap,versus dir){
  int R=0,U=0;
  int found=0;
  
  while(ap->prev){
    if(ap->locus->dextra ==ap->prev->locus) R++;
    if(ap->locus->sinistra == ap->prev->locus) R--;
    if(ap->locus->sursum == ap->prev->locus) U++;
    if(ap->locus->deorsum == ap->prev->locus) U--;
    /*check neighbor condition*/
    //DX
    if(dir==DX && R==1 && U==0)
      {
	return ap->prev->locus;
      }
    //R-U
    if(dir==DX && (R==1) && U==+1)
      {
	return ap->prev->locus->deorsum;
      }
    //R-D
    if(dir==DX&&(R==1)&&U==-1)
      {
	return ap->prev->locus->sursum;
      }
    
    //Sinistra
    //L
    if(dir==SX&&R==-1&&(U==0))
      {
	return ap->prev->locus;
      }
    //L-U
    if(dir==SX&&(R==-1)&&U==+1)
      {
	return ap->prev->locus->deorsum;
      }
    //L-D
    if(dir==SX&&(R==-1)&&U==-1)
      {
	return ap->prev->locus->sursum;
      }

    //Sursum
    //SU
    if(dir==DEORSUM&&R==0&&U==1)
      {
	return ap->prev->locus;
      }
    //U-L
    if(dir==DEORSUM&&(R==-1)&&U==+1)
      {
	return ap->prev->locus->dextra;
      }
    //U-R
    if(dir==DEORSUM&&(R==1)&&U==+1)
      {
	return ap->prev->locus->sinistra;
      }

    //Deorsum
    // D
    if(dir==SURSUM&&R==0&&U==-1)
      {
	return ap->prev->locus;
      }
    //D-L
    if(dir==SURSUM&&(R==-1)&&U==-1)
      {
	return ap->prev->locus->dextra;
      }
    //D-R
    if(dir==SURSUM&&(R==1)&&U==-1)
      {
	return ap->prev->locus->sinistra;
      }

    ap=ap->prev;
  }
  return NULL;
}
