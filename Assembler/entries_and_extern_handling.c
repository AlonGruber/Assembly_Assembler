#include "entries_and_extern_handling.h"


/*head for the entries and externs list */
static entries_and_externs_struct* entries_and_externs_head = NULL;

void addENTandEXT(char* label, int address,int line, data_type_enum data_type, def_or_oc deforoc)
{
    entries_and_externs_struct* new_ext_ent = malloc(sizeof(entries_and_externs_struct));
    new_ext_ent->label = malloc(MAX_LINE_LENGTH);
    strcpy(new_ext_ent->label, label);
    new_ext_ent->deforoc = deforoc;
    new_ext_ent->type = data_type;
    new_ext_ent->address = address;
    new_ext_ent->next_pointer = NULL;
    checkLabelIsNotExternAndEntry(label,data_type,line, deforoc);
    if (!entries_and_externs_head)
        entries_and_externs_head = new_ext_ent;
    else
    {
        entries_and_externs_struct* pointer = entries_and_externs_head;
        while (pointer->next_pointer)
            pointer = pointer->next_pointer;
        pointer->next_pointer = new_ext_ent;
    }
}

void checkLabelIsNotExternAndEntry(char* label, data_type_enum data_type,int line, def_or_oc deforoc)
{
    entries_and_externs_struct* pointer = entries_and_externs_head;
    while (pointer) {
        if ((strcmp(pointer->label, label) == 0) && (pointer->type != data_type) && pointer->deforoc == definition && deforoc == definition)
            addNewError("Same label cannot be defined as extern and entry",NULL,line);
       pointer = pointer->next_pointer;
    }
}

entries_and_externs_struct* findInENTandEXTList(char* label)
{
    entries_and_externs_struct* pointer = entries_and_externs_head;
    while (pointer)
    {
        if (strcmp(pointer->label, label) == 0)
            return pointer;
        pointer = pointer->next_pointer;
    }
    return NULL;
}

entries_and_externs_struct* getENTandEXThead()
{
	return entries_and_externs_head;
}

void freeENTandEXTList()
{
    entries_and_externs_struct* pointer1 = entries_and_externs_head;
    entries_and_externs_struct* pointer2;
    if (!pointer1)
        return;
    while (pointer1)
    {
        pointer2 = pointer1;
        pointer1 = pointer1->next_pointer;
        free(pointer2->label);
        free(pointer2);
    }
    entries_and_externs_head = NULL;
}
