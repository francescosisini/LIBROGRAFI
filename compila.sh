gcc -o tuki5.game -DFUGA=$2  ghost_team/gioca_fantasmi.c PacMan/$1 mvc/tuki5_controllo.c mvc/tuki5_modello.c mvc/tuki5_visore.c agri/lib/src/libagri.c -Iagri/lib/include -Imvc  -lm 
