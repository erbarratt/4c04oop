#ifndef INC_4C04_STRINGS_H
#define INC_4C04_STRINGS_H

#include <stddef.h>
#include <stdint.h>

	/**
	* Public String4c04_t declaration
	*/
		struct String4c04_t {
			
			//public methods
				char * (*strncatcat)(char * dest, size_t max, const char* strArgs, ...);
				char * (*hex)(uint32_t hex, size_t size, char * dest);
			
		};
	
	//public function delcaration footprint
		void String4c04_t_instantiate(void * eOBJ);
		char * String4c04_t_strncatcat(char * dest, size_t max, const char* strArgs, ...);
		char * String4c04_t_hex(uint32_t hex, size_t size, char * dest);

#endif //INC_4C04_STRINGS_H
