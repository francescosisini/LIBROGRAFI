#!/bin/sh

if [ "$#" -ne 3 ]; then
    echo "3  parameters required:\n
    \tUser code file (gioca_tuki.c for example)\n
    \t1 or 0 to activate or no run away option\n
    \tTime delay for each game cycles (ms)\n"
    exit
fi

gcc -pedantic -std=c99 -o tuki5.game -DFUGA=$2 -DDELAY=$3 \
$1 \
ghost_team/gioca_fantasmi.c \
mvc/tuki5_controllo.c \
mvc/tuki5_modello.c \
mvc/tuki5_visore.c \
agri/lib/src/libagri.c \
-Iagri/lib/include \
-Imvc \
-lm 
