#include "error_handling.h"


/*a head for the error list*/
static error_struct* error_head = NULL;

void addNewError(char* error_string, char* additional_error_data, int error_at_line)
{
    error_struct* new_error = malloc(sizeof(error_struct));
    new_error->error_string = malloc(MAX_LINE_LENGTH);
    strcpy(new_error->error_string, error_string);
    new_error->error_at_line = error_at_line;
    new_error->next_error_ptr = NULL;
    if (!additional_error_data)
        new_error->additional_error_data = NULL;
    else
    {
        new_error->additional_error_data = malloc(MAX_LINE_LENGTH);
        strcpy(new_error->additional_error_data, additional_error_data);
    }

    if (!error_head)
        error_head = new_error;
    else
    {
        error_struct* error_pointer = error_head;
        while (error_pointer->next_error_ptr) 
            error_pointer = error_pointer->next_error_ptr;
        error_pointer->next_error_ptr = new_error;
    }
}

bool ifCondAddError(int condition, char* error_string, char* additional_error_data, int error_at_line) {
    if (condition) {
        addNewError(error_string, additional_error_data, error_at_line);
        return true;
    }
    return false;
}

void printErrorList()
{
    error_struct* error_pointer = error_head;
    while (error_pointer)
    {
            if (error_pointer->additional_error_data && error_pointer->error_at_line)
               printf("Error @ Line %d: %s %s \n", error_pointer->error_at_line,error_pointer->error_string, error_pointer->additional_error_data);
            else if(error_pointer->additional_error_data)
                printf("Error:  %s %s\n", error_pointer->error_string, error_pointer->additional_error_data);
            else if (error_pointer->error_at_line)
                printf("Error @ Line %d: %s  \n", error_pointer->error_at_line,error_pointer->error_string);
            else 
                printf("Error: %s \n", error_pointer->error_string);
    error_pointer = error_pointer->next_error_ptr;
    } 
}

bool foundErrors()
{
    if (error_head)
        return true;
    else
        return false;
}



void deleteErrorList()
{
    error_struct* error_pointer_1 = error_head;
    if (!error_head)
        return;  
    while (error_pointer_1)
    {
        error_struct* error_pointer_2 = error_pointer_1;
        error_pointer_1 = error_pointer_1->next_error_ptr;
        free(error_pointer_2->additional_error_data);
        free(error_pointer_2->error_string);
        free(error_pointer_2);
    }
    error_head = NULL;
}
