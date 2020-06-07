#define NNODI 34
#define PORTE 10

typedef enum  {SX,DEORSUM,DX,SURSUM,FIXO} versus;
enum genus {MURO,ALTRO};
typedef enum genus rei_genus;
/*** GRAFO COME LISTA DI ARCHI ***/


/*** GRAFO COME ARRAY DI VERTICI ***/

typedef struct {
  int linea;
  int columna;
  int index;
  int ianua[PORTE];
} agri_Vertex;

typedef struct nodus_coda
{
  //Riferimento al nodus del grafo
  int index;

  //Priorità
  double prio;
  
  //Navigazione coda 
  struct nodus_coda * post;
  
} Nodus;

//Tipo per la coda di priorità
typedef Nodus * Ordo;
//Tipo per il cammino finale
typedef int * agri_Via;

/*____________________________________________
 * 
 * Inserimento ordinato in base alla priorità
 */
void Ordo_amoveo_nodus(Ordo * l, int index);

void Ordo_insero_nodus(Ordo * l,int index, double prio);

int Ordo_pop(Ordo * pOrdo);

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

agri_Via agri_astar(int start, int goal,
		    agri_Vertex * agri_Vertices_Colligati,
		    double (*spatium)(int ab, int ad),
		    double (*euristica)(int ab, int ad),
		    )
{

  if(start==goal) return 0;
  
  double fscore[NNODI];
  double gscore[NNODI];
  int precedente[NNODI];

  //Nodi in valutazione per il path da start a goal
  Ordo candidati = 0;

  
  
  for(int i=0;i<NNODI;i++)
    {
      fscore[i] = INFINITO;
      gscore[i] = INFINITO;
    }
  gscore[start] = 0;
  fscore[start]=euristica_h(start,goal);

  Ordo_insero_nodus(&candidati,start,(1./fscore[start]));

  while(candidati != 0)
    {
      printf("Pop ");
      fflush(stdout);
      int corrente = Ordo_pop(&candidati);
      printf("%d\n",corrente);
      /* Arrivato al nodus goal torna il cammino */
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
                    
          agri_Via percorso = malloc((i+1)*sizeof(int));
	  
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
      int vicino[IANUA];
      for(int i=0; i<IANUA; i++)
	{
	  vicino[i] = agri_Vertices_Colligati[corrente].ianua[i];
	}
      printf("Il nodus %d\n",corrente);
      for(int i =0; i<IANUA; i++)
        {
          int iv = vicino[i];
	  printf("ha vicino %d\n",iv);
          /* ogni nodus è predisposto per 4 vicini, ma molti nodi ne hanno
             solo 3*/
          if(iv == -1)continue;

          double d =  spatium(corrente, iv);
          double tent_gscore = gscore[corrente]+d;
	  printf("a distanza %lf\n",d);
          if(tent_gscore <= gscore[iv])
            {
	      
              /* Trovato cammino migliore a questo nodus passando per corrente*/
              precedente[iv] = corrente;
              gscore[iv] = tent_gscore;
              fscore[iv] = gscore[iv] +  euristica(iv, goal);
	     
              Ordo_insero_nodus(&candidati,iv, ( 1./fscore[iv]));
	     
	      fflush(stdout);
            }
	}
       //Stampiamo la Ordo corrente
      Ordo cd = candidati;
      printf("----------------------\n");
      while(cd)
	{
	  printf("Ordo: nodus %d, %lf\n",cd->index,cd->prio);
	  cd=cd->post;
	}
    }
  return 0;
  
}


/*__________________________________________________________
 *|
 *| Torna l'index del nodus presente in (riga, colonna)
 *| Se non è presente alcun nodus (il fantasma è su un ramo)
 *| torna -1
 */
int index_nodus_cella(int riga, int col)
{
  for(int i=0; i<NNODI;i++)
    {
      if(agri_Vertices_Colligati[i].columna == col && agri_Vertices_Colligati[i].linea == riga)
        return agri_Vertices_Colligati[i].index;
    }
  return -1;
}

/*** GRAFO COME LISTA DI CELLE  ***/

/*
  ITA: Attributi della cella
  ENG: Cell attributes
 */
typedef struct dato
{
  int visitata;
  rei_genus rei;
} Attributi;

/*
  ITA: vicini di ogni cella
  ENG: cell's neighbords
 */
typedef struct cella {
  Attributi d;
  struct cella* dextra;
  struct cella* deorsum; //GIU
  struct cella* sinistra;
  struct cella* sursum; //SU
} agri_Cella;

/*
  ITA: Tabellam composto da celle
  ENG: Graph composed by cells
 */
typedef agri_Cella* agri_Tabella;

/*
  ITA: elementi della lista dei passi
  ENG: elements of the step list
 */
typedef struct nodo
{
  agri_Cella * locus;
  struct nodo * next;
  struct nodo * prev;
}agri_Passo;

/*
  ITA: lista dei passi
  ENG: step list
 */
typedef agri_Passo* agri_Iter;  


/*
  ITA: inizializza un grafo vuoto
  ENG: initialize an empty graph
 */
void agri_creo_Tabellam(agri_Tabella* g);
/*
  ITA: Aggiunge al grafo una nuova cella con attributi d, collegandola alla direzione
  dir cella corrente
  ENG: Adds a new cell, with the attributes d, to the graph, linking it to the
  direction dir of the current cell
 */
agri_Tabella agri_addo_Tabellam(agri_Tabella tabella,Attributi d,versus dir);

/*
  ITA: collega le cella da e a lungo la direzione da ---> a
 */
void agri_colligo_Cellas(agri_Cella * da, agri_Cella * a, versus da_a);



/*
  ITA: inizializza una lista di passo puntata da p_camm cammimo vuoto
  ENG: initialize an empty list of steps
 */
void agri_creo_Iter(agri_Iter* p_camm);
/*
  ITA: aggiunge una Cella nella lista puntata da p_camm dei passi compiuti
  ENG: adds a cell in the list pointed to by p_camm of the steps performed
 */
void agri_addo_Iter(agri_Iter * p_camm, agri_Cella * p_cella);
/*
  ITA:
 */
agri_Cella* agri_rivela_Cella(agri_Iter ap,versus ricerca);




