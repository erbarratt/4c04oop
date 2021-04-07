#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "lib/program_pub.h"
	
	/**
	* Instantiate Program Object
	* @param void* eOBJ Self object
	* @return void
	*/
		void Program4c04_t_instantiate(void * eOBJ, struct CPU4c04_t* cpu)
		{
			eSELF(Program4c04_t);
			
			//instantiate parent object
				eCONSTRUCT(String4c04_t, &self->strings);
			
			//bind params
				self->cpu = cpu;
				self->memLength = 256;
				self->progMemLoc = 0x80;
				self->stackMemLoc = 0x7F;
			
			//bind public methods
				self->disassembleCode = &Program4c04_t_disassembleCode;
					
		}
	
	/**
	* Dissassemble the memory program into coded lines to display
	* @param void* eOBJ Self object
	* @return void
	*/
		void Program4c04_t_disassembleCode(void* eOBJ)
		{
			eSELF(Program4c04_t);
			
			//make pointer to parent to use it's methods
			//saves us typing self->strings->
			ePARENT(String4c04_t, strings);
			
			char line [50] = "";
			char num[5];

			for(uint8_t i = 0; i < 128; i++){
				strncpy(self->code[i], strings->strncatcat(strcpy(line, "$"), 49, strings->hex(i, 2, num),": NOP c2", NULL), 12);
			}
		
			////start at program address
			//	uint16_t addr = self->progMemLoc;
			//	uint16_t lineAddr;
			//	char cycles[10];
			//
			//while(addr < self->memLength){
			//
			//	//start line string
			//		lineAddr = addr;
			//		uint8_t opcode = self->cpu->RAM[addr];
			//		snprintf(cycles, 4,"%d", self->cpu->instructions[opcode].cycles);
			//		strings->strncatcat(strcpy(line, "$"), 49, strings->hex(addr, 2, num),": ",self->cpu->instructions[opcode].name," c",cycles, NULL);
			//
			//	//get next addr
			//		addr++;
			//
			//	//use instructions array to fill in the mem locations where data and not opcodes are
			//		for(int i = 0; i < self->cpu->instructions[opcode].pcoShifts; i++){
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
