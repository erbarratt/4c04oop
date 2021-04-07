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
		void Debug4c04_t_consoleLog(char * msg);
		void Debug4c04_t_consoleErr(char * msg);

#endif //INC_4C04_DEBUG_H
