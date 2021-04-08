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
		
	/*
	* Set a flag for the draw functions to read
	* @param void * eOBJ Self
	* @param DRAWFLAGS f The bit
	* @param bool v On or off
	* @return void
	*/
		void CPU4c04_t_setDrawflag(void * eOBJ, DRAWFLAGS f, bool v)
		{
			eSELF(CPU4c04_t);
			
			if(v)
				self->drawflags |= f;
			else
				self->drawflags &= ~f;
			
		}
		
	/**
	* Returns the value of a specific bit of the drawflags
	* @param void * eOBJ Self
	* @param DRAWFLAGS f The bit
	* @return uint8_t
	 */
		uint8_t CPU4c04_t_getDrawflag(void * eOBJ, DRAWFLAGS f)
		{
			eSELF(CPU4c04_t);
			return ((self->drawflags & f) > 0) ? 1 : 0;
		}
		
	/*
	* Read a byte from memory
	* @param void * eOBJ Self
	* @param uint8_t addrs
	* @param bool incPCO Increment PCO or not
	* @return uint8_t
	*/
		uint8_t CPU4c04_t_read(void * eOBJ, uint8_t addr, bool incPCO)
		{
			eSELF(CPU4c04_t);
				if(incPCO){
				self->PCO++;
				self->vmt->setDrawflag(self, PCO, true);
			}
			return self->RAM[addr];
		}
		
	/*
	* Write a byte to memory
	* @param void * eOBJ Self
	* @param uint8_t addr
	* @param uint8_t data
	* @return void
	*/
		void CPU4c04_t_write(void * eOBJ, uint8_t addr, uint8_t data)
		{
			eSELF(CPU4c04_t);
			self->RAM[addr] = data;
		}
		
	/*
	* Write a byte to the top of the stack
	* @param void * eOBJ Self
	* @param uint8_t data
	* @return void
	*/
		void CPU4c04_t_stackPush(void * eOBJ, uint8_t data)
		{
			eSELF(CPU4c04_t);
			self->vmt->write(self, self->STP, data);
			self->STP--;
			self->vmt->setDrawflag(self, STP, true);
		}
		
	/*
	* Read a byte from the top of the stack
	* @param void * eOBJ Self
	* @return uint8_t
	*/
		uint8_t CPU4c04_t_stackPop(void * eOBJ)
		{
			eSELF(CPU4c04_t);
			self->STP++;
			uint8_t data = self->RAM[self->STP];
			self->vmt->setDrawflag(self, STP, true);
			return data;
		}
		
	/*
	* Get the value in an addressable register
	* @param void * eOBJ Self
	* @param uint8_t reg Which register
	* @return uint8_t
	*/
		uint8_t CPU4c04_t_regVal(void * eOBJ, uint8_t reg)
		{
			eSELF(CPU4c04_t);
			switch(reg){
				
				case 0:
				default:
					return self->AR0;
				case 1:
					return self->AR1;
				case 2:
					return self->AR2;
				case 3:
					return self->AR3;
				
			}
		}
		
	/*
	* Set the value in an addressable register
	* @param void * eOBJ Self
	* @param uint8_t reg Which register
	* @param uint8_t data
	* @return uint8_t
	*/
		uint8_t CPU4c04_t_setReg(void * eOBJ, uint8_t reg, uint8_t data)
		{
			eSELF(CPU4c04_t);
			switch(reg){
			
				case 0:
				default:
					self->AR0 = data;
					self->vmt->setDrawflag(self, AR0, true);
				break;
				case 1:
					self->AR1= data;
					self->vmt->setDrawflag(self, AR1, true);
				break;
				case 2:
					self->AR2= data;
					self->vmt->setDrawflag(self, AR2, true);
				break;
				case 3:
					self->AR3= data;
					self->vmt->setDrawflag(self, AR3, true);
				break;
				
			}
			
			return data;
		}
		
	/*
	* Set the value in an internal register
	* @param void * eOBJ Self
	* @param uint8_t reg Which register
	* @param uint8_t data
	* @return uint8_t
	*/
		uint8_t CPU4c04_t_setIr(void * eOBJ, uint8_t reg, uint8_t data)
		{
			eSELF(CPU4c04_t);
			
			switch(reg){
		
				case 1:
				default:
					self->IR1= data;
					self->vmt->setDrawflag(self, IR1, true);
				break;
				case 2:
					self->IR2= data;
					self->vmt->setDrawflag(self, IR2, true);
				break;
				
			}
			
			return data;
		}
		
	/*
	* Set the PCO
	* @param void * eOBJ Self
	* @param uint8_t data
	* @return uint8_t
	*/
		uint8_t CPU4c04_t_setPco(void * eOBJ, uint8_t data)
		{
			eSELF(CPU4c04_t);
			self->PCO= data;
			self->vmt->setDrawflag(self, PCO, true);
			return data;
		}

	////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////
	//INSTRUCTIONS
	
	/*
	* Instruction: No Operation
	* @return void
	*/
		void CPU4c04_t_NOP(){
		}
		
	/*
	* Instruction: Load register from value
	* 3 cycles
	* Z,N
	* @return void
	*/
		void CPU4c04_t_LRV(void * eOBJ)
		{
			eSELF(CPU4c04_t);
		
			switch(self->CRE){
				
				//load IR1 with the identifier for which register to finally load
					case 3:
						self->vmt->setIr(self, 1, self->vmt->read(self, self->PCO, true));
					break;
					
				//load IR2 with the value at mem location
					case 2:
						self->vmt->setIr(self, 2, self->vmt->read(self, self->PCO, true));
					break;
					
				//load the value at IR2 into register chosen in IR1
					case 1:
						self->vmt->setReg(self, self->IR1, self->IR2);
						self->Z = (self->IR2 == 0x00);
						self->N = ((self->IR2 & 0x0080) == 0x0080);
					break;
			
			}
			
		}
		
	/*
	* Instruction: Load register from memory addr
	* 4 cycles
	* Z,N
	* @return void
	*/
		void CPU4c04_t_LRM(void * eOBJ){ eSELF(CPU4c04_t);
		
			switch(self->CRE){
				
				//load IR1 with the identifier for which register to finally load
					case 4:
						self->vmt->setIr(self, 1, self->vmt->read(self, self->PCO, true));
					break;
					
				//load IR2 with the mem address for the value
					case 3:
						self->vmt->setIr(self, 2, self->vmt->read(self, self->PCO, true));
					break;
					
				//load the value stored at mem location in IR2 into IR2
					case 2:
						self->vmt->setIr(self, 2, self->vmt->read(self, self->IR2, false));
					break;
					
				//load the value at IR2 into register chosen in IR1, flags
					case 1:
						self->vmt->setReg(self, self->IR1, self->IR2);
						self->Z = (self->IR2 == 0x00);
						self->N = ((self->IR2 & 0x0080) == 0x0080);
					break;
			
			}
			
		}
		
	/*
	* Instruction: Load register from mem loc in other Register
	* 4 cycles
	* Z,N
	* @return void
	*/
		void CPU4c04_t_LRR(void * eOBJ){ eSELF(CPU4c04_t);
		
			switch(self->CRE){
				
				//load IR1 with the identifier for which register to finally load
					case 4:
						self->vmt->setIr(self, 1, self->vmt->read(self, self->PCO, true));
					break;
					
				//Set IR2 to be the reigster to take the mem loc from
					case 3:
						self->vmt->setIr(self, 2, self->vmt->read(self, self->PCO, true));
					break;
					
				//set IR2 to be the value of the register set in IR2
					case 2:
						self->vmt->setIr(self, 2, self->vmt->read(self, self->vmt->regVal(self, self->IR2), false));
					break;
					
				//load the value at IR2 into register chosen in IR1
					case 1:
						self->vmt->setReg(self, self->IR1, self->IR2);
						self->Z = (self->IR2 == 0x00);
						self->N = ((self->IR2 & 0x0080) == 0x0080);
					break;
			
			}
			
		}
		
	/*
	* Instruction: Load register by transfer from another register
	* 4 cycles
	* Z,N
	* @return void
	*/
		void CPU4c04_t_LRT(void * eOBJ){ eSELF(CPU4c04_t);
		
			switch(self->CRE){
				
				//load IR1 with the identifier for which register to finally load into
					case 4:
						self->vmt->setIr(self, 1, self->vmt->read(self, self->PCO, true));
					break;
					
				//Set IR2 to be the reigster to take the value from
					case 3:
						self->vmt->setIr(self, 2, self->vmt->read(self, self->PCO, true));
					break;
					
				//set IR2 to be the value of the register set in IR2
					case 2:
						self->vmt->setIr(self, 2, self->vmt->regVal(self, self->IR2));
					break;
					
				//load the value at IR2 into register chosen in IR1
					case 1:
						self->vmt->setReg(self, self->IR1, self->IR2);
						self->Z = (self->IR2 == 0x00);
						self->N = ((self->IR2 & 0x0080) == 0x0080);
					break;
			
			}
			
		}
		
	/*
	* Instruction: Store register at memory adddress in next read value
	* 3 cycles
	* @return void
	*/
		void CPU4c04_t_STV(void * eOBJ){ eSELF(CPU4c04_t);
		
			switch(self->CRE){
			
				//load IR1 with the identifier for which register to finally load
					case 3:
						self->vmt->setIr(self, 1, self->vmt->read(self, self->PCO, true));
					break;
					
				//load IR2 with address of the destination memory location
					case 2:
						self->vmt->setIr(self, 2, self->vmt->read(self, self->PCO, true));
					break;
					
				//store the value in the register chosen at IR1 into mem location IR2
					case 1:
						self->vmt->write(self, self->IR2, self->vmt->regVal(self, self->IR1));
					break;
			
			}
		
		}
		
	/*
	* Instruction: Store register at memory adddress of register set in next byte
	* x cycles
	* @return void
	*/
		void CPU4c04_t_STR(void * eOBJ){ eSELF(CPU4c04_t);
		
			switch(self->CRE){
			
				//load IR1 with the identifier for which register to finally load
					case 4:
						self->vmt->setIr(self, 1, self->vmt->read(self, self->PCO, true));
					break;
					
				//load IR2 with the id or the register where the mem location is
					case 3:
						self->vmt->setIr(self, 2, self->vmt->read(self, self->PCO, true));
					break;
					
				//get the memory location from the chosen register
					case 2:
						self->vmt->setIr(self,2, self->vmt->regVal(self,self->IR2));
					break;
					
				//store the value in the register chosen at IR1 into mem location IR2
					case 1:
						self->vmt->write(self, self->IR2, self->vmt->regVal(self,self->IR1));
					break;
			
			}
		
		}
		
	/*
	* Instruction: Bump (Increment) value in register
	* 4 cycles
	* V,Z,N
	* @return void
	*/
		void CPU4c04_t_BMP(void * eOBJ){ eSELF(CPU4c04_t);
		
			switch(self->CRE){
			
				//load IR1 with the identifier for which register to bump
					case 4:
						self->vmt->setIr(self, 1, self->vmt->read(self, self->PCO, true));
					break;
					
				//set IR2 to be the value of the register set in IR2
					case 3:
						self->vmt->setIr(self,2, self->vmt->regVal(self,self->IR1));
					break;
					
				//do bump
					case 2:{
					
						uint16_t temp = self->IR2;
						temp++;
						self->vmt->setIr(self,2, (uint8_t) temp & 0xFF);
						
						//overflowed?
							self->V = (temp > 255);
						//now zero?
							self->Z = (self->IR2 == 0);
						//negative?
							self->N = ((self->IR2 & 0x0080) == 0x0080);
						
					} break;
					
				//store the value in the register chosen at IR1 from IR2
					case 1:{
						
						self->vmt->setReg(self, self->IR1, self->IR2);
						
					} break;
			
			}
		
		}
		
	/*
	* Instruction: Squash (Decrement) value in register
	* 4 cycles
	* V,Z,N
	* @return void
	*/
		void CPU4c04_t_SQR(void * eOBJ){ eSELF(CPU4c04_t);
		
			switch(self->CRE){
			
				//load IR1 with the identifier for which register to bump
					case 4:
						self->vmt->setIr(self, 1, self->vmt->read(self, self->PCO, true));
					break;
					
				//set IR2 to be the value of the register set in IR2
					case 3:
						self->vmt->setIr(self,2, self->vmt->regVal(self,self->IR1));
					break;
					
				//do bump
					case 2:{
					
						uint16_t temp = self->IR2;
						temp--;
						self->vmt->setIr(self,2, (uint8_t) temp & 0xFF);
						
						//overflowed?
							self->V = (temp > 255);
						//now zero?
							self->Z = (self->IR2 == 0);
						//negative?
							self->N = ((self->IR2 & 0x0080) == 0x0080);
						
					} break;
					
				//store the value in the register chosen at IR1 from IR2
					case 1:{
						
						self->vmt->setReg(self, self->IR1, self->IR2);
						
					} break;
			
			}
		
		}
		
	
	/**
	* Instruction: Add with Carry In
	*
	* Explanation:
	* The purpose of this function is to add a value to the accumulator and a carry bit. If
	* the result is > 255 there is an overflow setting the carry bit. Ths allows you to
	* chain together ADC instructions to add numbers larger than 8-bits. This in itself is
	* simple, however the 6502 supports the concepts of Negativity/Positivity and Signed Overflow.
	*
	* 10000100 = 128 + 4 = 132 in normal circumstances, we know this as unsigned and it allows
	* us to represent numbers between 0 and 255 (given 8 bits). The 6502 can also interpret
	* this word as something else if we assume those 8 bits represent the range -128 to +127,
	* i.e. it has become signed.
	*
	* Since 132 > 127, it effectively wraps around, through -128, to -124. This wraparound is
	* called overflow, and this is a useful to know as it indicates that the calculation has
	* gone outside the permissable range, and therefore no longer makes numeric sense.
	*
	* Note the implementation of ADD is the same in binary, this is just about how the numbers
	* are represented, so the word 10000100 can be both -124 and 132 depending upon the
	* context the programming is using it in. We can prove this!
	*
	*  10000100 =  132  or  -124
	* +00010001 = + 17      + 17
	*  ========    ===       ===     See, both are valid additions, but our interpretation of
	*  10010101 =  149  or  -107     the context changes the value, not the hardware!
	*
	* In principle under the -128 to 127 range:
	* 10000000 = -128, 11111111 = -1, 00000000 = 0, 00000000 = +1, 01111111 = +127
	* therefore negative numbers have the most significant set, positive numbers do not
	*
	* To assist us, the 6502 can set the overflow flag, if the result of the addition has
	* wrapped around. V <- ~(A^M) & A^(A+M+C) :D lol, let's work out why!
	*
	* Let's suppose we have A = 30, M = 10 and C = 0
	*          A = 30 = 00011110
	*          M = 10 = 00001010+
	*     RESULT = 40 = 00101000
	*
	* Here we have not gone out of range. The resulting significant bit has not changed.
	* So let's make a truth table to understand when overflow has occurred. Here I take
	* the MSB of each component, where R is RESULT.
	*
	* A  M  R | V | A^R | A^M |~(A^M) |
	* 0  0  0 | 0 |  0  |  0  |   1   |
	* 0  0  1 | 1 |  1  |  0  |   1   |
	* 0  1  0 | 0 |  0  |  1  |   0   |
	* 0  1  1 | 0 |  1  |  1  |   0   |  so V = ~(A^M) & (A^R)
	* 1  0  0 | 0 |  1  |  1  |   0   |
	* 1  0  1 | 0 |  0  |  1  |   0   |
	* 1  1  0 | 1 |  1  |  0  |   1   |
	* 1  1  1 | 0 |  0  |  0  |   1   |
	*
	* We can see how the above equation calculates V, based on A, M and R. V was chosen
	* based on the following hypothesis:
	*       Positive Number + Positive Number = Negative Result -> Overflow
	*       Negative Number + Negative Number = Positive Result -> Overflow
	*       Positive Number + Negative Number = Either Result -> Cannot Overflow
	*       Positive Number + Positive Number = Positive Result -> OK! No Overflow
	*       Negative Number + Negative Number = Negative Result -> OK! NO Overflow
	* @return uint8_t
	*/
	
	/*
	* Instruction: Add - <reg1> + <reg2>
	* 5 cycles
	* C,V,Z,N
	* @return void
	*/
		void CPU4c04_t_ADD(void * eOBJ){ eSELF(CPU4c04_t);
		
			switch(self->CRE){
			
				//load IR1 with the identifier for which register to add and store answer in
					case 5:
						self->vmt->setIr(self, 1, self->vmt->read(self, self->PCO, true));
					break;
					
				//load IR2 with the identifier for which other register to add
					case 4:
						self->vmt->setIr(self, 2, self->vmt->read(self, self->PCO, true));
					break;
					
				//Get value of second register and resotre in IR2
					case 3:
						self->vmt->setIr(self,2, self->vmt->regVal(self,self->IR2));
					break;
					
				//do addition into IR2 setting carry as necessary
					case 2:
					{
					
						uint8_t regVal = self->vmt->regVal(self,self->IR1);
						uint16_t temp = (uint16_t)((uint16_t)regVal + (uint16_t)self->IR2 + (uint16_t)self->C);
						
						// The signed Overflow flag
							self->V = (~((uint16_t)regVal ^ (uint16_t)self->IR2) & ((uint16_t)regVal ^ (uint16_t)temp)) & 0x0080;
						
						// The carry flag out exists in the high byte bit 0
							self->C = temp > 255;
							
						// The Zero flag is set if the result is 0
							self->Z = ((temp & 0x00FF) == 0);
							
						// The negative flag is set to the most significant bit of the result
							self->N = ((temp & 0x0080) == 0x0080);
							
						self->vmt->setIr(self,2, (uint8_t)(temp & 0x00FF));
						
					}
					break;
					
				//load the value at IR2 into register chosen in IR1
					case 1:
						self->vmt->setReg(self, self->IR1, self->IR2);
					break;
			
			}
		
		}
		
	/**
	* Instruction: Subtraction with Borrow In
	* Function:    A = A - M - (1 - C)
	* Flags Out:   C, V, N, Z
	*
	* Explanation:
	* Given the explanation for ADC above, we can reorganise our data
	* to use the same computation for addition, for subtraction by multiplying
	* the data by -1, i.e. make it negative
	*
	* A = A - M - (1 - C)  ->  A = A + -1 * (M - (1 - C))  ->  A = A + (-M + 1 + C)
	*
	* To make a signed positive number negative, we can invert the bits and add 1
	* (OK, I lied, a little bit of 1 and 2s complement :P)
	*
	*  5 = 00000101
	* -5 = 11111010 + 00000001 = 11111011 (or 251 in our 0 to 255 range)
	*
	* The range is actually unimportant, because if I take the value 15, and add 251
	* to it, given we wrap around at 256, the result is 10, so it has effectively
	* subtracted 5, which was the original intention. (15 + 251) % 256 = 10
	*
	* Note that the equation above used (1-C), but this got converted to + 1 + C.
	* This means we already have the +1, so all we need to do is invert the bits
	* of M, the data(!) therfore we can simply add, exactly the same way we did
	* before.
	* @return uint8_t
	*/
		
	/*
	* Instruction: Subtract <reg1> - <reg2>, store in reg1
	* 5 cycles
	* C,V,Z,N
	* @return void
	*/
		void CPU4c04_t_SUB(void * eOBJ){ eSELF(CPU4c04_t);
		
			switch(self->CRE){
			
				//load IR1 with the identifier for which register to subtract and store answer in
					case 5:
						self->vmt->setIr(self, 1, self->vmt->read(self, self->PCO, true));
					break;
					
				//load IR2 with the identifier for which other register to subtract
					case 4:
						self->vmt->setIr(self, 2, self->vmt->read(self, self->PCO, true));
					break;
					
				//Get value of second register and resotre in IR2
					case 3:
						self->vmt->setIr(self,2, self->vmt->regVal(self,self->IR2));
					break;
					
				//do subtraction into IR2 setting carry as necessary
					case 2:
					{
						uint16_t tempVal = ((uint16_t)self->IR2 ^ 0x00FF);
						uint8_t regVal = self->vmt->regVal(self,self->IR1);
						uint16_t temp = (uint16_t)((uint16_t)regVal + tempVal + (uint16_t)self->C);
						
						// The carry flag out exists in the high byte bit 0
							self->C = temp > 255;
							
						// The Zero flag is set if the result is 0
							self->Z = ((temp & 0x00FF) == 0);
							
						// The negative flag is set to the most significant bit of the result
							self->N = ((temp & 0x0080) == 0x0080);
							
						self->vmt->setIr(self,2, (uint8_t)(temp & 0x00FF));
						
					}
					break;
					
				//load the value at IR2 into register chosen in IR1
					case 1:
						self->vmt->setReg(self, self->IR1, self->IR2);
					break;
			
			}
		
		}
		
	/*
	* Instruction: Jump
	* 2 cycles
	* @return void
	*/
		void CPU4c04_t_JMP(void * eOBJ){ eSELF(CPU4c04_t);
		
			switch(self->CRE){
			
				//load IR1 with memory address to jump to
					case 2:
						self->vmt->setIr(self, 1, self->vmt->read(self, self->PCO, true));
					break;
					
				//load IR2 with address of the destination memory location
					case 1:
						self->vmt->setPco(self, self->IR1);
					break;
			
			}
		
		}
		
	/*
	* Instruction: Jump if Zero = 0
	* 2 cycles
	* @return void
	*/
		void CPU4c04_t_JOC(void * eOBJ){ eSELF(CPU4c04_t);
		
			switch(self->CRE){
			
				//load IR1 with the condition for jump
					case 3:
						self->vmt->setIr(self, 1, self->vmt->read(self, self->PCO, true));break;
					
				//load IR2 with the location to jump to
					case 2:
						self->vmt->setIr(self, 2, self->vmt->read(self, self->PCO, true));
					break;
					
				//Set PCO on condition
					case 1:{
					
						switch(self->IR1){
						
							//Not empty, Z = 0
								case 1:
									if(self->Z == false){
										self->vmt->setPco(self, self->IR2);
									}
								break;
								
							//empty, Z = 1
								case 2:
									if(self->Z == true){
										self->vmt->setPco(self, self->IR2);
									}
								break;
								
							//No Carry, C = 0
								case 3:
									if(self->C == false){
										self->vmt->setPco(self, self->IR2);
									}
								break;
								
							//Carry set, C = 1
								case 4:
									if(self->C == true){
										self->vmt->setPco(self, self->IR2);
									}
								break;
								
							//Not Negative, N = 0
								case 5:
									if(self->N == false){
										self->vmt->setPco(self, self->IR2);
									}
								break;
								
							//Negative set, N = 1
								case 6:
									if(self->N == true){
										self->vmt->setPco(self, self->IR2);
									}
								break;
								
							//Not Overflowed, V = 0
								case 7:
									if(self->V == false){
										self->vmt->setPco(self, self->IR2);
									}
								break;
								
							//Overflowed set, V = 1
								case 8:
									if(self->V == true){
										self->vmt->setPco(self, self->IR2);
									}
								break;
								
							default:
								//don't jump as condition not defined
							break;
						}
						
					} break;
			
			}
		
		}
		
	/*
	* Instruction: Jump to Subroutine
	* 3 cycles
	* @return void
	*/
		void CPU4c04_t_JSR(void * eOBJ)
		{
			eSELF(CPU4c04_t);
		
			switch(self->CRE){
			
				//put the next mem location onto stack
					case 3:
						self->vmt->stackPush(self, (uint8_t)(self->PCO+1));
					break;
				
				//load IR1 with memory address to jump to
					case 2:
						self->vmt->setIr(self, 1, self->vmt->read(self, self->PCO, true));
					break;
					
				//set new PCO
					case 1:
						self->vmt->setPco(self, self->IR1);
					break;
			
			}
		
		}
		
	/*
	* Instruction: Return from Subroutine
	* 2 cycles
	* @return void
	*/
		void CPU4c04_t_RFS(void * eOBJ){ eSELF(CPU4c04_t);
		
			switch(self->CRE){
			
				//Get the last mem loc from stack
					case 2:
						self->vmt->setIr(self,1, self->vmt->stackPop(self));
					break;
					
				//set new PCO
					case 1:
						self->vmt->setPco(self, self->IR1);
					break;
			
			}
		
		}
		
		
	/*
	* Instruction: Bitwise AND
	* 4 cycles
	* @return void
	*/
		void CPU4c04_t_AND(void * eOBJ){ eSELF(CPU4c04_t);
		
			switch(self->CRE){
			
				//load IR1 with the identifier for which register to do bitwise AND on
					case 4:
						self->vmt->setIr(self, 1, self->vmt->read(self, self->PCO, true));
					break;
					
				//load IR2 with the second value of the bitwise AND
					case 3:
						self->vmt->setIr(self, 2, self->vmt->read(self, self->PCO, true));
					break;
					
				//do the bitwise and using val from reg defined in IR1
					case 2:
						self->vmt->setIr(self,2, self->IR2 & self->vmt->regVal(self,self->IR1));
					break;
				
				//store back to original register
					case 1:
						self->vmt->setReg(self, self->IR1, self->IR2);
						//now zero?
							self->Z = (self->IR2 == 0);
						//negative?
							self->N = ((self->IR2 & 0x0080) == 0x0080);
					break;
			}
		
		}
		
	/*
	* Instruction: Bitwise OR
	* 4 cycles
	* @return void
	*/
		void CPU4c04_t_BOR(void * eOBJ){ eSELF(CPU4c04_t);
		
			switch(self->CRE){
			
				//load IR1 with the identifier for which register to do bitwise AND on
					case 4:
						self->vmt->setIr(self, 1, self->vmt->read(self, self->PCO, true));
					break;
					
				//load IR2 with the second value of the bitwise AND
					case 3:
						self->vmt->setIr(self, 2, self->vmt->read(self, self->PCO, true));
					break;
					
				//do the bitwise and using val from reg defined in IR1
					case 2:
						self->vmt->setIr(self,2, self->IR2 | self->vmt->regVal(self,self->IR1));
					break;
				
				//store back to original register
					case 1:
						self->vmt->setReg(self, self->IR1, self->IR2);
						//now zero?
							self->Z = (self->IR2 == 0);
						//negative?
							self->N = ((self->IR2 & 0x0080) == 0x0080);
					break;
			}
		
		}
		
	/*
	* Instruction: Bitwise AND between registers
	* 4 cycles
	* @return void
	*/
		void CPU4c04_t_NDR(void * eOBJ){ eSELF(CPU4c04_t);
		
			switch(self->CRE){
			
				//load IR1 with the identifier for which register to do bitwise AND on
					case 4:
						self->vmt->setIr(self, 1, self->vmt->read(self, self->PCO, true));
					break;
					
				//load IR2 with the second value of the bitwise AND
					case 3:
						self->vmt->setIr(self, 2, self->vmt->read(self, self->PCO, true));
					break;
					
				//do the bitwise and using val from reg defined in IR1
					case 2:
						self->vmt->setIr(self,2, self->vmt->regVal(self,self->IR1) & self->vmt->regVal(self,self->IR2));
					break;
				
				//store back to original register
					case 1:
						self->vmt->setReg(self, self->IR1, self->IR2);
						//now zero?
							self->Z = (self->IR2 == 0);
						//negative?
							self->N = ((self->IR2 & 0x0080) == 0x0080);
					break;
			}
		
		}
		
	/*
	* Instruction: Bitwise OR between registers
	* 4 cycles
	* @return void
	*/
		void CPU4c04_t_ORR(void * eOBJ){ eSELF(CPU4c04_t);
		
			switch(self->CRE){
			
				//load IR1 with the identifier for which register to do bitwise AND on
					case 4:
						self->vmt->setIr(self, 1, self->vmt->read(self, self->PCO, true));
					break;
					
				//load IR2 with the second value of the bitwise AND
					case 3:
						self->vmt->setIr(self, 2, self->vmt->read(self, self->PCO, true));
					break;
					
				//do the bitwise and using val from reg defined in IR1
					case 2:
						self->vmt->setIr(self,2, self->vmt->regVal(self,self->IR1) | self->vmt->regVal(self,self->IR2));
					break;
				
				//store back to original register
					case 1:
						self->vmt->setReg(self, self->IR1, self->IR2);
						//now zero?
							self->Z = (self->IR2 == 0);
						//negative?
							self->N = ((self->IR2 & 0x0080) == 0x0080);
					break;
			}
		
		}
		
	/*
	* Instruction: Bitwise XOR
	* 4 cycles
	* @return void
	*/
		void CPU4c04_t_XOV(void * eOBJ){ eSELF(CPU4c04_t);
		
			switch(self->CRE){
			
				//load IR1 with the identifier for which register to do bitwise AND on
					case 4:
						self->vmt->setIr(self, 1, self->vmt->read(self, self->PCO, true));
					break;
					
				//load IR2 with the second value of the bitwise AND
					case 3:
						self->vmt->setIr(self, 2, self->vmt->read(self, self->PCO, true));
					break;
					
				//do the bitwise and using val from reg defined in IR1
					case 2:
						self->vmt->setIr(self,2, self->IR2 ^ self->vmt->regVal(self,self->IR1));
					break;
				
				//store back to original register
					case 1:
						self->vmt->setReg(self, self->IR1, self->IR2);
						//now zero?
							self->Z = (self->IR2 == 0);
						//negative?
							self->N = ((self->IR2 & 0x0080) == 0x0080);
					break;
			}
		
		}
		
	/*
	* Instruction: Bitwise XOR between registers
	* 4 cycles
	* @return void
	*/
		void CPU4c04_t_XOR(void * eOBJ){ eSELF(CPU4c04_t);
		
			switch(self->CRE){
			
				//load IR1 with the identifier for which register to do bitwise AND on
					case 4:
						self->vmt->setIr(self, 1, self->vmt->read(self, self->PCO, true));
					break;
					
				//load IR2 with the second value of the bitwise AND
					case 3:
						self->vmt->setIr(self, 2, self->vmt->read(self, self->PCO, true));
					break;
					
				//do the bitwise and using val from reg defined in IR1
					case 2:
						self->vmt->setIr(self,2, self->vmt->regVal(self,self->IR1) ^ self->vmt->regVal(self,self->IR2));
					break;
				
				//store back to original register
					case 1:
						self->vmt->setReg(self, self->IR1, self->IR2);
						//now zero?
							self->Z = (self->IR2 == 0);
						//negative?
							self->N = ((self->IR2 & 0x0080) == 0x0080);
					break;
			}
		
		}
		
	/*
	* Instruction: Push Register to Stack
	* 3 cycles
	* @return void
	*/
		void CPU4c04_t_PRS(void * eOBJ){ eSELF(CPU4c04_t);
		
			switch(self->CRE){
			
				//load IR1 with the identifier for which register to push
					case 3:
						self->vmt->setIr(self, 1, self->vmt->read(self, self->PCO, true));
					break;
					
				//load IR2 with the value from reg defined in IR1
					case 2:
						self->vmt->setIr(self,2, self->vmt->regVal(self,self->IR1));
					break;
					
				//push to stack
					case 1:
						self->vmt->stackPush(self, self->IR2);
					break;
			}
		
		}
		
	/*
	* Instruction: Pop Stack to Register
	* 3 cycles
	* @return void
	*/
		void CPU4c04_t_PSR(void * eOBJ){ eSELF(CPU4c04_t);
		
			switch(self->CRE){
			
				//load IR1 with the identifier for which register to push
					case 3:
						self->vmt->setIr(self, 1, self->vmt->read(self, self->PCO, true));
					break;
					
				//load IR2 with the value from reg defined in IR1
					case 2:
						self->vmt->setIr(self,2, self->vmt->stackPop(self));
					break;
					
				//populate register with value now in IR2
					case 1:
						self->vmt->setReg(self, self->IR1, self->IR2);
					break;
			}
		
		}
		
	////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////
	//PUBLIC METHODS

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
				self->execute = &CPU4c04_t_execute;
				self->getDrawflag = &CPU4c04_t_getDrawflag;
				
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
		
	/**
	* Execute current instruction or look for next instruction
	* @param void* eOBJ Self
	* @return void
	*/
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
