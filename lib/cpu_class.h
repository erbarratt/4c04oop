#ifndef INC_4C04_CPU_CLASS_H
#define INC_4C04_CPU_CLASS_H

	/**
	* CPU private class virtual method table
	*/
		struct CPU4c04_t_vmt{
		
			void (*loadInstructions)(void * eOBJ);
		
			void (*NOP)(void * eOBJ);

			void (*LRV)(void * eOBJ);
			void (*LRM)(void * eOBJ);
			void (*LRR)(void * eOBJ);
			void (*LRT)(void * eOBJ);

			void (*STV)(void * eOBJ);
			void (*STR)(void * eOBJ);

			void (*BMP)(void * eOBJ);
			void (*SQR)(void * eOBJ);
			void (*ADD)(void * eOBJ);
			void (*SUB)(void * eOBJ);

			void (*JMP)(void * eOBJ);
			void (*JOC)(void * eOBJ);
			void (*JSR)(void * eOBJ);
			void (*RFS)(void * eOBJ);

			void (*AND)(void * eOBJ);
			void (*BOR)(void * eOBJ);
			void (*NDR)(void * eOBJ);
			void (*ORR)(void * eOBJ);
			void (*XOV)(void * eOBJ);
			void (*XOR)(void * eOBJ);

			void (*PRS)(void * eOBJ);
			void (*PSR)(void * eOBJ);
		
		};
		
		typedef struct CPU4c04_t_vmt CPU4c04_t_vmt;
		
		void CPU4c04_t_loadInstructions(void * eOBJ);
		
		void CPU4c04_t_NOP(void * eOBJ);

		void CPU4c04_t_LRV(void * eOBJ);
		void CPU4c04_t_LRM(void * eOBJ);
		void CPU4c04_t_LRR(void * eOBJ);
		void CPU4c04_t_LRT(void * eOBJ);

		void CPU4c04_t_STV(void * eOBJ);
		void CPU4c04_t_STR(void * eOBJ);

		void CPU4c04_t_BMP(void * eOBJ);
		void CPU4c04_t_SQR(void * eOBJ);
		void CPU4c04_t_ADD(void * eOBJ);
		void CPU4c04_t_SUB(void * eOBJ);

		void CPU4c04_t_JMP(void * eOBJ);
		void CPU4c04_t_JOC(void * eOBJ);
		void CPU4c04_t_JSR(void * eOBJ);
		void CPU4c04_t_RFS(void * eOBJ);

		void CPU4c04_t_AND(void * eOBJ);
		void CPU4c04_t_BOR(void * eOBJ);
		void CPU4c04_t_NDR(void * eOBJ);
		void CPU4c04_t_ORR(void * eOBJ);
		void CPU4c04_t_XOV(void * eOBJ);
		void CPU4c04_t_XOR(void * eOBJ);

		void CPU4c04_t_PRS(void * eOBJ);
		void CPU4c04_t_PSR(void * eOBJ);
		
		void        CPU4c04_t_setDrawflag(DRAWFLAGS f, bool v);
		uint8_t     CPU4c04_t_getDrawflag(DRAWFLAGS f);
		uint8_t     CPU4c04_t_read(uint8_t addr, bool incPCO);
		void        CPU4c04_t_write(uint8_t addr, uint8_t data);
		void        CPU4c04_t_stackPush(uint8_t data);
		uint8_t     CPU4c04_t_stackPop();
		uint8_t     CPU4c04_t_regVal(uint8_t reg);
		uint8_t     CPU4c04_t_setReg(uint8_t reg, uint8_t data);
		uint8_t     CPU4c04_t_setIr(uint8_t reg, uint8_t data);
		uint8_t     CPU4c04_t_setPco(uint8_t data);

	/**
	* CPU private class structure
	*/
		typedef struct {
			//public properties
				//instructions array
					INSTRUCTION instructions[64];
			
				//program counter
					uint8_t PCO;
					
				//stack pointer
					uint8_t STP;
				
				//current opcode
					uint8_t OPC;
					
				//remaining cycles
					uint8_t CRE;
			
				//internal registers, 8bits
					uint8_t IR1;
					uint8_t IR2;
				
				//addressable registers, 8 bits
					uint8_t AR0;
					uint8_t AR1;
					uint8_t AR2;
					uint8_t AR3;
				
				//ROM + RAM
					uint8_t RAM[256];
				
				//Carry flag
					bool C;
				
				//Zero Flag
					bool Z;
				
				//Overflow
					bool V;
					
				//Negative Flag
					bool N;
				
				//current instruction
					INSTRUCTION INS;
					
				//last op address
					uint8_t lastOpAddr;
					
				//drawflags
					DRAWFLAGS drawflags;
					
			//public methods
				void (*reset)(void * eOBJ);
				void (*execute)(void * eOBJ);
				
			//private methods
				CPU4c04_t_vmt * vmt;
			
		} CPU4c04_t;

#endif //INC_4C04_CPU_CLASS_H
