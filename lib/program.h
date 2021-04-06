#ifndef INC_4C04_PROGRAM_H
#define INC_4C04_PROGRAM_H

	#include "eOOPc.h"
	#include "strings.h"
	
	/**
	* Public Program4c04_t declaration
	*/
		struct Program4c04_t {

			//parent - must be full struct and first
				eDIR_EXTENDS(String4c04_t, strings);
			
			//public props
				char code[128][100];
				uint16_t memLength;
				uint16_t progMemLoc;
				uint16_t stackMemLoc;
			
			//public methods
				void (*disassembleCode)(void * eOBJ);
			
		};
	
	//public function delcaration footprint
		void Program4c04_t_instantiate(void * eOBJ);

#endif //INC_4C04_PROGRAM_H
