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

  //open connection
  cnsl_open(devname);
  printf(PROGNAME); printf(": connecting...\n\n");

  my_sem_script();

}
