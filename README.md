# Mangia e Fuggi
(ovvero, i miracolosi schemi di Pac-Man per complerare il lebirinto senza essere catturato dal Ghost-Team)

**New** Dal 31 agosto il libro su Amazon [Applicazioni di grafi e algoritmi alla fuga di Pac-Man dal Ghosts Team](https://www.amazon.it/dp/B08GTJ2KHM)

## Il labirinto di Pac-Man su una piattaforma Open Source
La piattaforma [Tuki-5](mvc) è una implementazione parziale del gioco del Pac-Man in linguaggio C.
Sfruttando la piattaforma si possono sviluppare specifci *agents* per studiare le strategie di *attacco* e di *difesa* nel gioco
La piattaforma di gioco insieme al codice sono descritte nel libro [Sfidare gli algoritmi](https://www.amazon.it/Sfidare-gli-algoritmi-videogiochi-Linux/dp/1695109325) ed è presente su [GitHub](https://github.com/francescosisini/LIBRO-Sfidare-gli-algoritmi-5-videogiochi-in-C-su-Linux-codice)

### Pac-Man vaga per il labirinto
Questo *agent* percorre tutto il labirinto sfidando i fantasmi, ma se vince è solo... una questione di fortuna!

Prova il [codice](PacMan/gioca_tuki_random.c)

### Pac-Man segue il filo di Arianna
La logica implementata da questo *agent* è quella del boustrohpedon, un algoritmo di path-covering

Prova il [codice](PacMan/gioca_tuki_boustrophedon.c)

### Pac-Man si crea un grafo del labirinto
La teoria dei grafi offre una base formale per sviluppare algoritmi di path search e exploring. Questo *agent* mentre vaga per il labirinto crea *mentalmente* un grafo dove gli incroci rappresentano i **vertici** e i corridoi sono gli **archi**

Prova il [codice](PacMan/gioca_tuki_generagrafo.c)

### Pac-Man punta al bersaglio
Utilizzando l'algoritmo su grafo A*, l'*agent* punta diritto al nodo che vuole raggiungere

Prova il [codice](PacMan/gioca_tuki_esploraeritorna.c)

### Pac-Man ha un percorso
Questo *agent* cerca di seguire un percorso sub-ottimale predefinito prima del gioco. Peccato che i fantasmi lo distraggano dal suo compito...

Prova il [codice](PacMan/gioca_tuki_percorso.c)

### Pac-Man pesa i percorsi e evita i fantasmi senza fuggire
Questo *agent* sfrutta l'euristica per evitare i fantasmi senza sfugirli direttamente

Prova il [codice](PacMan/gioca_tuki_pesato.c)

### Pac-Man ottimizza il percorso
Questo *agent* sfrutta l'algorimo breadth-first per ottimizzare il percorso

Prova il [codice](PacMan/gioca_tuki_respiro.c)


### Pac-Man ottimizza il percorso ed evita i fantasmi senza fuggire
Questo *agent* combina i due precendenti per ottimizzare il percorso e sfuggire ai fantasmi

Prova il [codice](PacMan/gioca_tuki_evita.c)

<!--[Applicazioni di grafi e algoritmi alla fuga di Pac-Man dal Ghosts Team](https://www.amazon.it/Applicazioni-grafi-algoritmi-Pac-Man-Ghosts-ebook/dp/B087GLBPNM/)
![KIndle](mezza.jpg)-->
