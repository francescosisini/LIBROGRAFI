#include "libagri.h"
#include <stdio.h>

int main()
{
  //Il grafo
  agri_Colligationes_Colligatae g = 0;

  //un edge
  agri_Colligatio colligatio;
  //due vertici
  agri_Vertex v_a, v_da;

  //iniizializzo vertici
  v_a.index = 2;
  v_a.linea = 2;
  v_a.columna = 2;
  
  v_da.index = 1;
  v_da.linea = 1;
  v_da.columna = 1;

  //Li collego
  colligatio.ad = v_a;
  colligatio.ab = v_da;
  colligatio.longitudo = 5;
  colligatio.meta = SX;
  colligatio.discessus = DX;
  agri_Colligationem_insero(&g, colligatio);

  //Inizializzo nuovo vertice
   v_a.index = 3;
  v_a.linea = 3;
  v_a.columna = 3;
  
  v_da.index = 4;
  v_da.linea = 4;
  v_da.columna = 4;

  //Li collego
  colligatio.ad = v_a;
  colligatio.ab = v_da;
  colligatio.longitudo = 5;
  colligatio.meta = DX;
  colligatio.discessus = SX;
  agri_Colligationem_insero(&g, colligatio);

  //Inizializzo nuovo vertice
   //Inizializzo nuovo vertice
   v_a.index = 3;
  v_a.linea = 3;
  v_a.columna = 3;
  
  v_da.index = 1;
  v_da.linea = 1;
  v_da.columna = 2;

  //Li collego
  colligatio.ad = v_a;
  colligatio.ab = v_da;
  colligatio.longitudo = 5;
  colligatio.meta = -1;
  colligatio.discessus = -1;
  agri_Colligationem_insero(&g, colligatio);




  
  
  agri_Colligationes_Colligatae array;
  int n = agri_dispono(g , &array);

  agri_Verticum_Dispositio d;
  int s = agri_muto(g,&d);
  for(int i=0; i<s;i++)
    {
      printf("inx %d\n",d[i].index);
    }
  
  for(int i = 0; i<n;i++)
    {
      printf("%d; %d:%d\n",n,g->colligatio.ad.linea,array[i].colligatio.ad.linea);
      g = g->next;
    }
  
      
}
