void view_init();

/** Stampa il labirinto */
void view_labirinto(oggetto **labirinto);

/** stampa l'oggetto (se) presente in posizione r e c */
int view_sfondo(int r, int c,oggetto **labirinto);

/** stampa i giocatori sul campo */
int view_giocatori(posizioni giocatori, oggetto ** labirinto, char inblue);

/** stampa il punteggio */
void view_punteggio(int punti);

/** stampa la fine del gioco */
void view_gameover(char * messaggio);

/** stamp la presentazione */
void view_presentazione();

/** stampa la fine di pacman */
void view_mangiato(posizioni g);

void delay(int millis);

