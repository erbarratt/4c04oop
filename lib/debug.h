#ifndef INC_4C04_DEBUG_H
#define INC_4C04_DEBUG_H

	/**
	* Public Window4c04_t declaration
	*/
		struct Debug4c04_t {
			
			//public props
			
			//public methods
				void (*consoleLog)(void * eOBJ, char * msg);
				void (*consoleErr)(void * eOBJ, char * msg);
			
		};
	
	//public function delcaration footprint
		void Debug4c04_t_instantiate(void * eOBJ);
		void Debug4c04_t_consoleLog(void * eOBJ, char * msg);
		void Debug4c04_t_consoleErr(void * eOBJ, char * msg);

#endif //INC_4C04_DEBUG_H
