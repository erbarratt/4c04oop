#include "lib/cpu_pub.h"
#include "lib/cpu_class.h"

	/**
	* Instantiate CPU VMT object
	* @param void* eOBJ self
	* @return void
	*/
		void CPU4c04_t_vmt_instantiate(void * eOBJ)
		{
			eSELF(CPU4c04_t_vmt);
			
			self->loadInstructions = &CPU4c04_t_loadInstructions;
			
			self->setDrawflag = &CPU4c04_t_setDrawflag;
			self->getDrawflag = &CPU4c04_t_getDrawflag;
			self->read = &CPU4c04_t_read;
			self->write = &CPU4c04_t_write;
			self->stackPush = &CPU4c04_t_stackPush;
			self->stackPop = &CPU4c04_t_stackPop;
			self->regVal = &CPU4c04_t_regVal;
			self->setReg = &CPU4c04_t_setReg;
			self->setIr = &CPU4c04_t_setIr;
			self->setPco = &CPU4c04_t_setPco;
			
			self->NOP = &CPU4c04_t_NOP;
			self->LRV = &CPU4c04_t_LRV;
			self->LRM = &CPU4c04_t_LRM;
			self->LRR = &CPU4c04_t_LRR;
			self->LRT = &CPU4c04_t_LRT;
			
			self->STV = &CPU4c04_t_STV;
			self->STR = &CPU4c04_t_STR;
			
			self->BMP = &CPU4c04_t_BMP;
			self->SQR = &CPU4c04_t_SQR;
			self->ADD = &CPU4c04_t_ADD;
			self->SUB = &CPU4c04_t_SUB;
			
			self->JMP = &CPU4c04_t_JMP;
			self->JOC = &CPU4c04_t_JOC;
			self->JSR = &CPU4c04_t_JSR;
			self->RFS = &CPU4c04_t_RFS;
			
			self->AND = &CPU4c04_t_AND;
			self->BOR = &CPU4c04_t_BOR;
			self->NDR = &CPU4c04_t_NDR;
			self->ORR = &CPU4c04_t_ORR;
			self->XOV = &CPU4c04_t_XOV;
			self->XOR = &CPU4c04_t_XOR;
			
			self->PRS = &CPU4c04_t_PRS;
			self->PSR = &CPU4c04_t_PSR;
			
		}
	
	/**
	* Define instruction set and copy to object struct member
	* @param void* eOBJ self
	* @return void
	*/
		void CPU4c04_t_loadInstructions(void * eOBJ)
		{
		
			eSELF(CPU4c04_t);
			
			//copy instructions array into memory in object
				INSTRUCTION instructions[64] = {
					{"NOP", "No Operation",                        &CPU4c04_t_NOP, 2, 0},       //00
					
					{"LRV", "Load Register, from Value",           &CPU4c04_t_LRV, 3, 2},       //01 [#reg0-2] [#val]
					{"LRM", "Load Register, from Memory",          &CPU4c04_t_LRM, 4, 2},       //02 [#reg0-2] [$mem]
					{"LRR", "Load Register, from Register",        &CPU4c04_t_LRR, 4, 2},       //03 [#reg0-2] [#reg0-2]
					{"LRT", "Load Register, Transfer",             &CPU4c04_t_LRT, 4, 2},       //04 [#reg0-2] [#reg0-2]
					
					{"STV", "Store Register, to Mem Value",        &CPU4c04_t_STV, 3, 2},       //05 [#reg0-2] [$mem]
					{"STR", "Store Register, to Register Mem",     &CPU4c04_t_STR, 4, 2},       //06 [#reg0-2] [#reg0-2] Stores first reg in mem loc of second reg
					
					{"BMP", "Bump Register",                       &CPU4c04_t_BMP, 4, 1},       //07 [#reg0-2]++
					{"SQR", "Squash Register",                     &CPU4c04_t_SQR, 4, 1},       //08 [#reg0-2]--
			
					{"ADD", "Add RX to Ry, Store in RX",           &CPU4c04_t_ADD, 2, 2},       //09 [#reg0-2] [#reg0-2] Stores in first reg defined
					{"SUB", "Sub RY from RX, Store in RX",         &CPU4c04_t_SUB, 2, 2},       //0a [#reg0-2] [#reg0-2] Stores in first reg defined
					
					{"JMP", "Jump, from Value",                    &CPU4c04_t_JMP, 2, 1},       //0b [$mem]
					{"JOC", "Jump on Condition",                   &CPU4c04_t_JOC, 3, 2},       //0c [#con] [$mem]
					{"JSR", "Jump to Subroutine",                  &CPU4c04_t_JSR, 3, 1},       //0d [$mem]
					{"RFS", "Return from Subroutine",              &CPU4c04_t_RFS, 2, 0},       //0e
					
					{"AND", "Bitwise AND, from Value",             &CPU4c04_t_AND, 4, 2},       //0f [#reg0-2] [#val]
					{"BOR", "Bitwise OR, from Value",              &CPU4c04_t_BOR, 4, 2},       //10 [#reg0-2] [#val]
					{"NDR", "Bitwise AND, from Register",          &CPU4c04_t_NDR, 4, 2},       //11 [#reg0-2] [#reg0-2] Stores in first reg defined
					{"ORR", "Bitwise OR, from Register",           &CPU4c04_t_ORR, 4, 2},       //12 [#reg0-2] [#reg0-2] Stores in first reg defined
					{"XOV", "Bitwise XOR, from Value",             &CPU4c04_t_XOV, 4, 2},       //13 [#reg0-2] [#reg0-2] Stores in first reg defined
					{"XOR", "Bitwise XOR, from Register",          &CPU4c04_t_XOR, 4, 2},       //14 [#reg0-2] [#reg0-2] Stores in first reg defined
					
					{"PRS", "Push Register to Stack",              &CPU4c04_t_PRS, 3, 1},       //15 [#reg0-2]
					{"PSR", "Pop Stack to Register",               &CPU4c04_t_PSR, 3, 1},       //16 [#reg0-2]
					
				};
				
				memcpy(self->instructions, instructions, sizeof(instructions));
		
		}
		
		void        CPU4c04_t_setDrawflag(void * eOBJ, DRAWFLAGS f, bool v)
		{
			eSELF(CPU4c04_t);
		}
		uint8_t     CPU4c04_t_getDrawflag(void * eOBJ, DRAWFLAGS f)
		{
			eSELF(CPU4c04_t);
		}
		uint8_t     CPU4c04_t_read(void * eOBJ, uint8_t addr, bool incPCO)
		{
			eSELF(CPU4c04_t);
		}
		void        CPU4c04_t_write(void * eOBJ, uint8_t addr, uint8_t data)
		{
			eSELF(CPU4c04_t);
		}
		void        CPU4c04_t_stackPush(void * eOBJ, uint8_t data)
		{
			eSELF(CPU4c04_t);
		}
		uint8_t     CPU4c04_t_stackPop(void * eOBJ)
		{
			eSELF(CPU4c04_t);
		}
		uint8_t     CPU4c04_t_regVal(void * eOBJ, uint8_t reg)
		{
			eSELF(CPU4c04_t);
		}
		uint8_t     CPU4c04_t_setReg(void * eOBJ, uint8_t reg, uint8_t data)
		{
			eSELF(CPU4c04_t);
		}
		uint8_t     CPU4c04_t_setIr(void * eOBJ, uint8_t reg, uint8_t data)
		{
			eSELF(CPU4c04_t);
		}
		uint8_t     CPU4c04_t_setPco(void * eOBJ, uint8_t data)
		{
			eSELF(CPU4c04_t);
		}

	void CPU4c04_t_NOP(void * eOBJ)
		{
			eSELF(CPU4c04_t);
		}
	
		void CPU4c04_t_LRV(void * eOBJ)
		{
			eSELF(CPU4c04_t);
		}
		void CPU4c04_t_LRM(void * eOBJ)
		{
			eSELF(CPU4c04_t);
		}
		void CPU4c04_t_LRR(void * eOBJ)
		{
			eSELF(CPU4c04_t);
		}
		void CPU4c04_t_LRT(void * eOBJ)
		{
			eSELF(CPU4c04_t);
		}
	
		void CPU4c04_t_STV(void * eOBJ)
		{
			eSELF(CPU4c04_t);
		}
		void CPU4c04_t_STR(void * eOBJ)
		{
			eSELF(CPU4c04_t);
		}
	
		void CPU4c04_t_BMP(void * eOBJ)
		{
			eSELF(CPU4c04_t);
		}
		void CPU4c04_t_SQR(void * eOBJ)
		{
			eSELF(CPU4c04_t);
		}
		void CPU4c04_t_ADD(void * eOBJ)
		{
			eSELF(CPU4c04_t);
		}
		void CPU4c04_t_SUB(void * eOBJ)
		{
			eSELF(CPU4c04_t);
		}
	
		void CPU4c04_t_JMP(void * eOBJ)
		{
			eSELF(CPU4c04_t);
		}
		void CPU4c04_t_JOC(void * eOBJ)
		{
			eSELF(CPU4c04_t);
		}
		void CPU4c04_t_JSR(void * eOBJ)
		{
			eSELF(CPU4c04_t);
		}
		void CPU4c04_t_RFS(void * eOBJ)
		{
			eSELF(CPU4c04_t);
		}
	
		void CPU4c04_t_AND(void * eOBJ)
		{
			eSELF(CPU4c04_t);
		}
		void CPU4c04_t_BOR(void * eOBJ)
		{
			eSELF(CPU4c04_t);
		}
		void CPU4c04_t_NDR(void * eOBJ)
		{
			eSELF(CPU4c04_t);
		}
		void CPU4c04_t_ORR(void * eOBJ)
		{
			eSELF(CPU4c04_t);
		}
		void CPU4c04_t_XOV(void * eOBJ)
		{
			eSELF(CPU4c04_t);
		}
		void CPU4c04_t_XOR(void * eOBJ)
		{
			eSELF(CPU4c04_t);
		}
	
		void CPU4c04_t_PRS(void * eOBJ)
		{
			eSELF(CPU4c04_t);
		}
		void CPU4c04_t_PSR(void * eOBJ)
		{
			eSELF(CPU4c04_t);
		}

	/**
	* Instantiate CPU object
	* @param void* eOBJ self
	* @return void
	*/
		void CPU4c04_t_instantiate(void * eOBJ)
		{
			eSELF(CPU4c04_t);
			
			//public methods
				self->findHexFromCommand = &CPU4c04_t_findHexFromCommand;
				self->reset = &CPU4c04_t_reset;
				self->execute = &CPU4c04_t_reset;
				
			//private methods vmt
				self->vmt = eNEW(CPU4c04_t_vmt);
				eCONSTRUCT(CPU4c04_t_vmt, self->vmt);
			
			//reset CPU now, which also acts as definition for struct members
				eCALLna(self, reset);
			
		}
		
	/**
	* Find a command using a string index
	* @param void* eOBJ selfg index
	* @param uint8_t * command Command
	* @return uint8_t
	*/
		uint8_t CPU4c04_t_findHexFromCommand(void * eOBJ, uint8_t * command)
		{
			eSELF(CPU4c04_t);
	
			for(uint16_t k = 0; k < 64; k++){
				
				if(strcmp((char*)command, self->instructions[k].name) == 0){
					return (uint8_t)k;
				}
				
			}
			
			return 0;
		
		}
	
	/**
	* Reset CPU object properties to default values
	* @param void* eOBJ self
	* @return void
	*/
		void CPU4c04_t_reset(void * eOBJ)
		{
			eSELF(CPU4c04_t);
			
			//define instructions into cpu object
				self->vmt->loadInstructions(self);
			
			//fill ram+rom with NOPS
				for(int i = 0; i < 256; i++){
					self->RAM[i] = 0x00;
				}
			
			//internal registers
				self->IR1 = 0x0000;
					//@1
				self->IR2 = 0x0000;
					//@1
				self->AR0 = 0x00;
					//@1
				self->AR1 = 0x00;
					//@1
				self->AR2 = 0x00;
					//@1
				self->AR3 = 0x00;
					//@1
					
			//flag bits
				self->C = 0;
				self->Z = 0;
				self->V = 0;
				self->N = 0;
			
			//reset program counter to start of program memory (ROM)
				self->PCO = PROG_MEM_LOC;
				self->lastOpAddr = PROG_MEM_LOC;
					//@1
					
				self->OPC = 0x00;
				
			//reset stack pointer to bottom of stack
				self->STP = STACK_MEM_LOC;
				
			//set remaing cycles to 0, which indicates read new instruction
				self->CRE = 0;
				
			//reset drawflags for draw functions
				self->drawflags = 0x00;
		
		}
		
		void CPU4c04_t_execute(void * eOBJ)
		{
			eSELF(CPU4c04_t);
			
			//clear any drawflags before execution to see what's happened this cycle
			self->drawflags = 0x00;
	
			if(self->CRE == 0){
			
				//check to see if program has ended, if so loop back
					if(self->PCO > 0xfb){
						self->PCO = 0x80;
					}
			
				//set last opcode location for drawing code lines
					self->lastOpAddr = self->PCO;
			
				//read next instruction
					self->IR1 = self->vmt->read(self, self->PCO, true);
					
					self->vmt->setDrawflag(self, IR1, true);
					//@1
					self->INS = self->instructions[self->IR1];
					
				//set OP
					self->OPC = (uint8_t)self->IR1;
					self->vmt->setDrawflag(self, OPC, true);
					
				//set default cycles
					self->CRE = self->INS.cycles;
			
			} else {
			
				(*self->instructions[self->OPC].operate)(self);
				//@1
				
				self->CRE--;
			
			}
		
		}
