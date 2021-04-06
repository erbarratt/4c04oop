#include <stdio.h>
#include <stdlib.h>
#include "lib/debug.h"
#include "lib/eOOPc.h"

	typedef struct {
		
		//public props
		
		//public methods
			void (*consoleLog)(char * msg);
			void (*consoleErr)(char * msg);
		
	} Debug4c04_t;

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
