#ifndef ENT_AND_EXT_HANDLING
#define ENT_AND_EXT_HANDLING
#include "utils.h"
#include "error_handling.h"

/*enum for telling if the entry is a definition ie starts with .entry or .external
or if its an occurance ie - if it has already been defined and now it appears in the code as symbol*/
typedef enum def_or_oc {
	definition,
	occurance
}def_or_oc;

/*struct for holding all the enties and externals
label string for the name itself
the address for where the label was found
enum to tell if ts a definition or occurance
a data type enum to tell if the node contains an entry or external label
and a pointer to the next node
*/
typedef struct entries_and_externs_struct
{
	char* label;
	int address;
	def_or_oc deforoc;
	data_type_enum type;
	struct entries_and_externs_struct* next_pointer;
} entries_and_externs_struct;


/*add a label to the list*/
void addENTandEXT(char* label, int address, int line, data_type_enum data_type, def_or_oc deforoc);

/*used while adding a label to check that the same label is not entry and extern*/
void checkLabelIsNotExternAndEntry(char* label, data_type_enum data_type, int line, def_or_oc deforoc);

/*find a node in the list with the label input, return the node pointer,
or null if not found*/
entries_and_externs_struct* findInENTandEXTList(char* label);

/*return the head of the list*/
entries_and_externs_struct* getENTandEXThead();
/*frees all of the list*/
void freeENTandEXTList();












#endif




