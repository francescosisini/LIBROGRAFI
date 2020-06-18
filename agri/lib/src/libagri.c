#include "libagri.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>



/*** GRAFO COME ARRAY DI VERTICI ***/




agri_Vertex agri_Verticem_creo(int index, int linea, int columna)
{
  agri_Vertex v;
  v.index =  index;
  v.linea = linea;
  v.columna = columna;
  for(int i = 0;i<PORTE; i++)
    v.ianua[i] = -1;
  return v;
}

void agri_Colligationem_insero(agri_Colligationes_Colligatae * pg, agri_Colligatio colligatio)
{

  agri_Colligationes_Colligatae cg = *pg;
  
  if(colligatio.ab.index == colligatio.ad.index)
    return;
  
   while(cg)
    {
      /* 
	 ITA: l'arco è già nel grafo
	 ENG: the edge is already in the graph
      */
      if(cg->colligatio.ab.index == colligatio.ab.index
	 && cg->colligatio.ad.index == colligatio.ad.index)
      	return;
      cg = cg->next;
    }
  
  agri_Membrum * aux = malloc(sizeof(agri_Membrum));
  if(aux == 0) exit(1);
  aux -> colligatio = colligatio;
  aux -> next = *pg;
  *pg = aux;
}

int agri_Verticem_quaero(agri_Colligationes_Colligatae g, int linea, int columna)
{
  while(g)
    {
      if(g->colligatio.ab.linea == linea && g->colligatio.ab.columna == columna)
	return g->colligatio.ab.index;
      if(g->colligatio.ad.linea == linea && g->colligatio.ad.columna == columna)
	return g->colligatio.ad.index;
      g = g->next;
    }
  return -1;
}

void agri_libero(agri_Colligationes_Colligatae g)
{
  agri_Colligationes_Colligatae g_t;
  while(g)
    {
      g_t = g;
      g = g->next;
      free(g);
      
    }
}

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
		    double (*euristica)(int ab, int ad),
		    int nmembri
		    )
{
  if(start==goal)
    {
      return 0;
    }
  double fscore[nmembri];
  double gscore[nmembri];
  int precedente[nmembri];

  //Nodi in valutazione per il path da start a goal
  Ordo candidati = 0;
  
  for(int i=0;i<nmembri;i++)
    {
      fscore[i] = INFINITO;
      gscore[i] = INFINITO;
    }
  gscore[start] = 0;
  fscore[start]=euristica(start,goal);

  Ordo_insero_nodus(&candidati,start,(1./fscore[start]));

  while(candidati != 0)
    {
      fflush(stdout);
      int corrente = Ordo_pop(&candidati);
     
      /* Arrivato al nodus goal torna il cammino */
      if(corrente == goal)
        {
	  
	  fflush(stdout);
          int i = 0;
          int aux[nmembri];
          
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

      for(int i =0; i<PORTE; i++)
        {
          int iv = vicino[i];

          /* ogni nodus è predisposto per 4 vicini, ma molti nodi ne hanno
             solo 3*/
          if(iv == -1)continue;

          double d =  spatium(corrente, iv);
          double tent_gscore = gscore[corrente]+d;

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
    }
  
  return 0;
  
}

int index_nodus_cella(int riga, int col, agri_Vertex * agri_Vertices_Colligati,int nmembri)
{
  for(int i=0; i<nmembri;i++)
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

/*
  ITA: da un grafo di archi ad un grafo di vertici
 */
int  agri_muto(agri_Colligationes_Colligatae g,agri_Verticum_Dispositio* d)
{
  //1 detremino il numero di nodi nella lista
  //2 alloco spazio nello heap
  //3
  
  //1.Trasformo prima la losta di archi in un array di archi
  agri_Colligationes_Colligatae array;
  int n = agri_dispono(g , &array);
  
  //Array di vertici
  int sz = 0;
  agri_Verticum_Dispositio v = malloc(2*n*sizeof(agri_Vertex));
  
  for(int i=0; i<n; i++)
    {
      
      int ix_ab = (array+i)->colligatio.ab.index;
      int ix_ad = (array+i)->colligatio.ad.index;
      int ix = Verticem_quaero(v,ix_ab,sz);
      
      if(ix<0)
	{
	  memcpy(v+sz,&((array+i)->colligatio.ab),sizeof(agri_Vertex));
	  ix = sz;
	  sz++;
	}
      int iy = Verticem_quaero(v,ix_ad,sz);
      
      if(iy<0)
	{
	  memcpy(v+sz,&((array+i)->colligatio.ad),sizeof(agri_Vertex));
	  iy = sz;
	  sz++;
	}

      /* collego i vertici */
      if ((array+i)->colligatio.discessus != -1)
	{
	  //Assegna la porta in base alla direzione
	  (v+ix)->ianua[(array+i)->colligatio.discessus]=ix_ad;
	  (v+iy)->ianua[agri_Versum_inverto((array+i)->colligatio.meta)]=ix_ab;
	  
	}
      else
	{
	  //Cerco la prima porta libera
	  int k = 0;
	  while((v+ix)->ianua[k]!=-1)k++;
	  (v+ix)->ianua[k] = ix_ad;

	  k = 0;
	  while((v+iy)->ianua[k]!=-1)k++;
	  (v+iy)->ianua[k] = ix_ab;
	  
	}
      
      
    }
  qsort(v, sz, sizeof(agri_Vertex),&compar);
  *d = v;
  return sz;
}

int compar(const void * a, const void * b)
{
  return (((agri_Vertex*)a)->index-((agri_Vertex*)b)->index);
}

int Verticem_quaero(agri_Verticum_Dispositio v, int index, int size)
{
  for(int i=0; i<size;i++)
    {
      if((v+i)->index==index)
	return i;
    }
  
  return -1;
  
}

/*
  ITA: crea un'array di vertici partendo da una lista collegata di vertici

 */
int agri_dispono(agri_Colligationes_Colligatae list ,agri_Colligationes_Colligatae * array)
{
  agri_Colligationes_Colligatae g = list;
  
  int n = 0;
  while(g)
    { 
      n++;
      g = g->next;
    }
  if (n==0) return 0;
  
  (*array) = malloc(n*sizeof(agri_Membrum));
  g = list;
  
  for(int i=0; i<n;i++)
    { 
      memcpy(*array+i,g,sizeof(agri_Membrum));
      
      if(i<n+1)
	(*array+i)->next = (*array+i+1);
      
      g = g->next;
    }
  return n;
}

versus agri_Versum_inverto(versus v)
{
  if (v == SX) return DX;
  if (v == DX) return SX;
  if (v == DEORSUM) return SURSUM;
  if (v == SURSUM) return DEORSUM;
  if (v == FIXO) return FIXO;
  return FIXO;

}


