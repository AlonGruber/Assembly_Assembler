#include "symbol_handling.h"


/*struct that points to the head of the symbol struct*/
static symbol_struct* symbol_head = NULL;


void addSymbolToList(char* symbol_label, int symbol_address,attribute att, int symbol_line)
{
    symbol_struct* new_symbol = malloc(sizeof(symbol_struct));
    new_symbol->symbol_label = malloc(MAX_LINE_LENGTH);
    strcpy(new_symbol->symbol_label, symbol_label);
    new_symbol->symbol_address = symbol_address;
    new_symbol->symbol_attribute = att;
    new_symbol->next_symbol = NULL;
    addErrorIfSymbolExists(new_symbol, symbol_line);
    if (!symbol_head)
        symbol_head = new_symbol;
    else
    {
        symbol_struct* symbol_pointer = symbol_head;
        while (symbol_pointer->next_symbol)
            symbol_pointer = symbol_pointer->next_symbol;
        symbol_pointer->next_symbol = new_symbol;
    }
}


void addErrorIfSymbolExists(symbol_struct* symbol_check, int symbol_line)
{
    symbol_struct* symbol_pointer = symbol_head;
    while (symbol_pointer)
    {
        ifCondAddError((strcmp(symbol_pointer->symbol_label, symbol_check->symbol_label) == 0), "Multiple symbols with label", symbol_check->symbol_label, symbol_line);
        symbol_pointer = symbol_pointer->next_symbol;
    }
}

symbol_struct* findSymbolInList(char* symbol_label)
{
    symbol_struct* symbol_pointer = symbol_head;
    while (symbol_pointer)
    {
        if (strcmp(symbol_pointer->symbol_label, symbol_label)==0)
            return symbol_pointer;
        symbol_pointer = symbol_pointer->next_symbol;
    }
    return NULL;
}


void addICToAllGuideDataSymbols(int IC)
{
    symbol_struct* symbol_pointer = symbol_head;
    while (symbol_pointer)
    {
        if (symbol_pointer->symbol_attribute == guide_data)
        {
            symbol_pointer->symbol_address += IC;
        }
        symbol_pointer = symbol_pointer->next_symbol;
    }
}

void deleteSymbolList()
{
    symbol_struct* symbol_pointer1 = symbol_head;
    if (!symbol_pointer1)
        return;
    while (symbol_pointer1)
    {
        symbol_struct* symbol_pointer2 = symbol_pointer1;
        symbol_pointer1 = symbol_pointer1->next_symbol;
        free(symbol_pointer2->symbol_label);
        free(symbol_pointer2);
    }
    symbol_head = NULL;
}

symbol_struct* getSymbolHead()
{
    return symbol_head;
}
