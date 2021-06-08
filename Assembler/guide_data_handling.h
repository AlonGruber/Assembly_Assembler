#ifndef GUIDE_DATA_HANDLING_H
#define GUIDE_DATA_HANDLING_H
#include "utils.h"
#include "error_handling.h"

/*This section manages all the data found in the program*/

/*struct for holding a byte of guide data -
the address stores the location of the data-
first it gets DC as we go through the first pass,
and when we finish we add IC to it to get the final address location
the type indicates what type of data we are looking at -a char, a byte, half word or word
and a pointer to the next guide data node*/
typedef struct guide_data_struct
{
	unsigned char data;
	int address;
	data_type_enum type;
	struct guide_data_struct* next_guide_data;
} guide_data_struct;


/*we add a node to the list*/
void addGuideData(char guide_data, data_type_enum data_type, int line,int * DC);

/*we get a list of word of some type and add them word by word to the list using addWordType*/
void AddGuideWordList(char * word_data, data_type_enum data_type,int line, int *DC);

/*we get a single word of some type, check it for its size and add it to the list*/
void addWordType(char* number, data_type_enum data_type, int line, int* DC);

/*after we get a .asciz word, we check that the following data is really a string,
and that it also has quotation marks - and add it */
void addAsciz(char* string, int line, int* DC);

/*when adding guide data, we asign DC to it,
only after we finish reading all the instructions we add IC to it,
so that the data will be added at the end of the file*/
void addICToAllGuideData(int IC);

/*frees all the guide data list memory*/
void freeGuideDataList();

/*return the guide data list head*/
guide_data_struct* getGuideDataHead();


#endif
