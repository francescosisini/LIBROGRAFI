#include "tuki5_modello.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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
 *| I nodi del grafo el labirinto
 */
nodo grafo[34];

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

/*__________________________________________________________
 *|
 *| Una cella del labirinto
 */
typedef struct {
  int riga;
  int colonna;
} cella;

/*_____________________________________________________________
 *|
 *| restituisce la direzione in cui si deve muovere il fantasma
 *| sceliendo tra le due libere quella diversa dalla
 *| cella <precedete>
 *| Il comportamento è deterministico solo se la cella 
 *| corrente non è un nodo del grafo
 */
direzione prossima_cella(cella corrente, cella precedente, oggetto **lab)
{
  int riga = corrente.riga;
  int colonna = corrente.colonna;
  
 /* oggetti ai 4 angoli della cella corrente */
  oggetto o_sx, o_dx, o_su, o_giu;
  o_sx = lab[riga][colonna-1];
  o_dx = lab[riga][colonna+1];
  o_su = lab[riga-1][colonna];
  o_giu = lab[riga+1][colonna];
  
  if(o_sx == J || o_sx == U  || o_sx == V )
    {
      if(precedente.colonna != colonna - 1)
          return SINISTRA;
    }

   if(o_dx == J || o_dx == U || o_dx == V)
    {
      if(precedente.colonna != colonna + 1)
        return DESTRA;
        
    }

    if(o_su == J || o_su == U || o_su == V)
    {
      if(precedente.riga != riga - 1)
        return SU;
    }

    if(o_giu == J || o_giu == U || o_giu == V)
      {
        if(precedente.riga != riga + 1)
          return GIU;
      }
}

/*____________________________________________
 *|
 *| Distanza  tra due celle
 */
double distanza_celle(cella a, cella b)
{
  double d=(a.riga-b.riga)*(a.riga-b.riga)+(a.colonna-b.colonna)*(a.colonna-b.colonna);
  return sqrt(d);
}

direzione gioca_blinky(posizioni p, oggetto **lab)
{
  static int turno = 0;

  static int colonna_old,riga_old;
   
  turno+=1;
    
  /* indica l'edge su cui si sta muovendo il fantasma */
  static nodo nodo_da, nodo_a;

  int riga = p.blinky_y;
  int colonna = p.blinky_x;
 
  direzione ld =  FERMO;
  
  if(turno == 1)
    {
      collega_nodi();
    }

  /* uscita dalla casetta dei fantasmi */
  if(turno<7)
    {
      if(turno<5)
        return SU;

      nodo_a = grafo[12];
      nodo_da = grafo[12];
      
      colonna_old = -1;
      colonna = nodo_a.colonna;

      riga_old = -1;
      riga = nodo_a.riga;
      return SINISTRA;
    }
  
  /* Sono su un nodo? */
  int inx = indice_nodo_cella(riga,colonna);
    
  /* cella su cui si trova e cella precedente */
  cella c, pr;
  c.riga = riga;
  c.colonna = colonna;
  pr.riga = riga_old;
  pr.colonna = colonna_old;
  
  if(inx<0)
    {
      /*________________________________________________ 
       *|  Non sono su un nodo. Il percorso è obbligato 
       *| sono definiti: nodo_da, nodo_a, x e y _old
       *| satbilisce il prossimo passo come l'unico
       *| possibile in modo che non sia ne un muro ne la 
       *| posizione attuale
       */
                 
      ld = prossima_cella(c, pr, lab);

      colonna_old = colonna;
      riga_old = riga;
      
      return ld; 
            
    }
  else
    {
      /*________________________________________________
       *|
       *| Sono su un nodo, devo decidere il prossimo
       *| edge su cui muovermi
       *| se non ci sono stati errori inx ==  nodo_a.indice
       *| in base alla posizione di tuki.
       *| Al termine di questo blocco devo:
       *| nodo_da <- noda_a
       *| nodo_a <- nodo_dest
       */

      if(inx != nodo_a.indice)
        {
          //printf("Ai miei tempi si programmava meglio.\n Mi rifiuto di continuare inx.%d != nodo.%d  riga=%d, colonna=%d\n",inx, nodo_a.indice,riga,colonna);
          
          //exit(0);
        }
      
      /* Nodo temporaneo */
      nodo n_d;

      /* calcola la distanza tra i prossimi nodi e tuki */
      double d_sx = 10000, d_dx = 10000, d_su = 10000, d_giu = 10000;

      cella tuki;
      tuki.riga = p.tuki_y;
      tuki.colonna = p.tuki_x;

      cella s;
      
      if(nodo_a.n_sx >= 0)
        {
          n_d = grafo[nodo_a.n_sx];
          if(n_d.indice != nodo_da.indice && n_d.indice >= 0)
            {
              s.riga = n_d.riga;
              s.colonna = n_d.colonna;
              d_sx = distanza_celle(s, tuki);
            }
        }
      if(nodo_a.n_dx >= 0)
        {
          n_d = grafo[nodo_a.n_dx];
          if(n_d.indice != nodo_da.indice && n_d.indice >= 0)
            {
              s.riga = n_d.riga;
              s.colonna = n_d.colonna;
              d_dx = distanza_celle(s, tuki);
            }
        }
      if(nodo_a.n_su >= 0)
        {
          n_d = grafo[nodo_a.n_su];
          if(n_d.indice != nodo_da.indice && n_d.indice >= 0)
            {
              s.riga = n_d.riga;
              s.colonna = n_d.colonna;
              d_su = distanza_celle(s, tuki);
            }
        }
      if(nodo_a.n_giu >= 0)
        {
          n_d = grafo[nodo_a.n_giu];
          if(n_d.indice != nodo_da.indice && n_d.indice >= 0)
            {
              s.riga = n_d.riga;
              s.colonna = n_d.colonna;
              d_giu = distanza_celle(s, tuki);
            }
        }
          nodo_da =  nodo_a;

      int ind;
      /* cerco il nodo più vicino a tuki */
      if(d_sx<=d_dx && d_sx<=d_su && d_sx<=d_giu)
        {
          ind = nodo_a.n_sx;
          nodo_a = grafo[ind];
          
          ld = SINISTRA;   
        }else if(d_dx<=d_sx && d_dx<=d_su && d_dx<=d_giu)
        {
          ind = nodo_a.n_dx;
          nodo_a = grafo[ind];
          
          ld = DESTRA;
        } else if(d_su<=d_sx && d_su<=d_dx && d_su<=d_giu)
        {
          ind = nodo_a.n_su;
          nodo_a = grafo[ind];
          
          ld = SU;
        } else if(d_giu<=d_sx && d_giu<=d_dx && d_giu<=d_su)
        {
          ind = nodo_a.n_giu;
          
          nodo_a = grafo[ind];
          
          ld = GIU;          
        }
      
      colonna_old = colonna;
      riga_old = riga;

      if(nodo_da.indice == nodo_a.indice)
        {
          //printf("Errore: da %d != a %d direzione: %d",nodo_da.indice,nodo_a.indice,ld);
          //exit(0);
        }
            
      return ld;
     
    }
            
  return ld;
}

direzione gioca_pinky(posizioni p, oggetto **lab)
{

  static int turno = 0;

  static int colonna_old,riga_old;

  static cella tuki, tuki_old;
      
  turno+=1;
    
  /* indica l'edge su cui si sta muovendo il fantasma */
  static nodo nodo_da, nodo_a;

  int riga = p.pinky_y;
  int colonna = p.pinky_x;
 
  direzione ld =  FERMO;
  

  /* uscita dalla casetta dei fantasmi */
  if(turno<5)
    return FERMO;
  if(turno<12 && turno>5)
    {
      if(turno<10)
        return SU;

      nodo_a = grafo[13];
      nodo_da = grafo[13];
      
      colonna_old = -1;
      colonna = nodo_a.colonna;

      riga_old = -1;
      riga = nodo_a.riga;
      return DESTRA;
    }
  
  /* Sono su un nodo? */
  int inx = indice_nodo_cella(riga,colonna);
  
  /* cella su cui si trova e cella precedente */
  cella c, pr;
  c.riga = riga;
  c.colonna = colonna;
  pr.riga = riga_old;
  pr.colonna = colonna_old;
  
  if(inx<0)
    {
      /*________________________________________________ 
       *|  Non sono su un nodo. Il percorso è obbligato 
       *| sono definiti: nodo_da, nodo_a, x e y _old
       *| satbilisce il prossimo passo come l'unico
       *| possibile in modo che non sia ne un muro ne la 
       *| posizione attuale
       */
                 
      ld = prossima_cella(c, pr, lab);

      colonna_old = colonna;
      riga_old = riga;
      
      return ld; 
    }
  else
    {
      /*________________________________________________
       *|
       *| Sono su un nodo, devo decidere il prossimo
       *| edge su cui muovermi
       *| se non ci sono stati errori inx ==  nodo_a.indice
       *| in base alla posizione di tuki.
       *| Al termine di questo blocco devo:
       *| nodo_da <- noda_a
       *| nodo_a <- nodo_dest
       */

      if(inx != nodo_a.indice)
        {
          //printf("Ai miei tempi si programmava meglio.\n Mi rifiuto di continuare inx.%d != nodo.%d  riga=%d, colonna=%d\n",inx, nodo_a.indice,riga,colonna);
          
          //exit(0);
        }
      
      /* Nodo temporaneo */
      nodo n_d;

      /* calcola la distanza tra i prossimi nodi e la cella 4 passi
       avanti a Tuki */
      double d_sx = 10000, d_dx = 10000, d_su = 10000, d_giu = 10000;
      
      cella s;
      tuki.riga = p.tuki_y;
      tuki.colonna = p.tuki_x;

      /* In che direzione muove Tuki?
       * righe o colonne?
       * crescenti o descresceti?
       */
      int d_colonna, d_riga;
      d_colonna = tuki.colonna - tuki_old.colonna;
      d_riga = tuki.riga - tuki_old.riga;
      tuki_old.colonna = tuki.colonna;
      tuki_old.riga = tuki.riga;

      /* stabilisco la cella 4 passi avanti a Tuki */
      if(d_colonna !=0)
        {
          tuki.colonna += 4*d_colonna;
        }
      else if(d_riga != 0)
        {
          tuki.riga += 4*d_riga;
        } 
      else
        {
          tuki.riga = 7;
          tuki.colonna= 6;
        }
      
      if(nodo_a.n_sx >= 0)
        {
          n_d = grafo[nodo_a.n_sx];
          if(n_d.indice != nodo_da.indice && n_d.indice >= 0)
            {
              s.riga = n_d.riga;
              s.colonna = n_d.colonna;
              d_sx = distanza_celle(s, tuki);
            }
        }
      
      if(nodo_a.n_dx >= 0)
        {
          n_d = grafo[nodo_a.n_dx];
          if(n_d.indice != nodo_da.indice && n_d.indice >= 0)
            {
              s.riga = n_d.riga;
              s.colonna = n_d.colonna;
              d_dx = distanza_celle(s, tuki);
            }
        }
      
      if(nodo_a.n_su >= 0)
        {
          n_d = grafo[nodo_a.n_su];
          if(n_d.indice != nodo_da.indice && n_d.indice >= 0)
            {
              s.riga = n_d.riga;
              s.colonna = n_d.colonna;
              d_su = distanza_celle(s, tuki);
            }
        }
      
      if(nodo_a.n_giu >= 0)
        {
          n_d = grafo[nodo_a.n_giu];
          if(n_d.indice != nodo_da.indice && n_d.indice >= 0)
            {
              s.riga = n_d.riga;
              s.colonna = n_d.colonna;
              d_giu = distanza_celle(s, tuki);
            }
        }

      nodo_da =  nodo_a;

      int ind;
      /* cerco il nodo più vicino a tuki */
      if(d_sx<=d_dx && d_sx<=d_su && d_sx<=d_giu)
        {
          ind = nodo_a.n_sx;
          nodo_a = grafo[ind];
          
          ld = SINISTRA;   
        }else if(d_dx<=d_sx && d_dx<=d_su && d_dx<=d_giu)
        {
          ind = nodo_a.n_dx;
          nodo_a = grafo[ind];
         
          ld = DESTRA;
        } else if(d_su<=d_sx && d_su<=d_dx && d_su<=d_giu)
        {
          ind = nodo_a.n_su;
          nodo_a = grafo[ind];
         
          ld = SU;
        } else if(d_giu<=d_sx && d_giu<=d_dx && d_giu<=d_su)
        {
          ind = nodo_a.n_giu;
          
          nodo_a = grafo[ind];
          
          ld = GIU;          
        }
      
      colonna_old = colonna;
      riga_old = riga;

      if(nodo_da.indice == nodo_a.indice)
        {
          printf("Errore: da %d != a %d direzione: %d",nodo_da.indice,nodo_a.indice,ld);
          //exit(0);
        }
        
      return ld;
     
    }
  return ld;
       
}

direzione gioca_inky(posizioni p, oggetto **lab)
{
  static int turno = 0;
  static int colonna_old,riga_old;
  
  turno+=1;
  
  /* indica l'edge su cui si sta muovendo il fantasma */
  static nodo nodo_da, nodo_a;
  
  int riga = p.inky_y;
  int colonna = p.inky_x;
  
  direzione ld =  FERMO;

  /* uscita dalla casetta dei fantasmi */
  if(turno<10)
    return FERMO;
  if(turno<17 && turno>10)
    {
      if(turno<15)
        return SU;
      
      nodo_a = grafo[13];
      nodo_da = grafo[13];
      
      colonna_old = -1;
      colonna = nodo_a.colonna;
      
      riga_old = -1;
      riga = nodo_a.riga;
      return DESTRA;
    }
  
  /* Sono su un nodo? */
  int inx = indice_nodo_cella(riga,colonna);
  
  /* cella su cui si trova e cella precedente */
  cella c, pr;
  c.riga = riga;
  c.colonna = colonna;
  pr.riga = riga_old;
  pr.colonna = colonna_old;
  
  if(inx<0)
    {
      /*________________________________________________ 
       *|  Non sono su un nodo. Il percorso è obbligato 
       *| sono definiti: nodo_da, nodo_a, x e y _old
       *| satbilisce il prossimo passo come l'unico
       *| possibile in modo che non sia ne un muro ne la 
       *| posizione attuale
       */
                 
      ld = prossima_cella(c, pr, lab);

      colonna_old = colonna;
      riga_old = riga;
      
      return ld; 
    }
  else
    {
      /*________________________________________________
       *|
       *| Sono su un nodo, devo decidere il prossimo
       *| edge su cui muovermi
       *| se non ci sono stati errori inx ==  nodo_a.indice
       *| in base alla posizione di tuki.
       *| Al termine di questo blocco devo:
       *| nodo_da <- noda_a
       *| nodo_a <- nodo_dest
       */

      if(inx != nodo_a.indice)
        {
          //printf("Ai miei tempi si programmava meglio.\n Mi rifiuto di continuare inx.%d != nodo.%d  riga=%d, colonna=%d\n",inx, nodo_a.indice,riga,colonna);
          
          //exit(0);
        }
      
      /* Nodo temporaneo */
      nodo n_d;

      /* calcola la distanza tra i prossimi nodi e la cella intermedia 
         tra Tuki e Blinky */
      double d_sx = 10000, d_dx = 10000, d_su = 10000, d_giu = 10000;
      
      cella s;
      cella tuki, blinky;
      tuki.riga = p.tuki_y;
      tuki.colonna = p.tuki_x;
      blinky.riga = p.blinky_y;
      blinky.colonna = p.blinky_x;
      
      int m_colonna, m_riga;
      m_colonna = (tuki.colonna + blinky.colonna)/2;
      m_riga = (tuki.riga + blinky.riga)/2;
      
      /* stabilisco la cella tra Tuki e Blinky */

      tuki.riga = m_riga;
      tuki.colonna = m_colonna;
      
      if(nodo_a.n_sx >= 0)
        {
          n_d = grafo[nodo_a.n_sx];
          if(n_d.indice != nodo_da.indice && n_d.indice >= 0)
            {
              s.riga = n_d.riga;
              s.colonna = n_d.colonna;
              d_sx = distanza_celle(s, tuki);
            }
        }
      
      if(nodo_a.n_dx >= 0)
        {
          n_d = grafo[nodo_a.n_dx];
          if(n_d.indice != nodo_da.indice && n_d.indice >= 0)
            {
              s.riga = n_d.riga;
              s.colonna = n_d.colonna;
              d_dx = distanza_celle(s, tuki);
            }
        }
      
      if(nodo_a.n_su >= 0)
        {
          n_d = grafo[nodo_a.n_su];
          if(n_d.indice != nodo_da.indice && n_d.indice >= 0)
            {
              s.riga = n_d.riga;
              s.colonna = n_d.colonna;
              d_su = distanza_celle(s, tuki);
            }
        }
      
      if(nodo_a.n_giu >= 0)
        {
          n_d = grafo[nodo_a.n_giu];
          if(n_d.indice != nodo_da.indice && n_d.indice >= 0)
            {
              s.riga = n_d.riga;
              s.colonna = n_d.colonna;
              d_giu = distanza_celle(s, tuki);
            }
        }

      nodo_da =  nodo_a;

      int ind;
      /* cerco il nodo più vicino a tuki */
      if(d_sx<=d_dx && d_sx<=d_su && d_sx<=d_giu)
        {
          ind = nodo_a.n_sx;
          nodo_a = grafo[ind];
          
          ld = SINISTRA;   
        }else if(d_dx<=d_sx && d_dx<=d_su && d_dx<=d_giu)
        {
          ind = nodo_a.n_dx;
          nodo_a = grafo[ind];
         
          ld = DESTRA;
        } else if(d_su<=d_sx && d_su<=d_dx && d_su<=d_giu)
        {
          ind = nodo_a.n_su;
          nodo_a = grafo[ind];
         
          ld = SU;
        } else if(d_giu<=d_sx && d_giu<=d_dx && d_giu<=d_su)
        {
          ind = nodo_a.n_giu;
          
          nodo_a = grafo[ind];
          
          ld = GIU;          
        }
      
      colonna_old = colonna;
      riga_old = riga;

      if(nodo_da.indice == nodo_a.indice)
        {
          printf("Errore: da %d != a %d direzione: %d",nodo_da.indice,nodo_a.indice,ld);
          //exit(0);
        }
        
      return ld;
    }
  return ld;
}

direzione gioca_clyde(posizioni p, oggetto **lab)
{
  static int turno = 0;
  
  static int colonna_old,riga_old;
  
  turno+=1;
  
  /* indica l'edge su cui si sta muovendo il fantasma */
  static nodo nodo_da, nodo_a;
  
  int riga = p.clyde_y;
  int colonna = p.clyde_x;
  
  direzione ld =  FERMO;
  static FILE * f;
  if(turno == 1)
    {
      collega_nodi();
      //f=fopen("debugs.txt","w+");
    }

  /* uscita dalla casetta dei fantasmi */
  if(turno<7)
    {
      if(turno<5)
        return SU;

      nodo_a = grafo[13];
      nodo_da = grafo[13];
      
      colonna_old = -1;
      colonna = nodo_a.colonna;

      riga_old = -1;
      riga = nodo_a.riga;
      return DESTRA;
    }
  
  /* Sono su un nodo? */
  int inx = indice_nodo_cella(riga,colonna);
  //fprintf(f,"R: %d, C: %d, inx:%d\n",riga,colonna,inx);
  
  
  /* cella su cui si trova e cella precedente */
  cella c, pr;
  c.riga = riga;
  c.colonna = colonna;
  pr.riga = riga_old;
  pr.colonna = colonna_old;
  
  if(inx<0)
    {
      /*________________________________________________ 
       *|  Non sono su un nodo. Il percorso è obbligato 
       *| sono definiti: nodo_da, nodo_a, x e y _old
       *| satbilisce il prossimo passo come l'unico
       *| possibile in modo che non sia ne un muro ne la 
       *| posizione attuale
       */
                 
      ld = prossima_cella(c, pr, lab);

      colonna_old = colonna;
      riga_old = riga;
      
      return ld; 
    }
  else
    {
      /*________________________________________________
       *|
       *| Sono su un nodo, devo decidere il prossimo
       *| edge su cui muovermi
       *| se non ci sono stati errori inx ==  nodo_a.indice
       *| in base alla posizione di tuki.
       *| Al termine di questo blocco devo:
       *| nodo_da <- noda_a
       *| nodo_a <- nodo_dest
       */

      if(inx != nodo_a.indice)
        {
          //printf("Ai miei tempi si programmava meglio.\n Mi rifiuto di continuare inx.%d != nodo.%d  riga=%d, colonna=%d\n",inx, nodo_a.indice,riga,colonna);
          
          //exit(0);
        }
      
      /* Nodo temporaneo */
      nodo n_d;

      /* calcola la distanza tra i prossimi nodi e tuki */
      double d_sx = 10000, d_dx = 10000, d_su = 10000, d_giu = 10000;

      cella tuki,clyde;
      tuki.riga = p.tuki_y;
      tuki.colonna = p.tuki_x;
      clyde.riga  = p.clyde_y;
      clyde.colonna = p.clyde_x;

      double ds = distanza_celle(tuki,clyde);
      if(ds <= 8)
        {
          tuki.riga = 28;
          tuki.colonna = 3;
        }

      cella s;

      //fprintf(f,"1) nodo_a.indice %d\n",nodo_a.indice);
      
      if(nodo_a.n_sx >= 0)
        {
          n_d = grafo[nodo_a.n_sx];
          if(n_d.indice != nodo_da.indice && n_d.indice >= 0)
            {
              s.riga = n_d.riga;
              s.colonna = n_d.colonna;
              d_sx = distanza_celle(s, tuki);
            }
        }
      if(nodo_a.n_dx >= 0)
        {
          n_d = grafo[nodo_a.n_dx];
          if(n_d.indice != nodo_da.indice && n_d.indice >= 0)
            {
              s.riga = n_d.riga;
              s.colonna = n_d.colonna;
              d_dx = distanza_celle(s, tuki);
            }
        }
      if(nodo_a.n_su >= 0)
        {
          n_d = grafo[nodo_a.n_su];
          if(n_d.indice != nodo_da.indice && n_d.indice >= 0)
            {
              s.riga = n_d.riga;
              s.colonna = n_d.colonna;
              d_su = distanza_celle(s, tuki);
            }
        }
      if(nodo_a.n_giu >= 0)
        {
          n_d = grafo[nodo_a.n_giu];
          if(n_d.indice != nodo_da.indice && n_d.indice >= 0)
            {
              s.riga = n_d.riga;
              s.colonna = n_d.colonna;
              d_giu = distanza_celle(s, tuki);
            }
        }
          nodo_da =  nodo_a;

      int ind;
      /* cerco il nodo più vicino a tuki */
      if(d_sx<=d_dx && d_sx<=d_su && d_sx<=d_giu)
        {
          ind = nodo_a.n_sx;
          nodo_a = grafo[ind];
          //fprintf(f,"1.1) noda_a.n_sx:%d ->nodo_a.indice:%d\n",ind,nodo_a.indice);
          ld = SINISTRA;   
        }else if(d_dx<=d_sx && d_dx<=d_su && d_dx<=d_giu)
        {
          ind = nodo_a.n_dx;
          nodo_a = grafo[ind];
          //fprintf(f,"1.1) noda_a.n_dx:%d ->nodo_a.indice:%d\n",ind,nodo_a.indice);
          ld = DESTRA;
        } else if(d_su<=d_sx && d_su<=d_dx && d_su<=d_giu)
        {
          ind = nodo_a.n_su;
          nodo_a = grafo[ind];
          //fprintf(f,"1.1) noda_a.n_su:%d ->nodo_a.indice:%d\n",ind,nodo_a.indice);
          ld = SU;
        } else if(d_giu<=d_sx && d_giu<=d_dx && d_giu<=d_su)
        {
          ind = nodo_a.n_giu;
          
          nodo_a = grafo[ind];
          //fprintf(f,"1.1) noda_a.n_giu:%d ->nodo_a.indice:%d\n",ind,nodo_a.indice);
          ld = GIU;          
        }
      
      colonna_old = colonna;
      riga_old = riga;

      if(nodo_da.indice == nodo_a.indice)
        {
          //printf("Errore: da %d != a %d direzione: %d",nodo_da.indice,nodo_a.indice,ld);
          //exit(0);
        }
      //fprintf(f,"2) nodo_a.indice %d\n",nodo_a.indice);
      return ld;
    }
        
  return ld;
  
  
}
