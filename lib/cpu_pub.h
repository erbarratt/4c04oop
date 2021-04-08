#ifndef INC_4C04_CPU_PUB_H
#define INC_4C04_CPU_PUB_H

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "eOOPc.h"
#include "common.h"
	
	/**
	* bit field for cpu status
	*/
		typedef enum
		{
		
			PCO = (1 << 0),	// Program Counter
			IR1 = (1 << 1),	// Internal Reg 1
			IR2 = (1 << 2),	// Internal Reg 2
			AR0 = (1 << 3),	// Addressable Reg 0
			AR1 = (1 << 4),	// Addressable Reg 1
			AR2 = (1 << 5),	// Addressable Reg 2
			AR3 = (1 << 6),	// Addressable Reg 3
			OPC = (1 << 7),	// Current Opcode
			STP = (1 << 8),	// Stack Pointer
			
		} DRAWFLAGS;

	/**
	* Instruction struct
	* @var struct INSTRUCTION
	* @param char[] name
	* @param char[] label
	* @param void (*operate)
	* @param uint8_t cycles
	* @param uint8_t pcoShifts
	*/
		typedef struct{
			char name[10];
			char label[50];
			void (*operate )(void * eOBJ);
			uint8_t cycles;
			uint8_t pcoShifts;
		} INSTRUCTION;
	
	/**
	* CPU public class structure
	*/
		struct CPU4c04_t{
			
			//public props
				INSTRUCTION instructions[64];
				uint8_t PCO;
				uint8_t STP;
				uint8_t OPC;
				uint8_t CRE;
				uint8_t IR1;
				uint8_t IR2;
				uint8_t AR0;
				uint8_t AR1;
				uint8_t AR2;
				uint8_t AR3;
				uint8_t RAM[MEM_LENGTH];
				bool C;
				bool Z;
				bool V;
				bool N;
				INSTRUCTION INS;
				uint8_t lastOpAddr;
				DRAWFLAGS drawflags;
				
			//public methods
				uint8_t (*findHexFromCommand)(void * eOBJ, uint8_t * command);
				void (*reset)(void * eOBJ);
				void (*execute)(void * eOBJ);
				uint8_t (*getDrawflag)(void * eOBJ, DRAWFLAGS f);
			
		};
		
		void CPU4c04_t_instantiate(void * eOBJ);
		uint8_t CPU4c04_t_findHexFromCommand(void * eOBJ, uint8_t * command);
		void CPU4c04_t_reset(void * eOBJ);
		void CPU4c04_t_execute(void * eOBJ);
		uint8_t CPU4c04_t_getDrawflag(void * eOBJ, DRAWFLAGS f);

#endif //INC_4C04_CPU_PUB_H
