#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "console.h"
#include "sem_script.h"

#define PROGNAME "SEM-Console"

//print error
void cnsl_perror (char * mesg) {
  printf(PROGNAME); printf(": %s\n", mesg);
  exit(1);
}

void usage(char *message){
  cnsl_perror("usage: ./console -s <serial port>\n");
  cnsl_perror(message);
}

//
// MAIN ROUTINE
//

int main(int argc, char* argv[]) {

  char *devname = 0;
  int i;

  if (argc < 3)
    usage("PROGNAME: not enough program arguments\n");

  for (i = 1; i < argc; i++) {
    if (argv[i][0] == '-' && !argv[i][2]) {
      if (argv[i][1] == 's')
        devname = argv[++i];
      else usage("PROGNAME: unexpected argument\n");
    } else  usage("PROGNAME: unexpected argument\n");
  }

  printf("\n\n");
  //open connection
  printf(PROGNAME); printf(": connecting...\n\n");
  cnsl_open(devname);
  printf(PROGNAME); printf(": connected successfully\n\n");
  
  /* Unset stdin and stdout buffering */
	setvbuf(stdin, NULL, _IONBF, 0);
	setvbuf(stdout, NULL, _IONBF, 0);

  char c; 
  
  while(1) {
    c = cnsl_getchar(); //Wait for board
    if (c=='\x02') break;
    else putchar(c);
  }

  cnsl_putchar('\x06');
  printf("Starting scrip\n");
  
  my_sem_script();
  
  cnsl_putchar('\x06');
  while (1) {
    //get byte from target
    c = cnsl_getchar();
    if(c=='\x06') break;
    else putchar(c);
  }
  
  return 0;
}
