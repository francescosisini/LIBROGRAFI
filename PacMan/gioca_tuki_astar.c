#include "tuki5_modello.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#define INFINITO 9999
#define NNODI 34


/*__________________________________________________________
 *|
 *| Nodo del grafo che rappresenta il labirinto
 */
typedef struct {
  int riga;
  int colonna;
  int indice;
  int n_sx;
  int n_dx;
  int n_su;
  int n_giu;
} nodo;

/*___________________________________________________________
 *|
 *| I nodi del grafo del labirinto
 */
nodo grafo[NNODI];




/*_______________________________
 * ALgoritmo A*
 */

// Coda
typedef struct nodo_coda
{
  //Riferimento al nodo del grafo
  int indice;

  //Priorità
  double prio;
  
  //Navigazione coda 
  struct nodo_coda * post;
  
} Nodo;

//Tipo per la coda di priorità
typedef Nodo * Coda;
//Tipo per il cammino finale
typedef int * Percorso;



/*____________________________________________
 * 
 * Inserimento ordinato in base alla priorità
 */

void coda_elimina_nodo(Coda * l, int indice)
{
  
  while (*l) {
    if ((*l)->indice == indice)
      break;
    l = &(*l)->post;
  }
  if (*l) {
    Nodo* aux = *l;
    *l = (*l)->post;
    free(aux);
  } 
}


void coda_inserisci_nodo(Coda * l,int indice, double prio)
{
    
  Nodo * aux = (Nodo *)malloc(sizeof(Nodo));
  aux->indice =  indice;
  aux->prio = prio;

  /* il nodo è già in coda */
  coda_elimina_nodo(l,  indice);

  while (*l) {
    if ((*l)->prio < prio)
      break;
    l = &(*l)->post;
  }
  
  aux->post = *l;
  *l = aux;
}
void coda_stampa(Coda c)
{
  while(c)
    {
      printf(" Nodo %d, fscore %lf\n",c->indice,c->prio);
      c = c->post;
    }
}

int coda_pop(Coda * pcoda)
{
  
  /* puntatore al prio nodo */
  Coda candidato = *pcoda;
  
  int n = candidato->indice;

  /* aggiorna la coda */
  (*pcoda) = candidato->post;
  
  free(candidato);

  return n;
}



double euristica_h(int start, int goal)
{
  int x1,x2,y1,y2;
  double d;
  x1=grafo[start].colonna;
  y1=grafo[start].riga;
  x2=grafo[goal].colonna;
  y2=grafo[goal].riga;
  //Euristica uguale al quadrato della distanza euclidea
  d = (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);
  return sqrt(d);
}

double distanza_esatta(int da_nodo, int a_nodo)
{
  int s = da_nodo;
  int g = a_nodo;
  static int d[NNODI][NNODI];
  static int init = 0;
  if(!init)
    {
      for(int i=0; i<NNODI;i++)
        for(int j=0; j<NNODI;j++)
          d[i][j]=INFINITO;

      d[0][2]=8;
      d[0][3]=3;
      d[0][5]=9;
      d[2][0]=8;
      d[3][0]=3;
      d[5][0]=9;
      
      d[1][6]=9;
      d[1][8]=3;
      d[1][9]=8;
      d[6][1]=9;
      d[8][1]=3;
      d[9][1]=8;
      
      d[2][3]=4;
      d[2][10]=7;
      d[3][2]=4;
      d[10][2]=7;
      
      d[3][4]=2;
      d[3][10]=2;
      d[4][3]=2;
      d[10][3]=2;
      
      d[4][5]=2;
      d[4][12]=8;
      d[5][4]=2;
      d[12][4]=8;
      
      d[5][6]=2;
      d[6][5]=2;
      
      d[6][7]=2;
      d[7][6]=2;
      
      d[7][8]=2;
      d[7][13]=8;
      d[8][7]=2;
      d[13][7]=8;
      
      d[8][9]=4;
      d[8][11]=2;
      d[9][8]=4;
      d[11][8]=2;

      d[9][11]=7;
      d[11][9]=7;
      
      d[10][14]=5;
      d[14][10]=5;
      
      d[11][17]=5;
      d[17][11]=5;
      
      d[12][13]=2;
      d[12][15]=5;
      d[13][12]=2;
      d[15][12]=5;
      
      d[13][16]=5;
      d[16][13]=5;
      
      d[14][15]=2;
      d[14][20]=5;
      d[15][14]=2;
      d[20][14]=5;
      
      d[14][17]=6;
      d[17][14]=6;
      
      d[15][18]=2;
      d[18][15]=2;
      
      d[16][17]=2;
      d[16][19]=2;
      d[17][16]=2;
      d[19][16]=2;
      
      d[17][23]=5;
      d[23][17]=5;
      
      d[18][19]=8;
      d[18][21]=2;
      d[19][18]=8;
      d[21][18]=2;
      
      d[19][22]=2;
      d[22][19]=2;
  
      d[20][30]=12;
      d[20][24]=2;
      d[20][21]=2;
      d[30][20]=12;
      d[24][20]=2;
      d[21][30]=2;
      
      d[21][26]=5;
      d[26][21]=5;
      
      d[22][27]=5;
      d[22][23]=2;
      d[27][22]=5;
      d[23][22]=2;
      
      d[23][29]=2;
      d[23][31]=12;
      d[29][23]=2;
      d[31][23]=12;
      
      d[24][30]=5;
      d[24][25]=2;
      d[30][24]=5;
      d[25][24]=2;
      
      d[25][26]=2;
      d[25][32]=8;
      d[26][25]=2;
      d[32][25]=8;
      
      d[26][27]=2;
      d[27][26]=2;
      
      d[27][28]=2;
      d[28][27]=2;
      
      d[28][33]=8;
      d[28][29]=2;
      d[33][28]=8;
      d[29][28]=2;
      
      d[29][31]=5;
      d[31][29]=5;
      
      d[30][32]=15;
      d[32][30]=15;
      
      d[31][33]=15;
      d[33][31]=15;
      
      d[32][33]=2;
      d[33][32]=2;

      init=1;
    }
  
  return (double)d[s][g];

}


Percorso A_star(int start, int goal)
{

  if(start==goal) return 0;
  
  double fscore[NNODI];
  double gscore[NNODI];
  int precedente[NNODI];

  //Nodi in valutazione per il path da start a goal
  Coda candidati = 0;

  
  
  for(int i=0;i<NNODI;i++)
    {
      fscore[i] = INFINITO;
      gscore[i] = INFINITO;
    }
  gscore[start] = 0;
  fscore[start]=euristica_h(start,goal);

  coda_inserisci_nodo(&candidati,start,(1./fscore[start]));

  while(candidati != 0)
    {
      printf("Pop ");
      fflush(stdout);
      int corrente = coda_pop(&candidati);
      printf("%d\n",corrente);
      /* Arrivato al nodo goal torna il cammino */
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
                    
          Percorso percorso = malloc((i+1)*sizeof(int));
	  
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
      int vicino[4];
      vicino[0] = grafo[corrente].n_sx;
      vicino[1] = grafo[corrente].n_dx;
      vicino[2] = grafo[corrente].n_su;
      vicino[3] = grafo[corrente].n_giu;
      printf("Il nodo %d\n",corrente);
      for(int i =0; i<4; i++)
        {
          int iv = vicino[i];
	  printf("ha vicino %d\n",iv);
          /* ogni nodo è predisposto per 4 vicini, ma molti nodi ne hanno
             solo 3*/
          if(iv == -1)continue;

          double d =  distanza_esatta(corrente, iv);
          double tent_gscore = gscore[corrente]+d;
	  printf("a distanza %lf\n",d);
          if(tent_gscore <= gscore[iv])
            {
	      
              /* Trovato cammino migliore a questo nodo passando per corrente*/
              precedente[iv] = corrente;
              gscore[iv] = tent_gscore;
              fscore[iv] = gscore[iv] +  euristica_h(iv, goal);
	     
              coda_inserisci_nodo(&candidati,iv, ( 1./fscore[iv]));
	     
	      fflush(stdout);
            }
	 
          

        }
       //Stampiamo la coda corrente
      Coda cd = candidati;
      printf("----------------------\n");
      while(cd)
	{
	  printf("coda: nodo %d, %lf\n",cd->indice,cd->prio);
	  cd=cd->post;
	}
      
      
      

    }
  return 0;
  
}


void collega_nodi();

direzione gioca_tuki(posizioni posi, oggetto **labx){

  static int init = 0;
  if(!init)
    {
      collega_nodi();
      init = 1;
    }


}

/*___________________________________________________________
 *|
 *| Crea un grafo corrispondente al labirinto del tuki
 */
void collega_nodi()
{
  grafo[0].riga = 3;
  grafo[0].colonna = 6;
  grafo[0].indice = 0;
  grafo[0].n_sx = 2;
  grafo[0].n_dx = 5;
  grafo[0].n_su = -1;
  grafo[0].n_giu = 3;

  grafo[1].riga = 3;
  grafo[1].colonna = 21;
  grafo[1].indice = 1;
  grafo[1].n_sx = 6;
  grafo[1].n_dx = 9;
  grafo[1].n_su = -1;
  grafo[1].n_giu = 8;

  grafo[2].riga = 7;
  grafo[2].colonna = 1;
  grafo[2].indice = 2;
  grafo[2].n_sx = -1;
  grafo[2].n_dx = 3;
  grafo[2].n_su = 0;
  grafo[2].n_giu = 10;

  grafo[3].riga = 7;
  grafo[3].colonna = 6;
  grafo[3].indice = 3;
  grafo[3].n_sx = 2;
  grafo[3].n_dx = 4;
  grafo[3].n_su = 0;
  grafo[3].n_giu = 10;

  grafo[4].riga = 7;
  grafo[4].colonna = 9;
  grafo[4].indice = 4;
  grafo[4].n_sx = 3;
  grafo[4].n_dx = 5;
  grafo[4].n_su = -1;
  grafo[4].n_giu = 12;

  grafo[5].riga = 7;
  grafo[5].colonna = 12;
  grafo[5].indice = 5;
  grafo[5].n_sx = 4;
  grafo[5].n_dx = 6;
  grafo[5].n_su = 0;
  grafo[5].n_giu = -1;

  grafo[6].riga = 7;
  grafo[6].colonna = 15;
  grafo[6].indice = 6;
  grafo[6].n_sx = 5;
  grafo[6].n_dx = 7;
  grafo[6].n_su = 1;
  grafo[6].n_giu = -1;

  grafo[7].riga = 7;
  grafo[7].colonna = 18;
  grafo[7].indice = 7;
  grafo[7].n_sx = 6;
  grafo[7].n_dx = 8;
  grafo[7].n_su = -1;
  grafo[7].n_giu = 13;

  grafo[8].riga = 7;
  grafo[8].colonna = 21;
  grafo[8].indice = 8;
  grafo[8].n_sx = 7;
  grafo[8].n_dx = 9;
  grafo[8].n_su = 1;
  grafo[8].n_giu = 11;

  grafo[9].riga = 7;
  grafo[9].colonna = 26;
  grafo[9].indice = 9;
  grafo[9].n_sx = 8;
  grafo[9].n_dx = -1;
  grafo[9].n_su = 1;
  grafo[9].n_giu = 11;

  grafo[10].riga = 10;
  grafo[10].colonna = 6;
  grafo[10].indice = 10;
  grafo[10].n_sx = 2;
  grafo[10].n_dx = -1;
  grafo[10].n_su = 3;
  grafo[10].n_giu = 14;

  grafo[11].riga = 10;
  grafo[11].colonna = 21;
  grafo[11].indice = 11;
  grafo[11].n_sx = -1;
  grafo[11].n_dx = 9;
  grafo[11].n_su = 8;
  grafo[11].n_giu = 17;

  grafo[12].riga = 13;
  grafo[12].colonna = 12;
  grafo[12].indice = 12;
  grafo[12].n_sx = 15;
  grafo[12].n_dx = 13;
  grafo[12].n_su = 4;
  grafo[12].n_giu = -1;

  grafo[13].riga = 13;
  grafo[13].colonna = 15;
  grafo[13].indice = 13;
  grafo[13].n_sx = 12;
  grafo[13].n_dx = 16;
  grafo[13].n_su = 7;
  grafo[13].n_giu = -1;

  grafo[14].riga = 16;
  grafo[14].colonna = 6;
  grafo[14].indice = 14;
  grafo[14].n_sx = -1;
  grafo[14].n_dx = 15;
  grafo[14].n_su = 10;
  grafo[14].n_giu = 20;

  grafo[15].riga = 16;
  grafo[15].colonna = 9;
  grafo[15].indice = 15;
  grafo[15].n_sx = 14;
  grafo[15].n_dx = -1;
  grafo[15].n_su = 12;
  grafo[15].n_giu = 18;

  grafo[16].riga = 16;
  grafo[16].colonna = 18;
  grafo[16].indice = 16;
  grafo[16].n_sx = -1;
  grafo[16].n_dx = 17;
  grafo[16].n_su = 13;
  grafo[16].n_giu = 19;

  grafo[17].riga = 16;
  grafo[17].colonna = 21;
  grafo[17].indice = 17;
  grafo[17].n_sx = 16;
  grafo[17].n_dx = -1;
  grafo[17].n_su = 11;
  grafo[17].n_giu = 23;

  grafo[18].riga = 19;
  grafo[18].colonna = 9;
  grafo[18].indice = 18;
  grafo[18].n_sx = -1;
  grafo[18].n_dx = 19;
  grafo[18].n_su = 15;
  grafo[18].n_giu = 21;

  grafo[19].riga = 19;
  grafo[19].colonna = 18;
  grafo[19].indice = 19;
  grafo[19].n_sx = 18;
  grafo[19].n_dx = -1;
  grafo[19].n_su = 16;
  grafo[19].n_giu = 22;

  grafo[20].riga = 22;
  grafo[20].colonna = 6;
  grafo[20].indice = 20;
  grafo[20].n_sx = 30;
  grafo[20].n_dx = 21;
  grafo[20].n_su = 14;
  grafo[20].n_giu = 24;

   grafo[21].riga = 22;
  grafo[21].colonna = 9;
  grafo[21].indice = 21;
  grafo[21].n_sx = 20;
  grafo[21].n_dx = 26;
  grafo[21].n_su = 18;
  grafo[21].n_giu = -1;

  grafo[22].riga = 22;
  grafo[22].colonna = 18;
  grafo[22].indice = 22;
  grafo[22].n_sx = 27;
  grafo[22].n_dx = 23;
  grafo[22].n_su = 19;
  grafo[22].n_giu = -1;

  grafo[23].riga = 22;
  grafo[23].colonna = 21;
  grafo[23].indice = 23;
  grafo[23].n_sx = 22;
  grafo[23].n_dx = 31;
  grafo[23].n_su = 17;
  grafo[23].n_giu = 29;

  grafo[24].riga = 25;
  grafo[24].colonna = 6;
  grafo[24].indice = 24;
  grafo[24].n_sx = -1;
  grafo[24].n_dx = 25;
  grafo[24].n_su = 20;
  grafo[24].n_giu = 30;

  grafo[25].riga = 25;
  grafo[25].colonna = 9;
  grafo[25].indice = 25;
  grafo[25].n_sx = 24;
  grafo[25].n_dx = 26;
  grafo[25].n_su = -1;
  grafo[25].n_giu = 32;

  grafo[26].riga = 25;
  grafo[26].colonna = 12;
  grafo[26].indice = 26;
  grafo[26].n_sx = 25;
  grafo[26].n_dx = 27;
  grafo[26].n_su = 21;
  grafo[26].n_giu = -1;

  grafo[27].riga = 25;
  grafo[27].colonna = 15;
  grafo[27].indice = 27;
  grafo[27].n_sx = 26;
  grafo[27].n_dx = 28;
  grafo[27].n_su = 22;
  grafo[27].n_giu = -1;

  grafo[28].riga = 25;
  grafo[28].colonna = 18;
  grafo[28].indice = 28;
  grafo[28].n_sx = 27;
  grafo[28].n_dx = 29;
  grafo[28].n_su = -1;
  grafo[28].n_giu = 33;

  grafo[29].riga = 25;
  grafo[29].colonna = 21;
  grafo[29].indice = 29;
  grafo[29].n_sx = 28;
  grafo[29].n_dx = -1;
  grafo[29].n_su = 23;
  grafo[29].n_giu = 31;

  grafo[30].riga = 28;
  grafo[30].colonna = 3;
  grafo[30].indice = 30;
  grafo[30].n_sx = 32;
  grafo[30].n_dx = 24;
  grafo[30].n_su = 20;
  grafo[30].n_giu = -1;

  grafo[31].riga = 28;
  grafo[31].colonna = 24;
  grafo[31].indice = 31;
  grafo[31].n_sx = 29;
  grafo[31].n_dx = 33;
  grafo[31].n_su = 23;
  grafo[31].n_giu = -1;

  grafo[32].riga = 31;
  grafo[32].colonna = 12;
  grafo[32].indice = 32;
  grafo[32].n_sx = 30;
  grafo[32].n_dx = 33;
  grafo[32].n_su = 25;
  grafo[32].n_giu = -1;

  grafo[33].riga = 31;
  grafo[33].colonna = 15;
  grafo[33].indice = 33;
  grafo[33].n_sx = 32;
  grafo[33].n_dx = 31;
  grafo[33].n_su = 28;
  grafo[33].n_giu = -1;
  
}

/*__________________________________________________________
 *|
 *| Torna l'indice del nodo presente in (riga, colonna)
 *| Se non è presente alcun nodo (il fantasma è su un ramo)
 *| torna -1
 */
int indice_nodo_cella(int riga, int col)
{
  for(int i=0; i<34;i++)
    {
      if(grafo[i].colonna == col && grafo[i].riga == riga)
        return grafo[i].indice;
    }
  return -1;
}

int main(int argc, char * argv[])
{
  int s = atoi(argv[1]);
  int g = atoi(argv[2]);
  collega_nodi();
  Percorso pc = A_star(s,g);
 while(*pc>=0)
    {
      printf("->%d\n",*pc);
      pc++;
    }
  
}
