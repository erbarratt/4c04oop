#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "lib/program.h"

	typedef struct {
		
		//public props
			char code[128][100];
			uint16_t memLength;
			uint16_t progMemLoc;
			uint16_t stackMemLoc;
		
		//public methods
			void (*disassembleCode)(void * eOBJ);
			
		//private props
			struct String4c04_t* strings;
		
	} Program4c04_t;
	
	/**
	* Dissassemble the memory program into coded lines to display
	* @param void* eOBJ Self object
	* @return void
	*/
		void Program4c04_t_disassembleCode(void * eOBJ)
		{
			eSELF(Program4c04_t);
			
			char line [50] = "";
			char num[5];
			char cycles[10];

			for(uint8_t i = 0; i < 128; i++){
				strncpy(self->code[i], self->strings->strncatcat(strcpy(line, "$"), 49, self->strings->hex(i, 2, num),": NOP c2", NULL), 12);
			}
		
			////start at program address
			//	uint16_t addr = self->progMemLoc;
			//	uint16_t lineAddr;
			//
			//while(addr < self->memLength){
			//
			//	//start line string
			//		lineAddr = addr;
			//		uint8_t opcode = cpu.RAM[addr];
			//		snprintf(cycles, 4,"%d", instructions[opcode].cycles);
			//		strings->strncatcat(strcpy(line, "$"), 49, self->strings->hex(addr, 2, num),": ",instructions[opcode].name," c",cycles, NULL);
			//
			//	//get next addr
			//		addr++;
			//
			//	//use instructions array to fill in the mem locations where data and not opcodes are
			//		for(int i = 0; i < instructions[opcode].pcoShifts; i++){
			//
			//			strcpy(self->code[addr], "---");
			//			addr++;
			//
			//		}
			//
			//	//write that line to code array
			//		strcpy(self->code[lineAddr], line);
			//
			//}
			//
			//for(uint16_t i = self->progMemLoc; i < self->memLength; i++){
			//	//	printf("%s\n", code[i]);
			//}
		
		}

	/**
	* Instantiate Program Object
	* @param void* eOBJ Self object
	* @return void
	*/
		void Program4c04_t_instantiate(void * eOBJ)
		{
			eSELF(Program4c04_t);
			
			//instantiate sub object
				eNEW_NOARGS_S(String4c04_t, self->strings);
			
			//bind params
				self->memLength = 256;
				self->progMemLoc = 0x80;
				self->stackMemLoc = 0x7F;
			
			//bind methods
				
				//public
					self->disassembleCode = &Program4c04_t_disassembleCode;
					
		}
		
	
	
