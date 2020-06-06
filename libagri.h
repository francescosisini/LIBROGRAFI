typedef enum  {SX,DEORSUM,DX,SURSUM,FIXO} versus;
enum genus {MURO,ALTRO};
typedef enum genus rei_genus;

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
  struct cella* deorsum;
  struct cella* sinistra;
  struct cella* sursum;
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
