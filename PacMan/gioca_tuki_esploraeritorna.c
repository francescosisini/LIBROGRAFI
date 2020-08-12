/*___________________________________________________________
 * 
 * FILE: gioca_tuki_esploraeritorna.c
 */
#include "tuki5_modello.h"
#include "libagri.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define SCONOSCIUTO -2
#define GUINZAGLIO 5

char * dir(versus d)
{
  if(d == SX) return "SX";
  if(d == DX) return "DX";
  if(d == DEORSUM) return "DEORSUM";
  if(d == SURSUM) return "SURSUM";
  if(d == FIXO) return "FIXO";
  return "-1";  
}

agri_Vertex agri_Vertices_Colligati[NNODI];

double euri(int start, int goal)
{
  int x1, x2, y1, y2;
  double d;
  x1 = agri_Vertices_Colligati[start].columna;
  y1 = agri_Vertices_Colligati[start].linea;
  x2 = agri_Vertices_Colligati[goal].columna;
  y2 = agri_Vertices_Colligati[goal].linea;

  d = (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);
  
  return sqrt(d);
}

int distanze[NNODI][NNODI];

double dist(int da_nodus, int a_nodus)
{
  int s = da_nodus;
  int g = a_nodus;
  
  return (double)distanze[s][g];
}

void stampa(agri_Colligationes_Colligatae g)
{
  FILE * f = fopen("grafi.csv","w+t");
  while(g)
    {
      fprintf(f," %d,%d,\n",
	      g->colligatio.ab.index,
	      g->colligatio.ad.index);
      
      g = g->next;
    }
  fclose(f);
}

bool oggetto_accessibile(oggetto s)
{
  if(s == 'J' || s == 'U' || s == 'V')
    return true;
  else
    return false;
}

typedef enum {ESPLORA, DECIDI, RITORNA} Modo;

direzione gioca_tuki(posizioni posi, oggetto **labx)
{
  static agri_Verticum_Dispositio vert_disp;
  static int nodi_percorsi = 0;
  static int * percorso_fuga = 0;
  static int * copia;
  static Modo modo_gioco = ESPLORA;
  static int mosse = 0;
  mosse++;

  labx[14][12]='A';
  labx[14][13]='A';
  labx[14][11]='A';
  labx[14][14]='A';

  static agri_Colligationes_Colligatae g = 0;

  static int vertice_da = SCONOSCIUTO;
  static int vertici_contati = SCONOSCIUTO;
  static int direzione_arrivo = FERMO;
  static int direzione_partenza = FERMO;
  static int longitudo_colligatio = 0;
  static int i_da, j_da;
  
  static direzione ld = SINISTRA;
  
  static bool init = false;
  if(!init)
    {
      srand(time(0));
      init = true;
    }

  int i = posi.tuki_y;
  int j = posi.tuki_x;
  
  longitudo_colligatio++;

  oggetto vicino[4];
  vicino[0] = labx[i][j-1]; //sinistra - left
  vicino[1] = labx[i][j+1]; //destra - right
  vicino[2] = labx[i-1][j]; //su - up
  vicino[3] = labx[i+1][j]; //giu - down

  oggetto s = vicino[0];
  oggetto d = vicino[1];
  oggetto a = vicino[2];
  oggetto b = vicino[3];

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

  char s_g = 0, d_g = 0, a_g = 0, b_g = 0;
  for (int ig=0; ig<4; ig++)
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

  int nd = 0;
  for(int k=0; k<4; k++)
    nd += (1*oggetto_accessibile(vicino[k]));
  
  fflush(stdout);

  bool nodo_rilevato = false;
  
  if(vertice_da == SCONOSCIUTO && nd>2)
    {
      fflush(stdout);
      vertice_da = 0;
      i_da = i;
      j_da = j;
      vertici_contati = 1;
      longitudo_colligatio = 0;
    }
  else if(nd>2)
    {
      int vertice_a = agri_Verticem_quaero(g,i,j);
      if(vertice_a<0)
	{
	  vertice_a = vertici_contati;
	  vertici_contati++;
	  nodi_percorsi++;
	}
      agri_Colligatio colligatio;
      agri_Vertex v_a, v_da;
      v_a = agri_Verticem_creo(vertice_a,i,j);
      v_da = agri_Verticem_creo(vertice_da,i_da,j_da);
      
      distanze[vertice_da][vertice_a] = longitudo_colligatio;
      
      colligatio.ad = v_a;
      colligatio.ab = v_da;
      colligatio.longitudo = longitudo_colligatio;
      colligatio.meta = direzione_arrivo;
      colligatio.discessus = direzione_partenza;
      agri_Colligationem_insero(&g, colligatio);
      nodo_rilevato = true;

      longitudo_colligatio = 0;
      vertice_da = vertice_a;
      i_da = i;
      j_da = j;
      
      stampa(g);
    }

  bool disponibile = false;

  bool aleatorio = false;

  if(nodi_percorsi == GUINZAGLIO)
    modo_gioco = DECIDI;

  if((s_g || d_g || a_g || b_g) && FUGA)
    {
      direzione esc[4];
      for(int i=0;i<4;i++) esc[i]=FERMO;
      int ki = 0; //direzioni buone, good directions
      if(copia) free(copia);
      copia = 0;
      modo_gioco = ESPLORA;
      nodi_percorsi = 0;
      
      if(oggetto_accessibile(s) && !s_g)
	{
	  esc[ki] = SINISTRA;
	  ki++;
	}
      if(oggetto_accessibile(a) && !a_g)
	{
	  esc[ki] = SU;
	  ki++;
	}
      if(oggetto_accessibile(d) && !d_g)
	{
	  esc[ki] = DESTRA;
	  ki++;
	}
      if(oggetto_accessibile(b) && !b_g)
	{
	  esc[ki] = GIU;
	  ki++;
	}
      if(ki == 0)
	{
	  return FERMO;
	}
      ld = esc[rand()%ki];
      
      direzione_arrivo = ld;
      if(nodo_rilevato)
	direzione_partenza = ld;
      return ld;
    }
  
  if(modo_gioco == ESPLORA)
    {
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
	  else if(!oggetto_accessibile(d) && ld == DESTRA)
	    {	
	      ld = rand()%2;
	      if(ld==0) ld = SU;
	      else
		ld = GIU;
	      aleatorio = true;
	    }
	  else if(!oggetto_accessibile(a) && ld == SU)
	    {
	      ld = rand()%2;
	      if(ld==0) ld = SINISTRA;
	      else
		ld = DESTRA;
	      aleatorio = true;
	    }
	  else if(!oggetto_accessibile(b) && ld == GIU)
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
  
  else if(modo_gioco == DECIDI)
    {
      nodi_percorsi = 0;
      int s = agri_muto(g,&vert_disp);
      
      percorso_fuga = agri_astar(vertice_da,0,vert_disp,&dist,&euri,vertici_contati);
      if(percorso_fuga == 0)
	{
	  modo_gioco = ESPLORA;
	  ld = FERMO;
	  return ld;
	}
      copia = percorso_fuga;
      modo_gioco = RITORNA;
    }
  if(modo_gioco == RITORNA)
    {
      if(nodo_rilevato == true)
	{
	  int indice_nodo = *percorso_fuga;
	  if(indice_nodo == -1)
	    {
	      nodi_percorsi = 0;
	      modo_gioco = ESPLORA;
	      free(copia);
	      copia = 0;
	      return rand()%4;
	    } 
	  percorso_fuga++;

	  if(vert_disp[vertice_da].ianua[SINISTRA] == indice_nodo)
	    {
	      ld = SINISTRA;
	    }
	  if(vert_disp[vertice_da].ianua[DESTRA] == indice_nodo)
	    {
	      ld = DESTRA;
	    }
	  if(vert_disp[vertice_da].ianua[SU] == indice_nodo)
	    {
	      ld = SU;
	    }
	  if(vert_disp[vertice_da].ianua[GIU] == indice_nodo)
	    {
	      ld = GIU;
	    }	  
	}
      
      //SINISTRA
      if(ld == SINISTRA && oggetto_accessibile(s))
	return ld;
      if(ld == SINISTRA && oggetto_accessibile(a))
	return ld = SU;
      if(ld == SINISTRA && oggetto_accessibile(b))
	return ld = GIU;
      
      //DESTRA
      if(ld == DESTRA && oggetto_accessibile(d))
	return ld;
      if(ld == DESTRA && oggetto_accessibile(a))
	return ld = SU;
      if(ld == DESTRA && oggetto_accessibile(b))
	return ld = GIU;
      
      //SU
      if(ld == SU && oggetto_accessibile(a))
	return ld;
      if(ld == SU && oggetto_accessibile(s))
	return ld = SINISTRA;
      if(ld == SU && oggetto_accessibile(d))
	return ld = DESTRA;
      
      //GIU
      if(ld == GIU && oggetto_accessibile(b))
	return ld;
      if(ld == GIU && oggetto_accessibile(s))
	return ld = SINISTRA;
      if(ld == GIU && oggetto_accessibile(d))
	return ld = DESTRA;      
    }  
}
