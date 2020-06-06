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

/*
  ITA:  I grafi sono implementati come
  liste di archi tra vertici
  ENG: Graphs are edges lists 
 */

/* 
   ITA: Verice del grafo 
   ENG: Graph vertex
*/
typedef struct {
  /* 
     ITA: Indice univoco nel grafo 
     ENG: Unique index into the graph
  */
  int indice;
  /* 
    ITA: attributi
    ENG: attributes
  */
  int riga, colonna;//row and column
} agri_Vertice;

/* 
   ITA: Arco orientato e pesato
   ENG: diricted and weighted edge ("arco" means edge) 
*/
typedef struct arco {
  /* 
     ITA: vertici collegati dall'arco
     ENG: vertices connected by the edge
  */
  agri_Vertice da, a;
   /* 
    ITA: attributi
    ENG: attributes
   */
  direzione partenza, arrivo;
  int lunghezza;
} agri_Arco;

/* 
   ITA: Elemento della lista di archi
   ENG: Edges list item
*/
typedef struct elemento {
  agri_Arco arco;
  struct  elemento *  next;
} agri_Elemento;

typedef agri_Elemento * agri_Grafo;

/*
  ITA: Inserisce l'arco in testa alla lista
  ENG: inserts an edge on top of the list
*/
void agri_Arco_inserisci(agri_Grafo * pg, agri_Arco arco);

/* ITA: Cerca tra gli elementi del grafo se uno degli archi è connesso
   ad un vertice in riga e colonna. Se lo trova torna l'indice del
   vertice, altrimenti -1
   ENG: Looks into the graph for a vertex whose row and column attributes
   are equal to riga and colonna
*/
int agri_Vertice_cerca(agri_Grafo g, int riga, int colonna);


void stampa(agri_Grafo g)
{
  FILE * f = fopen("grafi.csv","w+t");
  while(g)
    {
      fprintf(f," %d,%d,\n",
	      g->arco.da.indice,
	      g->arco.a.indice);
	      
      g = g->next;
    }
      fclose(f);
}



/* 
   ITA: Controlla se l'oggetto nella cella non è un muro
   ENG: chcks if the object into the cell is or not a wall
*/
bool oggetto_accessibile(oggetto s)
{
  if(s == 'J' || s == 'U' || s == 'V')
    return true;
  else
    return false;
}
/*
direzione direzione_opposta(direzione d)
{
  if(d == SINISTRA) return DESTRA;
  if(d == DESTRA) return SINISTRA;
  if(d == SU) return GIU;
  if(d == GIU) return SU;
  return FERMO;

}
*/

direzione gioca_tuki(posizioni posi, oggetto **labx)

{

  /*
    ITA: per generare il grafo impediamo a PAC-MAN di entrare nella
    casa dei fantasmi
    ENG: to generte maze graph we prevent PAC-MAN to get into 
    ghosts' house
   */
  labx[14][12]='A';
  labx[14][13]='A';
  labx[14][11]='A';
  labx[14][14]='A';
  
  static agri_Grafo g = 0;

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
  
  /* 
     ITA: Direzione presa nel turno di gioco precedente 
     ENG: Direction taken into the previous game cycle
  */
  static int direzione_arrivo = FERMO;
  static int direzione_partenza = FERMO;
  
  static int lunghezza_arco = 0;
  static int i_da, j_da;

   /* 
     ITA: Direzione presa nel turno di gioco corrente 
     ENG: Direction taken into the current game cycle
  */
  static direzione ld = SINISTRA;
  
  static bool init = false;
  if(!init)
    {
      srand(time(0));
      init = true;
    }
  
  /* 
     ITA: Posizione di Pac-Man nel labirinto
     ENG: PAC-MAN's row and column
   */
  int i = posi.tuki_y;
  int j = posi.tuki_x;

  lunghezza_arco++;
  
  /* Celle confinanti (neighbors) */
  oggetto vicino[4];
  vicino[0] = labx[i][j-1]; //sinistra - left
  vicino[1] = labx[i][j+1]; //destra - right
  vicino[2] = labx[i-1][j]; //su - up
  vicino[3] = labx[i+1][j]; //giu - down

  /*  
      ITA: Conta il numero di vicini accessibili
      ENG: Counts the number of accessible neighbors
   */
  int nd = 0;
  for(int k=0; k<4; k++)
    nd += (1*oggetto_accessibile(vicino[k]));
  
  fflush(stdout);

  /* ITA: È vero se nel ciclo di gioco corrente viene rilevato un nodo */
  /* ENG: Is true if in the current game cycle a node is detetcted  */
  bool nodo_rilevato = false;

  if(vertice_da == SCONOSCIUTO && nd>2)
    {
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
      int vertice_a = agri_Vertice_cerca(g,i,j);
      if(vertice_a<0)
	{
	  vertice_a = vertici_contati;
	  vertici_contati++;
	}
      agri_Arco arco;
      agri_Vertice v_a, v_da;
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
      agri_Arco_inserisci(&g, arco);
      nodo_rilevato = true;

      lunghezza_arco = 0;
      vertice_da = vertice_a;
      i_da = i;
      j_da = j;
      
      //stampa(g);
      
    }

  /* Variabile ausiliarie con nomi più comodi */
  oggetto s = vicino[0];
  oggetto d = vicino[1];
  oggetto a = vicino[2];
  oggetto b = vicino[3];

   /* ITA: Gestione ostacoli
      ENG: dealing with obstacles
    */
  bool disponibile = false;
  
  /* ITA: Questo bool garantisce che per ogni 
     turno di gioco la scelta della direzione abbia 
     una componente casuale. 
     Questo al fine di evitare loop che sarebbero causati 
     dall'assenza della squadra fantasma 
     ENG: this bool is set to true if during the direction
     decision a random step has been taken. This in order to
     avoid loops that would be caused by runs without ghosts
  */
  bool aleatorio = false;
  
  /* 
     ITA: se la cella successiva nella direzione corrente non è disponibile,
     ne viene scelta un'altra e viene eseguita una nuova iterazione
     ENG: if the next cell in the current direction is not available, it chooses
     another one and new iteration is executed
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
    
    
    direzione_arrivo = ld;
    if(nodo_rilevato)
      direzione_partenza = ld;
    
    if(aleatorio) return ld;
    
        
    /*
      ITA: Se la direzione non è aleatoria la cambiamo qui
      ENG: If a random step has not been taken during the
      direction decision, we do it here
    */
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

    direzione_arrivo = ld;
    if(nodo_rilevato)
      direzione_partenza = ld;
    return ld;
}


void agri_Arco_inserisci(agri_Grafo * pg, agri_Arco arco)
{

  agri_Grafo cg = *pg;
  
  if(arco.da.indice == arco.a.indice)
    return;
  
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
  
  agri_Elemento * aux = malloc(sizeof(agri_Elemento));
  if(aux == 0) exit(1);
  aux -> arco = arco;
  aux -> next = *pg;
  *pg = aux;
}

int agri_Vertice_cerca(agri_Grafo g, int riga, int colonna)
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
