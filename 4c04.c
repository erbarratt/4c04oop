/**
*
* 4c04 L EOT Processor Emulator, oop edition
*
* The 4c04 is a fictional virtual CPU, complete with it's own assembly language.
*
* It's a true 8-bit (byte) processor; it can only address memory locations 0-255 (256 bytes),
* and store 8 bits on one of four addressable registers.
*
* The memory is laid out as follows:
*
* 	- 0x00 - 0x6F is 112 bytes of none reserved RAM
* 	- 0x70 - 0x7F is 16 bytes of reserved Stack memory
* 	- 0x80 - 0xFF is 128 bytes of reserved ROM for program logic and data
*
* This application mounts the 4c04 program through the use of an included assembler. Put your assembly in a file called "prog.txt" in
* the same directory as the executable, and that will be assembled into the ROM area of memory.
*
* Details for the Assembly syntax can be found in draw.c
*
* To compile, you must link the X11 libraries
* On Linux:
* 		sudo apt-get install -y libx11-dev
*
* The emulator requires an X11 enabled desktop environment.
* On Linux:
* 		sudo apt install x11-apps
* On Windows:
* 		Install XMing
* 		Install Putty
* 		Enable and Install Ubuntu for WSL (Windows Subsystem for Linux)
* 		Install X11 on Ubuntu
* 		Configure Putty to forward X11
* 		Launch via Putty from Ubuntu (./4c04)
*
*/
#include <unistd.h> //usleep
#include <stdbool.h>
#include "lib/eOOPc.h"
#include "lib/window_pub.h"
#include "lib/debug_pub.h"
#include "lib/program_pub.h"

int main(void){

	struct Debug4c04_t* console = eNEW(Debug4c04_t);
	eCONSTRUCT(Debug4c04_t, console);
	
	struct CPU4c04_t* cpu = eNEW(CPU4c04_t);
	eCONSTRUCT(CPU4c04_t, cpu);

	struct Program4c04_t* program = eNEW(Program4c04_t);
	
	eCONSTRUCT(Program4c04_t, program, cpu, console);

	console->consoleLog("4c04 L EOT CPU Emulator\nSystem Booting...\n");

	eCALLna(program,loadProgram);

	console->consoleLog("Program Loaded...\n");

	eCALLna(program,disassembleCode);

	console->consoleLog("Opening Window...\n");

	struct Window4c04_t * window = eNEW(Window4c04_t);
	eCONSTRUCT(Window4c04_t, window, 640, 1000);
	eCALLna(window, getNextEvent);

	//auto play?
		bool autoPlaySlow = false;
		bool autoPlayFast = false;

	while (1) {

		if(autoPlaySlow || autoPlayFast){

			usleep(autoPlaySlow ? 200000 : 500);

			//send random key code so auto continues
				eCALLna(window, randKeycodeEvnt);

		}

		eCALLna(window, getNextEvent);

		if (window->evnt->type == KeyPress) {

			if(window->evnt->xkey.keycode == 24){

				//quit "q"
					break;

			} else if (window->evnt->xkey.keycode == 27) {

				//restart "r"
					eCALLna(cpu, reset);

				//load program again
					eCALLna(program,loadProgram);

				//dissemble code
					eCALLna(program,disassembleCode);

				//draw current state
					//draw_all(display, window, gc);

			} else if(window->evnt->xkey.keycode == 38){

				//autoplay toggle
					autoPlaySlow = (autoPlaySlow) ? false : true;
					autoPlayFast = false;

			}  else if(window->evnt->xkey.keycode == 39){

				//autoplay toggle
					autoPlayFast = (autoPlayFast) ? false : true;
					autoPlaySlow = false;

			} else {

				//progress through next cycle
					eCALLna(cpu,execute);

				//draw current state
					//draw_all(display, window, gc);

			}

		} else {

			//all other events
				//draw_all(display, window, gc);

		}

	}

	eCALLna(window, closeWindow);

	eDESTROY(window);
	
	return 0;
 
}
