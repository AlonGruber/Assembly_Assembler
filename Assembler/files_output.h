#ifndef ASSEMBLE_FILES
#define ASSEMBLE_FILES
#include "utils.h"
#include "instruction_handling.h"
#include "guide_data_handling.h"
#include "symbol_handling.h"
#include "entries_and_extern_handling.h"

#define ENTRY_EXTENSION ".ent"
#define EXTERN_EXTENSION ".ext"
#define _8BITS 8
#define _32BITS 32

/*creates a new file with the extension provided with the writing mode*/
FILE* createFile(char* filename, char* extension);

/*checks that the input filename ends with the assembler - .as enxtension
and removes it for further work*/
bool checkFileIsAssemblerAndRemoveExtension(char* input_file);

/*used in encodeing the guide data to hex - 
first we go over the array and encode it in binary encoding by
rotating to the right and doing a bitwise AND with 1,
then we go over the cells at jumps of 4 at a time and put in the hex encoded
string the matching hex letter*/
void _8bitsToHex(unsigned int data, char* hex_encoded);

/*same idea as with the _8bitsToHex function, only this time we repeat the process 
for 32 bits - for the instructions, and also we switch the order of the numbers
since the endiadess differs*/
void _32bitsToHex(unsigned int* data,char* hex_encoded);

/*this function writes all the files - explained in the function */
void writeAllFiles(int IC, int DC, char* name);

/*when we get the 32 bit encoded string its without spaces, we add them*/
void addSpaces(char* newbase);

/*fills a buffer with null chars - used between writing to file*/
void clearbuffer(char* buffer);







#endif