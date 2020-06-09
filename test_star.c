#include "tuki5_modello.h"
#include "libagri.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#define PORTE 10
#define INFINITO 9999
#define NNODI 34


/*___________________________________________________________
 *|
 *| I nodi del grafo del labirinto
 */
agri_Vertex agri_Vertices_Colligati[NNODI];


double euristica_h(int start, int goal)
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



void Ordo_stampa(Ordo c)
{
  while(c)
    {
      printf(" Nodus %d, fscore %lf\n",c->index,c->prio);
      c = c->post;
    }
}

double distanza_esatta(int da_nodus, int a_nodus)
{
  int s = da_nodus;
  int g = a_nodus;
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
  agri_Vertices_Colligati[0].linea = 3;
  agri_Vertices_Colligati[0].columna = 6;
  agri_Vertices_Colligati[0].index = 0;
  agri_Vertices_Colligati[0].ianua[0] = 2;
  agri_Vertices_Colligati[0].ianua[1] = 5;
  agri_Vertices_Colligati[0].ianua[2] = -1;
  agri_Vertices_Colligati[0].ianua[3] = 3;

  agri_Vertices_Colligati[1].linea = 3;
  agri_Vertices_Colligati[1].columna = 21;
  agri_Vertices_Colligati[1].index = 1;
  agri_Vertices_Colligati[1].ianua[0] = 6;
  agri_Vertices_Colligati[1].ianua[1] = 9;
  agri_Vertices_Colligati[1].ianua[2] = -1;
  agri_Vertices_Colligati[1].ianua[3] = 8;

  agri_Vertices_Colligati[2].linea = 7;
  agri_Vertices_Colligati[2].columna = 1;
  agri_Vertices_Colligati[2].index = 2;
  agri_Vertices_Colligati[2].ianua[0] = -1;
  agri_Vertices_Colligati[2].ianua[1] = 3;
  agri_Vertices_Colligati[2].ianua[2] = 0;
  agri_Vertices_Colligati[2].ianua[3] = 10;

  agri_Vertices_Colligati[3].linea = 7;
  agri_Vertices_Colligati[3].columna = 6;
  agri_Vertices_Colligati[3].index = 3;
  agri_Vertices_Colligati[3].ianua[0] = 2;
  agri_Vertices_Colligati[3].ianua[1] = 4;
  agri_Vertices_Colligati[3].ianua[2] = 0;
  agri_Vertices_Colligati[3].ianua[3] = 10;

  agri_Vertices_Colligati[4].linea = 7;
  agri_Vertices_Colligati[4].columna = 9;
  agri_Vertices_Colligati[4].index = 4;
  agri_Vertices_Colligati[4].ianua[0] = 3;
  agri_Vertices_Colligati[4].ianua[1] = 5;
  agri_Vertices_Colligati[4].ianua[2] = -1;
  agri_Vertices_Colligati[4].ianua[3] = 12;

  agri_Vertices_Colligati[5].linea = 7;
  agri_Vertices_Colligati[5].columna = 12;
  agri_Vertices_Colligati[5].index = 5;
  agri_Vertices_Colligati[5].ianua[0] = 4;
  agri_Vertices_Colligati[5].ianua[1] = 6;
  agri_Vertices_Colligati[5].ianua[2] = 0;
  agri_Vertices_Colligati[5].ianua[3] = -1;

  agri_Vertices_Colligati[6].linea = 7;
  agri_Vertices_Colligati[6].columna = 15;
  agri_Vertices_Colligati[6].index = 6;
  agri_Vertices_Colligati[6].ianua[0] = 5;
  agri_Vertices_Colligati[6].ianua[1] = 7;
  agri_Vertices_Colligati[6].ianua[2] = 1;
  agri_Vertices_Colligati[6].ianua[3] = -1;

  agri_Vertices_Colligati[7].linea = 7;
  agri_Vertices_Colligati[7].columna = 18;
  agri_Vertices_Colligati[7].index = 7;
  agri_Vertices_Colligati[7].ianua[0] = 6;
  agri_Vertices_Colligati[7].ianua[1] = 8;
  agri_Vertices_Colligati[7].ianua[2] = -1;
  agri_Vertices_Colligati[7].ianua[3] = 13;

  agri_Vertices_Colligati[8].linea = 7;
  agri_Vertices_Colligati[8].columna = 21;
  agri_Vertices_Colligati[8].index = 8;
  agri_Vertices_Colligati[8].ianua[0] = 7;
  agri_Vertices_Colligati[8].ianua[1] = 9;
  agri_Vertices_Colligati[8].ianua[2] = 1;
  agri_Vertices_Colligati[8].ianua[3] = 11;

  agri_Vertices_Colligati[9].linea = 7;
  agri_Vertices_Colligati[9].columna = 26;
  agri_Vertices_Colligati[9].index = 9;
  agri_Vertices_Colligati[9].ianua[0] = 8;
  agri_Vertices_Colligati[9].ianua[1] = -1;
  agri_Vertices_Colligati[9].ianua[2] = 1;
  agri_Vertices_Colligati[9].ianua[3] = 11;

  agri_Vertices_Colligati[10].linea = 10;
  agri_Vertices_Colligati[10].columna = 6;
  agri_Vertices_Colligati[10].index = 10;
  agri_Vertices_Colligati[10].ianua[0] = 2;
  agri_Vertices_Colligati[10].ianua[1] = -1;
  agri_Vertices_Colligati[10].ianua[2] = 3;
  agri_Vertices_Colligati[10].ianua[3] = 14;

  agri_Vertices_Colligati[11].linea = 10;
  agri_Vertices_Colligati[11].columna = 21;
  agri_Vertices_Colligati[11].index = 11;
  agri_Vertices_Colligati[11].ianua[0] = -1;
  agri_Vertices_Colligati[11].ianua[1] = 9;
  agri_Vertices_Colligati[11].ianua[2] = 8;
  agri_Vertices_Colligati[11].ianua[3] = 17;

  agri_Vertices_Colligati[12].linea = 13;
  agri_Vertices_Colligati[12].columna = 12;
  agri_Vertices_Colligati[12].index = 12;
  agri_Vertices_Colligati[12].ianua[0] = 15;
  agri_Vertices_Colligati[12].ianua[1] = 13;
  agri_Vertices_Colligati[12].ianua[2] = 4;
  agri_Vertices_Colligati[12].ianua[3] = -1;

  agri_Vertices_Colligati[13].linea = 13;
  agri_Vertices_Colligati[13].columna = 15;
  agri_Vertices_Colligati[13].index = 13;
  agri_Vertices_Colligati[13].ianua[0] = 12;
  agri_Vertices_Colligati[13].ianua[1] = 16;
  agri_Vertices_Colligati[13].ianua[2] = 7;
  agri_Vertices_Colligati[13].ianua[3] = -1;

  agri_Vertices_Colligati[14].linea = 16;
  agri_Vertices_Colligati[14].columna = 6;
  agri_Vertices_Colligati[14].index = 14;
  agri_Vertices_Colligati[14].ianua[0] = -1;
  agri_Vertices_Colligati[14].ianua[1] = 15;
  agri_Vertices_Colligati[14].ianua[2] = 10;
  agri_Vertices_Colligati[14].ianua[3] = 20;

  agri_Vertices_Colligati[15].linea = 16;
  agri_Vertices_Colligati[15].columna = 9;
  agri_Vertices_Colligati[15].index = 15;
  agri_Vertices_Colligati[15].ianua[0] = 14;
  agri_Vertices_Colligati[15].ianua[1] = -1;
  agri_Vertices_Colligati[15].ianua[2] = 12;
  agri_Vertices_Colligati[15].ianua[3] = 18;

  agri_Vertices_Colligati[16].linea = 16;
  agri_Vertices_Colligati[16].columna = 18;
  agri_Vertices_Colligati[16].index = 16;
  agri_Vertices_Colligati[16].ianua[0] = -1;
  agri_Vertices_Colligati[16].ianua[1] = 17;
  agri_Vertices_Colligati[16].ianua[2] = 13;
  agri_Vertices_Colligati[16].ianua[3] = 19;

  agri_Vertices_Colligati[17].linea = 16;
  agri_Vertices_Colligati[17].columna = 21;
  agri_Vertices_Colligati[17].index = 17;
  agri_Vertices_Colligati[17].ianua[0] = 16;
  agri_Vertices_Colligati[17].ianua[1] = -1;
  agri_Vertices_Colligati[17].ianua[2] = 11;
  agri_Vertices_Colligati[17].ianua[3] = 23;

  agri_Vertices_Colligati[18].linea = 19;
  agri_Vertices_Colligati[18].columna = 9;
  agri_Vertices_Colligati[18].index = 18;
  agri_Vertices_Colligati[18].ianua[0] = -1;
  agri_Vertices_Colligati[18].ianua[1] = 19;
  agri_Vertices_Colligati[18].ianua[2] = 15;
  agri_Vertices_Colligati[18].ianua[3] = 21;

  agri_Vertices_Colligati[19].linea = 19;
  agri_Vertices_Colligati[19].columna = 18;
  agri_Vertices_Colligati[19].index = 19;
  agri_Vertices_Colligati[19].ianua[0] = 18;
  agri_Vertices_Colligati[19].ianua[1] = -1;
  agri_Vertices_Colligati[19].ianua[2] = 16;
  agri_Vertices_Colligati[19].ianua[3] = 22;

  agri_Vertices_Colligati[20].linea = 22;
  agri_Vertices_Colligati[20].columna = 6;
  agri_Vertices_Colligati[20].index = 20;
  agri_Vertices_Colligati[20].ianua[0] = 30;
  agri_Vertices_Colligati[20].ianua[1] = 21;
  agri_Vertices_Colligati[20].ianua[2] = 14;
  agri_Vertices_Colligati[20].ianua[3] = 24;

   agri_Vertices_Colligati[21].linea = 22;
  agri_Vertices_Colligati[21].columna = 9;
  agri_Vertices_Colligati[21].index = 21;
  agri_Vertices_Colligati[21].ianua[0] = 20;
  agri_Vertices_Colligati[21].ianua[1] = 26;
  agri_Vertices_Colligati[21].ianua[2] = 18;
  agri_Vertices_Colligati[21].ianua[3] = -1;

  agri_Vertices_Colligati[22].linea = 22;
  agri_Vertices_Colligati[22].columna = 18;
  agri_Vertices_Colligati[22].index = 22;
  agri_Vertices_Colligati[22].ianua[0] = 27;
  agri_Vertices_Colligati[22].ianua[1] = 23;
  agri_Vertices_Colligati[22].ianua[2] = 19;
  agri_Vertices_Colligati[22].ianua[3] = -1;

  agri_Vertices_Colligati[23].linea = 22;
  agri_Vertices_Colligati[23].columna = 21;
  agri_Vertices_Colligati[23].index = 23;
  agri_Vertices_Colligati[23].ianua[0] = 22;
  agri_Vertices_Colligati[23].ianua[1] = 31;
  agri_Vertices_Colligati[23].ianua[2] = 17;
  agri_Vertices_Colligati[23].ianua[3] = 29;

  agri_Vertices_Colligati[24].linea = 25;
  agri_Vertices_Colligati[24].columna = 6;
  agri_Vertices_Colligati[24].index = 24;
  agri_Vertices_Colligati[24].ianua[0] = -1;
  agri_Vertices_Colligati[24].ianua[1] = 25;
  agri_Vertices_Colligati[24].ianua[2] = 20;
  agri_Vertices_Colligati[24].ianua[3] = 30;

  agri_Vertices_Colligati[25].linea = 25;
  agri_Vertices_Colligati[25].columna = 9;
  agri_Vertices_Colligati[25].index = 25;
  agri_Vertices_Colligati[25].ianua[0] = 24;
  agri_Vertices_Colligati[25].ianua[1] = 26;
  agri_Vertices_Colligati[25].ianua[2] = -1;
  agri_Vertices_Colligati[25].ianua[3] = 32;

  agri_Vertices_Colligati[26].linea = 25;
  agri_Vertices_Colligati[26].columna = 12;
  agri_Vertices_Colligati[26].index = 26;
  agri_Vertices_Colligati[26].ianua[0] = 25;
  agri_Vertices_Colligati[26].ianua[1] = 27;
  agri_Vertices_Colligati[26].ianua[2] = 21;
  agri_Vertices_Colligati[26].ianua[3] = -1;

  agri_Vertices_Colligati[27].linea = 25;
  agri_Vertices_Colligati[27].columna = 15;
  agri_Vertices_Colligati[27].index = 27;
  agri_Vertices_Colligati[27].ianua[0] = 26;
  agri_Vertices_Colligati[27].ianua[1] = 28;
  agri_Vertices_Colligati[27].ianua[2] = 22;
  agri_Vertices_Colligati[27].ianua[3] = -1;

  agri_Vertices_Colligati[28].linea = 25;
  agri_Vertices_Colligati[28].columna = 18;
  agri_Vertices_Colligati[28].index = 28;
  agri_Vertices_Colligati[28].ianua[0] = 27;
  agri_Vertices_Colligati[28].ianua[1] = 29;
  agri_Vertices_Colligati[28].ianua[2] = -1;
  agri_Vertices_Colligati[28].ianua[3] = 33;

  agri_Vertices_Colligati[29].linea = 25;
  agri_Vertices_Colligati[29].columna = 21;
  agri_Vertices_Colligati[29].index = 29;
  agri_Vertices_Colligati[29].ianua[0] = 28;
  agri_Vertices_Colligati[29].ianua[1] = -1;
  agri_Vertices_Colligati[29].ianua[2] = 23;
  agri_Vertices_Colligati[29].ianua[3] = 31;

  agri_Vertices_Colligati[30].linea = 28;
  agri_Vertices_Colligati[30].columna = 3;
  agri_Vertices_Colligati[30].index = 30;
  agri_Vertices_Colligati[30].ianua[0] = 32;
  agri_Vertices_Colligati[30].ianua[1] = 24;
  agri_Vertices_Colligati[30].ianua[2] = 20;
  agri_Vertices_Colligati[30].ianua[3] = -1;

  agri_Vertices_Colligati[31].linea = 28;
  agri_Vertices_Colligati[31].columna = 24;
  agri_Vertices_Colligati[31].index = 31;
  agri_Vertices_Colligati[31].ianua[0] = 29;
  agri_Vertices_Colligati[31].ianua[1] = 33;
  agri_Vertices_Colligati[31].ianua[2] = 23;
  agri_Vertices_Colligati[31].ianua[3] = -1;

  agri_Vertices_Colligati[32].linea = 31;
  agri_Vertices_Colligati[32].columna = 12;
  agri_Vertices_Colligati[32].index = 32;
  agri_Vertices_Colligati[32].ianua[0] = 30;
  agri_Vertices_Colligati[32].ianua[1] = 33;
  agri_Vertices_Colligati[32].ianua[2] = 25;
  agri_Vertices_Colligati[32].ianua[3] = -1;

  agri_Vertices_Colligati[33].linea = 31;
  agri_Vertices_Colligati[33].columna = 15;
  agri_Vertices_Colligati[33].index = 33;
  agri_Vertices_Colligati[33].ianua[0] = 32;
  agri_Vertices_Colligati[33].ianua[1] = 31;
  agri_Vertices_Colligati[33].ianua[2] = 28;
  agri_Vertices_Colligati[33].ianua[3] = -1;
  
}


int main(int argc, char * argv[])
{
  int s = atoi(argv[1]);
  int g = atoi(argv[2]);
  collega_nodi();
  agri_Via pc = agri_astar(s,g,agri_Vertices_Colligati,&distanza_esatta,&euristica_h);
 while(*pc>=0)
    {
      printf("->%d\n",*pc);
      pc++;
    }
  
}
