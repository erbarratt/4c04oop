/**
* Strings class public delcaration file
*
* Strings has no _pri.h file.
*/
#ifndef INC_4C04_STRINGS_H
#define INC_4C04_STRINGS_H

#include <stdint.h>

	/**
	* Public String4c04_t declaration
	*/
		struct String4c04_t {
			
			//public methods
				char * (*strncatcat)(char * dest, size_t max, const char* strArgs, ...);
				char * (*hex)(uint32_t hex, size_t size, char * dest);
			
		};
		
	//no private so, put typedef here
		typedef struct String4c04_t String4c04_t;
	
	//public function delcaration footprint
		void String4c04_t_instantiate(void * eOBJ);
		

#endif //INC_4C04_STRINGS_H
