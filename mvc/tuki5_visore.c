/*
  The Green Race - A C-Language coding game based on  Path planning problem
  
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



/*** Includes ***/
#include <ctype.h>
#include <locale.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>
#include "tuki5_modello.h"
#include "tuki5_visore.h"

/*** Define ***/
#define COFFSET(width) (cols-width)/2
#define ROFFSET(heigh) (rows-heigh)/2

/*** Data ***/
struct termios orig_termios;
int rows,cols;


/*** Terminal ***/


void die(const char *s) {
  write(STDOUT_FILENO, "\x1b[2J", 4);
  write(STDOUT_FILENO, "\x1b[H", 3);

  perror(s);
  exit(1);
}


  
int leggi_dimensioni_terminale(int *rows, int *cols) {
  struct winsize ws;
  if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0) {
    return -1;
  } else {
    *cols = ws.ws_col;
    *rows = ws.ws_row;
    return 0;
  }
  }
  
  
void disabilita_modo_raw() {
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1)
      die("tcsetattr");
  }
  
void abilita_modo_raw() {
  
  if (tcgetattr(STDIN_FILENO, &orig_termios) == -1) die("tcgetattr");
  atexit(disabilita_modo_raw);
  
  struct termios raw = orig_termios;
  raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
  raw.c_oflag &= ~(OPOST);
  raw.c_cflag |= (CS8);
  raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
  raw.c_cc[VMIN] = 0;
  raw.c_cc[VTIME] = 1;
  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) die("tcsetattr");
  
}

void view_init()
{
  //abilita_modo_raw();
  leggi_dimensioni_terminale(&rows, &cols);
  setlocale(LC_CTYPE, "");
}


/*** output ***/
char * terminale_str(oggetto e)
{
  
  static char bc,ic,pc,cc,tc=0;
  static char st[2];
  st[0]=e;
  st[1]=0;
  bc=ic=pc=cc=tc=0;
  if(e==BLINKY)
    {
      if(bc==0)
        {
          bc=1;
          return "\x1b[1mb";
          //return "\u2229";
        }
      else
        {
          
          bc=0;
          return "B";
          //return "\u2126";
        }
    }

   if(e==INKY)
    {
      if(ic==0)
        {
          ic=1;
          return "\x1b[1mi";
        }
      else
        {
          ic=0;
          return "i";
        }
    }

    if(e==PINKY)
    {
      if(pc==0)
        {
          pc=1;
          return "\x1b[1mp";
        }
      else
        {
          pc=0;
          return "_";
        }
    }

     if(e==CLYDE)
    {
      if(cc==0)
        {
          cc=1;
          return "\x1b[1mc";
        }
      else
        {
          cc=0;
          return "c";
        }
    }

     if(e==TUKI)
    {
      if(tc==0)
        {
          tc=1;
          return "\x1b[1m@";
        }
      else
        {
          tc=0;
          return "O";
        }
    }

  
  
  if(e==B)
    return "\u2557";
  
  if(e==A)
    return "\x1b[38:5:21m\u2554";
  
  if(e==J)
    return " ";
  
  if(e==C)
    return "\u255a";
  
  if(e==D)
    return "\u255D";

  if(e==E)
    return "\u2550";

  if(e==F)
    return "\u2551";

  if(e==G)
    return "\u250c";
  
  if(e==H)
    return "\u2510";

  if(e==K)
    return "\u2596";

  if(e==I)
    return "\u2555";
  
  if(e==L)
    return "\u2552";
  
  if(e==M)
     return "\u259F";
   
   if(e==N)
     return "\u2599";
   
   if(e==O)
     return "\u2559";
   
   if(e==P)
     return "\u2553";
   
   if(e==Q)
     return "\u255c";
   
   if(e==R)
     return "\u2556";
   
   if(e==S)
     return "\u2502";
   
   if(e==T)
      return "\u2500";
    
   if(e==W)
     return "\u2514";
   
   if(e==X)
     return "\u2551";
   
     if(e==Y)
       return "\u2518";

     if(e==V) //PIllola
       return "\x1b[38:5:231m\u2022\x1b[38:5:21m";
           
     if(e==U) //Trifogli
       return "\x1b[38:5:231m.\x1b[38:5:21m";
     //return "\x1b[38:5:231m\u2022\x1b[38:5:21m";
     
     if(e==Z)
       return "\u2550";
     
     if(e==a)
       return "\u2598";
     
  return st;
}



void view_labirinto(oggetto **campo)
{
  int x,y;
  int rof=ROFFSET(ALTEZZA*1);
  int cof=COFFSET(LARGHEZZA);
  char str[25];
  
  for(int i=0;i<ALTEZZA;i++)
    for(int j=0;j<LARGHEZZA;j++)
      {
        x=j+cof;
        y=i+rof;
        sprintf(str,"\x1b[%d;%dH%s",y,x,terminale_str(*(*(campo+i)+j)));
        write(STDOUT_FILENO, str, strlen(str));
      }
  printf("\x1b[%d;%dH",y,1);
}

int view_sfondo(int r, int c,oggetto **campo)
{
  int x,y;
  int rof=ROFFSET(ALTEZZA*1);
  int cof=COFFSET(LARGHEZZA);
  char str[25];
  
  x=c+cof;
  y=r+rof;
  sprintf(str,"\x1b[%d;%dH%s",y,x,terminale_str(*(*(campo+r)+c)));
  write(STDOUT_FILENO, str, strlen(str));
  
  return 0;
}

void view_mangiato(posizioni g)
{
  int x,y;
  int rof=ROFFSET(ALTEZZA);
  int cof=COFFSET(LARGHEZZA);
  char str[80];
  char* str_lst="@*[]\\||//#+^@";
  
  x=g.tuki_x+cof;
  y=g.tuki_y+rof;
  for(int i=0;i<strlen(str_lst);i++)
    {
      sprintf(str,"\x1b[38:5:229m\x1b[%d;%dH%c",y,x,*(str_lst+i));
      write(STDOUT_FILENO, str, strlen(str));
      delay(50);
    }


}



int view_giocatori(posizioni g, oggetto ** lab,char in_blue)
{
  static posizioni g_prec;
  static char init=0;
  char pu[20];
  /* colori dei fantasmi */
  int bl,in,pi,cl;
  if(in_blue)
    {
      strcpy(pu,"\x1b[5m");
      bl=in=pi=cl=57;
    }
  else
    {
      strcpy(pu,"");
      bl=196;
      in=117;
      pi=218;
      cl=215;
    }
  
  if(init==0)
    {
      g_prec=g;
      init=1;
    }
  
  int x,y;
  int rof=ROFFSET(ALTEZZA);
  int cof=COFFSET(LARGHEZZA);
  char str[80];


  /** Tuki */
  // Ripristina il campo
  x = g_prec.tuki_x;
  y = g_prec.tuki_y;
  sprintf(str,"\x1b[38:5:229m\x1b[%d;%dH%s",y+rof,x+cof,terminale_str(*(*(lab+y)+x)));
  write(STDOUT_FILENO, str, strlen(str));
  
  //Stampa Tuki
  x=g.tuki_x+cof;
  y=g.tuki_y+rof;
  sprintf(str,"\x1b[38:5:229m\x1b[%d;%dH%s",y,x,terminale_str(TUKI));
  write(STDOUT_FILENO, str, strlen(str));

  /** Blinky */
  // Ripristina il campo
  x = g_prec.blinky_x;
  y = g_prec.blinky_y;
  sprintf(str,"\x1b[38:5:229m\x1b[%d;%dH%s",y+rof,x+cof,terminale_str(*(*(lab+y)+x)));
  write(STDOUT_FILENO, str, strlen(str));

  // stampa Blinky 
  x=g.blinky_x+cof;
  y=g.blinky_y+rof;
  sprintf(str,"%s\x1b[38:5:%dm\x1b[%d;%dH%s\x1b[0m",pu,bl,y,x,terminale_str(BLINKY));
  write(STDOUT_FILENO, str, strlen(str));

  /** Inky */
   // Ripristina il campo
  x = g_prec.inky_x;
  y = g_prec.inky_y;
  sprintf(str,"\x1b[38:5:229m\x1b[%d;%dH%s",y+rof,x+cof,terminale_str(*(*(lab+y)+x)));
  write(STDOUT_FILENO, str, strlen(str));
  
  // stampa inky 
  x=g.inky_x+cof;
  y=g.inky_y+rof;
  sprintf(str,"%s\x1b[38:5:%dm\x1b[%d;%dH%s\x1b[0m",pu,in,y,x,terminale_str(INKY));
  write(STDOUT_FILENO, str, strlen(str));

  /** Pinky */
  // Ripristina il campo
  x = g_prec.pinky_x;
  y = g_prec.pinky_y;
  sprintf(str,"\x1b[38:5:229m\x1b[%d;%dH%s",y+rof,x+cof,terminale_str(*(*(lab+y)+x)));
  write(STDOUT_FILENO, str, strlen(str));

  //stampa pinky
  x=g.pinky_x+cof;
  y=g.pinky_y+rof;
  sprintf(str,"%s\x1b[38:5:%dm\x1b[%d;%dH%s\x1b[0m",pu,pi,y,x,terminale_str(PINKY));
  write(STDOUT_FILENO, str, strlen(str));

  /** Clyde */
  // Ripristina il campo
  x = g_prec.clyde_x;
  y = g_prec.clyde_y;
  sprintf(str,"\x1b[38:5:229m\x1b[%d;%dH%s",y+rof,x+cof,terminale_str(*(*(lab+y)+x)));
  write(STDOUT_FILENO, str, strlen(str));

  // stampa clyde
  x=g.clyde_x+cof;
  y=g.clyde_y+rof;
  sprintf(str,"%s\x1b[38:5:%dm\x1b[%d;%dH%s\x1b[0m",pu,cl,y,x,terminale_str(CLYDE));
  write(STDOUT_FILENO, str, strlen(str));

  /** Memorizza le posizioni del turno appena visualizzato */
  g_prec=g;

  
}

void view_punteggio(int punti)
{
  char str2[50];
  char str[60];
  sprintf(str2,"Score %d ",punti);
  int l=strlen(str2);
  int rof=ROFFSET(ALTEZZA*1);
  int cof=COFFSET(l);
  sprintf(str,"\x1b[%d;%dH%s",ALTEZZA+2,cof,str2);
  write(STDOUT_FILENO, str, strlen(str));
}

void view_gameover(char * message)
{
  char str2[50];
  char str[60];
  
  int l=strlen(message);
  int rof=ROFFSET(ALTEZZA*1);
  int cof=COFFSET(l);
  sprintf(str,"\x1b[%d;%dH%s\r\n\r\n",rof+12+1,cof,message);
  write(STDOUT_FILENO, str, strlen(str));
  //Set cursor at the begin of last line
  
  printf("\x1b[%d;%dH",rows,1);
}

void delay(int milliseconds){
  long pause;
  clock_t now,then;
  
  pause = milliseconds*(CLOCKS_PER_SEC/1000);
  now = then = clock();
  char c;
  while( (now-then) < pause )
    {
      now = clock();
    }
}

void fading( char * str,int r, int c)
{
  float gray=232;
  float inc=0.03;
  float vrs=1;
  while(gray<255)
    {
      printf("\x1b[%d;%dH\x1b[38;5;%dm%s\x1b[m",r,c,(int)gray,str);
      if(gray<255){
        vrs=+1;
      }
      if(gray<=232){
        //vrs=1;
      }
      delay(1);
      gray+=vrs*inc;
    } 
  fflush(stdout);
    

}


void view_presentazione(){
  char str2[50];
  char str[60];
  char * message[]={"TUKI e Pacman","Coding-game prodotto e distribuito","da Scuola Sisini","visita http://pumar.it"};
  int l,rof,cof;
  
  printf("\x1b[%d;%dH",1,1);
  write(STDOUT_FILENO, "\x1b[2J", 4);
  for(int i=0;i<4;i++)
    {
      l=strlen(message[i]);
      rof=ROFFSET(ALTEZZA*1.5);
      cof=COFFSET(l);
      fading(message[i],rof+ALTEZZA/2+i,cof);
      delay(100);
    }
  printf("\x1b[%d;%dH",1,1);
  delay(1250);
  write(STDOUT_FILENO, "\x1b[2J", 4);
   
}



