/*
* Window class source file
*
* The window class deal with management of the X11 window, creation, population and temrination
*/
#include "lib/window_pub.h"         //public declaration
#include "lib/window_class.h"       //private typedef declaration
		
	/**
	* Create the window of a given height and width
	* @param void* eOBJ Self object
	* @param unsigned int height Window height
	* @param unsigned int width Window width
	* @return void
	*/
		void Window4c04_t_instantiate(void * eOBJ, struct Debug4c04_t* debug, unsigned int height, unsigned int width)
		{
			eSELF(Window4c04_t);
			
			//bind properties
			
				//instantiate sub object
					self->debug = debug;
			
				//set public window sizes
					self->height = height;
					self->width = width;
					
				//set aside space for evnt??
					self->evnt = (XEvent*)malloc(sizeof(XEvent));
				
				//open a connection to the x server that controls a display
				//NULL uses value of the DISPLAY env var
					self->display = XOpenDisplay(NULL);
					
				//if not set, then probably on only terminal.
					if (self->display == NULL) {
						self->debug->consoleErr("\x1b[31mCannot open display. Run from linux desktop GUI or through Xming + PuTTy on Windows.\x1b[0m\n");
					}
				
				//get default screen (screen 1) of system
					self->screen = DefaultScreen(self->display);
				
				//define the window to open
					self->window = XCreateSimpleWindow(
						self->display,                                      //display pointer
						RootWindow(self->display, self->screen),   //parent window
						10,                                                 //x
						10,                                                 //y
						self->width,                                        //width
						self->height,                                       //height 20 lines @ 30px line height, 20px font height + 10 border
						0,                                                  //border width
						0x252525,                                           //border color
						0x252525                                            //background color
					);
				
				//ask the X server to report the events set in the x mask
					XSelectInput(self->display, self->window, ExposureMask | KeyPressMask);
				
				//map the window to the display, and use above to generate Expose events
					XMapWindow(self->display, self->window);
				
				//set graphics context and font
					self->font = XLoadQueryFont(self->display, "10x20");
					self->gc = XCreateGC(self->display, self->window, 0, 0);
					XSetFont(self->display, self->gc, self->font->fid);
					
			//bind methods
				
				//public
					self->randKeycodeEvnt = &Window4c04_randKeyCodeEvnt;
					self->getNextEvent = &Window4c04_getNextEvent;
					self->clearWindow = &Window4c04_clearWindow;
					self->closeWindow = &Window4c04_closeWindow;
			
		}
	
	/**
	* Generate a random keycode event and send to display
	* @param void* eOBJ Self object
	* @return void
	*/
		void Window4c04_randKeyCodeEvnt(void * eOBJ)
		{
			eSELF(Window4c04_t);
		
			//create a random keypress event and send it, so the following XNextEvent catches it
				XKeyEvent event;
				event.display     = self->display;
				event.window      = self->window;
				event.root        = RootWindow(self->display, self->screen);
				event.subwindow   = None;
				event.time        = CurrentTime;
				event.x           = 1;
				event.y           = 1;
				event.x_root      = 1;
				event.y_root      = 1;
				event.same_screen = True;
				event.keycode     = XKeysymToKeycode(self->display, 42);
				event.state       = 0;
				event.type = KeyPress;
				
				XSendEvent(self->display, self->window, True, KeyPressMask, (XEvent *)&event);
		
		}

	/**
	* Get next event from event queue in display
	* @param void* eOBJ Self object
	* @return void
	*/
		void Window4c04_getNextEvent(void * eOBJ)
		{
			eSELF(Window4c04_t);
			XNextEvent(self->display, self->evnt);
		}

	/**
	* Get next event from event queue in display
	* @param void* eOBJ Self object
	* @return void
	*/
		void Window4c04_clearWindow(void * eOBJ)
		{
			eSELF(Window4c04_t);
			XClearWindow(self->display, self->window);
		}

	/**
	* Close the display
	* @param void* eOBJ Self object
	* @return void
	*/
		void Window4c04_closeWindow(void * eOBJ)
		{
			eSELF(Window4c04_t);
			XCloseDisplay(self->display);
		}
