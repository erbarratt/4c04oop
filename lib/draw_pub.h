#ifndef INC_4C04_DRAW_PUB_H
#define INC_4C04_DRAW_PUB_H

	#include "eOOPc.h"
	#include "strings_pub.h"
	#include "cpu_pub.h"
	
	/**
	* Public Draw4c04_t declaration
	*/
		struct Draw4c04_t {

			//parent - must be full struct and first
				eINHERITS(String4c04_t, strings);
			
			//public props
				struct Program4c04_t* program;
				struct Window4c04_t * window;
				struct CPU4c04_t * cpu;
			
			//public methods
				void (*draw)(void * eOBJ);
			
		};
		
		void Draw4c04_t_instantiate(void * eOBJ, struct Window4c04_t * window, struct CPU4c04_t* cpu, struct Program4c04_t* program);

#endif //INC_4C04_DRAW_PUB_H
