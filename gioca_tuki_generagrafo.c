/*___________________________________________________________
 * 
 * FILE: gioca_tuki_generagrafo.c
 */
#include "tuki5_modello.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define NNODI 34
#define SCONOSCIUTO -2

/********* SEZIONE GRAFO ***************/

/*
 * Data Model: il grafo è implementato come
 * una lista di archi tra vertici
 */

/* Verice del grafo */
typedef struct {
  /* Chiave unica */
  int indice;
  /* attributi */
  int riga, colonna;
} grafo_Vertice;

/* Arco orientato e pesato */
typedef struct arco {
  /* vertici collegati - chiave unica composta */
  grafo_Vertice da, a;
  /* attributi */
  direzione partenza, arrivo;
  int lunghezza;
} grafo_Arco;

/* Elemento della lista di archi */
typedef struct elemento {
  grafo_Arco arco;
  /* Navigazione lista*/
  struct  elemento *  next;
} grafo_Elemento;

/* Puntatore alla lista di archi */
typedef grafo_Elemento * grafo_Grafo;

/* Inserisce l'arco in testa alla lista */
void grafo_inserisci(grafo_Grafo * pg, grafo_Arco arco)
{

  grafo_Grafo cg = *pg;
  while(cg)
    {
      /* 
	 ITA: l'arco è già nel grafo
	 ENG: the edge is already in the graph
      */
      if(cg->arco.da.indice == arco.da.indice && cg->arco.a.indice == arco.a.indice)
	return;
      cg = cg->next;
    }
  
  grafo_Elemento * aux = malloc(sizeof(grafo_Elemento));
  if(aux == 0) exit(1);
  aux -> arco = arco;
  aux -> next = *pg;
  *pg = aux;
}

/* Cerca tra gli elementi del grafo se uno degli archi è connesso
   ad un vertice in riga e colonna. Se lo trova torna l'indice del
   vertice, altrimenti -1
*/
int grafo_Vertice_cerca(grafo_Grafo g, int riga, int colonna)
{
  while(g)
    {
      if(g->arco.da.riga == riga && g->arco.da.colonna == colonna)
	return g->arco.da.indice;
      if(g->arco.a.riga == riga && g->arco.a.colonna == colonna)
	return g->arco.a.indice;
      g = g->next;
    }
  return -1;
}

void grafo_stampa(grafo_Grafo g)
{
  FILE * f = fopen("grafi.txt","w+t");
  while(g)
    {
      fprintf(f," Arco (%d,%d)\n",
	      g->arco.da.indice,
	      g->arco.a.indice);
	      
      g = g->next;
    }
      fclose(f);
}



/* Controlla se l'oggetto nella cella non è un muro */
bool oggetto_accessibile(oggetto s)
{
  if(s == 'J' || s == 'U' || s == 'V')
    return true;
  else
    return false;
}

direzione direzione_opposta(direzione d)
{
  if(d == SINISTRA) return DESTRA;
  if(d == DESTRA) return SINISTRA;
  if(d == SU) return GIU;
  if(d == GIU) return SU;
  return FERMO;

}


direzione gioca_tuki(posizioni posi, oggetto **labx)

{

  /* Grafo del labirinto */
  static grafo_Grafo g = 0;

  /* 
     ITA: Se Tuki è su un vertice, deve aggiungere l'arco
     che ha appena attraversato al grafo. Le seguenti variabili
     sono i due vertici dell'arco
     
     ENG: If Tuki is on a vertex he has to add the edge he has
     just traversed to the graph. The following variables 
     are the two vertices of the edge
  */
  
  static int vertice_da = SCONOSCIUTO;
  static int vertici_contati = SCONOSCIUTO;

  /*
    ITA: I nodi possono essere collegati 
    da sinistra a destra o dall'alto in basso, 
    quando l'arco non fa curve, ma non tutti 
    gli archi sono linee rette. Anche archi che collegano 
    i nodi da sinistra verso l'alto, verso destra 
    e così via, sono presenti nel labirinto Pac-Man.
    
    ENG: Nodes can be connected as left to right or up to down,
    when the edge makes no curves, but not all the edges are 
    straight lines. Edges  connecting nodes left to up, up to right 
    and so on, are also  present in the Pac-Man maze.
   */
  
  /* Direzione presa nel turno di gioco precedente */
  static int direzione_arrivo = FERMO;
  /* Direzione presa nel turno di gioco precedente */
  static int direzione_partenza = FERMO;
  static int lunghezza_arco = 0;
  static int i_da, j_da;

  /* Direzione presa in questo turno di gioco */
  static direzione ld = SINISTRA;
  
  static bool init = false;
  if(!init)
    {
      srand(time(0));
      init = true;
    }
  
  /* Posizione di Tuki o Pac-Man nel labirinto*/
  int i = posi.tuki_y;
  int j = posi.tuki_x;

  lunghezza_arco++;
  
  /* Celle confinanti (neighbors) */
  oggetto vicino[4];
  vicino[0] = labx[i][j-1]; //sinistra
  vicino[1] = labx[i][j+1]; //destra
  vicino[2] = labx[i-1][j]; //su
  vicino[3] = labx[i+1][j]; //giu

  /*  
      ITA: Conta il numero di vicini accessibili
      ENG: Counts the number of accessible neighbors
   */
  int nd = 0;
  for(int k=0; k<4; k++)
    nd += (1*oggetto_accessibile(vicino[k]));
  
  fflush(stdout);

  /* IT: È vero se nel ciclo di gioco corrente viene rilevato un nodo */
  /* EN: Is true if in the current game cycle a node is detetcted  */
  bool nodo_rilevato = false;

  if(vertice_da == SCONOSCIUTO && nd>2)
    {
      printf("caz");
      fflush(stdout);
      vertice_da = 0;
      i_da = i;
      j_da = j;
      vertici_contati = 1;
      lunghezza_arco = 0;
    }
  else if(nd>2)
    {
      
      /* 
	 ITA: Se siamo qui, Tuki è su un vertice
	 ENG: If we are here Tuki position is a vertex 
      */
      int vertice_a = grafo_Vertice_cerca(g,i,j);
      if(vertice_a<0)
	{
	  vertice_a = vertici_contati;
	  vertici_contati++;
	}
      grafo_Arco arco;
      grafo_Vertice v_a, v_da;
      v_a.indice = vertice_a;
      v_a.riga = i;
      v_a.colonna = j;

      v_da.indice = vertice_da;
      v_da.riga = i_da;
      v_da.colonna = j_da;
      
      arco.a = v_a;
      arco.da = v_da;
      arco.lunghezza = lunghezza_arco;
      arco.arrivo = direzione_arrivo;
      arco.partenza = direzione_partenza;
      grafo_inserisci(&g, arco);
      nodo_rilevato = true;

      vertice_da = vertice_a;
      i_da = i;
      j_da = j;
      
      grafo_stampa(g);
    }

  /* Variabile ausiliarie con nomi più comodi */
  oggetto s = vicino[0];
  oggetto d = vicino[1];
  oggetto a = vicino[2];
  oggetto b = vicino[3];

   /* Gestione ostacoli */
  bool disponibile = false;
  
  /* Questo bool garantisce che per ogni 
     ciclo di gioco la scelta della direzione abbia 
     una componente casuale. 
     Questo al fine di evitare loop che sarebbero causati 
     dall'assenza della squadra fantasma */
  bool aleatorio = false;
  
  /* 
     se la cella successiva nella direzione corrente non è disponibile,
     ne viene scelta un'altra e viene eseguita una nuova iterazione
  */
  while(!disponibile)
    {
      if(!oggetto_accessibile(s) && ld == SINISTRA)
        {
          ld = rand()%2;
          if(ld==0)
            ld = SU;
          else
            ld = GIU;
          aleatorio = true;
        }
      else
        
        if(!oggetto_accessibile(d) && ld == DESTRA)
          {
	    
            ld = rand()%2;
            if(ld==0) ld = SU;
            else
              ld = GIU;
            aleatorio = true;
          }
        else
	  if(!oggetto_accessibile(a) && ld == SU)
            {
              ld = rand()%2;
              if(ld==0) ld = SINISTRA;
              else
                ld = DESTRA;
              aleatorio = true;
            }
          else
            if(!oggetto_accessibile(b) && ld == GIU)
	      {
                ld = rand()%2;
                if(ld==0) ld = SINISTRA;
                else
                  ld = DESTRA;
                aleatorio = true;
	      }
            else
              disponibile = true;
    }
    
    // Memorizzazione per il pac_grafo
    direzione_arrivo = ld;
    if(nodo_rilevato)
      direzione_partenza = ld;
    
    if(aleatorio) return ld;
    
        
    /* Se la direzione non è aleatoria la cambiamo qui */
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

    // Memorizzazione per il pac_grafo
    direzione_arrivo = ld;
    if(nodo_rilevato)
      direzione_partenza = ld;
    return ld;
  
}
