/**
* Debug class public delcaration file
*
* Debug has no _pri.h file.
*/
#ifndef INC_4C04_DEBUG_H
#define INC_4C04_DEBUG_H

	/**
	* Public Debug4c04_t declaration
	*/
		struct Debug4c04_t {
			
			//public props
			
			//public methods
				void (*consoleLog)(char * msg);
				void (*consoleErr)(char * msg);
			
		};
		
		typedef struct Debug4c04_t Debug4c04_t;
	
	//public function delcaration footprint
		void Debug4c04_t_instantiate(void * eOBJ);

#endif //INC_4C04_DEBUG_H
