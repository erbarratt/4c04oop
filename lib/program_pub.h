#ifndef INC_4C04_PROGRAM_PUB_H
#define INC_4C04_PROGRAM_CLASS_H

	#include "eOOPc.h"
	#include "strings_pub.h"
	#include "cpu_pub.h"
	
	/**
	* Public Program4c04_t declaration
	*/
		struct Program4c04_t {

			//parent - must be full struct and first
				eINHERITS(String4c04_t, strings);
			
			//public props
				struct CPU4c04_t* cpu;
				char code[128][100];
				uint16_t memLength;
				uint16_t progMemLoc;
				uint16_t stackMemLoc;
			
			//public methods
				void (*disassembleCode)(void * eOBJ);
			
		};
		
	typedef struct Program4c04_t Program4c04_t;
	
	//public function delcaration footprint
		void Program4c04_t_instantiate(void * eOBJ, struct CPU4c04_t* cpu);
		void Program4c04_t_disassembleCode(void * eOBJ);

#endif //INC_4C04_PROGRAM_PUB_H
