/*
* Debug class source file
*
* Since the debug class struct only has public members, there is no need for a _pri.h file,
* therefor private source function declarations are in this file
*
* The debug class simply writes messages to the console or stderr
*/
#include <stdio.h>
#include "lib/debug_pub.h"
#include "lib/eOOPc.h"

	//private source function declarations
		void Debug4c04_t_consoleLog(char * msg);
		void Debug4c04_t_consoleErr(char * msg);

	/**
	* Create the window of a given height and width
	* @param void* eOBJ Self object
	* @return void
	*/
		void Debug4c04_t_instantiate(void * eOBJ)
		{
			eSELF(Debug4c04_t);
			
			//bind methods
				
				//public
					self->consoleLog = &Debug4c04_t_consoleLog;
					self->consoleErr = &Debug4c04_t_consoleErr;
					
		}

	/**
	* Print to console
	* @return void
	*/
		void Debug4c04_t_consoleLog(char * msg){
			printf("%s", msg);
		}
		
	/**
	* Print to stderr
	* @return void
	*/
		void Debug4c04_t_consoleErr(char * msg){
			fprintf(stderr, "%s", msg);
			exit(1);
		}
