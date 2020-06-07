#include "libagri.h"
#include <stdlib.h>
#include <stdio.h>



/*** GRAFO COME ARRAY DI VERTICI ***/
void Ordo_amoveo_nodus(Ordo * l, int index)
{
  
  while (*l) {
    if ((*l)->index == index)
      break;
    l = &(*l)->post;
  }
  if (*l) {
    Nodus* aux = *l;
    *l = (*l)->post;
    free(aux);
  } 
}

void Ordo_insero_nodus(Ordo * l,int index, double prio)
{
    
  Nodus * aux = (Nodus *)malloc(sizeof(Nodus));
  aux->index =  index;
  aux->prio = prio;

  /* il nodus è già in Ordo */
  Ordo_amoveo_nodus(l,  index);

  while (*l) {
    if ((*l)->prio < prio)
      break;
    l = &(*l)->post;
  }
  
  aux->post = *l;
  *l = aux;
}

int Ordo_pop(Ordo * pOrdo)
{
  
  /* puntatore al prio nodus */
  Ordo candidato = *pOrdo;
  
  int n = candidato->index;

  /* aggiorna la Ordo */
  (*pOrdo) = candidato->post;
  
  free(candidato);

  return n;
}

agri_Via agri_astar(int start, int goal,
		    agri_Vertex * agri_Vertices_Colligati,
		    double (*spatium)(int ab, int ad),
		    double (*euristica)(int ab, int ad)
		    )
{

  if(start==goal) return 0;
  
  double fscore[NNODI];
  double gscore[NNODI];
  int precedente[NNODI];

  //Nodi in valutazione per il path da start a goal
  Ordo candidati = 0;

  
  
  for(int i=0;i<NNODI;i++)
    {
      fscore[i] = INFINITO;
      gscore[i] = INFINITO;
    }
  gscore[start] = 0;
  fscore[start]=euristica(start,goal);

  Ordo_insero_nodus(&candidati,start,(1./fscore[start]));

  while(candidati != 0)
    {
      printf("Pop ");
      fflush(stdout);
      int corrente = Ordo_pop(&candidati);
      printf("%d\n",corrente);
      /* Arrivato al nodus goal torna il cammino */
      if(corrente == goal)
        {
	  printf("-start == goal-\n");
	  fflush(stdout);
          int i = 0;
          int aux[NNODI];
          
          do{
            aux[i]=corrente;
            corrente=precedente[corrente];
            i++;
          }while(corrente != start);
                    
          agri_Via percorso = malloc((i+1)*sizeof(int));
	  
          int j =0 ;
          for(int k = i-1;k >=0 ;k--,j++)
            {
              percorso[j] = aux[k];
	      printf("Costruzione percorso + =%d\n", percorso[j]); 
            }
	  // Segnale di fine percorso
	  percorso[j]=-1;
          return percorso;
        }
     
      /* Nel labirinto di Pac-Man ci sono al massimo 4 vicini */
      int vicino[PORTE];
      for(int i=0; i<PORTE; i++)
	{
	  vicino[i] = agri_Vertices_Colligati[corrente].ianua[i];
	}
      printf("Il nodus %d\n",corrente);
      for(int i =0; i<PORTE; i++)
        {
          int iv = vicino[i];
	  printf("ha vicino %d\n",iv);
          /* ogni nodus è predisposto per 4 vicini, ma molti nodi ne hanno
             solo 3*/
          if(iv == -1)continue;

          double d =  spatium(corrente, iv);
          double tent_gscore = gscore[corrente]+d;
	  printf("a distanza %lf\n",d);
          if(tent_gscore <= gscore[iv])
            {
	      
              /* Trovato cammino migliore a questo nodus passando per corrente*/
              precedente[iv] = corrente;
              gscore[iv] = tent_gscore;
              fscore[iv] = gscore[iv] +  euristica(iv, goal);
	     
              Ordo_insero_nodus(&candidati,iv, ( 1./fscore[iv]));
	     
	      fflush(stdout);
            }
	}
       //Stampiamo la Ordo corrente
      Ordo cd = candidati;
      printf("----------------------\n");
      while(cd)
	{
	  printf("Ordo: nodus %d, %lf\n",cd->index,cd->prio);
	  cd=cd->post;
	}
    }
  return 0;
  
}

int index_nodus_cella(int riga, int col, agri_Vertex * agri_Vertices_Colligati)
{
  for(int i=0; i<NNODI;i++)
    {
      if(agri_Vertices_Colligati[i].columna == col && agri_Vertices_Colligati[i].linea == riga)
        return agri_Vertices_Colligati[i].index;
    }
  return -1;
}
/*** GRAFO COME LISTA DI CELLE  ***/

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
