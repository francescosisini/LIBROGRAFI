#include "tuki5_modello.h"
#include "libagri.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#define PORTE 10
#define INFINITO 9999
#define NODI_LAB_POT 44


/*___________________________________________________________
 *|
 *| I nodi del grafo del labirinto
 */
agri_Vertex grafo[NNODI];
int b_iter[]={13,12,15,14,17,14,15,12,15,14,20,21,18,15,14,20};
int p_iter[]={12,13,16,19,22,23,17,11,8,7,6,5,4,3,2,0};
int passo;


double euristica_h(int start, int goal)
{
  int x1,x2,y1,y2;
  double d;
  x1 = grafo[start].columna;
  y1 = grafo[start].linea;
  x2 = grafo[goal].columna;
  y2 = grafo[goal].linea;
  //Euristica uguale al quadrato della distanza euclidea
  d = (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);
  /*
  if(start == 15)
    {
      return 200;
    }
  */
  if(grafo[b_iter[passo]].ianua[SINISTRA] == start ||
     grafo[b_iter[passo]].ianua[DESTRA] == start ||
     grafo[b_iter[passo]].ianua[SU] == start ||
     grafo[b_iter[passo]].ianua[GIU] == start)
    {
      return 300;
    }

  if(grafo[p_iter[passo]].ianua[SINISTRA] == start ||
     grafo[p_iter[passo]].ianua[DESTRA] == start ||
     grafo[p_iter[passo]].ianua[SU] == start ||
     grafo[p_iter[passo]].ianua[GIU] == start)
    {
      return 225;
    }
  
  
  return sqrt(d);
}



void Ordo_stampa(Ordo c)
{
  while(c)
    {
      printf(" Nodus %d, fscore %lf\n",c->index,c->prio);
      c = c->post;
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
      distanze[21][20]=2;
      
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

      distanze[34][0]=4;
      distanze[0][34]=4;

      distanze[34][2]=3;
      distanze[2][34]=3;

      distanze[35][0]=5;
      distanze[0][35]=5;

      distanze[35][5]=3;
      distanze[5][35]=3;

      distanze[36][1]=5;
      distanze[1][36]=5;

      distanze[36][6]=3;
      distanze[6][36]=3;

      distanze[37][1]=4;
      distanze[1][37]=4;

      distanze[37][9]=3;
      distanze[9][37]=3;

      distanze[38][2]=2;
      distanze[2][38]=2;

      distanze[38][10]=4;
      distanze[10][38]=4;

      distanze[39][9]=2;
      distanze[9][39]=2;

      distanze[39][11]=4;
      distanze[11][39]=4;

      distanze[40][20]=4;
      distanze[20][40]=4;

      distanze[40][30]=7;
      distanze[30][40]=7;

      distanze[41][23]=4;
      distanze[23][41]=4;

      distanze[41][31]=7;
      distanze[31][41]=7;

      distanze[42][30]=4;
      distanze[30][42]=4;

      distanze[42][32]=10;
      distanze[32][42]=10;

      distanze[43][31]=4;
      distanze[31][43]=4;

      distanze[43][33]=10;
      distanze[33][43]=10;

      init=1;
    }
  return (double)distanze[s][g];
}

/*
  ITA: Crea un grafo corrispondente al labirinto di Pac-Man
  ENG: Create a graph corresponding to the maze of Pac-Man
 */
void collega_tuki_nodi()
{
  static int cam[]=
    {
      3,10,38,2,34,0,3,2,3,0,35,5,4,3,4,12,13,
      7,6,5,6,36,1,8,7,8,1,37,9,39,11,39,9,8,11,17,
      16,13,12,15,14,17,23,22,19,16,19,15,
      21,40,20,14,20,40,30,42,32,33,43,31,41,
      23,29,31,29,28,33,28,27,22,27,26,21,26,
      25,32,25,24,20,24,30
    };
  
  int *cammino = cam;
  
  grafo[0].linea = 3;
  grafo[0].columna = 6;
  grafo[0].index = 0;
  grafo[0].ianua[SINISTRA] = 34;
  grafo[0].ianua[DESTRA] = 35;
  grafo[0].ianua[SU] = -1;
  grafo[0].ianua[GIU] = 3;
  
  grafo[1].linea = 3;
  grafo[1].columna = 21;
  grafo[1].index = 1;
  grafo[1].ianua[SINISTRA] = 36;
  grafo[1].ianua[DESTRA] = 37;
  grafo[1].ianua[SU] = -1;
  grafo[1].ianua[GIU] = 8;

  grafo[2].linea = 7;
  grafo[2].columna = 1;
  grafo[2].index = 2;
  grafo[2].ianua[SINISTRA] = -1;
  grafo[2].ianua[DESTRA] = 3;
  grafo[2].ianua[SU] = 34;
  grafo[2].ianua[GIU] = 38;

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
  grafo[5].ianua[SU] = 35;
  grafo[5].ianua[GIU] = -1;

  grafo[6].linea = 7;
  grafo[6].columna = 15;
  grafo[6].index = 6;
  grafo[6].ianua[SINISTRA] = 5;
  grafo[6].ianua[DESTRA] = 7;
  grafo[6].ianua[SU] = 36;
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
  grafo[9].ianua[SU] = 37;
  grafo[9].ianua[GIU] = 39;
  
  grafo[10].linea = 10;
  grafo[10].columna = 6;
  grafo[10].index = 10;
  grafo[10].ianua[SINISTRA] = 38;
  grafo[10].ianua[DESTRA] = -1;
  grafo[10].ianua[SU] = 3;
  grafo[10].ianua[GIU] = 14;

  grafo[11].linea = 10;
  grafo[11].columna = 21;
  grafo[11].index = 11;
  grafo[11].ianua[SINISTRA] = -1;
  grafo[11].ianua[DESTRA] = 39;
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
  grafo[20].ianua[SINISTRA] = 40;
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
  grafo[23].ianua[DESTRA] = 41;
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
  grafo[30].ianua[SINISTRA] = 42;
  grafo[30].ianua[DESTRA] = 24;
  grafo[30].ianua[SU] = 40;
  grafo[30].ianua[GIU] = -1;

  grafo[31].linea = 28;
  grafo[31].columna = 24;
  grafo[31].index = 31;
  grafo[31].ianua[SINISTRA] = 29;
  grafo[31].ianua[DESTRA] = 43;
  grafo[31].ianua[SU] = 41;
  grafo[31].ianua[GIU] = -1;

  grafo[32].linea = 31;
  grafo[32].columna = 12;
  grafo[32].index = 32;
  grafo[32].ianua[SINISTRA] = 42;
  grafo[32].ianua[DESTRA] = 33;
  grafo[32].ianua[SU] = 25;
  grafo[32].ianua[GIU] = -1;

  grafo[33].linea = 31;
  grafo[33].columna = 15;
  grafo[33].index = 33;
  grafo[33].ianua[SINISTRA] = 32;
  grafo[33].ianua[DESTRA] = 43;
  grafo[33].ianua[SU] = 28;
  grafo[33].ianua[GIU] = -1;

  grafo[34].linea = 3;
  grafo[34].columna = 1;
  grafo[34].index = 34;
  grafo[34].ianua[SINISTRA] = -1;
  grafo[34].ianua[DESTRA] = 0;
  grafo[34].ianua[SU] = -1;
  grafo[34].ianua[GIU] = 2;

  grafo[35].linea = 3;
  grafo[35].columna = 12;
  grafo[35].index = 35;
  grafo[35].ianua[SINISTRA] = 0;
  grafo[35].ianua[DESTRA] = -1;
  grafo[35].ianua[SU] = -1;
  grafo[35].ianua[GIU] = 5;

  grafo[36].linea = 3;
  grafo[36].columna = 15;
  grafo[36].index = 36;
  grafo[36].ianua[SINISTRA] = -1;
  grafo[36].ianua[DESTRA] = 1;
  grafo[36].ianua[SU] = -1;
  grafo[36].ianua[GIU] = 6;

  grafo[37].linea = 3;
  grafo[37].columna = 26;
  grafo[37].index = 37;
  grafo[37].ianua[SINISTRA] = 1;
  grafo[37].ianua[DESTRA] = -1;
  grafo[37].ianua[SU] = -1;
  grafo[37].ianua[GIU] = 9;

  grafo[38].linea = 10;
  grafo[38].columna = 1;
  grafo[38].index = 38;
  grafo[38].ianua[SINISTRA] = -1;
  grafo[38].ianua[DESTRA] = 10;
  grafo[38].ianua[SU] = 2;
  grafo[38].ianua[GIU] = -1;

  grafo[39].linea = 10;
  grafo[39].columna = 26;
  grafo[39].index = 39;
  grafo[39].ianua[SINISTRA] = 11;
  grafo[39].ianua[DESTRA] = -1;
  grafo[39].ianua[SU] = 9;
  grafo[39].ianua[GIU] = -1;

  grafo[40].linea = 22;
  grafo[40].columna = 1;
  grafo[40].index = 40;
  grafo[40].ianua[SINISTRA] = -1;
  grafo[40].ianua[DESTRA] = 20;
  grafo[40].ianua[SU] = -1;
  grafo[40].ianua[GIU] = 30;

  grafo[41].linea = 22;
  grafo[41].columna = 26;
  grafo[41].index = 41;
  grafo[41].ianua[SINISTRA] = 23;
  grafo[41].ianua[DESTRA] = -1;
  grafo[41].ianua[SU] = -1;
  grafo[41].ianua[GIU] = 31;

  grafo[42].linea = 31;
  grafo[42].columna = 1;
  grafo[42].index = 42;
  grafo[42].ianua[SINISTRA] = -1;
  grafo[42].ianua[DESTRA] = 32;
  grafo[42].ianua[SU] = 30;
  grafo[42].ianua[GIU] = -1;

  grafo[43].linea = 31;
  grafo[43].columna = 26;
  grafo[43].index = 43;
  grafo[43].ianua[SINISTRA] = 33;
  grafo[43].ianua[DESTRA] = -1;
  grafo[43].ianua[SU] = 31;
  grafo[43].ianua[GIU] = -1;
}

/*_______________________________
 * 
 * MAIN 1
 */
/*
int main(int argc, char * argv[])
{

  int s = atoi(argv[1]);
  int g = atoi(argv[2]);

  collega_tuki_nodi();

  agri_Via pc = agri_astar(s,g,grafo,&distanza_esatta,&euristica_h,34);

  while(*pc>=0)
    {
      printf("->%d\n",*pc);
      pc++;
    }
}
*/
/*_______________________________
 * 
 * MAIN 2
 */
 /*
int main(int argc, char * argv[])
{
  int s = atoi(argv[1]);
  int g = atoi(argv[2]);
  
  collega_tuki_nodi();

  while(s != g)
    {
    printf("%d->\t",s);
      agri_Via pc = agri_astar(s,g,grafo,&distanza_esatta,&euristica_h,NODI_LAB_POT);
      s = *pc;
      while(*pc>=0)
	{
	  printf("%d\t",*pc);
	  pc++;
	}
      printf("\n");
    }
}
 */
/*_______________________________
 * 
 * MAIN 3
 */

int main(int argc, char * argv[])
{
  int s = atoi(argv[1]);
  int g = atoi(argv[2]);
  
  collega_tuki_nodi();
  
  while(s != g)
    {

      printf("%d->\t",s);
      agri_Via pc = agri_astar(s,g,grafo,&distanza_esatta,&euristica_h,NODI_LAB_POT);
      s = *pc;
      
      while(*pc>=0)
	{
	  printf("%d\t",*pc);
	  pc++;
	}
      printf(":%d :%d\n",b_iter[passo],p_iter[passo]);
      passo += 1;
    }
}

