/*** SECTION: battlefiled  ***/
#define ALTEZZA 35
#define LARGHEZZA 28

/**
 * Gli oggetti nel campo
 */
typedef enum {
  //Angoli
   a='a', 
   A = 'A', //ANGOLO ALTO SIN BORDO
   B = 'B', //ANGOLO ALTO DES BORDO
   C = 'C', //ANGOLO BASSO SIN BORDO 
   D = 'D', //ANGOLO BASSO DES BORDO
   E = 'E', //MURO ORR BORDO
   F = 'F', //MURO VER BORDO
   G = 'G', //ANGOLO ALTO SIN 
   H = 'H', //ANGOLO ALTO DES
   I = 'I', //ANGOLO ALTO DES
   J = 'J', //SPAZIO
   K = 'K',
   L = 'L', //ANGOLO ALTO SIN
   M = 'M', //ANGOLO BASSO DES
   N = 'N', //ANGOLO BASSO SIN
   O = 'O', //ANGOLO BASSO SIN
   P = 'P', //ANGOLO ALTO SIN
   Q = 'Q', //ANGOLO BASSO DES
   R = 'R', //ANGOLO ALTO DES
   S = 'S', //MURO VER
   T = 'T', //MURO ORR
   U = 'U', //PUNTINO
   V = 'V', //PILLOLA
   X = 'X', //MURO VER BORDO
   Y = 'Y', //ANGOLO BASSO DES
   W = 'W', //ANGOLO BASSO SIN
   Z = 'Z', //MURO ORZZ BORDO
   //Cibo
   TRIFOGLIO ='.',
   PILLOLA = 'O'
} oggetto;


/**
 * I 5 giocatori
 */
typedef enum {
  //Personaggi
  BLINKY='b',
  INKY='i',
  PINKY='p',
  CLYDE='c',
  TUKI='@',

} giocatore;


#ifndef PLAYER
typedef enum  {SINISTRA,SU,DESTRA,GIU,FERMO} direzione;
#define PLAYER 
#endif

typedef struct  {
  int tuki_x, tuki_y;
  int blinky_x, blinky_y;
  int inky_x, inky_y;
  int pinky_x, pinky_y;
  int clyde_x, clyde_y;
} posizioni;



/*** interfaccia***/

/* elabora l'evoluzione del gioco e torna 0 quando il tuki è mangiato */
int mdl_passo
(direzione tuki,
 direzione blinky,
 direzione inky,
 direzione pinky,
 direzione clyde);

/* torna una copia del campo ad uso dei giocatori */
oggetto **  mdl_campo();

/* copia delle posizioni dei giocatori, ad uso dei giocatori */
posizioni mdl_posizioni();

/* crea il campo, ad uso del controller */
int mdl_genera_campo();

/* libera la memoria del campo */
void mdl_libera_campo();

/* torna il punteggio del tuki */
int mdl_punteggio();

/* torna lo stato di superpacman */
char mdl_superpacman();



