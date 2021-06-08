#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H
#include "utils.h"

/*struct for an error-
the error string is a must for any error,
if we have extra data to print we add it in the additional error data
the line is a must also - the line of the input file that triggered the error
and a pointer to the next error*/
typedef struct error_struct {
	char* error_string;
	char* additional_error_data;
	int error_at_line;
	struct error_struct* next_error_ptr;
} error_struct;



/*add an error node to the list,if additional_error_data is not null,
we allocate more data for it*/
void addNewError(char* error_string, char* additional_error_data,int error_at_line);

/*checks if a condition is met, if so, add an error-
used to make the code more readable and have less if's,
also returns true or false whether an error was added or not */
bool ifCondAddError(int condition, char* error_string, char* additional_error_data, int error_at_line);

/*print all the errors in the list,
if the list has some null pointers they are not printed*/
void printErrorList();

/*returns the head - ie if some error was found in the code*/
bool foundErrors();

/*frees the error list*/
void deleteErrorList();


#endif
