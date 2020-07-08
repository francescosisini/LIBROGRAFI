# English instructions
- Clone the project: ``git clone https: // github.com / francescosisini / LIBROGRAFI.git``
- Choose one of the Pac-Man agents among:
   - ``Gioca_tuki_random.c`` Pac-Man explores the maze by randomly choosing where to turn
   - ``Gioca_tuki_boustrophedon.c`` Pac-Man explores the maze deterministically with the boustrophedon algorithm
   - ``Gioca_tuki_generagrafo.c`` Pac-Man generates a vertex-arc graph while exploring the maze
   - ``Gioca_tuki_esploraeritorna.c`` Pac-Man uses the graph he generates online to navigate the maze
   - ``Gioca_tuki_percorso.c`` Pac-Man starts the game with the graph of the whole labyrinth and uses it to complete it suboptimally
  - Compile  specifying whether to activate the escape mechanism and the interval in milliseconds between the steps:
  `` ./compila.sh PacMan / Gioca_tuki_percorso.c 1 50``
  - Size the terminal at least 60x60
  - run `` ./tuki5.game 1`` where 1 indicates the number of ghosts (from 0 to 4)


# Italiano
- Clona il progetto: ``git clone https://github.com/francescosisini/LIBROGRAFI.git``
- Scegli uno degli agent Pac-Man tra:
  - ``gioca_tuki_random.c`` Pac-Man esplora il labirinto scegliendo casualmente dove svoltare
  - ``gioca_tuki_boustrophedon.c`` Pac-Man esplora il labirinto in modo deterministico con l'algoritmo boustrophedon
  - ``gioca_tuki_generagrafo.c``Pac-Man genera un grafo vertici-archi mentre esplora il labirinto
  - ``gioca_tuki_esploraeritorna.c``Pac-Man usa il grafo che genera on-line per navigare il labirinto
  - ``gioca_tuki_percorso.c`` Pac-Man inizia il gioco con il grafo di tutto il labirinto e lo sfrutta per completarlo in modo subottimale
 - Compila specificando se attivare il meccanismo di fuga e l'intervallo in millisecondi tra i passi: 
 ``./compila.sh PacMan/gioca_tuki_percorso.c  1 50`` 
 - Dimensioni il terminale ad almeno 60x60
 - esegui ``./tuki5.game 1`` dove 1 indica il numero dei fantasmi (da 0 a 4)

