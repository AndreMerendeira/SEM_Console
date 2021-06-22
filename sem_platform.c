#include "sem.h"

int IDLE = 0;


/*
Waits for the response from SEM Core
Response terminated by returning to a state (signaled by "> ")
*/
void wait_resp () {
  char resp_buffer[1400];
  unsigned int i=0;
  char c;

  while (1) {
    //get byte from target
    c = cnsl_getchar();
    if (c=='\r')	//SEM core sends a \r at the end of each line
			c='\n';		//Swap it for a \n
    resp_buffer[i]=c;
    i++;
    resp_buffer[i]='\0';
		// "> " signals the end of a response
		if(i>1 && resp_buffer[i-2]=='>') break;
  }

  printf("%s",resp_buffer); //print response
}

/*
Waits for the response from SEM Core,
but marks the asked line with "<-----"
*/
void wait_resp_w_word (unsigned int word) {
	unsigned int line=0;
  char resp_buffer[1400];
  unsigned int i=0;
  char c;

  while (1) {
    //get byte from target
    c = cnsl_getchar();
    if (c=='\r')	//SEM core sends a \r at the end of each line
			c='\n';		//Swap it for a \n
    resp_buffer[i]=c;
    i++;
    resp_buffer[i]='\0';
		// "> " signals the end of a response
		if(i>1 && resp_buffer[i-2]=='>') break;
  }

	//find line with requested <word> while printing the response
	for (i=0; resp_buffer[i] != '\0'; i++) {
		if(resp_buffer[i]=='\n') {
			if (line-1==word)
				printf(" <--------");
			line++;
		}
		printf("%c", resp_buffer[i]);
	}
}

/*
Enters IDLE state and waits for response
*/
void idle_cmd() {

	if (!IDLE) {
		cnsl_puts("I\r"); //Enter IDLE state

		wait_resp();
		IDLE=1;
	}
}

/*
Enters OBSERVATION state and waits for response
*/
void observation_cmd() {

	idle_cmd();
	cnsl_puts("O\r"); //Enter OBSERVATION state

	wait_resp();
	IDLE = 0;
}

/*
Enters DETECT ONLY state and waits for response
*/
void detect_only_cmd() {

	idle_cmd();
	cnsl_puts("D\r"); //Enter DETECT ONLY state

	wait_resp();
	IDLE = 0;
}

/*
Enters DIAGNOSTIC SCAN state and waits for response
*/
void diagnostic_cmd() {

	idle_cmd();
	cnsl_puts("U\r"); //Enter DIAGNOSTIC SCAN state

	wait_resp();
}

/*
Performs a software reset on the SEM core
The reset returns an initilization report
*/
void reset_cmd() {

	idle_cmd();
	cnsl_puts("R 00\r"); //Send reset command

	wait_resp();
	IDLE = 0;
}

/*
Ask the core for a status report
*/
void status_cmd() {

	idle_cmd();
	cnsl_puts("S\r"); //Send status command

	wait_resp();
}

/*
Prints the contents of <lfa> Configuration Frame present in <slr> (Super Logic Region)
<word> argument is used to signal (with "<-----") which line contains the word we're interested in
<bit> argument is ignored, but necessary
*/
void query_cmd (unsigned int slr, unsigned int lfa, unsigned int word, unsigned int bit) {
	unsigned int location = 0;

	idle_cmd();
	//Assemble the location
	location |= bit;
	location |= word << 5;
	location |= lfa << 12;
	location |= slr << 29;

	cnsl_printf("Q C0%08X\r", location); //Send query command

	wait_resp_w_word(word);
}

/*
Injects an error (bit flip) in given address with 10 digits (hex)
*/
void err_injection_cmd_in_addr (char addr [10]) {
	idle_cmd();

  //uart_printf("Injecting error at addr: %s\n", addr);
	cnsl_printf("N %s\r", addr); //Send error injection command

	wait_resp();
}

/*
Injects an error (bit flip) in <bit>, of <word> in <lfa> (Linear Frame Address),
of <slr> (Super Logic Region)
*/
void err_injection_cmd (unsigned int slr, unsigned int lfa, unsigned int word, unsigned int bit) {
	char cmd_buffer [11] = "";
	unsigned int location = 0;

	//uart_printf("Injecting error frame: %d\t word: %d\t bit: %d\n", lfa, word, bit);

	//Assemble the location
	location |= bit;
	location |= word << 5;
	location |= lfa << 12;
	location |= slr << 29;

  sprintf(cmd_buffer,"C0%08X", location);
  err_injection_cmd_in_addr (cmd_buffer);

}
