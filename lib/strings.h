#ifndef INC_4C04_STRINGS_H
#define INC_4C04_STRINGS_H

#include <stddef.h>
#include <stdint.h>

/**
* Public Window4c04_t declaration
*/
		struct String4c04_t {
			
			//public props
			
			//public methods
				char * (*strncatcat)(char * dest, size_t max, const char* strArgs, ...);
				char * (*hex)(char * dest, uint32_t hex, size_t size);
			
		};
	
	//public function delcaration footprint
		void String4c04_t_instantiate(void * eOBJ);
		char * String4c04_t_strncatcat(char * dest, size_t max, const char* strArgs, ...);
		char * String4c04_t_hex(char * dest, uint32_t hex, size_t size);

#endif //INC_4C04_STRINGS_H
