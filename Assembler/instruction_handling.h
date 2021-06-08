#ifndef INSTRUCTIONS_
#define INSTRUCTIONS_
#include "utils.h"
#include "error_handling.h"
#include "symbol_handling.h"

/*This section of the code handles the processing of all the instructions found in the code*/

/*defines for all the sizes used here*/
#define  UNUSED_SIZE 6 
#define  FUNCT_SIZE 5 
#define  RD_SIZE 5 
#define  RT_SIZE 5 
#define  RS_SIZE 5 
#define  OPCODE_SIZE 6 
#define  IMMEDIATE_SIZE 16 
#define  REG_J_SIZE 1 
#define  ADDRESS_SIZE 25 



/*struct for the R instruction - set in same size and order as in project booklet*/
typedef struct R_instruction_struct {
	unsigned int unused : UNUSED_SIZE;
	unsigned int funct : FUNCT_SIZE;
	unsigned int rd : RD_SIZE;
	unsigned int rt : RT_SIZE;
	unsigned int rs : RS_SIZE;
	unsigned int opcode : OPCODE_SIZE;
}R_instruction_struct;

/*struct for the I instruction - set in same size and order as in project booklet*/
typedef struct I_instruction_struct {
	int immediate : IMMEDIATE_SIZE;
	unsigned int rt : RT_SIZE;
	unsigned int rs : RS_SIZE;
	unsigned int opcode : OPCODE_SIZE;
}I_instruction_struct;

/*struct for the J instruction - set in same size and order as in project booklet*/
typedef struct J_instruction_struct {
	unsigned int address : ADDRESS_SIZE;
	unsigned int reg : REG_J_SIZE;
	unsigned int opcode : OPCODE_SIZE;
}J_instruction_struct;

/*union struct - has each one of the instructions,
this way we can wrap all the instructions under the same union,
so that the wrapper for all the instructions will be the same*/
typedef union all_instructions_union {
	R_instruction_struct R_instruction;
	I_instruction_struct I_instruction;
	J_instruction_struct J_instruction;
}all_instructions_union;

/*enum used to tell which of the commands is stored in union*/
typedef enum which_instruction {
	R = 1,
	I = 2,
	J = 3
}which_instruction;


/*The complete instruction struct, contains the union for all the instructions,
and an instruction type enum for telling which command is stored there
also contains the address according to IC
and the line the instructions is in the input file
finally, if we have a label in the instruction, we have it as a string,
and a pointer to the next instruction in the list*/
typedef struct instruction_struct {
	all_instructions_union instructions;
	which_instruction which_instruction;
	int instruction_address;
	int instruction_line;
	char* instruction_label;
	struct instruction_struct* next_instruction_pointer;
}instruction_struct;


/*Main function for this section
We get an input from the first pass for each line which is an instruction
We process the string word by word to validate that the instruction itself is 
a valid option for an instruction ie opcode, and also we validate each one 
of the strings throught the instruciton - ie be it register, label or immediate
we increace IC for each command we read, and assign*/
void processInstruction(char* instruction_string, int line, int* IC);

/*Adds the instruction to the list in the next avaliable pointer*/
void addInstruction(instruction_struct* instruction);

/*We search on the list for an instruction that has a non NULL in the
instruction label struct, meaning the instruction itself has a label,
which means that we need to refer to that label in the instruction itself,
used in the second pass after we have all the label information*/
instruction_struct* findInstructionWithoutLabelData();

/*We expect a register - if the next string is a register assign it, if not add error */
void checkAndErrorForRegister(Registers_enum * r, char* word_in_instruction_string, int line, char* error_text);

/*We expect a no more text - if something exists after the end of the instruction - add error */
void checkAndErrorIfExtraneousText(char* word_in_instruction_string, int line, char* error_text);

/*We expect an immediate number  - if the next string is an immediate within range -  assign it, if not add error */
void checkAndErrorForImmediate(int16_t * immediate,char* word_in_instruction_string, int line,char * error_text);

/*We expect a label string - if the next string is a label assign it, if not add error */
void checkAndErrorForLabel(instruction_struct* instruction, char* word_in_instruction_string, int line, char* error_text);

/*checks for the jmp command*/
void checkAndErrorForJMP(Registers_enum * r,bool * is_reg,instruction_struct * instruction, char* word_in_instruction_string, int line);

/*many of the create instruction functions below imploy the same function type but with set parameters*/

/*creates an R arithmetic type instructions - fills all the fields accordingly*/
void createRArithmeticInstuction(R_instruction_struct* pointer_to_struct, opcode_enum opcode_enum, Registers_enum rs_enum, Registers_enum rt_enum, Registers_enum rd_enum, funct_enum funct_enum);
/*creates an R copy type instructions - fills all the fields accordingly*/
void createRCopyInstruction(R_instruction_struct* pointer_to_struct, opcode_enum opcode_enum, Registers_enum rs_enum, Registers_enum rd_enum, funct_enum funct_enum);
/*creates an I arithmetic type instructions - fills all the fields accordingly*/
void createIArithmeticInstuction(I_instruction_struct* pointer_to_struct, opcode_enum opcode_enum, Registers_enum rs_enum, int16_t immediate, Registers_enum rt_enum);
/*creates an I branch type instructions - fills all the fields accordingly*/
void createIBranchInstuction(I_instruction_struct* pointer_to_struct, opcode_enum opcode_enum, Registers_enum rs_enum, Registers_enum rt_enum, int16_t immediate);
/*creates an I memory type instructions - fills all the fields accordingly*/
void createIMemoryInstuction(I_instruction_struct* pointer_to_struct, opcode_enum opcode_enum, Registers_enum rs_enum, int16_t immediate, Registers_enum rt_enum);
/*creates an J type instructions - fills all the fields accordingly*/
void createJInstuction(J_instruction_struct* pointer_to_struct, opcode_enum opcode_enum, bool is_reg, uint32_t address);

/*deletes all the instructions in the list including the labels*/
void freeInstructionList();

/*returns the head of the instruction list*/
instruction_struct* getInstructionHead();

#endif