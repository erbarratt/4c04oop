#ifndef INC_4C04_WINDOW_CLASS_H
#define INC_4C04_WINDOW_CLASS_H

	/**
	* Private Window4c04_t declaration
	*/
		typedef struct{
			
			//public props
				unsigned int height;
				unsigned int width;
				XEvent* evnt;
				Display* display;
				Window window;
				int screen;
				XFontStruct* font;
				GC gc;
				struct Debug4c04_t* debug;
			
			//public methods
				void (*randKeycodeEvnt)(void * eOBJ);
				void (*getNextEvent)(void * eOBJ);
				void (*clearWindow)(void * eOBJ);
				void (*closeWindow)(void * eOBJ);
				
			//private props
			
			//private methods
			
		} Window4c04_t;
		
	void Window4c04_randKeyCodeEvnt(void * eOBJ);
	void Window4c04_getNextEvent(void * eOBJ);
	void Window4c04_clearWindow(void * eOBJ);
	void Window4c04_closeWindow(void * eOBJ);

#endif //INC_4C04_WINDOW_CLASS_H
