#include "sem_script.h"
#include <time.h>
#include <math.h>

/*NOTE: WRITE YOUR SCRIPT IN THE FOLLOWING FUNCTION.*/

/*
Defines the Weibull distribuition scale parameter
NOTE: this regulates the scale for the time intervals (measured in ms)
used to inject errors, meaning that a scale of 100 will generate intervals
with a scale of 100ms
*/
#define SCALE 100
//Defines the Weibull distribuition shape parameter (SHAPE=1 is the 
//value that better represents electrical errors)
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
  
  //Reset the SEM core
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
    wait_time = SCALE*val_aux; //waiting period based on Weibull distribution
    
    //get the error address from file
    while (1) {
      c = fgetc(fp);
      if (c == EOF || c == '\n') 
        break;
      buffer[i++]=c;
    }
    if (c == EOF) break;
    
    //inject error after the waiting time has elapsed
    while (1) {
      end = clock() / (CLOCKS_PER_SEC / 1000);
      if((end-start) >= wait_time) {
        err_injection_cmd_in_addr(buffer);
        break;
      }
    }
  }
  
  printf("Finished error injection\n\n");
  
  fclose(fp);
}
