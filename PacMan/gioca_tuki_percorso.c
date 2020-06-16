/*___________________________________________________________
 * 
 * FILE: gioca_tuki_generagrafo.c
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
#define GUINZAGLIO 10

/*
  ITA: array di vertici del grafo completo del Pac-Man
 */
static agri_Vertex grafo[34];

/*
  ITA: array della sequnza dei vertici più efficiente
  per completare il percorso
 */
int * cammino;
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
  int x1,x2,y1,y2;
  double d;
  x1=agri_Vertices_Colligati[start].columna;
  y1=agri_Vertices_Colligati[start].linea;
  x2=agri_Vertices_Colligati[goal].columna;
  y2=agri_Vertices_Colligati[goal].linea;
  //Euristica uguale al quadrato della distanza euclidea
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


/*___________________________________________________________
 *|
 *| Crea un grafo corrispondente al labirinto del tuki
 */
void collega_tuki_nodi()
{
  static int cam[]={3,10,2,0,3,2,3,0,5,6,3,4,12,13,17,
	     6,5,6,1,8,1,9,8,11,17,16,13,12,15,
	     14,17,23,22,19,16,19,18,15,18,21,20,
	     14,20,30,32,33,31,23,29,28,33,28,27,
	     22,27,26,21,26,25,32,25,20,24,30};
  cammino = cam;
  
  grafo[0].linea = 3;
  grafo[0].columna = 6;
  grafo[0].index = 0;
  grafo[0].ianua[SINISTRA] = 2;
  grafo[0].ianua[DESTRA] = 5;
  grafo[0].ianua[SU] = -1;
  grafo[0].ianua[GIU] = 3;

  grafo[1].linea = 3;
  grafo[1].columna = 21;
  grafo[1].index = 1;
  grafo[1].ianua[SINISTRA] = 6;
  grafo[1].ianua[DESTRA] = 9;
  grafo[1].ianua[SU] = -1;
  grafo[1].ianua[GIU] = 8;

  grafo[2].linea = 7;
  grafo[2].columna = 1;
  grafo[2].index = 2;
  grafo[2].ianua[SINISTRA] = -1;
  grafo[2].ianua[DESTRA] = 3;
  grafo[2].ianua[SU] = 0;
  grafo[2].ianua[GIU] = 10;

  grafo[3].linea = 7;
  grafo[3].columna = 6;
  grafo[3].index = 3;
  grafo[3].ianua[SINISTRA] = 2;
  grafo[3].ianua[DESTRA] = 4;
  grafo[3].ianua[SU] = 0;
  grafo[3].ianua[GIU] = 10;

  grafo[4].linea = 7;
  grafo[4].columna = 9;
  grafo[4].index = 4;
  grafo[4].ianua[SINISTRA] = 3;
  grafo[4].ianua[DESTRA] = 5;
  grafo[4].ianua[SU] = -1;
  grafo[4].ianua[GIU] = 12;

  grafo[5].linea = 7;
  grafo[5].columna = 12;
  grafo[5].index = 5;
  grafo[5].ianua[SINISTRA] = 4;
  grafo[5].ianua[DESTRA] = 6;
  grafo[5].ianua[SU] = 0;
  grafo[5].ianua[GIU] = -1;

  grafo[6].linea = 7;
  grafo[6].columna = 15;
  grafo[6].index = 6;
  grafo[6].ianua[SINISTRA] = 5;
  grafo[6].ianua[DESTRA] = 7;
  grafo[6].ianua[SU] = 1;
  grafo[6].ianua[GIU] = -1;

  grafo[7].linea = 7;
  grafo[7].columna = 18;
  grafo[7].index = 7;
  grafo[7].ianua[SINISTRA] = 6;
  grafo[7].ianua[DESTRA] = 8;
  grafo[7].ianua[SU] = -1;
  grafo[7].ianua[GIU] = 13;

  grafo[8].linea = 7;
  grafo[8].columna = 21;
  grafo[8].index = 8;
  grafo[8].ianua[SINISTRA] = 7;
  grafo[8].ianua[DESTRA] = 9;
  grafo[8].ianua[SU] = 1;
  grafo[8].ianua[GIU] = 11;

  grafo[9].linea = 7;
  grafo[9].columna = 26;
  grafo[9].index = 9;
  grafo[9].ianua[SINISTRA] = 8;
  grafo[9].ianua[DESTRA] = -1;
  grafo[9].ianua[SU] = 1;
  grafo[9].ianua[GIU] = 11;

  grafo[10].linea = 10;
  grafo[10].columna = 6;
  grafo[10].index = 10;
  grafo[10].ianua[SINISTRA] = 2;
  grafo[10].ianua[DESTRA] = -1;
  grafo[10].ianua[SU] = 3;
  grafo[10].ianua[GIU] = 14;

  grafo[11].linea = 10;
  grafo[11].columna = 21;
  grafo[11].index = 11;
  grafo[11].ianua[SINISTRA] = -1;
  grafo[11].ianua[DESTRA] = 9;
  grafo[11].ianua[SU] = 8;
  grafo[11].ianua[GIU] = 17;

  grafo[12].linea = 13;
  grafo[12].columna = 12;
  grafo[12].index = 12;
  grafo[12].ianua[SINISTRA] = 15;
  grafo[12].ianua[DESTRA] = 13;
  grafo[12].ianua[SU] = 4;
  grafo[12].ianua[GIU] = -1;

  grafo[13].linea = 13;
  grafo[13].columna = 15;
  grafo[13].index = 13;
  grafo[13].ianua[SINISTRA] = 12;
  grafo[13].ianua[DESTRA] = 16;
  grafo[13].ianua[SU] = 7;
  grafo[13].ianua[GIU] = -1;

  grafo[14].linea = 16;
  grafo[14].columna = 6;
  grafo[14].index = 14;
  grafo[14].ianua[SINISTRA] = -1;
  grafo[14].ianua[DESTRA] = 15;
  grafo[14].ianua[SU] = 10;
  grafo[14].ianua[GIU] = 20;

  grafo[15].linea = 16;
  grafo[15].columna = 9;
  grafo[15].index = 15;
  grafo[15].ianua[SINISTRA] = 14;
  grafo[15].ianua[DESTRA] = -1;
  grafo[15].ianua[SU] = 12;
  grafo[15].ianua[GIU] = 18;

  grafo[16].linea = 16;
  grafo[16].columna = 18;
  grafo[16].index = 16;
  grafo[16].ianua[SINISTRA] = -1;
  grafo[16].ianua[DESTRA] = 17;
  grafo[16].ianua[SU] = 13;
  grafo[16].ianua[GIU] = 19;

  grafo[17].linea = 16;
  grafo[17].columna = 21;
  grafo[17].index = 17;
  grafo[17].ianua[SINISTRA] = 16;
  grafo[17].ianua[DESTRA] = -1;
  grafo[17].ianua[SU] = 11;
  grafo[17].ianua[GIU] = 23;

  grafo[18].linea = 19;
  grafo[18].columna = 9;
  grafo[18].index = 18;
  grafo[18].ianua[SINISTRA] = -1;
  grafo[18].ianua[DESTRA] = 19;
  grafo[18].ianua[SU] = 15;
  grafo[18].ianua[GIU] = 21;

  grafo[19].linea = 19;
  grafo[19].columna = 18;
  grafo[19].index = 19;
  grafo[19].ianua[SINISTRA] = 18;
  grafo[19].ianua[DESTRA] = -1;
  grafo[19].ianua[SU] = 16;
  grafo[19].ianua[GIU] = 22;

  grafo[20].linea = 22;
  grafo[20].columna = 6;
  grafo[20].index = 20;
  grafo[20].ianua[SINISTRA] = 30;
  grafo[20].ianua[DESTRA] = 21;
  grafo[20].ianua[SU] = 14;
  grafo[20].ianua[GIU] = 24;

   grafo[21].linea = 22;
  grafo[21].columna = 9;
  grafo[21].index = 21;
  grafo[21].ianua[SINISTRA] = 20;
  grafo[21].ianua[DESTRA] = 26;
  grafo[21].ianua[SU] = 18;
  grafo[21].ianua[GIU] = -1;

  grafo[22].linea = 22;
  grafo[22].columna = 18;
  grafo[22].index = 22;
  grafo[22].ianua[SINISTRA] = 27;
  grafo[22].ianua[DESTRA] = 23;
  grafo[22].ianua[SU] = 19;
  grafo[22].ianua[GIU] = -1;

  grafo[23].linea = 22;
  grafo[23].columna = 21;
  grafo[23].index = 23;
  grafo[23].ianua[SINISTRA] = 22;
  grafo[23].ianua[DESTRA] = 31;
  grafo[23].ianua[SU] = 17;
  grafo[23].ianua[GIU] = 29;

  grafo[24].linea = 25;
  grafo[24].columna = 6;
  grafo[24].index = 24;
  grafo[24].ianua[SINISTRA] = -1;
  grafo[24].ianua[DESTRA] = 25;
  grafo[24].ianua[SU] = 20;
  grafo[24].ianua[GIU] = 30;

  grafo[25].linea = 25;
  grafo[25].columna = 9;
  grafo[25].index = 25;
  grafo[25].ianua[SINISTRA] = 24;
  grafo[25].ianua[DESTRA] = 26;
  grafo[25].ianua[SU] = -1;
  grafo[25].ianua[GIU] = 32;

  grafo[26].linea = 25;
  grafo[26].columna = 12;
  grafo[26].index = 26;
  grafo[26].ianua[SINISTRA] = 25;
  grafo[26].ianua[DESTRA] = 27;
  grafo[26].ianua[SU] = 21;
  grafo[26].ianua[GIU] = -1;

  grafo[27].linea = 25;
  grafo[27].columna = 15;
  grafo[27].index = 27;
  grafo[27].ianua[SINISTRA] = 26;
  grafo[27].ianua[DESTRA] = 28;
  grafo[27].ianua[SU] = 22;
  grafo[27].ianua[GIU] = -1;

  grafo[28].linea = 25;
  grafo[28].columna = 18;
  grafo[28].index = 28;
  grafo[28].ianua[SINISTRA] = 27;
  grafo[28].ianua[DESTRA] = 29;
  grafo[28].ianua[SU] = -1;
  grafo[28].ianua[GIU] = 33;

  grafo[29].linea = 25;
  grafo[29].columna = 21;
  grafo[29].index = 29;
  grafo[29].ianua[SINISTRA] = 28;
  grafo[29].ianua[DESTRA] = -1;
  grafo[29].ianua[SU] = 23;
  grafo[29].ianua[GIU] = 31;

  grafo[30].linea = 28;
  grafo[30].columna = 3;
  grafo[30].index = 30;
  grafo[30].ianua[SINISTRA] = 32;
  grafo[30].ianua[DESTRA] = 24;
  grafo[30].ianua[SU] = 20;
  grafo[30].ianua[GIU] = -1;

  grafo[31].linea = 28;
  grafo[31].columna = 24;
  grafo[31].index = 31;
  grafo[31].ianua[SINISTRA] = 29;
  grafo[31].ianua[DESTRA] = 33;
  grafo[31].ianua[SU] = 23;
  grafo[31].ianua[GIU] = -1;

  grafo[32].linea = 31;
  grafo[32].columna = 12;
  grafo[32].index = 32;
  grafo[32].ianua[SINISTRA] = 30;
  grafo[32].ianua[DESTRA] = 33;
  grafo[32].ianua[SU] = 25;
  grafo[32].ianua[GIU] = -1;

  grafo[33].linea = 31;
  grafo[33].columna = 15;
  grafo[33].index = 33;
  grafo[33].ianua[SINISTRA] = 32;
  grafo[33].ianua[DESTRA] = 31;
  grafo[33].ianua[SU] = 28;
  grafo[33].ianua[GIU] = -1;
  
}

double distanza_esatta(int da_nodo, int a_nodo)
{
  int s = da_nodo;
  int g = a_nodo;
  static int distanze[NNODI][NNODI];
  static int init = 0;
  if(!init)
    {
      for(int i=0; i<NNODI;i++)
        for(int j=0; j<NNODI;j++)
          distanze[i][j]=INFINITO;

      distanze[0][2]=8;
      distanze[0][3]=3;
      distanze[0][5]=9;
      distanze[2][0]=8;
      distanze[3][0]=3;
      distanze[5][0]=9;
      
      distanze[1][6]=9;
      distanze[1][8]=3;
      distanze[1][9]=8;
      distanze[6][1]=9;
      distanze[8][1]=3;
      distanze[9][1]=8;
      
      distanze[2][3]=4;
      distanze[2][10]=7;
      distanze[3][2]=4;
      distanze[10][2]=7;
      
      distanze[3][4]=2;
      distanze[3][10]=2;
      distanze[4][3]=2;
      distanze[10][3]=2;
      
      distanze[4][5]=2;
      distanze[4][12]=8;
      distanze[5][4]=2;
      distanze[12][4]=8;
      
      distanze[5][6]=2;
      distanze[6][5]=2;
      
      distanze[6][7]=2;
      distanze[7][6]=2;
      
      distanze[7][8]=2;
      distanze[7][13]=8;
      distanze[8][7]=2;
      distanze[13][7]=8;
      
      distanze[8][9]=4;
      distanze[8][11]=2;
      distanze[9][8]=4;
      distanze[11][8]=2;

      distanze[9][11]=7;
      distanze[11][9]=7;
      
      distanze[10][14]=5;
      distanze[14][10]=5;
      
      distanze[11][17]=5;
      distanze[17][11]=5;
      
      distanze[12][13]=2;
      distanze[12][15]=5;
      distanze[13][12]=2;
      distanze[15][12]=5;
      
      distanze[13][16]=5;
      distanze[16][13]=5;
      
      distanze[14][15]=2;
      distanze[14][20]=5;
      distanze[15][14]=2;
      distanze[20][14]=5;
      
      distanze[14][17]=6;
      distanze[17][14]=6;
      
      distanze[15][18]=2;
      distanze[18][15]=2;
      
      distanze[16][17]=2;
      distanze[16][19]=2;
      distanze[17][16]=2;
      distanze[19][16]=2;
      
      distanze[17][23]=5;
      distanze[23][17]=5;
      
      distanze[18][19]=8;
      distanze[18][21]=2;
      distanze[19][18]=8;
      distanze[21][18]=2;
      
      distanze[19][22]=2;
      distanze[22][19]=2;
  
      distanze[20][30]=12;
      distanze[20][24]=2;
      distanze[20][21]=2;
      distanze[30][20]=12;
      distanze[24][20]=2;
      distanze[21][30]=2;
      
      distanze[21][26]=5;
      distanze[26][21]=5;
      
      distanze[22][27]=5;
      distanze[22][23]=2;
      distanze[27][22]=5;
      distanze[23][22]=2;
      
      distanze[23][29]=2;
      distanze[23][31]=12;
      distanze[29][23]=2;
      distanze[31][23]=12;
      
      distanze[24][30]=5;
      distanze[24][25]=2;
      distanze[30][24]=5;
      distanze[25][24]=2;
      
      distanze[25][26]=2;
      distanze[25][32]=8;
      distanze[26][25]=2;
      distanze[32][25]=8;
      
      distanze[26][27]=2;
      distanze[27][26]=2;
      
      distanze[27][28]=2;
      distanze[28][27]=2;
      
      distanze[28][33]=8;
      distanze[28][29]=2;
      distanze[33][28]=8;
      distanze[29][28]=2;
      
      distanze[29][31]=5;
      distanze[31][29]=5;
      
      distanze[30][32]=15;
      distanze[32][30]=15;
      
      distanze[31][33]=15;
      distanze[33][31]=15;
      
      distanze[32][33]=2;
      distanze[33][32]=2;

      init=1;
    }
  return (double)distanze[s][g];
}


/*__________________________________________________________
 *|
 *| Torna l'indice del nodo presente in (riga, colonna)
 *| Se non è presente alcun nodo (il fantasma è su un ramo)
 *| torna -1
 */
int indice_tuki_nodo_cella(int riga, int col)
{
  for(int i=0; i<34;i++)
    {
      if(grafo[i].columna == col && grafo[i].linea == riga)
        return grafo[i].index;
    }
  return -1;
}


typedef enum {ESPLORA, DECIDI, NAVIGA} Modo;

direzione gioca_tuki(posizioni posi, oggetto **labx)
{
  static int * percorso_fuga = 0;
  static int * copia;
  static Modo modo_gioco = ESPLORA;
  static int nodo_bersaglio = 0;
  
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

  /*
    ITA: creazione esterna del grafo del labirinto
   */
  collega_tuki_nodi();

  static int vertice_da = SCONOSCIUTO;
  static int vertici_contati = SCONOSCIUTO;

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

  longitudo_colligatio++;
  
  /* Celle confinanti (neighbors) */
  oggetto vicino[4];
  vicino[0] = labx[i][j-1]; //sinistra - left
  vicino[1] = labx[i][j+1]; //destra - right
  vicino[2] = labx[i-1][j]; //su - up
  vicino[3] = labx[i+1][j]; //giu - down

  /* Variabile ausiliarie con nomi più comodi */
  oggetto s = vicino[0];
  oggetto d = vicino[1];
  oggetto a = vicino[2];
  oggetto b = vicino[3];

  /*
    ITA: cerca un fantasma nelle celle vicine
    
  */
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

  /*
    ITA: flag di presenza del fantasma
   */
  char s_g = 0, d_g = 0,a_g = 0,b_g = 0;
  for (int ig = 0; ig<4; ig++)
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
  
  if(nd>2)
    {
      
      /* 
	 ITA: Se siamo qui, Tuki è su un vertice
	 ENG: If we are here Tuki position is a vertex 
      */
      int vertice_a = agri_Verticem_quaero(grafo,i,j);
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

      //Aggiorno per la funzioen dist
      distanze[vertice_da][vertice_a] = longitudo_colligatio;
            
      colligatio.ad = v_a;
      colligatio.ab = v_da;
      colligatio.longitudo = longitudo_colligatio;
      colligatio.meta = direzione_arrivo;
      colligatio.discessus = direzione_partenza;
      
      nodo_rilevato = true;

      longitudo_colligatio = 0;
      vertice_da = vertice_a;
      i_da = i;
      j_da = j;
    }

  /* ITA: Gestione ostacoli
     ENG: dealing with obstacles
  */
  bool disponibile = false;
    
  bool aleatorio = false;
  
 
  /* Se un fantasma è nelle vicinanze prendo la prima cella buona */
  if((s_g || d_g || a_g || b_g) && FUGA)
    {

      /*
	ITA: direzioni possibili di fuga
       */
      direzione esc[4];
      for(int i=0;i<4;i++) esc[i]=FERMO;
      int ki = 0; //direzioni buone
      if(copia) free(copia);
      copia = 0;
      modo_gioco = ESPLORA;
            
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
      
      if(ki == 0) return FERMO;

      ld = esc[rand()%ki];
      
      return ld;
    }
  
  if(modo_gioco == ESPLORA)
    {
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
  else if(modo_gioco == DECIDI)
    {
      printf("##Torno da %d a %d\n",vertice_da,0);
      percorso_fuga = agri_astar(vertice_da,0,grafo,&dist,&euri);
      if(percorso_fuga == 0)
	{
	  modo_gioco = ESPLORA;
	  ld = FERMO;
	  return ld;
	}
      copia = percorso_fuga;
      modo_gioco = NAVIGA;
    }
  if(modo_gioco == NAVIGA)
    {
      if(nodo_rilevato == true)
	{
	  /*
	    ITA: pesco il prossimo nodo
	  */
	  int indice_nodo = *percorso_fuga;
	  if(indice_nodo == -1)
	    {
	      printf("***Completato il cammino\n");
	      nodo_bersaglio++;
	      modo_gioco = ESPLORA;
	      free(copia);
	      copia = 0;
	      return FERMO;
	    }
	  percorso_fuga++;
	  /*
	    ITA: Cerco il percorso per il nodo indice_nodo
	    antro in d[vertice_da] e controllo le sue porte
	    finché non trovo quella che collega a indice_nodo
	  */
	  if(grafo[vertice_da].ianua[SINISTRA] == indice_nodo)
	    {
	      ld = SINISTRA;
	    }
	  if(grafo[vertice_da].ianua[DESTRA] == indice_nodo)
	    {
	      ld = DESTRA;
	    }
	  if(grafo[vertice_da].ianua[SU] == indice_nodo)
	    {
	      ld = SU;
	    }
	  if(grafo[vertice_da].ianua[GIU] == indice_nodo)
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
