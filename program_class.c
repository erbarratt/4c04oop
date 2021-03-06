/*
* Program class source file
*
* Since the program class struct only has public members, there is no need for a _pri.h file,
* therefor private source function declarations are in this file
*
* The program class deals with assembling into binary code from the prog.txt file,
* then disassembling this back into mnemonic commands at those points in memory*
*/

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "lib/program_pub.h"

	//private source function declarations
		bool Program4c04_t_isHexChar(uint8_t c);
		uint8_t Program4c04_t_getHexChar(uint8_t c);
		void Program4c04_t_loadProgram(void * eOBJ);
		void Program4c04_t_disassembleCode(void * eOBJ);
	
	/**
	* Instantiate Program Object
	* @function public
	* @param void* eOBJ Self object
	* @param struct CPU4c04_t* cpu CPU object pointer
	* @param struct Debug4c04_t* console Debug object pointer
	* @return void
	*/
		void Program4c04_t_instantiate(void * eOBJ, struct CPU4c04_t* cpu, struct Debug4c04_t* console)
		{
			eSELF(Program4c04_t);
			
			//instantiate parent object
				eCONSTRUCT(String4c04_t, &self->strings);
				
			//upcast a pointer to use strings as a local var
				ePARENT(String4c04_t, strings);
				
			//make space and allocate for strings
			//128 char array pointers
				char line[50];
				char num[5];
				for (uint32_t i = 0; i < MEM_LENGTH; i++){
                    self->code[i] = (char*)malloc((100+1) * sizeof(char)); // yeah, I know sizeof(char) is 1, but to make it clear...
                    strncpy(self->code[i], strings->strncatcat(strcpy(line, "$"), 49, strings->hex(i, 2, num),": NOP c2", NULL), 12);
				}
			
			//bind params
				self->cpu = cpu;
				self->console = console;
			
			//bind public methods
				self->isHexChar = &Program4c04_t_isHexChar;
				self->getHexChar = &Program4c04_t_getHexChar;
				self->loadProgram = &Program4c04_t_loadProgram;
				self->disassembleCode = &Program4c04_t_disassembleCode;
				
		}
		
	/**
	* Test if char is a valid member of the hex notation 0-9 a-f A-F
	* @function public
	* @param uint_t c Character to test
	* @return bool
	*/
		bool Program4c04_t_isHexChar(uint8_t c)
		{
			if (
				(c >= '0' && c <= '9') ||
				(c >= 'a' && c <= 'f') ||
				(c >= 'A' && c <= 'F')
			){
				return true;
			}
			
			return false;
		}
		
	/**
	* Convert a char from it's asscii value into a number literal of that representation
	* @function public
	* @param uint_t c Character to convert
	* @return uint8_t
	*/
		uint8_t Program4c04_t_getHexChar(uint8_t c)
		{
	
		//lookup 8 bit value of hex character to store in tmp
			switch(c){
				case '1': return 0x01;
				case '2': return 0x02;
				case '3': return 0x03;
				case '4': return 0x04;
				case '5': return 0x05;
				case '6': return 0x06;
				case '7': return 0x07;
				case '8': return 0x08;
				case '9': return 0x09;
				case 'a': case 'A': return 0x0A;
				case 'b': case 'B': return 0x0B;
				case 'c': case 'C': return 0x0C;
				case 'd': case 'D': return 0x0D;
				case 'e': case 'E': return 0x0E;
				case 'f': case 'F': return 0x0F;
				default: return 0x00;
			}
	
	}
		
	/**
	* Load a program from a text file called prog.txt
	* @function public
	* @param void* eOBJ Self
	* @return void
	*/
		void Program4c04_t_loadProgram(void * eOBJ)
		{
		
			/*
			* Assembly rules:
			*
			* lines should never start with white space
			*
			* comments are started with the ';' character and always stopped with a new line
			*
			* commands are always 3 letters words "NPG"
			* command lines must start with a command word followed by spaces and 2 digit hex values or register pointers as arguments (oprands)
			* 1 command per line
			*
			* Subroutines must be defined before calling
			* Subroutines are derfined as starting a new line with the character '@' followed by up to 10 chars, no spaces
			* Subroutines are called by starting a new line with '>' and then typing the matching subroutine name, no spaces
			*
			* Addressable Registers can be defined using RX, where X is 0 - 3, insted of the hex equivalent
			* '$' characters are ignored, and so can be used to define memory locations
			*
			* ':' characters denote a memory marker, useful for literal jumps to that position
			* Markers can contain no spaces and are up to 10 characters
			* Use a marker by the character '-' followed by the marker name defined above
			*
			* ^ followed by a hex number pair will move the address of where you're writing memory to to that location
			*
			* # at the start of a line puts the assembler in data mode, where it will sequentially write the bytes defined after it
			* ! at the start of a line puts the assembler in command mode, where it will parse commands as normal
			*
			*/
			
			eSELF(Program4c04_t);
			
			//make pointer to parent to use it's methods
				//saves us typing self->strings->
				//ePARENT(String4c04_t, strings);
		
			//load program into program memory
				FILE * fp;
				
				fp = fopen("prog.txt", "r");
				
				if (fp == NULL){
					self->console->consoleErr("\x1b[31mNo Assembly File 'prog.txt'. Closing...\x1b[0m\n");
				}
			
			//holding vars
			
				//a subroutine could be defined at an point in memory
					char subroutines[MEM_LENGTH][12];
					uint8_t lastSubroutineAddr = 0;
					uint8_t subroutineLocCount = 0;
					bool inSubroutineDef = false;
					
				//markers
					char markers[MEM_LENGTH][12];
				
				uint8_t command[4] = "NOP";
				int col = 0;
				uint8_t c, new, tmp;
				uint8_t hi = 0x00;
				uint8_t lo;
				
				int bytes = 0;
				uint8_t addr = PROG_MEM_LOC;
				
				bool comment = false;
				bool dataMode = false;
				bool characterLiteral = false;
	
			//process file
				int i = 1;
				while(1){
					
					//get next char
						c = (uint8_t)fgetc(fp);
						//printf("%c", c);
			
					//check if end of file or end of memory now
						if(feof(fp) || bytes > 128){
							break;
						}
						
					//see if we got comment
						if(c == ';'){
							comment = true;
							continue;
						}
						
						if(comment && c != '\n'){
							continue;
						}
					
					//new line starts the command
						if(c == '\n'){
							comment = false;
							col = 0;
							continue;
						}
						
					//jump to mem loc
						if(col == 0 && c == '^'){
						
							//get following two bytes and transform
							bool hiSet = false;
							while(1){
							
								uint8_t cHere = (uint8_t)fgetc(fp);
								//printf("%c", cHere);
								
								if(self->isHexChar(cHere) == false){
									continue;
								}
								
								if(hiSet == false){
									hi = self->getHexChar(cHere);
									hiSet = true;
								} else {
									lo = self->getHexChar(cHere);
									addr =  (uint8_t)(hi << 4) | lo;
									break;
								}
							
							}
							
							while(true){
							
								char cHere = (char)fgetc(fp);
								//printf("%c", cHere);
								
								if(cHere == '\n'){
									break;
								}
							
							}
							
							continue;
						
						}
						
					//see if we're in data mode
						if(col == 0 && c == '#'){
						
							dataMode = true;
							
							//read to next newline
								while(true){
								
									char cHere = (char)fgetc(fp);
									//printf("%c", cHere);
									
									if(cHere == '\n'){
										break;
									}
								
								}
							
							continue;
						}
						
					//see if we're in command mode
						if(col == 0 && c == '!'){
							
							dataMode = false;
							
							//read to next newline
								for(int j = 0; j < 10; j++){
								
									char cHere = (char)fgetc(fp);
									//printf("%c", cHere);
									
									if(cHere == '\n'){
										break;
									}
								
								}
							
							continue;
							
						}
						
					//if col index 0 - 3, then we're looking to build command
						if(col < 3 && !dataMode){
						
							//subroutine defintion
								if(col == 0 && c == '@'){
								
									//define the label, only take in the first 10 chars
										int j;
										bool hitNewLine = false;
										for(j = 0; j < 10; j++){
										
											char cHere = (char)fgetc(fp);
											//printf("%c", cHere);
											
											if(
												cHere == '\n'
											){
												hitNewLine = true;
												break;
											}
											
											if(
												cHere == ' ' ||
												cHere == '\t'
											){
												break;
											}
											
											subroutines[addr][j] = cHere;
										
										}
										
										subroutines[addr][j] = '\0';
										
									//set as now being in a subroutine for the following instructions
									//to be able to add them to count of subroutine instructions
									//this count is then used to determine the length of the subroutine
									//so it can be retrospectively put as the jump value when we hit the RFS instruction
									
										inSubroutineDef = true;
										lastSubroutineAddr = addr;
										
										uint8_t commandHere[4] = "JMP";
										self->cpu->RAM[addr] = self->cpu->findHexFromCommand(self->cpu, commandHere);
										addr++;
										self->cpu->RAM[addr] = 0x00; //00 for now
										addr++;
										
									//read to next newline
										if(hitNewLine == false){
											while(true){
											
												char cHere = (char)fgetc(fp);
												//printf("%c", cHere);
												
												if(cHere == '\n'){
													break;
												}
											
											}
										}
										
									//reset col so next line works correctly
										comment = false;
										col = 0;
										
									continue;
								
								}
								
							//subroutine replacement
								else if(col == 0 && c == '>'){
								
									//construct label to match in the subroutine array
										char subLabel[12];
										
										int j;
										bool hitNewLine = false;
										for(j = 0; j < 10; j++){
										
											char cHere = (char)fgetc(fp);
											//printf("%c", cHere);
											
											if(cHere == '\n'){
												hitNewLine = true;
												break;
											}
											
											if(
												cHere == ' ' ||
												cHere == '\t'
											){
												break;
											}
											
											subLabel[j] = cHere;
										
										}
										
										subLabel[j] = '\0';
									
									//now go through subroutines array to find match
										for(j = 0; j < MEM_LENGTH; j++){
										
											if(strcmp(subroutines[j], subLabel) == 0){
												
												//we've found a match, to J represents the start of that subroutine
												//that will always be 12 XX, so we need to set JSR value to two beyond that
													uint8_t commandHere[4] = "JSR";
													self->cpu->RAM[addr] = self->cpu->findHexFromCommand(self->cpu, commandHere); //JSR
													addr++;
													self->cpu->RAM[addr] = (uint8_t)(j+2);
													addr++;
												
												//we might be in a subroutine definition, so we need to include these two bytes in that count too
													if(inSubroutineDef){
														subroutineLocCount++;
														subroutineLocCount++;
													}
												
												break;
												
											}
										
										}
										
									//read to next newline
										if(hitNewLine == false){
											while(true){
											
												char cHere = (char)fgetc(fp);
												//printf("%c", cHere);
												
												if(cHere == '\n'){
													break;
												}
											
											}
										}
										
									//reset col so next line works correctly
										comment = false;
										col = 0;
									
									continue;
								
								}
								
							//markers
								else if(col == 0 && c == ':'){
								
									//define the label, only take in the first 10 chars
										int j;
										bool hitNewLine = false;
										for(j = 0; j < 10; j++){
										
											char cHere = (char)fgetc(fp);
											//printf("%c", cHere);
											
											if(cHere == '\n'){
												hitNewLine = true;
												break;
											}
											
											if(
												cHere == ' ' ||
												cHere == '\t'
											){
												break;
											}
											
											markers[addr][j] = cHere;
										
										}
										
										markers[addr][j] = '\0';
										
									//markers are just places in memory, and are ignored at execution
									//they are always a JMP to just after themselves
										//self->cpu->RAM[addr] = 0x12; //JMP
										//addr++;
										//self->cpu->RAM[addr] = (uint8_t)(addr+1);
										//addr++;
										
									//read to next newline
										if(hitNewLine == false){
											while(true){
											
												char cHere = (char)fgetc(fp);
												//printf("%c", cHere);
												
												if(cHere == '\n'){
													break;
												}
											
											}
										}
										
									//reset col so next line works correctly
										comment = false;
										col = 0;
										
									continue;
								
								}
						
							//command line
								if(c != ' ' && c != '\t'){
									command[col] = c;
								} else {
									continue;
								}
								
								if(col == 2){
								
									//find instruction and write as it's hex equivalent
										self->cpu->RAM[addr] = self->cpu->findHexFromCommand(self->cpu, command);
									
									//RFS means we can close current subroutine count and set where to jump now
										if (strcmp((char*)command, "RFS") == 0){
											
											if(inSubroutineDef){
												self->cpu->RAM[lastSubroutineAddr+1] = (uint8_t)(lastSubroutineAddr+3+subroutineLocCount);
												subroutineLocCount = 0;
												inSubroutineDef = false;
											}
											
										}
								
									addr++;
									bytes++;
									if(inSubroutineDef){
										subroutineLocCount++;
									}
								
								}
								
								col++;
						
					//otherwise, we're always reading hex pairs
						} else {
						
							//set character literal mode
								if(i == 1 && c == '"'){
									characterLiteral = true;
									i++;
									continue;
								}
							
							//replace "R" with 0, making code easier to read
								if(i== 1 && c == 'R'){
									hi = 0x00;
									i++;
									continue;
								}
								
							//raplce markers with addr
								if(i == 1 && c == '-'){
								
									//construct label to match in the subroutine array
										char markerLabel[12];
										bool hitNewLine = false;
										
										int j;
										for(j = 0; j < 10; j++){
										
											char cHere = (char)fgetc(fp);
											//printf("%c", cHere);
											
											if(cHere == '\n'){
												hitNewLine = true;
												break;
											}
											
											if(
												cHere == ' ' ||
												cHere == '\t'
											){
												break;
											}
											
											markerLabel[j] = cHere;
										
										}
										
										markerLabel[j] = '\0';
									
									//now go through subroutines array to find match
										for(j = 0; j < MEM_LENGTH; j++){
										
											if(strcmp(markers[j], markerLabel) == 0){
												
												//we've found a match, to J represents the start of that subroutine
												//that will always be 12 XX, so we need to set JSR value to two beyond that
													self->cpu->RAM[addr] = (uint8_t)(j);
													addr++;
												
												break;
												
											}
										
										}
										
									//read to next newline
										if(hitNewLine == false){
											while(true){
											
												char cHere = (char)fgetc(fp);
												//printf("%c", cHere);
												
												if(cHere == '\n'){
													break;
												}
											
											}
										}
										
									//reset col so next line works correctly
										comment = false;
										col = 0;
									
									continue;
								
								}
							
							//following char is taken as the value, no matter what
								if(characterLiteral){
								
									//reset i and flag so character after this continues to be parsed as normal
										i = 1;
										characterLiteral = false;
								
									//store the value as the character ascii binary
										self->cpu->RAM[addr] = c;
										addr++;
										bytes++;
										if(inSubroutineDef){
											subroutineLocCount++;
										}
							
							//get the hex val and store as byte is on lo pass
								} else {
					
									//check this char is in valid hex char set
										if(self->isHexChar(c) == false){
											continue;
										}
										
										tmp = (uint8_t)self->getHexChar(c);
							
									//write only when hex built from both chars in txt file
										if(i == 1){
											i++;
											hi = tmp;
										} else {
											lo = tmp;
											i = 1;
											
											//new is hi bit shifted left by four, bitwise OR's with lo
											//since lo always has 4 leading zeros, the hi 1 bits are always written (one OR the other bit is 1...)
											new = (uint8_t)(hi << 4) | lo;
											self->cpu->RAM[addr] = new;
											addr++;
											bytes++;
											if(inSubroutineDef){
												subroutineLocCount++;
											}
										}
									
								}
							
						}
			
				}
				
			//close file
				fclose(fp);
		
		}
	
	/**
	* Dissassemble the memory program into coded lines to display
	* @function public
	* @param void* eOBJ Self
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
		
			//start at program address
				uint16_t addr = PROG_MEM_LOC;
				uint16_t lineAddr;
				char cycles[10];
				
			int j = 1;
			
			while(addr < MEM_LENGTH){

				//start line string
					lineAddr = addr;
					uint8_t opcode = self->cpu->RAM[addr];
					snprintf(cycles, 4,"%d", self->cpu->instructions[opcode].cycles);
					strings->strncatcat(
						strcpy(line, "$"),
						49,
						strings->hex(addr, 2, num),
						": ",
						self->cpu->instructions[opcode].name,
						" c",
						cycles,
						NULL
					);
					
				//get next addr
					addr++;

				//use instructions array to fill in the mem locations where data and not opcodes are
					for(int i = 0; i < self->cpu->instructions[opcode].pcoShifts && addr < MEM_LENGTH; i++){
					
						strcpy(self->code[addr], "---");
						addr++;

					}
					
				if(addr <= MEM_LENGTH){

					//write that line to code array
						strcpy(self->code[lineAddr], line);
						
						j++;
						
				} else {
					break;
				}

			}
			
			//for(uint16_t i = PROG_MEM_LOC; i < MEM_LENGTH; i++){
				//printf("%#x: %p %s\n", i, (void*)self->code[i], self->code[i]);
			//}
		
		}
