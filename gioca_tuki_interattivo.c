#include "tuki5_modello.h"

#include <ctype.h>
#include <errno.h>
#include <locale.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

enum editorKey {
  BACKSPACE = 127,
  ARROW_LEFT = 1000,
  ARROW_RIGHT,
  ARROW_UP,
  ARROW_DOWN,
  DEL_KEY,
  HOME_KEY,
  END_KEY,
  PAGE_UP,
  PAGE_DOWN
};

int leggi_tastiera()
{
  int nread;
  char c;
  while ((nread = read(STDIN_FILENO, &c, 1)) != 1) {
    if (nread == -1 && errno != EAGAIN) exit(1);
  }
  if (c == '\x1b') {
    char seq[3];
    if (read(STDIN_FILENO, &seq[0], 1) != 1) return '\x1b';
    if (read(STDIN_FILENO, &seq[1], 1) != 1) return '\x1b';
    if (seq[0] == '[')
      {
	if (seq[1] >= '0' && seq[1] <= '9')
	  {
	    if (read(STDIN_FILENO, &seq[2], 1) != 1) return '\x1b';
	    if (seq[2] == '~') {
	      switch (seq[1]) {
	      case '1': return HOME_KEY;
	      case '3': return DEL_KEY;
	      case '4': return END_KEY;
	      case '5': return PAGE_UP;
	      case '6': return PAGE_DOWN;
	      case '7': return HOME_KEY;
	      case '8': return END_KEY;
	      }
	    }
	  } else
	  {
	    switch (seq[1])
	      {
	      case 'A': return ARROW_UP;
	      case 'B': return ARROW_DOWN;
	      case 'C': return ARROW_RIGHT;
	      case 'D': return ARROW_LEFT;
	      case 'H': return HOME_KEY;
	      case 'F': return END_KEY;
	      }
	  }
      }
    
    else if (seq[0] == 'O')
      {
	switch (seq[1]) {
	case 'H': return HOME_KEY;
	case 'F': return END_KEY;
	}
      }
    return '\x1b';
    
    
  } else
    {
      return c;
      
    }
}

direzione gioca_tuki(posizioni p, oggetto **labx)
{
  //  static int turno = 0;
  //static direzione ld=SINISTRA;
  
  //return ld;
  
  //turno+=1;
  
  static direzione dir = FERMO;
  char c;
  
  int i=p.tuki_y;
  int j=p.tuki_x;
  
  
  int ch = leggi_tastiera();
  
  switch (ch)
    {      
      
    case ARROW_UP:
      // -su
      dir = SU;
      break;
    case ARROW_DOWN:
      dir = GIU;
      break;
    case ARROW_LEFT:
      dir = SINISTRA;
      break;
    case ARROW_RIGHT:
      dir = DESTRA;
      break;
   
    }
  read(STDIN_FILENO, &ch, 1);
  return dir;
}
