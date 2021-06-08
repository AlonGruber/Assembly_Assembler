#ifndef READ_CODE_H
#define READ_CODE_H
#include "utils.h"
#include "error_handling.h"
#include "symbol_handling.h"
#include "guide_data_handling.h"
#include "instruction_handling.h"
#include "entries_and_extern_handling.h"

#define GUIDE_ENTRY_STRING ".entry"
#define GUIDE_EXTERN_STRING ".extern"
#define GUIDE_ASCIZ_STRING ".asciz"
#define GUIDE_DB_STRING ".db"
#define GUIDE_DH_STRING ".dh"
#define GUIDE_DW_STRING ".dw"

#define RESERVED_ENTRY_STRING "entry"
#define RESERVED_EXTERN_STRING "extern"
#define RESERVED_ASCIZ_STRING "asciz"
#define RESERVED_DB_STRING "db"
#define RESERVED_DH_STRING "dh"
#define RESERVED_DW_STRING "dw"

/*most of explanation for these functions is inside them*/

/*used to check if string is one of the reserved words*/
bool checkIfStringIsReservedWord(char* input);

/*checks if the input string is a comment or not by checking for ; char,
returns true or false*/
bool checkIfStringIsComment(char* input_word);

/*checks if the string is one of the opcodes
returns true or false*/
bool checkIfStringIsOpcode(char* input_word);

/*we get a string and return which of the possible guide words it is*/
int whichGuideWord(char* input_word);
void firstPass(FILE* file, int* IC_PTR, int* DC_PTR);
void secondPass(int IC);

#endif


