/*___________________________________________________________
 * 
 * FILE: gioca_tuki_evita.c
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
#define PROFONDITA_RICERCA 60
#define DISTANZA_SICUREZZA 16
#define TENTATIVI 50

#define NODI_LAB_POT 600

posizioni g_posi;
int n_vertici;
oggetto **lab;
static agri_Vertex grafo[NODI_LAB_POT];
agri_Vertex agri_Vertices_Colligati[NODI_LAB_POT];

int phantasmatis_presentia
(
 int start, 
 agri_Vertex * agri_Vertices_Colligati,
 int (*fantasma_presente)(int ),
 int nmembri
 )
{
  static int iter; 
  int precedente[nmembri];
  Ordo candidati = 0;
  int livello = 0;
  
  Ordo_insero_nodus(&candidati,start,1);

  while(candidati != 0)
    {
      livello++;
      int corrente = Ordo_pop(&candidati);
     
      /* restituisce il livello del nodo in cui ha trovato un fantasma */
      if(fantasma_presente(corrente)||livello>PROFONDITA_RICERCA)
        {
	  return livello;
        }
     
      int vicino[PORTE];
      for(int i=0; i<PORTE; i++)
	{
	  vicino[i] = agri_Vertices_Colligati[corrente].ianua[i];
	}
      
      for(int i =0; i<PORTE; i++)
        {
	  int iv = vicino[i];
	  
          if(iv == -1)continue;
	  	  
	  precedente[iv] = corrente;
	  	  
	  Ordo_insero_nodus(&candidati,iv,1);
	}
    }
  return 0;
}

int trova_vertice(int riga, int colonna)
{
  for(int i = 0; i<NODI_LAB_POT;i++)
    {
      if(grafo[i].linea == riga && grafo[i].columna == colonna)
	return grafo[i].index;
    }
  return -1;
}

int visitatus(int vertice)
{
  int r = grafo[vertice].linea;
  int c = grafo[vertice].columna;
  
  if(lab[r][c] == U ||lab[r][c] == V)
    return 0;
  return 1;
}

int phantasmatis(int vertice)
{
  
  int r = grafo[vertice].linea;
  int c = grafo[vertice].columna;

  if(r>=15 && r<=17 && c>=11 && c<=16)
    return 0;
  
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

  for(int i = 0; i<4; i++)
    {
      int v = trova_vertice(y_g[i], x_g[i]);
      if(grafo[v].ianua[SINISTRA] == vertice ||
	 grafo[v].ianua[DESTRA] == vertice ||
	 grafo[v].ianua[SU] == vertice ||
	 grafo[v].ianua[GIU] == vertice||
	 grafo[v].index == vertice
	 )
	{
	  return 1;
	}
    }
  return 0;
}

int evita_casa_fantasmi(int vertice)
{
  int r = grafo[vertice].linea;
  int c = grafo[vertice].columna;
  if(r>=15 && r<=17 && c>=11 && c<=16)
    return 0;

  return vertice;  
}

bool oggetto_accessibile(oggetto s)
{
  if(s == 'J' || s == 'U' || s == 'V')
    return true;
  else
    return false;
}

bool area_accessibile(int r, int c)
{
  if (r<3) return false;
  if(r>32) return false;
  if( r>=12 && r<=14 && (c<=4 || c>= 23)) return false;
  if( r>=18 && r<=20 && (c<=4 || c>= 23)) return false;
  return true;
}

double euri(int start, int goal)
{
  if(start<0)
    {
      exit(1);
    }

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

  int peso_g[]={700,700,700,700};
  
  int x1,x2,y1,y2;
  double d;
  x1 = agri_Vertices_Colligati[start].columna;
  y1 = agri_Vertices_Colligati[start].linea;
  x2 = agri_Vertices_Colligati[goal].columna;
  y2 = agri_Vertices_Colligati[goal].linea;

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

void collega_tuki_nodi(oggetto **labx)
{
  int i_aux,j_aux;
  int k = 0;
  /* Genera i vertici del grafo */
  for(int i = 3; i<ALTEZZA-3; i++)
    {
      for(int j = 1; j<LARGHEZZA-1; j++)
	{
	  if( oggetto_accessibile(labx[i][j]) && area_accessibile(i,j))
	    {
	      grafo[k].linea = i;
	      grafo[k].columna = j;
	      grafo[k].index = k;
	      k++;
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
  g_posi = posi;
  lab = labx;
  
  int vertice_corrente = -1;
    
  if(!init)
    {
      collega_tuki_nodi(labx);
      struct timeval time; 
      gettimeofday(&time,NULL);
      
      srand((time.tv_sec * 1000) + (time.tv_usec / 1000));
      init = 1;
    }
  
  static direzione ld = SINISTRA;
  
  int i = posi.tuki_y;
  int j = posi.tuki_x;

  int prossimo_vertice = -1;
  
  vertice_corrente = trova_vertice(i,j);
  char sicuro = 0;
  
  /* STABILISCO IL PROSSIMO VERTICE */
  if(
     vertice_corrente == vertice_goal||
     vertice_goal == -1
     )
    {
      /* cerca la pillola */
      vertice_goal = agri_breadthfirstsearch
	(vertice_corrente, 
	 grafo,
	 visitatus,
	 NODI_LAB_POT
	 );
      /* verifica la presenza di fantasmi */
      
      sicuro = phantasmatis_presentia (vertice_goal, 
				       grafo,
				       phantasmatis,
				       NODI_LAB_POT
				       );
      int tent = 0;
      while(sicuro<DISTANZA_SICUREZZA)
	{
	  do{
	    tent++;
	    vertice_goal = (double)rand()/((double)RAND_MAX)*NODI_LAB_POT;
	  }
	  while(
		labx[grafo[vertice_goal].linea]
		[grafo[vertice_goal].columna] == 'J' &&
		tent<TENTATIVI
		);
	  if(tent == TENTATIVI)
	    vertice_goal = 1;
	  
	  vertice_goal = evita_casa_fantasmi(vertice_goal);
	  sicuro = phantasmatis_presentia
	    (vertice_goal, 
	     grafo,
	     phantasmatis,
	     NODI_LAB_POT
	     );
	}
    }
  
  percorso_fuga = agri_astar
    (vertice_corrente,
     vertice_goal,
     grafo,&distanza_esatta,&euri,NODI_LAB_POT);
  
  prossimo_vertice = *percorso_fuga;
  free(percorso_fuga);

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
