
#ifndef UTILS_H
#define UTILS_H
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <limits.h>
#include <ctype.h>


/*All the constants used in the project are united in utils.h -*/
#define MAX_LINE_LENGTH 80
#define REGISTER_COUNT 32
#define OPCODE_COUNT 27
#define LABEL_MAX_SIZE 31


/*Enum for boolean values - 0 is false naturally and 1 for true*/
typedef enum bool{
	false,
	true
}bool;

/*Used to distinguish between the different guide data types found while searching for guide data - ie starting with . */
typedef enum data_type_enum {
	data_type_enum_entry = 1,
	data_type_enum_extern = 2,
	data_type_enum_asciz = 3,
	data_type_enum_char =4,
	data_type_enum_db = 5,
	data_type_enum_dh = 6,
	data_type_enum_dw = 7
}data_type_enum;

/*enum for all the opcodes in the project*/
typedef enum opcode_enum {
	add_opcode_enum = 0,
	sub_opcode_enum = 0,
	and_opcode_enum = 0,
	or_opcode_enum = 0,
	nor_opcode_enum = 1,
	move_opcode_enum = 1,
	mvhi_opcode_enum = 1,
	mvlo_opcode_enum = 1,
	addi_opcode_enum = 10,
	subi_opcode_enum = 11,
	andi_opcode_enum = 12,
	ori_opcode_enum = 13,
	nori_opcode_enum = 14,
	bne_opcode_enum = 15,
	beq_opcode_enum = 16,
	blt_opcode_enum = 17,
	bgt_opcode_enum = 18,
	lb_opcode_enum = 19,
	sb_opcode_enum = 20,
	lw_opcode_enum = 21,
	sw_opcode_enum = 22,
	lh_opcode_enum = 23,
	sh_opcode_enum = 24,
	jmp_opcode_enum = 30,
	la_opcode_enum = 31,
	call_opcode_enum = 32,
	stop_opcode_enum = 63
}opcode_enum;

/*enum for all the funct codes in the project*/
typedef enum funct_enum {
	no_funct = 0,
	add_funct = 1,
	sub_funct = 2,
	and_funct = 3,
	or_funct = 4,
	nor_funct = 5,
	move_funct = 1,
	mvhi_funct = 2,
	mvlo_funct = 3
}funct_enum;

/*used to distinguish between the instuction types themselfes - R,I,J and also to tell
within the R,I,J types themselfes, as explained in the project booklet*/
typedef enum instruction_type{
	RArithmeticInstuction=1,
	RCopyInstuction,
	IArithmeticInstuction,
	IBranchInstuction,
	IMemoryInstuction,
	JInstuction
}instruction_type;

/*used to distinguish between the instuction types themselfes - R,I,J and also to tell
within the R,I,J types themselfes, as explained in the project booklet*/

/*enum for all the registers in the project - from 0 to 31*/
typedef enum Registers_enum {
	Register_0 = 0,
	Register_1 = 1,
	Register_2 = 2,
	Register_3 = 3,
	Register_4 = 4,
	Register_5 = 5,
	Register_6 = 6,
	Register_7 = 7,
	Register_8 = 8,
	Register_9 = 9,
	Register_10 = 10,
	Register_11 = 11,
	Register_12 = 12,
	Register_13 = 13,
	Register_14 = 14,
	Register_15 = 15,
	Register_16 = 16,
	Register_17 = 17,
	Register_18 = 18,
	Register_19 = 19,
	Register_20 = 20,
	Register_21 = 21,
	Register_22 = 22,
	Register_23 = 23,
	Register_24 = 24,
	Register_25 = 25,
	Register_26 = 26,
	Register_27 = 27,
	Register_28 = 28,
	Register_29 = 29,
	Register_30 = 30,
	Register_31 = 31
}Registers_enum;

/*This struct is used only in the static array below- 
we use it to store useful information about all the different instructions.
This way when we find a match for the string part of the instruction,
we can find a match using the string part of the struct,
and then get the opcode,funct,and instruction*/
typedef struct opcode_struct {
	const char* opcode_string;
	opcode_enum opcode_enum;
	funct_enum funct_enum;
	instruction_type instruction_type;
}opcode_struct;


/*checks if the input string is guide data or not by checking for . char,
returns true or false*/
bool checkIfStringIsGuideData(char* input_word);

/*checks if the input string is a valid label,
by making sure all the chars are digits and letters,
returns true or false*/
bool checkIfLabelStringIsValidInInstruction(char * input_word);

/*checks if the input string is a label or not,
then adds a \0 char at the end,
returns true or false*/
bool checkIfLabelStringIsValidInStart(char* input_word);

/*checks if the immediate number is within range ie not too big or too small,
returns true or false*/
bool checkIfImmediateInRange(char* input_word);

/*checks if the immediate number string is an actual number,
returns true or false*/
bool checkIfStringIsImmediateNumber(char* input_word);


/*checks if the string is one of the registers
returns true or false*/
bool checkIfStringIsRegister(char* input_word);

#endif
