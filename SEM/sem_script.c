#include "sem_script.h"
#include <time.h>
#include <math.h>

/*NOTE: WRITE YOUR SCRIPT IN THE FOLLOWING FUNCTION.
  FINISH WITH ctrl+c IN THE OPEN TERMINAL.
  IF YOU NEED TO CHECK ERROR CORRECTION AFTER INJECTION,
  LAUNCH A NEW wait_resp() FUNCTION TO RECEIVE THE RESPONSE.
*/

/*
Defines the Weibull distribuition scale parameter
NOTE: this regulates the scale for the time intervals (measured in ms)
used to inject errors, meaning that a scale of 100 will generate intervals
with a scale of 100ms
*/
#define SCALE 100
//Defines the Weibull distribuition shape parameter
#define SHAPE 1


#ifdef ULTRASCALE_P
  #define ADDR_SIZE 11
#else
  #define ADDR_SIZE 10
#endif

void my_sem_script (){

  FILE * fp;  
  char buffer [ADDR_SIZE];
  char c;
  clock_t start, end;
  int wait_time;
  double U, val_aux;

  //Wait initial response
  wait_resp();
  
  reset_cmd();

  fp = fopen("injectionRange.txt", "r");
  if (fp == NULL) {
    printf("Failed to open file\n");
    exit(EXIT_FAILURE);
  }

  while(1) {
    size_t i = 0;
    start = clock() / (CLOCKS_PER_SEC / 1000);
    U = ((rand()%10000)+1.0)/10000.0 ;
    val_aux = pow(-1.0*log(U), 1.0/SHAPE); //-ln(U)^(1/SHAPE)
    wait_time = SCALE*val_aux;
    
    while (1) {
      c = fgetc(fp);
      if (c == EOF || c == '\n') 
        break;
      buffer[i++]=c;
    }
    if (c == EOF) break;
    
    while (1) {
      end = clock() / (CLOCKS_PER_SEC / 1000);
      if((end-start) >= wait_time) {
        //printf("%ld >= %d\n", end-start, wait_time);
        err_injection_cmd_in_addr(buffer);
        break;
      }
    }
  }
  
  printf("Finished error injection\n\n");
  
  fclose(fp);
}
