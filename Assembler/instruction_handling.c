#include "instruction_handling.h"


/*static struct array containing all the needed information for each of the instruction operations*/
static opcode_struct OPCODES[OPCODE_COUNT] = { {"add",add_opcode_enum,add_funct,RArithmeticInstuction},{"sub",sub_opcode_enum,sub_funct,RArithmeticInstuction},{"and",and_opcode_enum,and_funct,RArithmeticInstuction},{"or",or_opcode_enum,or_funct,RArithmeticInstuction},{"nor",nor_opcode_enum,nor_funct,RArithmeticInstuction},{"move",move_opcode_enum,move_funct,RCopyInstuction},{"mvhi",mvhi_opcode_enum,mvhi_funct,RCopyInstuction},{"mvlo",mvlo_opcode_enum,mvlo_funct,RCopyInstuction},{"addi",addi_opcode_enum,no_funct,IArithmeticInstuction},{"subi",subi_opcode_enum,no_funct,IArithmeticInstuction} ,{"andi",andi_opcode_enum,no_funct,IArithmeticInstuction} ,{"ori",ori_opcode_enum,no_funct,IArithmeticInstuction} ,{"nori",nori_opcode_enum,no_funct,IArithmeticInstuction},{"bne",bne_opcode_enum,no_funct,IBranchInstuction},{"beq",beq_opcode_enum,no_funct,IBranchInstuction},{"blt",blt_opcode_enum,no_funct,IBranchInstuction},{"bgt",bgt_opcode_enum,no_funct,IBranchInstuction},{"lb",lb_opcode_enum,no_funct,IMemoryInstuction},{"sb",sb_opcode_enum,no_funct,IMemoryInstuction},{"lw",lw_opcode_enum,no_funct,IMemoryInstuction},{"sw",sw_opcode_enum,no_funct,IMemoryInstuction},{"lh",lh_opcode_enum,no_funct,IMemoryInstuction},{"sh",sh_opcode_enum,no_funct,IMemoryInstuction},{"jmp",jmp_opcode_enum,no_funct,JInstuction},{"la",la_opcode_enum,no_funct,JInstuction},{"call",call_opcode_enum,no_funct,JInstuction},{"stop",stop_opcode_enum,no_funct,JInstuction} };

/*a head for the linked list*/
static instruction_struct* instruction_head = NULL;


void addInstruction(instruction_struct* instruction)
{
	if (!instruction_head)
	{
		instruction_head = instruction;
	}
	else
	{
		instruction_struct* pointer = instruction_head;
		while (pointer->next_instruction_pointer)
			pointer = pointer->next_instruction_pointer;
		pointer->next_instruction_pointer = instruction;
	}
}



instruction_struct* findInstructionWithoutLabelData()
{
	instruction_struct* pointer = instruction_head;
	while (pointer) {
		if (pointer->instruction_label)
			return pointer;
		pointer = pointer->next_instruction_pointer;
	}
	return NULL;

}



void processInstruction(char* instruction_string, int line, int* IC)
{
	/*once we found a match for the opcode i is used to look in the right place in the static opcode array*/
	int i;
	instruction_struct* instruction = NULL;
	Registers_enum rs_enum = 0;
	Registers_enum rt_enum = 0;
	Registers_enum rd_enum = 0;
	int16_t immediate = 0;

	/*first we iterate on the first word and check if is a valid opcode*/
	for (i = 0; i < OPCODE_COUNT; i++)
	{
		if (strcmp(instruction_string, OPCODES[i].opcode_string)==0)
		{
			instruction = malloc(sizeof(instruction_struct));
			instruction->instruction_line = line;
			instruction->next_instruction_pointer = NULL;
			instruction->instruction_label = NULL;
			instruction->instruction_address = *IC;
			/*we assign IC and increase it since each instruciton takes 4 bytes*/
			*IC += 4;
			break;
		}
	}
	/*if its not a valid command*/
	if (!instruction)
	{
		addNewError("Unknown command", instruction_string,line);
		return;
	}
	/*if it is we continue to process it according to the information in the static opcode array*/
	switch (OPCODES[i].instruction_type)
	{
		case(RArithmeticInstuction):
		{
			instruction_string = strtok(NULL, " ,\t\r\n");
			checkAndErrorForRegister(&rs_enum, instruction_string,line, "First operand should be a register");
			instruction_string = strtok(NULL, " ,\t\r\n");
			checkAndErrorForRegister(&rt_enum, instruction_string, line, "Second operand should be a register");
			instruction_string = strtok(NULL, " ,\t\r\n");
			checkAndErrorForRegister(&rd_enum, instruction_string, line, "Third operand should be a register");
			instruction_string = strtok(NULL, " ,\t\r\n");
			checkAndErrorIfExtraneousText(instruction_string,line,"Instruction does not take more than 3 arguments");
			instruction->which_instruction = R;
			createRArithmeticInstuction(&instruction->instructions.R_instruction, OPCODES[i].opcode_enum, rs_enum, rt_enum, rd_enum, OPCODES[i].funct_enum);
			break;
		}
		case(RCopyInstuction):
		{
			instruction_string = strtok(NULL, " ,\t\r\n");
			checkAndErrorForRegister(&rd_enum, instruction_string, line, "First operand should be a register");
			instruction_string = strtok(NULL, " ,\t\r\n");
			checkAndErrorForRegister(&rs_enum, instruction_string, line, "Second operand should be a register");
			instruction_string = strtok(NULL, " ,\t\r\n");
			checkAndErrorIfExtraneousText(instruction_string, line, "Instruction does not take more than 2 arguments");
			instruction->which_instruction = R;
			createRCopyInstruction(&instruction->instructions.R_instruction, OPCODES[i].opcode_enum, rd_enum, rs_enum, OPCODES[i].funct_enum);
			break;
		}
		case(IArithmeticInstuction):
		{
			instruction_string = strtok(NULL, " ,\t\r\n");
			checkAndErrorForRegister(&rs_enum, instruction_string, line, "First operand should be a register");
			instruction_string = strtok(NULL, " ,\t\r\n");
			checkAndErrorForImmediate(&immediate, instruction_string, line, "Second operand should be an immediate");
			instruction_string = strtok(NULL, " ,\t\r\n");
			checkAndErrorForRegister(&rt_enum, instruction_string, line, "Third operand should be a register");
			instruction_string = strtok(NULL, " ,\t\r\n");
			checkAndErrorIfExtraneousText(instruction_string, line, "Instruction does not take more than 3 arguments");
			instruction->which_instruction = I;
			createIArithmeticInstuction(&instruction->instructions.I_instruction,OPCODES[i].opcode_enum,rs_enum,immediate,rt_enum);
			break;
		}
		case(IBranchInstuction):
		{
			instruction_string = strtok(NULL, " ,\t\r\n");
			checkAndErrorForRegister(&rs_enum, instruction_string, line, "First operand should be a register");
			instruction_string = strtok(NULL, " ,\t\r\n");
			checkAndErrorForRegister(&rt_enum, instruction_string, line, "Second operand should be a register");
			instruction_string = strtok(NULL, " ,\t\r\n");
			checkAndErrorForLabel(instruction, instruction_string, line, "Invalid label as operand");
			instruction_string = strtok(NULL, " ,\t\r\n");
			checkAndErrorIfExtraneousText(instruction_string, line, "Instruction does not take more than 3 arguments");
			instruction->which_instruction = I;
			createIBranchInstuction(&instruction->instructions.I_instruction,OPCODES[i].opcode_enum,rs_enum,rt_enum,0);
			break;
		}
		case(IMemoryInstuction):
		{
			instruction_string = strtok(NULL, " ,\t\r\n");
			checkAndErrorForRegister(&rs_enum, instruction_string, line, "First operand should be a register");
			instruction_string = strtok(NULL, " ,\t\r\n");
			checkAndErrorForImmediate(&immediate, instruction_string, line, "Second operand should be an immediate");
			instruction_string = strtok(NULL, " ,\t\r\n");
			checkAndErrorForRegister(&rt_enum, instruction_string, line, "Third operand should be a register");
			instruction_string = strtok(NULL, " ,\t\r\n");
			checkAndErrorIfExtraneousText(instruction_string, line, "Instruction does not take more than 3 arguments");
			instruction->which_instruction = I;
			createIMemoryInstuction(&instruction->instructions.I_instruction, OPCODES[i].opcode_enum, rs_enum, immediate, rt_enum);
			break;
		}
		case(JInstuction):
		{
			/*used to check if jump instruction is to a register*/
			bool reg = false;
			switch (OPCODES[i].opcode_enum)
			{
				case(jmp_opcode_enum):
				{
					instruction_string = strtok(NULL, " ,\t\r\n");
					checkAndErrorForJMP(&rt_enum,&reg,instruction,instruction_string,line);
					instruction_string = strtok(NULL, " ,\t\r\n");
					checkAndErrorIfExtraneousText(instruction_string, line, "Instruction does not take more than 1 arguments");
					break;
				}
				case(call_opcode_enum):
				case(la_opcode_enum):
				{
					instruction_string = strtok(NULL, " ,\t\r\n");
					checkAndErrorForLabel(instruction, instruction_string, line, "Invalid label as operand");
					instruction_string = strtok(NULL, " ,\t\r\n");
					checkAndErrorIfExtraneousText(instruction_string, line, "Instruction does not take more than 1 arguments");
					break;
				}
				case(stop_opcode_enum):
				{
					instruction_string = strtok(NULL, " ,\t\r\n");
					checkAndErrorIfExtraneousText(instruction_string, line,"Stop does not take arguments");
					break;
				}
				default:
					break;

			}
			instruction->which_instruction = J;
			if(reg)
				createJInstuction(&instruction->instructions.J_instruction,OPCODES[i].opcode_enum,reg, rt_enum);
			else
				createJInstuction(&instruction->instructions.J_instruction, OPCODES[i].opcode_enum, reg, 0);
			break;
		}
	}

	
	if (instruction)
		addInstruction(instruction);
}

void checkAndErrorForRegister(Registers_enum * r,char * instruction_string,int line,char * error_text)
{
	if (checkIfStringIsRegister(instruction_string))
		*r = strtol(instruction_string + 1, NULL, 10);
	else
		addNewError(error_text, instruction_string, line);
}

void checkAndErrorIfExtraneousText(char* instruction_string, int line,char * error_text)
{
	if (instruction_string)
		addNewError(error_text, instruction_string, line);
}

void checkAndErrorForImmediate(int16_t * immediate, char* instruction_string, int line,char * error_line)
{
	if (!checkIfStringIsImmediateNumber(instruction_string)) 
		addNewError(error_line, instruction_string, line);
	if (!checkIfImmediateInRange(instruction_string)) 
		addNewError("Immediate is not within range", instruction_string, line);
	else
		*immediate = strtol(instruction_string, NULL, 10);
}

void checkAndErrorForLabel(instruction_struct * instruction, char* instruction_string, int line, char* error_text)
{
	if (!checkIfLabelStringIsValidInInstruction(instruction_string)) 
		addNewError(error_text, instruction_string, line);
	else
	{
		instruction->instruction_label = malloc(MAX_LINE_LENGTH);
		strcpy(instruction->instruction_label, instruction_string);
	}
}

void checkAndErrorForJMP(Registers_enum * r, bool * is_reg, instruction_struct* instruction, char* instruction_string, int line)
{
	if (checkIfStringIsRegister(instruction_string)) {
		*r = strtol(instruction_string + 1, NULL, 10);
		*is_reg = true;

	}
	else if (!checkIfLabelStringIsValidInInstruction(instruction_string) && !checkIfStringIsRegister(instruction_string)) 
		addNewError("Invalid label as operand", instruction_string, line);
	else
	{
		instruction->instruction_label = malloc(MAX_LINE_LENGTH);
		strcpy(instruction->instruction_label, instruction_string);
	}
}

void createRArithmeticInstuction(R_instruction_struct* pointer_to_struct, opcode_enum opcode_enum, Registers_enum rs_enum, Registers_enum rt_enum, Registers_enum rd_enum, funct_enum funct_enum) {
	pointer_to_struct->funct = funct_enum;
	pointer_to_struct->rd = rd_enum;
	pointer_to_struct->rt = rt_enum;
	pointer_to_struct->rs = rs_enum;
	pointer_to_struct->opcode = opcode_enum;
	pointer_to_struct->unused = 0;
}

void createRCopyInstruction(R_instruction_struct* pointer_to_struct, opcode_enum opcode_enum, Registers_enum rs_enum, Registers_enum rd_enum, funct_enum funct_enum)
{
	createRArithmeticInstuction(pointer_to_struct, opcode_enum, rs_enum, 0, rd_enum, funct_enum);
}



void createIArithmeticInstuction(I_instruction_struct* pointer_to_struct, opcode_enum opcode_enum, Registers_enum rs_enum, int16_t immediate, Registers_enum rt_enum)
{
	pointer_to_struct->immediate = immediate;
	pointer_to_struct->rt = rt_enum;
	pointer_to_struct->rs = rs_enum;
	pointer_to_struct->opcode = opcode_enum;
}

void createIBranchInstuction(I_instruction_struct* pointer_to_struct, opcode_enum opcode_enum, Registers_enum rs_enum, Registers_enum rt_enum, int16_t immediate)
{
	createIArithmeticInstuction(pointer_to_struct, opcode_enum,rs_enum,immediate,rt_enum);
}

void createIMemoryInstuction(I_instruction_struct* pointer_to_struct, opcode_enum opcode_enum, Registers_enum rs_enum, int16_t immediate, Registers_enum rt_enum)
{
	createIArithmeticInstuction(pointer_to_struct, opcode_enum, rs_enum,immediate,rt_enum);
}


void createJInstuction(J_instruction_struct* pointer_to_struct, opcode_enum opcode_enum, bool is_reg, uint32_t address)
{
	pointer_to_struct->address = address;
	pointer_to_struct->reg = is_reg;
	pointer_to_struct->opcode = opcode_enum;
}




void freeInstructionList()
{
	instruction_struct* pointer1 = instruction_head;
	if (!pointer1)
		return;

	while (pointer1)
	{
		instruction_struct* pointer2 = pointer1;
		pointer1 = pointer1->next_instruction_pointer;
		free(pointer2->instruction_label);
		free(pointer2);
	}
	instruction_head = NULL;
}

instruction_struct* getInstructionHead()
{
	return instruction_head;
}
