#include "sem_script.h"

/*NOTE: WRITE YOUR SCRIPT IN THE FOLLOWING FUNCTION.
  FINISH WITH ctrl+c IN THE OPEN TERMINAL.
  IF YOU NEED TO CHECK ERROR CORRECTION AFTER INJECTION,
  LAUNCH A NEW wait_resp() FUNCTION TO RECEIVE THE RESPONSE.
*/
void my_sem_script (){

  //Catch initilization response
  wait_resp();

  reset_cmd();

	status_cmd();

  //query the frame
  query_cmd(0,36,1,21);
  //inject error at slr 0, frame 36, word 1, bit 21
  err_injection_cmd(0, 36,1,21);
	//check if bit was flipped
	query_cmd(0,36,1,21);

	observation_cmd();
	wait_resp(); //Wait for response to error detection

	printf("\n\n");

}
