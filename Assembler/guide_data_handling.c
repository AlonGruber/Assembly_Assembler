#include "guide_data_handling.h"

/*head for the start of the list*/
static guide_data_struct* guide_data_head = NULL;

void addGuideData(char guide_data, data_type_enum data_type, int line,int * DC)
{
    guide_data_struct* new_guide_data = malloc(sizeof(guide_data_struct));
    new_guide_data->data = (unsigned char)guide_data;
    new_guide_data->type = data_type;
    new_guide_data->address = *DC;
    new_guide_data->next_guide_data = NULL;
    if (!guide_data_head)
        guide_data_head = new_guide_data;
    else
    {
        guide_data_struct* pointer = guide_data_head;
        while (pointer->next_guide_data)
            pointer = pointer->next_guide_data;
        pointer->next_guide_data = new_guide_data;
    }
}



void AddGuideWordList(char* word_data, data_type_enum data_type, int line, int* DC)
{
    if (!(word_data = strtok(NULL, " ,\t\r\n"))) {
        addNewError("List cannot be empty", NULL, line);
        return;
    }
    else
    {
        addWordType(word_data, data_type, line,DC);
        while ((word_data = strtok(NULL, " ,\t\r\n")))
            addWordType(word_data, data_type,line, DC);
    }
}

void addWordType(char* number, data_type_enum data_type, int line, int* DC)
{
    long int num_in_word;
    num_in_word = strtol(number, NULL, 10);

    switch (data_type)
    {
    case(data_type_enum_db):
    {
        ifCondAddError((!(INT8_MIN < num_in_word) || !(num_in_word < INT8_MAX)), "Number is out of range for byte ", number, line);
        (*DC)++;
        addGuideData(num_in_word, data_type, line, DC);
        break;
    }
    /*we increment DC after each addition as we split the half word into 2 bytes by rotating it and doing bitwise AND with FF*/
    case(data_type_enum_dh):
    {
        ifCondAddError((!(INT16_MIN < num_in_word) || !(num_in_word < INT16_MAX)), "Number is out of range for half word ", number, line);
        (*DC)++;
        addGuideData((unsigned char)num_in_word & 0x00FF, data_type, line, DC);
        (*DC)++;
        addGuideData((unsigned char)((num_in_word & 0xFF00) >> 8), data_type, line, DC);
        break;
    }
    /*we increment DC after each addition as we split the word into 4 bytes by rotating it and doing bitwise AND with FF*/
    case(data_type_enum_dw):
    {
        ifCondAddError((!(INT_MIN < num_in_word) || !(num_in_word < INT_MAX)), "Number is out of range for word ", number, line);
        (*DC)++;
        addGuideData((unsigned char)((num_in_word & 0x000000FF)), data_type, line, DC);
        (*DC)++;
        addGuideData((unsigned char)((num_in_word & 0x0000FF00)>>8), data_type, line, DC);
        (*DC)++;
        addGuideData((unsigned char)((num_in_word & 0x00FF0000)>>16), data_type, line, DC);
        (*DC)++;
        addGuideData((unsigned char)((num_in_word & 0xFF000000)>>24), data_type, line, DC);
        break;
    }
    default:
        break;
    }
    
}

void addAsciz(char* asciz_string, int line, int* DC)
{ 
    if(!asciz_string){
    	addNewError("Asciz data cannot be empty", NULL, line);
    	return;
	}	
    if (strcmp(asciz_string, "\"")==0)
    {
        addNewError("Asciz string is empty!", NULL, line);
        return;
    }
    if ((*asciz_string == '"') && (asciz_string[strlen(asciz_string) - 1] == '"'))
    {
        asciz_string[strlen(asciz_string) - 1] = '\0';
        asciz_string++;
    }
    else
    {
        addNewError("Asciz string does not have quotation marks", NULL,line);
        return;
    }

    while (*asciz_string != '\0')
    {
        addGuideData(*asciz_string, data_type_enum_char,line,DC);
        asciz_string++;
        (*DC)++;
    }
    addGuideData('\0', data_type_enum_char, line, DC);
    (*DC)++;
}



void addICToAllGuideData(int IC)
{
    guide_data_struct* data_pointer = guide_data_head;
    if (!data_pointer)
    {
        return;
    }
    while (data_pointer)
    {
        data_pointer->address += IC;
        data_pointer = data_pointer->next_guide_data;
    }
}

guide_data_struct* getGuideDataHead()
{
    return guide_data_head;
}


void freeGuideDataList()
{
    guide_data_struct* guide_data_pointer1 = guide_data_head;
    if (!guide_data_pointer1)
        return;
    while (guide_data_pointer1)
    {
        guide_data_struct* guide_data_pointer2 = guide_data_pointer1;
        guide_data_pointer1 = guide_data_pointer1->next_guide_data;
        free(guide_data_pointer2);
    }
    guide_data_head = NULL;
}
