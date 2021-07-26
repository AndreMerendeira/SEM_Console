#include "sem_script.h"

/*NOTE: WRITE YOUR SCRIPT IN THE FOLLOWING FUNCTION.
  FINISH WITH ctrl+c IN THE OPEN TERMINAL.
  IF YOU NEED TO CHECK ERROR CORRECTION AFTER INJECTION,
  LAUNCH A NEW wait_resp() FUNCTION TO RECEIVE THE RESPONSE.
*/
void my_sem_script (){

  FILE * fp;
  char * line = NULL;
  size_t len, i = 0;
#ifdef ULTRASCALE_P
  char buffer [11]="";
#else
  char buffer [10]="";
#endif

  //Catch initilization response
  wait_resp();

  reset_cmd();

  status_cmd();

  fp = fopen("injectionRange.txt", "r");
  if (fp == NULL) {
    printf("Failed to open file\n");
    exit(EXIT_FAILURE);
  }

  while(getline(&line, &len, fp) != -1) {
    for (i=0; i<len-1; i++)
      buffer[i]=line[i];
    err_injection_cmd_in_addr(buffer);
  }
  
  printf("Finished error injection\n\n");
  
  fclose(fp);
  if (line)
  free(line);
}
