#ifndef SYMBOL_HANDLING_H
#define SYMBOL_HANDLING_H
#include "utils.h"
#include "error_handling.h"

/*This section handels the information storage of all the symbols.
whenever we encounter a label while running through the code,
it is added here*/

/*enum for distinguishing between code symbols
and guide data symbols*/
typedef enum attribute {
	code=1,
	guide_data=2
}attribute;

/*A struct for storing the symbol information
string for the label,
address of where it will sit eventually in the code -
if its a code symbol then its IC
if its a guide data symbol then its final IC+DC
symbol attribute enum for indicating between the two
and a pointer to the next symbol*/
typedef struct symbol_struct
{
	char* symbol_label;
	int symbol_address;
	attribute symbol_attribute;
	struct symbol_struct* next_symbol;
} symbol_struct;


/*creates a new struct and adds to it all the data,
besides the label itself which is assigned a string with malloc,
then adds it to the list at the next vacant pointer*/
void addSymbolToList(char* symbol_label, int symbol_address, attribute att, int symbol_line);

/*used by addSymbolToList , when adding a new symbol, we check on the already existing list
if a label with the same name and attribute already exists in the list, if it does
we add an error*/
void addErrorIfSymbolExists(symbol_struct* symbol_check, int symbol_line);

/*We look for the symbol by the label,
iterating on the list, if we found a match we return the pointer,
if not we return NULL*/
symbol_struct* findSymbolInList(char* symbol_label);

/*when we add a code symbol we assign IC to its address,
but when we see a guide data symbol we assign DC to it,
since all the data will be displayed at the end of the code,
and after we finish finding all the instructions we add the final IC
to all the guide data symbols*/
void addICToAllGuideDataSymbols(int IC);

/*iterates on all the list and frees all symbols*/
void deleteSymbolList();

/*returns the head pointer*/
symbol_struct* getSymbolHead();



#endif