#ifndef INC_4C04_WINDOW_H
#define INC_4C04_WINDOW_H

	#include "eOOPc.h"
	#include <X11/Xlib.h>

	/**
	* Public Window4c04_t declaration
	*/
		struct Window4c04_t {
			
			//public props
				unsigned int height;
				unsigned int width;
				XEvent* evnt;
				Display* display;
				Window window;
				int screen;
				XFontStruct* font;
				GC gc;
			
			//public methods
				void (*randKeycodeEvnt)(void * eOBJ);
				void (*getNextEvent)(void * eOBJ);
				void (*closeWindow)(void * eOBJ);
			
		};
	
	//public function delcaration footprint
		void Window4c04_t_instantiate(void * eOBJ, unsigned int height, unsigned int width);

#endif //INC_4C04_WINDOW_H
