#ifndef INC_4C04_DRAW_CLASS_H
#define INC_4C04_DRAW_CLASS_H

	/**
	* CPU private class virtual method table
	*/
		struct Draw4c04_t_vmt{
			
			void (*drawString)(void * eOBJ, unsigned long color, int x, int y, char * st);
			void (*drawCPU)(void * eOBJ);
			void (*drawRam)(void * eOBJ);
			void (*drawCode)(void * eOBJ, uint8_t addr);
		
		};
		
		typedef struct Draw4c04_t_vmt Draw4c04_t_vmt;
		
		void Draw4c04_t_vmt_drawString(void * eOBJ, unsigned long color, int x, int y, char * st);
		void Draw4c04_t_vmt_drawCPU(void * eOBJ);
		void Draw4c04_t_vmt_drawRam(void * eOBJ);
		void Draw4c04_t_vmt_drawCode(void* eOBJ, uint8_t addr);
	
	typedef struct {
	
		//parent - must be full struct and first
			eINHERITS(String4c04_t, strings);
			
		//public props
			struct Program4c04_t* program;
			struct Window4c04_t * window;
			struct CPU4c04_t * cpu;
		
		//public methods
			void (*draw)(void * eOBJ);
			
		//private methods
			Draw4c04_t_vmt * vmt;
	
	} Draw4c04_t;
	
	void Window4c04_t_draw(void * eOBJ);

#endif //INC_4C04_DRAW_CLASS_H
