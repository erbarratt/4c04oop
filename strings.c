#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "lib/strings.h"
#include "lib/eOOPc.h"

	typedef struct {
		
		//public props
		
		//public methods
			char * (*strncatcat)(char * dest, size_t max, const char* strArgs, ...);
			char * (*hex)(char * dest, uint32_t hex, size_t size);
		
	} String4c04_t;

	/**
	* Create the window of a given height and width
	* @param void* eOBJ Self object
	* @return void
	*/
		void String4c04_t_instantiate(void * eOBJ)
		{
			eSELF(String4c04_t);
			
			//bind methods
				
				//public
					self->strncatcat = &String4c04_t_strncatcat;
					self->hex = &String4c04_t_hex;
					
		}

	/**
	* Print to console
	* @return void
	*/
		char * String4c04_t_strncatcat(char * dest, size_t max, const char* strArgs, ...)
		{
			va_list valist;
			va_start(valist, strArgs);
			const char* str = strArgs;
			while (str != NULL){
				if(strlen(dest) + strlen(str) > max){
					strncpy ( dest+strlen(dest), str, max-strlen(dest) );
					return dest;
				}
				strcat(dest, str);
		        str = va_arg(valist, const char *);
			}
		    va_end(valist);
		    return dest;
		}
		
	/**
	* Print to stderr
	* @return void
	*/
		char * String4c04_t_hex(char * dest, uint32_t hex, size_t size)
		{
			//clamp size to at least 1 char
				size = (size < 1) ? 1 : size;
				size = (size > 8) ? 8 : size;
			
			//build format string
			// "%0<size>X"
				char digits[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8' };
				char formatInj[] = {digits[size], 'X'};
				char format[] = {'%', '0', formatInj[0], formatInj[1]};
			
			//create temp string and fill with blanks to intialise
				char tmp[size+1]; //max 8 chars
				for(int i = 0; i < (int)size; i++){
					tmp[i] = ' ';
				}
				
			//read the hex number into the tmp string by size+1 length in the format above
				snprintf(tmp, size+1, format, hex);
				
			//set last char as string null
				tmp[size] = '\0';
				
			//copy those bytes into the destination string
				strncpy(dest, tmp, size+1);
				
			return dest;
			
		}
