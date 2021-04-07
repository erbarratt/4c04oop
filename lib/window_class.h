#ifndef INC_4C04_WINDOW_CLASS_H
#define INC_4C04_WINDOW_CLASS_H

	/**
	* Private Window4c04_t declaration
	*/
		typedef struct  {
			
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
				
			//private props
				struct Debug4c04_t* debug;
				
			//private methods
			
		} Window4c04_t;

#endif //INC_4C04_WINDOW_CLASS_H
