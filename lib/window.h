#ifndef INC_4C04_WINDOW_H
#define INC_4C04_WINDOW_H

	#include "eOOPc.h"
	#include <X11/Xlib.h>

	/**
	* Public Window4c04_t declaration
	*/
		struct Window4c04_t {
			
			//public props
				ePROP_DEC(unsigned int, height);
				ePROP_DEC(unsigned int, width);
				ePROP_DEC(XEvent*, evnt);
				ePROP_DEC(Display*, display);
				ePROP_DEC(Window, window);
				ePROP_DEC(int, screen);
				ePROP_DEC(XFontStruct*, font);
				ePROP_DEC(GC, gc);
			
			//public methods
				void (*randKeycodeEvnt)(void * eOBJ);
				void (*getNextEvent)(void * eOBJ);
				void (*closeWindow)(void * eOBJ);
			
		};
	
	//public function delcaration footprint
		void Window4c04_t_instantiate(void * eOBJ, unsigned int height, unsigned int width);
		void Window4c04_randKeyCodeEvnt(void * eOBJ);
		void Window4c04_getNextEvent(void * eOBJ);
		void Window4c04_closeWindow(void * eOBJ);

#endif //INC_4C04_WINDOW_H
