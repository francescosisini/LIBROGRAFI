/*___________________________________________________________
 * 
 * FILE: gioca_tuki_percorso.c
 */
#include "tuki5_modello.h"
#include "libagri.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>

#define SCONOSCIUTO -2
#define GUINZAGLIO 10

#define NODI_LAB_POT 600

posizioni g_posi;
int n_vertici;

/*
  ITA: array di vertici del grafo completo del Pac-Man
  ENG: vertex array of the complete Pac-Man graph
*/
static agri_Vertex grafo[NODI_LAB_POT];

agri_Vertex agri_Vertices_Colligati[NODI_LAB_POT];

/* Evita la casa dei fantasmi */
int evita_casa_fantasmi(int vertice)
{
  int r = grafo[vertice].linea;
  int c = grafo[vertice].columna;
  if(r>=15 && r<=17 && c>=11 && c<=16)
    return 0;

  return vertice;
  
}

/*
  ITA: Restituisce l'indice del vertice presente in (riga, colonna).
  Se non è presente alcun nodo 
  restituisce -1
  ENG: Returns the index of the vertex present in (row, column).
  If no vertex is present 
  returns -1
 */
int trova_vertice(int riga, int colonna)
{
  for(int i = 0; i<NODI_LAB_POT;i++)
    {
      if(grafo[i].linea == riga && grafo[i].columna == colonna)
	return grafo[i].index;
    }
  return -1;
}

/* 
   ITA: Controlla se l'oggetto nella cella non è un muro
   ENG: checks if the object into the cell is or not a wall
*/
bool oggetto_accessibile(oggetto s)
{
  if(s == 'J' || s == 'U' || s == 'V')
    return true;
  else
    return false;
}


double euri(int start, int goal)
{
  if(start<0)
    {
      printf("Indice nodo start negativo\n");
      exit(1);

    }

  /*
    ITA: cerca un fantasma nelle celle vicine
    ENG: look for a ghost in neighboring cells
  */
  int x = g_posi.tuki_x;
  int y = g_posi.tuki_y;
  int x_g[4];
  int y_g[4];
  x_g[0] = g_posi.blinky_x;
  x_g[1] = g_posi.pinky_x;
  x_g[2] = g_posi.inky_x;
  x_g[3] = g_posi.clyde_x;
  
  y_g[0] = g_posi.blinky_y;
  y_g[1] = g_posi.pinky_y;
  y_g[2] = g_posi.inky_y;
  y_g[3] = g_posi.clyde_y;

  int peso_g[]={500,400,500,400};
  
  int x1,x2,y1,y2;
  double d;
  x1 = agri_Vertices_Colligati[start].columna;
  y1 = agri_Vertices_Colligati[start].linea;
  x2 = agri_Vertices_Colligati[goal].columna;
  y2 = agri_Vertices_Colligati[goal].linea;
  /*
    ITA: Euristica uguale al quadrato della distanza euclidea
    ENG: Heuristic equal to the square of the Euclidean distance
  */
  d = (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);

  for(int i = 0; i<4; i++)
    {
      int v = trova_vertice(y_g[i], x_g[i]);
      if(grafo[v].ianua[SINISTRA] == start ||
	 grafo[v].ianua[DESTRA] == start ||
	 grafo[v].ianua[SU] == start ||
	 grafo[v].ianua[GIU] == start||
	 grafo[v].index == start
	 )
	{
	  return peso_g[i];
	}
      
    }
  return(sqrt(d));
  
}



/*
  ITA: Crea un grafo corrispondente al labirinto di Pac-Man
  ENG: Create a graph corresponding to the maze of Pac-Man
 */
void collega_tuki_nodi(oggetto **labx)
{
  int i_aux,j_aux;
  int k = 0;
  /* Genera i vertici del grafo */
  for(int i = 3; i<ALTEZZA-3; i++)
    {
      for(int j = 1; j<LARGHEZZA-1; j++)
	{
	  if( oggetto_accessibile(labx[i][j]))
	    {
	      grafo[k].linea = i;
	      grafo[k].columna = j;
	      grafo[k].index = k;
	      k++;
	      // printf("Vertice: %d: (%d,%d)\n",k,i,j);
	    }
	} 
    }
  
  n_vertici = k;
  /* Collega i vertici del grafo */
  for(int k = 0; k<NODI_LAB_POT; k++)
    {
      int r = grafo[k].linea;
      int c = grafo[k].columna;
      if(c>0)
	grafo[k].ianua[SINISTRA] =  trova_vertice(r, c-1);
      if(c<LARGHEZZA - 1)
	grafo[k].ianua[DESTRA] = trova_vertice(r, c+1);
      if(r>0)
	grafo[k].ianua[SU] = trova_vertice(r-1, c);
      if(r<ALTEZZA-1)
	grafo[k].ianua[GIU] = trova_vertice(r+1, c);
    } 


}

double distanza_esatta(int da_nodo, int a_nodo)
{
  int s = da_nodo;
  int g = a_nodo;
  static int distanze[NODI_LAB_POT][NODI_LAB_POT];
  static int init = 0;
  if(!init)
    {
      for(int i=0; i<NODI_LAB_POT;i++)
        for(int j=0; j<NODI_LAB_POT;j++)
	  {
	    distanze[i][j]=INFINITO;
	    
	    if(grafo[da_nodo].ianua[SINISTRA] == a_nodo ||
	       grafo[da_nodo].ianua[DESTRA] == a_nodo ||
	       grafo[da_nodo].ianua[SU] == a_nodo ||
	       grafo[da_nodo].ianua[GIU] == a_nodo)
	      distanze[i][j] = 1;
	  }
      init = 1;
    }
  
  return (double)distanze[s][g];
}



direzione gioca_tuki(posizioni posi, oggetto **labx)
{
  static int * percorso_fuga = 0;
  static int vertice_goal = -1;
  static int init = 0;
  /* condivisione delle posizioni per accedere da euri **/
  g_posi = posi;
  
  int vertice_corrente = -1;
    
  /*
    ITA: Creazione esterna del grafo del labirinto
    ENG: External creation of the graph of the labyrinth
  */
  if(!init)
    {
      collega_tuki_nodi(labx);
      struct timeval time; 
      gettimeofday(&time,NULL);
      
      srand((time.tv_sec * 1000) + (time.tv_usec / 1000));
      init = 1;
    }
  
  /* 
     ITA: Direzione presa nel turno di gioco corrente 
     ENG: Direction taken into the current game cycle
  */
  static direzione ld = SINISTRA;
    
  /* 
     ITA: Posizione di Pac-Man nel labirinto
     ENG: Pac-Man's row and column
  */
  int i = posi.tuki_y;
  int j = posi.tuki_x;

  int prossimo_vertice = -1;
  
  vertice_corrente = trova_vertice(i,j);
  
  /* STABILISCO IL PROSSIMO VERTICE */
  if(
     vertice_corrente == vertice_goal||
     vertice_goal == -1
     )
    {
      do{
	vertice_goal = (double)rand()/((double)RAND_MAX)*NODI_LAB_POT;
      }
      while(labx[grafo[vertice_goal].linea][grafo[vertice_goal].columna] == 'J');
    }

  /* Evita la casa dei fantasmi */
  vertice_goal = evita_casa_fantasmi(vertice_goal);

  //printf("Passo %d -> %d \n",vertice_corrente,vertice_goal);

  do
    {
      percorso_fuga = agri_astar
	(vertice_corrente,
	 vertice_goal,
	 grafo,&distanza_esatta,&euri,NODI_LAB_POT);
      if(!percorso_fuga)
	vertice_goal = (double)rand()/((double)RAND_MAX)*NODI_LAB_POT;
    }while(!percorso_fuga);
  
  prossimo_vertice = *percorso_fuga;
  free(percorso_fuga);

  
  
  
  /*
    ITA:  Cerco il percorso per il nodo indice_nodo.
    Entro in d[vertice_da] e controllo le sue porte
    finché non trovo quella che collega a indice_nodo
    ENG: look for the path to the vertex indice_nodo.
    I enter d[vertice_da] and check its doors
    until I find the one that connects to indice_nodo
  */
  if(grafo[vertice_corrente].ianua[SINISTRA] == prossimo_vertice)
    {
      ld = SINISTRA;
    }
  if(grafo[vertice_corrente].ianua[DESTRA] == prossimo_vertice)
    {
      ld = DESTRA;
    }
  if(grafo[vertice_corrente].ianua[SU] == prossimo_vertice)
    {
      ld = SU;
    }
  if(grafo[vertice_corrente].ianua[GIU] == prossimo_vertice)
	{
	  ld = GIU;
	}
            
  return ld;
}
