/*
  The Tuki5 - A C-Language coding game based on Pacman game
  
  Copyright (C) 2018  Francesco Sisini (scuolaSisini)
  
  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
  
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */


/**
The Green Race - A C-Language coding game based on  Path planning problem
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#include "tuki5_modello.h"
#include "tuki5_visore.h"

/** DESCRIZIONE */
/**
   - Nel campo di gioco sono presenti trifogli, pillole, muri

   - La distribuzione degli oggetti nel campo di gioco è memorizzata in un array 2d

   - La posizione dei 5 giocatori è memorizzata in una singola struttura
   
   - Ad ogni personaggio del gioco è associata una funzione con il nome: gioca_<personaggio>
   che torna la mossa che il personaggio fa in un turno di gioco.
   
*/
/**
   -game-controller.c
   Il controller offre ai giocatori le 5 funzioni di controllo
   a turno chiama le 5 funzioni per permettere ad ogni giocatore di giocare
   il controller chiama poi il model comunicando la mossa del giocatore
   
   -game-model.c 
   il model elabora la mossa del giocatore valuatando la nuova posizione e verifica:
   1) se avviene una collisione tra giocatori
   2) se avviene una collisione con il muro
   3) se viene mangiato un trifoglio
   4) se viene mangiata una pillola
   
   -game-viewer.c
   stampa sullo schermo lo stato del gioco
   
*/

/* MACRO  */
#define MAJOR    0
#define MINOR    1
#define RELEASE  1

/* GLOBALS  */

/* PROTOTIPI  */
direzione gioca_tuki(posizioni p, oggetto** lab);
direzione gioca_blinky(posizioni p, oggetto** lab);
direzione gioca_inky(posizioni p, oggetto** lab);
direzione gioca_pinky(posizioni p, oggetto** lab);
direzione gioca_clyde(posizioni p, oggetto** lab);



int main(int argc, char **argv)
{

  /*
    ITA: numero di fantasmi nel labirinto (default 4)
    ENG: number of ghosts in the maze
   */
  int n_fantasmi = 4;
  if(argc>1)
    {
      n_fantasmi = atoi(argv[1]);
      if(n_fantasmi>4) n_fantasmi = 4;
    }
  
  /* Presentazione */
  view_init();
  //view_presentazione();
  
  /* Inizio gioco */
  int inizio=  mdl_genera_campo();

  if(!inizio) exit(1);
  
  /* Labirinto */
  oggetto ** lab = mdl_campo();
  view_labirinto(lab);
  
  
  /**
   * START GAME
   */
  int r=1;
  while(r){
  
    posizioni p=mdl_posizioni();
    
    if(lab==0) exit(1);

    direzione t = gioca_tuki(p, lab);
    
    direzione b = gioca_blinky(p, lab);
    
    direzione i = gioca_inky(p, lab);
    
    direzione pi = gioca_pinky(p, lab);
    
    direzione c = gioca_clyde(p, lab);

    char go;
    
    if(n_fantasmi == 0)
      go = mdl_passo(t,FERMO,FERMO,FERMO,FERMO);
    if(n_fantasmi == 1)
      go = mdl_passo(t,b,FERMO,FERMO,FERMO);
    if(n_fantasmi == 2)
      go = mdl_passo(t,b,i,FERMO,FERMO);
    if(n_fantasmi == 3)
      go = mdl_passo(t,b,i,pi,FERMO);
    if(n_fantasmi == 4)
      go = mdl_passo(t,b,i,pi,c);
    
    int pnt = mdl_punteggio();
    char inblu=mdl_superpacman();

    /** mostra campo e giocatori */
    r+=1;
    p=mdl_posizioni();//aggiorna le posizioni prima di mostrarle a video
    view_punteggio(pnt);
    view_giocatori(p,lab,inblu);
    delay(DELAY);
    // delay(250);


    /** Pacman è stato mangiato **/
    if(go==0)
      {
        view_mangiato(p);
        view_gameover("GAME OVER");
        exit(0);
      }

    /** Pacman ha finito le pastiglie 245 */
    if(pnt == 244)
      {
        view_gameover("Ha vinto TUKI!");
        exit(0);
      }
    
  }  
  /*end of the game*/
  
}


