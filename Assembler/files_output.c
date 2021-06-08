#include "files_output.h"


FILE* createFile(char* filename, char* extension)
{
    FILE* file = NULL;
    char file_name[30];
    strcpy(file_name, filename);
	if(extension)
		strcat(file_name, extension);
    if (!(file = fopen(file_name, "w")))
    {
        printf("Can't create file %s.\n", file_name);
        return NULL;
    }
    return file;
}

bool checkFileIsAssemblerAndRemoveExtension(char* input_file)
{
	char * word;
	word = strtok(input_file, ".");
	word = strtok(NULL, ".");
	if (strcmp(word, "as")==0)
		return true;
	return false;
}

void _8bitsToHex(unsigned int data, char* hex_encoded)
{
	char binBase[_8BITS];
	unsigned int i;
	int ONE = 1;
	for (i = 0; i < _8BITS; i++)
	{
		if (data & ONE)
			binBase[i] = '1';
		else
			binBase[i] = '0';
		ONE = ONE << 1;
	}
	for (i = 0; i < _8BITS; i += 4)
	{
		if (binBase[i] == '0' && binBase[i + 1] == '0' && binBase[i + 2] == '0' && binBase[i + 3] == '0')
			hex_encoded[1 - (i / 4)] = '0';
		if (binBase[i] == '1' && binBase[i + 1] == '0' && binBase[i + 2] == '0' && binBase[i + 3] == '0')
			hex_encoded[1 - (i / 4)] = '1';
		if (binBase[i] == '0' && binBase[i + 1] == '1' && binBase[i + 2] == '0' && binBase[i + 3] == '0')
			hex_encoded[1 - (i / 4)] = '2';
		if (binBase[i] == '1' && binBase[i + 1] == '1' && binBase[i + 2] == '0' && binBase[i + 3] == '0')
			hex_encoded[1 - (i / 4)] = '3';
		if (binBase[i] == '0' && binBase[i + 1] == '0' && binBase[i + 2] == '1' && binBase[i + 3] == '0')
			hex_encoded[1 - (i / 4)] = '4';
		if (binBase[i] == '1' && binBase[i + 1] == '0' && binBase[i + 2] == '1' && binBase[i + 3] == '0')
			hex_encoded[1 - (i / 4)] = '5';
		if (binBase[i] == '0' && binBase[i + 1] == '1' && binBase[i + 2] == '1' && binBase[i + 3] == '0')
			hex_encoded[1 - (i / 4)] = '6';
		if (binBase[i] == '1' && binBase[i + 1] == '1' && binBase[i + 2] == '1' && binBase[i + 3] == '0')
			hex_encoded[1 - (i / 4)] = '7';
		if (binBase[i] == '0' && binBase[i + 1] == '0' && binBase[i + 2] == '0' && binBase[i + 3] == '1')
			hex_encoded[1 - (i / 4)] = '8';
		if (binBase[i] == '1' && binBase[i + 1] == '0' && binBase[i + 2] == '0' && binBase[i + 3] == '1')
			hex_encoded[1 - (i / 4)] = '9';
		if (binBase[i] == '0' && binBase[i + 1] == '1' && binBase[i + 2] == '0' && binBase[i + 3] == '1')
			hex_encoded[1 - (i / 4)] = 'A';
		if (binBase[i] == '1' && binBase[i + 1] == '1' && binBase[i + 2] == '0' && binBase[i + 3] == '1')
			hex_encoded[1 - (i / 4)] = 'B';
		if (binBase[i] == '0' && binBase[i + 1] == '0' && binBase[i + 2] == '1' && binBase[i + 3] == '1')
			hex_encoded[1 - (i / 4)] = 'C';
		if (binBase[i] == '1' && binBase[i + 1] == '0' && binBase[i + 2] == '1' && binBase[i + 3] == '1')
			hex_encoded[1 - (i / 4)] = 'D';
		if (binBase[i] == '0' && binBase[i + 1] == '1' && binBase[i + 2] == '1' && binBase[i + 3] == '1')
			hex_encoded[1 - (i / 4)] = 'E';
		if (binBase[i] == '1' && binBase[i + 1] == '1' && binBase[i + 2] == '1' && binBase[i + 3] == '1')
			hex_encoded[1 - (i / 4)] = 'F';
	}

}

void _32bitsToHex(unsigned int* data,char* hex_encoded)
{
	unsigned char temp;
	char binBase[_32BITS];
	unsigned int i;
	int ONE = 1;
	for (i = 0; i < _32BITS; i++)
	{
		if (*data & ONE)
			binBase[i] = '1';
		else
			binBase[i] = '0';
		ONE = ONE << 1;
	}
	for (i = 0; i < _32BITS; i += 4)
	{
		if (binBase[i] == '0' && binBase[i + 1] == '0' && binBase[i + 2] == '0' && binBase[i + 3] == '0')
			hex_encoded[7 - (i / 4)] = '0';
		if (binBase[i] == '1' && binBase[i + 1] == '0' && binBase[i + 2] == '0' && binBase[i + 3] == '0')
			hex_encoded[7 - (i / 4)] = '1';
		if (binBase[i] == '0' && binBase[i + 1] == '1' && binBase[i + 2] == '0' && binBase[i + 3] == '0')
			hex_encoded[7 - (i / 4)] = '2';
		if (binBase[i] == '1' && binBase[i + 1] == '1' && binBase[i + 2] == '0' && binBase[i + 3] == '0')
			hex_encoded[7 - (i / 4)] = '3';
		if (binBase[i] == '0' && binBase[i + 1] == '0' && binBase[i + 2] == '1' && binBase[i + 3] == '0')
			hex_encoded[7 - (i / 4)] = '4';
		if (binBase[i] == '1' && binBase[i + 1] == '0' && binBase[i + 2] == '1' && binBase[i + 3] == '0')
			hex_encoded[7 - (i / 4)] = '5';
		if (binBase[i] == '0' && binBase[i + 1] == '1' && binBase[i + 2] == '1' && binBase[i + 3] == '0')
			hex_encoded[7 - (i / 4)] = '6';
		if (binBase[i] == '1' && binBase[i + 1] == '1' && binBase[i + 2] == '1' && binBase[i + 3] == '0')
			hex_encoded[7 - (i / 4)] = '7';
		if (binBase[i] == '0' && binBase[i + 1] == '0' && binBase[i + 2] == '0' && binBase[i + 3] == '1')
			hex_encoded[7 - (i / 4)] = '8';
		if (binBase[i] == '1' && binBase[i + 1] == '0' && binBase[i + 2] == '0' && binBase[i + 3] == '1')
			hex_encoded[7 - (i / 4)] = '9';
		if (binBase[i] == '0' && binBase[i + 1] == '1' && binBase[i + 2] == '0' && binBase[i + 3] == '1')
			hex_encoded[7 - (i / 4)] = 'A';
		if (binBase[i] == '1' && binBase[i + 1] == '1' && binBase[i + 2] == '0' && binBase[i + 3] == '1')
			hex_encoded[7 - (i / 4)] = 'B';
		if (binBase[i] == '0' && binBase[i + 1] == '0' && binBase[i + 2] == '1' && binBase[i + 3] == '1')
			hex_encoded[7 - (i / 4)] = 'C';
		if (binBase[i] == '1' && binBase[i + 1] == '0' && binBase[i + 2] == '1' && binBase[i + 3] == '1')
			hex_encoded[7 - (i / 4)] = 'D';
		if (binBase[i] == '0' && binBase[i + 1] == '1' && binBase[i + 2] == '1' && binBase[i + 3] == '1')
			hex_encoded[7 - (i / 4)] = 'E';
		if (binBase[i] == '1' && binBase[i + 1] == '1' && binBase[i + 2] == '1' && binBase[i + 3] == '1')
			hex_encoded[7 - (i / 4)] = 'F';
	}
	
	temp = hex_encoded[6];
	hex_encoded[6] = hex_encoded[0];
	hex_encoded[0] = temp;

	temp = hex_encoded[7];
	hex_encoded[7] = hex_encoded[1];
	hex_encoded[1] = temp;

	temp = hex_encoded[4];
	hex_encoded[4] = hex_encoded[2];
	hex_encoded[2] = temp;

	temp = hex_encoded[5];
	hex_encoded[5] = hex_encoded[3];
	hex_encoded[3] = temp;
}




void writeAllFiles(int IC, int DC, char* name)
{
	/*pointers to all the files we could write -
	object file,externs file and entries file*/
	FILE* objFile = NULL;
	FILE* entFile = NULL;
	FILE* extFile = NULL;
	/*since the instructions are 32 bit encoded,
	we use an int to point to the start of each instruction,
	and print that data after some modifications*/
	unsigned int* outputLine = NULL;
	/*pointers to the structs we will use*/
	instruction_struct* instructionPtr = NULL;
	guide_data_struct* guideDataPtr = NULL;
	entries_and_externs_struct* entAndExtPtr = NULL;
	symbol_struct* symbolPtr = NULL;
	int i = 0;
	/*buffer used in printing the 32 bit instructions */
	char _32bitPrint[12];
	/*buffer used in printing guide data - 8 bits at a time*/
	char _8bitPrint[3];
	/*null pointers to buffer*/
	_8bitPrint[2]='\0';
	_32bitPrint[11] = '\0';

	/*create an object file to write to */
	objFile = createFile(name,".ob");
	instructionPtr = getInstructionHead();
	/*write to the top of the object file the amount of instruction data in bytes, and guide data in bytes*/
	fprintf(objFile, "\t%d %d\n", IC - 100, DC);
	while (instructionPtr)
	{
		/*go over each of the instructions in the list, and according to the instruction
		in the union, assign a pointer to the start of it*/
		switch (instructionPtr->which_instruction)
		{
		case(R):
			outputLine = (unsigned int*)(&(instructionPtr->instructions.R_instruction));
			break;
		case(I):
			outputLine = (unsigned int*)(&(instructionPtr->instructions.I_instruction));
			break;
		case(J):
			outputLine = (unsigned int*)(&(instructionPtr->instructions.J_instruction));
		}
		/*decode the 32 bits in the instruction to hex string*/
		_32bitsToHex(outputLine, _32bitPrint);
		/*add spaces to the hex string*/
		addSpaces(_32bitPrint);
		/*print the hex string with the address of the instruction*/
		fprintf(objFile, "%04d %s\n", instructionPtr->instruction_address, _32bitPrint);
		/*clean the buffer for the next iteration*/
		clearbuffer(_32bitPrint);
		instructionPtr = instructionPtr->next_instruction_pointer;
	}

	guideDataPtr = getGuideDataHead();
	/*Go over all the available guide data*/
	while (guideDataPtr) {
		/*if we went over 4 bytes, print the current IC - 
		which is actually DC but at the end of IC*/
		if (i % 4 == 0)
			fprintf(objFile, "%04d ", IC);
		/*encode the guide data to hex*/
		_8bitsToHex(guideDataPtr->data, _8bitPrint);
		/*increase by 1*/
		i += 1;
		/*print the hex encoded data*/
		fprintf(objFile, "%s ", _8bitPrint);
		/*if we printed 4 bytes, add a new line and increase IC
		so that it gets printed in the start of the next iteration*/
		if (i % 4 == 0) {
			fprintf(objFile, "\n");
			IC += 4;
			/*clean the buffer for the next iteration*/
			clearbuffer(_8bitPrint);
		}
		guideDataPtr = guideDataPtr->next_guide_data;		
	}
	
	/*check in the entries and externals list if 
	externals exists to know if to create a file for it*/
	entAndExtPtr = getENTandEXThead();
	while (entAndExtPtr) {
		if (entAndExtPtr->type == data_type_enum_extern && entAndExtPtr->deforoc == occurance) {
			extFile = createFile(name, EXTERN_EXTENSION);
			break;
		}
		entAndExtPtr = entAndExtPtr->next_pointer;
	}
	/*check in the entries and externals list if
	entrys exists to know if to create a file for it*/
	entAndExtPtr = getENTandEXThead();
	while (entAndExtPtr) {
		if (entAndExtPtr->type == data_type_enum_entry && entAndExtPtr->deforoc == occurance) {
			entFile = createFile(name, ENTRY_EXTENSION);
			break;
		}
		entAndExtPtr = entAndExtPtr->next_pointer;
	}
	/*go over the external occurences and print them to file*/
	entAndExtPtr = getENTandEXThead();
	while (entAndExtPtr)
	{
		if (entAndExtPtr->type == data_type_enum_extern && entAndExtPtr->deforoc == occurance)
				fprintf(extFile, "%s %04d\n", entAndExtPtr->label, entAndExtPtr->address);
		entAndExtPtr = entAndExtPtr->next_pointer;
	}
	/*go over the entries occurences and print them to file,since these appear in the actual file,
	we go over the symbol table to check where they actually are to print their address*/
	entAndExtPtr = getENTandEXThead();
	while (entAndExtPtr)
	{
		if (entAndExtPtr->type == data_type_enum_entry && entAndExtPtr->deforoc == definition) {
			symbolPtr = findSymbolInList(entAndExtPtr->label);
			if(symbolPtr)
				fprintf(entFile, "%s %04d\n", entAndExtPtr->label, symbolPtr->symbol_address);
		}
		entAndExtPtr = entAndExtPtr->next_pointer;
	}
	printf("Operation completed successfully\n");
	if (objFile)
		fclose(objFile);
	if (entFile)
		fclose(entFile);
	if (extFile)
		fclose(extFile);
}


void addSpaces(char* newbase)
{
	newbase[10] = newbase[7];
	newbase[9] = newbase[6];

	newbase[8] = ' ';

	newbase[7] = newbase[5];
	newbase[6] = newbase[4];

	newbase[5] = ' ';

	newbase[4] = newbase[3];
	newbase[3] = newbase[2];

	newbase[2] = ' ';
}

void clearbuffer(char* buffer)
{
	int i;
	for (i = 0; i < strlen(buffer);i++) {
		*(buffer + i) = '\0';
	}
}
