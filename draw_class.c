/*
* Draw class source file
*
* The draw class creates the strings to draw to the window from the different elements
* of the 4c04 system
*/
#include <stdio.h>
#include "lib/draw_pub.h"
#include "lib/draw_class.h"
#include "lib/window_pub.h"
#include "lib/program_pub.h"

	/**
	* Instantiate Draw VMT object
	* @param void* eOBJ self
	* @return void
	*/
		void Draw4c04_t_vmt_instantiate(void * eOBJ)
		{
			eSELF(Draw4c04_t_vmt);
			
			self->drawString = &Draw4c04_t_vmt_drawString;
			self->drawCPU = &Draw4c04_t_vmt_drawCPU;
			self->drawRam = &Draw4c04_t_vmt_drawRam;
			self->drawCode = &Draw4c04_t_vmt_drawCode;
			
		}
		
	/**
	* Draw a string to the window at a given location and color
	* @param unisgned long color Hex code of colour
	* @param int x X coord - text pivot is bottom left of first character
	* @param int y Y coord - text pivot is bottom left of first character
	* @param char * str The text to be output
	* @return void
	*/
		void Draw4c04_t_vmt_drawString(void * eOBJ, unsigned long color, int x, int y, char * str)
		{
			eSELF(Draw4c04_t);
			
			XSetForeground(self->window->display, self->window->gc, color);
			
			XSetBackground(self->window->display, self->window->gc, 0x252525);
			XDrawString(self->window->display, self->window->window, self->window->gc, x, y, str, (int)strlen(str));
			
		}
		
	/**
	* Draw the current status of the CPU, color coded
	* @return void
	*/
		void Draw4c04_t_vmt_drawCPU(void * eOBJ)
		{
			eSELF(Draw4c04_t);
			
			//make pointer to parent to use it's methods
			//saves us typing self->strings->
			ePARENT(String4c04_t, strings);
			
			char hashTemp[5];
			char msg[50] = "CPU Status";
			int msgX = 780 + (int)(200 - (strlen(msg)*10)) / 2;
			
			self->vmt->drawString(self, COL_CYAN, msgX, 30, msg);
			
			//instruction txt
				strcat(strncpy(msg, "Instruction: ", 14), self->cpu->instructions[self->cpu->OPC].name);
				msgX = 780 + (int)(200 - (strlen(msg)*10)) / 2;
				self->vmt->drawString(self, ((self->cpu->getDrawflag(self->cpu, OPC) == 1) ? COL_MAGENTA : COL_WHITE), msgX, 60, msg);
			
			//PCO
				strings->strncatcat(strncpy(msg, "PCO-[", 6), 49, strings->hex(self->cpu->PCO, 2, hashTemp), "]", NULL);
				self->vmt->drawString(self, ((self->cpu->getDrawflag(self->cpu, PCO) == 1) ? COL_MAGENTA : COL_WHITE), 795, 90, msg);
				
			//OPC
				strings->strncatcat(strncpy(msg, "OPC-[", 6), 49, strings->hex(self->cpu->OPC, 2, hashTemp), "]", NULL);
				self->vmt->drawString(self, ((self->cpu->getDrawflag(self->cpu, OPC) == 1) ? COL_MAGENTA : COL_WHITE), 885, 90, msg);
				
			//STP
				strings->strncatcat(strncpy(msg, "STP-[", 6), 49, strings->hex(self->cpu->STP, 2, hashTemp), "]", NULL);
				self->vmt->drawString(self, ((self->cpu->getDrawflag(self->cpu, STP) == 1) ? COL_MAGENTA : COL_WHITE), 795, 120, msg);
				
			//CRE
				strings->strncatcat(strncpy(msg, "CRE-[", 6), 49, strings->hex(self->cpu->CRE, 2, hashTemp), "]", NULL);
				self->vmt->drawString(self, ((self->cpu->CRE > 0) ? COL_MAGENTA : COL_WHITE), 885, 120, msg);
				
			//IR1
				strings->strncatcat(strncpy(msg, "IR1-[", 6), 49, strings->hex(self->cpu->IR1, 2, hashTemp), "]", NULL);
				self->vmt->drawString(self, ((self->cpu->getDrawflag(self->cpu, IR1) == 1) ? COL_ORANGE : COL_WHITE), 795, 150, msg);
				
			//IR2
				strings->strncatcat(strncpy(msg, "IR2-[", 6), 49, strings->hex(self->cpu->IR2, 2, hashTemp), "]", NULL);
				self->vmt->drawString(self, ((self->cpu->getDrawflag(self->cpu, IR2) == 1) ? COL_ORANGE : COL_WHITE), 885, 150, msg);
				
			//AR0
				strings->strncatcat(strncpy(msg, "AR0-[", 6), 49, strings->hex(self->cpu->AR0, 2, hashTemp), "]", NULL);
				self->vmt->drawString(self, ((self->cpu->getDrawflag(self->cpu, AR0) == 1) ? COL_GREEN : COL_WHITE), 795, 180, msg);
				
			//AR1
				strings->strncatcat(strncpy(msg, "AR1-[", 6), 49, strings->hex(self->cpu->AR1, 2, hashTemp), "]", NULL);
				self->vmt->drawString(self, ((self->cpu->getDrawflag(self->cpu, AR1) == 1) ? COL_GREEN : COL_WHITE), 885, 180, msg);
				
			//AR2
				strings->strncatcat(strncpy(msg, "AR2-[", 6), 49, strings->hex(self->cpu->AR2, 2, hashTemp), "]", NULL);
				self->vmt->drawString(self, ((self->cpu->getDrawflag(self->cpu, AR2) == 1) ? COL_GREEN : COL_WHITE), 795, 210, msg);
				
			//AR3
				strings->strncatcat(strncpy(msg, "AR3-[", 6), 49, strings->hex(self->cpu->AR3, 2, hashTemp), "]", NULL);
				self->vmt->drawString(self, ((self->cpu->getDrawflag(self->cpu, AR3) == 1) ? COL_GREEN : COL_WHITE), 885, 210, msg);
				
			//cpu status flags
				self->vmt->drawString(self, ((self->cpu->C) ? COL_GREEN : COL_RED), 805, 240, ((self->cpu->C) ? "C:1" : "C:0"));
				self->vmt->drawString(self, ((self->cpu->Z) ? COL_GREEN : COL_RED), 845, 240, ((self->cpu->Z) ? "Z:1" : "Z:0"));
				self->vmt->drawString(self, ((self->cpu->V) ? COL_GREEN : COL_RED), 885, 240, ((self->cpu->V) ? "V:1" : "V:0"));
				self->vmt->drawString(self, ((self->cpu->N) ? COL_GREEN : COL_RED), 925, 240, ((self->cpu->N) ? "N:1" : "N:0"));
				
		}
		
	/**
	* Draw the contents of memory in a matrix of set height and width
	* @return void
	*/
		void Draw4c04_t_vmt_drawRam(void * eOBJ)
		{
			eSELF(Draw4c04_t);
			
			//make pointer to parent to use it's methods
			//saves us typing self->strings->
			ePARENT(String4c04_t, strings);
		
			uint8_t nAddr = 0x00;
			
			int y = 30; //10 + 20 height font
			int lineHeight = 30;
			int pcCol = 0, pcY = 0, pcX;
			uint8_t pcVal = 0;
			
			char txt[120];
			char hashTemp[5];
			
			//draw mem table header in cyan
				strncpy(txt, " RAM", 5);
				
				for (uint8_t col = 0; col < 16; col++){
				
					if(col == 8){
						strcat(txt, "  ");
					}
					
					if(col == 0){
						strcat(txt, " 00");
					} else {
						strings->strncatcat(txt, 119, " ", strings->hex(col, 2, hashTemp), NULL);
					}
					
				}
				
				strcat(txt, "      HEX > ASCII");
				self->vmt->drawString(self, COL_CYAN, 10, y, txt);
				
			//now draw bulk
				y += lineHeight;
				
				for (int row = 0; row < 16; row++){
				
					//shift stack down a bit
						if(row == 7){
							y += 15;
						}
				
					//split memory into two blocks
						if(row == 8){
						
							y += lineHeight  / 2;
							
							strncpy(txt, " ROM", 5);
				
							for (uint8_t col = 0; col < 16; col++){
							
								if(col == 8){
									strcat(txt, "  ");
								}
								
								if(col == 0){
									strcat(txt, " 00");
								} else {
									strings->strncatcat(txt, 119, " ", strings->hex(col, 2, hashTemp), NULL);
								}
								
							}
							
							strcat(txt, "      HEX > ASCII");
							self->vmt->drawString(self, COL_CYAN, 10, y, txt);
							
							y += lineHeight;
							
						}
				
					//draw the starting address of this line of bytes
						strcat(strncpy(txt, " $", 3), strings->hex(nAddr, 2, hashTemp));
						self->vmt->drawString(self, COL_CYAN, 10, y, txt);
					
					//now output the line of hex bytes
						strncpy(txt, "", 2);
						
						for (int col = 0; col < 16; col++){
						
							if(col == 8){
								strcat(txt, "  ");
							}
						
							if(self->cpu->RAM[nAddr] == 0){
								strcat(txt, " 00");
							} else {
								strings->strncatcat(txt, 119, " ", strings->hex(self->cpu->RAM[nAddr], 2, hashTemp), NULL);
							}
							
							if(nAddr == self->cpu->PCO-1 && self->cpu->PCO-1 >= PROG_MEM_LOC){
								pcCol = col;
								pcY = y;
								pcVal = self->cpu->RAM[nAddr];
							}
							
							nAddr++;
						}
					
					//now convert to ascii output
						strcat(txt, "  |");
						
						nAddr = (uint8_t)(nAddr - 0x10); //16
						for (int col = 0; col < 16; col++){
							
							if(col == 8){
								strcat(txt, " ");
							}
						
							if ((unsigned char)self->cpu->RAM[nAddr] >= ' ' && (unsigned char)self->cpu->RAM[nAddr] <= '~'){
								char c[10] = " ";
								snprintf(c, 2, "%c",  self->cpu->RAM[nAddr]);
								strcat(txt,c);
							} else {
								strcat(txt,".");
							}
							
							nAddr++;
						}
						
						strcat(txt,"|");
					
						if(row == 7){
						
							char * msg = "<- Stack";
							int msgX = 780 + (int)(200 - (strlen(msg)*10)) / 2;
							self->vmt->drawString(self, COL_CYAN, msgX, (9*30)+15, msg);
						
						}
					
					//draw line to screen
						self->vmt->drawString(self, 0xffffff, 50, y, txt);
					
					y += lineHeight;
					
				}
				
			//draw locations AFTER the above, so it's atop it
			//PC Hex value
				pcX = 50 + (pcCol*30) + ((pcCol >= 8) ? 20 : 0);
				
				strncpy(txt, " ", 2);
				if(pcVal == 0){
					strcat(txt, "00");
				} else {
					strcat(txt, strings->hex(pcVal, 2, hashTemp));
				}
				
				self->vmt->drawString(self, COL_ORANGE, pcX, pcY, txt);
				
			//now highlight ascii output
				pcX = 570 + (pcCol*10) + ((pcCol >= 8) ? 10 : 0);
				
				strncpy(txt, " ", 2);
				if (pcVal >= ' ' && pcVal <= '~'){
					char c[10] = " ";
					snprintf(c, 2, "%c",  pcVal);
					strcat(txt,c);
				} else {
					strcat(txt,".");
				}
				
				self->vmt->drawString(self, COL_ORANGE, pcX, pcY, txt);
			
		}
		
	/**
	* Draw codes lines surrounding last opcode address location
	* @param Display * display X11 display
	* @param Window window X11 window
	* @param GC gc X11 Graphics Context
	* @return void
	*/
		void Draw4c04_t_vmt_drawCode(void* eOBJ, uint8_t addr)
		{
		
			eSELF(Draw4c04_t);
			
			//printf("%p\n", (void*)self->program->code);
			
			for(uint16_t i = PROG_MEM_LOC; i < MEM_LENGTH; i++){
				//printf("--%#x: %p %s\n", i, (void*)self->program->code[i], self->program->code[i]);
			}
			
			//printf("%#x\n", addr);
			//printf("%s\n", self->program->code[addr]);
		
			char * msg = "Code Lines";
			int msgX = 780 + (int)(200 - (strlen(msg)*10)) / 2;
			self->vmt->drawString(self, COL_CYAN, msgX, 330, msg);
		
			char lines[8][100];
			
			int lower = 0, count = 0, nullLines = 0;
			uint16_t start;
			uint16_t lastOpAddrFound = 0;
			start = addr;
			
			//midpoint
				uint8_t midPoint = 3;
			
			//go backwards finding the 3 instructions before the current.
			//in the dissassembler, inter-instruction memorylocations are padded with ---
			//these are ignored as aren't instructions
			//programs are always surrounded with NOP commands from memory + code[] init
				while(lower < midPoint){
					
					start--;
					//printf("%#x\n", start);
					//printf("%s\n", self->program->code[start]);
					if(strcmp(self->program->code[start], "---") != 0){
						lower++;
						lastOpAddrFound = start;
						//reset null lines so we don't count 6 overall
						nullLines = 0;
					} else {
					
						nullLines++;
						if(nullLines == 6){
							start = lastOpAddrFound;
							
							for(int i = 0; i <= midPoint-lower; i++){
								strcpy(lines[i], "---");
							}
							
							count = midPoint-lower;
							lower = midPoint;
						}
						
					}
				
				}
				
			//now move forward from this position, ignore --- and store the op line
				while(count < 8){
				
					if(strcmp(self->program->code[start], "---") != 0 && start <= MEM_LENGTH){
						strcpy(lines[count], self->program->code[start]);
						count++;
					}
					
					start++;
				
				}
			
			//finally now we have full lines, output them highlighting current instruction
				for(int i = 0; i < 8; i++){
				
					int lineX = 780 + (int)(200 - (strlen(lines[i])*10)) / 2;
					int lineY = (12*30) + (i*30);
				
					if(i == midPoint){
						//draw cyan
						self->vmt->drawString(self, COL_CYAN, lineX, lineY, lines[i]);
					} else {
						//draw white
						self->vmt->drawString(self, COL_WHITE, lineX, lineY, lines[i]);
					}
				}
		
		}

	void Draw4c04_t_instantiate(void * eOBJ, struct Window4c04_t * window, struct CPU4c04_t* cpu, struct Program4c04_t* program)
	{
		eSELF(Draw4c04_t);
		
		//instantiate parent object
			eCONSTRUCT(String4c04_t, &self->strings);
		
		self->program = program;
		self->window = window;
		self->cpu = cpu;
		
		//private methods vmt
			self->vmt = eNEW(Draw4c04_t_vmt);
			eCONSTRUCT(Draw4c04_t_vmt, self->vmt);
		
		self->draw = &Window4c04_t_draw;
		
	}

	void Window4c04_t_draw(void * eOBJ)
	{
		eSELF(Draw4c04_t);
		
		//printf("%p\n", (void*)self->program->code);
		
		//clear window
			eCALLna(self->window, clearWindow);
			
			self->vmt->drawCPU(self);
			self->vmt->drawRam(self);
			self->vmt->drawCode(self, self->cpu->lastOpAddr);
		
		char * msg = "Press Space to step through CPU Cycles. Q = Quit, R = Reset, A = Slow Auto, F = Fast Auto.";
		int msgX = (int)(1000 - (strlen(msg)*10)) / 2;
		self->vmt->drawString(self, COL_WHITE, msgX, 615, msg);
	
	}
