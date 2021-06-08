#include "passes.h"

static char* OPCODE_STRINGS[OPCODE_COUNT] = { "add" ,"sub","and","or","nor","move","mvhi","mvlo","addi","subi","andi" ,"ori" ,"nori" ,"bne" ,"beq" ,"blt" ,"bgt","lb","sb","lw","sw","lh","sh","jmp","la","call","stop" };

bool checkIfStringIsReservedWord(char* input)
{
    if (strcmp(input, RESERVED_ENTRY_STRING) == 0)
        return true;
    if (strcmp(input, RESERVED_EXTERN_STRING) == 0)
        return true;
    if (strcmp(input, RESERVED_ASCIZ_STRING) == 0)
        return true;
    if (strcmp(input, RESERVED_DB_STRING) == 0)
        return true;
    if (strcmp(input, RESERVED_DH_STRING) == 0)
        return true;
    if (strcmp(input, RESERVED_DW_STRING) == 0)
        return true;
    return false;
}

bool checkIfStringIsComment(char* input_word)
{
    return(*input_word == ';');
}


bool checkIfStringIsOpcode(char* input_word)
{
    int i;
    for (i = 0; i < OPCODE_COUNT; i++)
    {
        if (strcmp(input_word, OPCODE_STRINGS[i]) == 0)
            return true;
    }
    return false;
}


int whichGuideWord(char* input_word) {

    if (strcmp(input_word, GUIDE_ENTRY_STRING) == 0)
        return data_type_enum_entry;
    else if (strcmp(input_word, GUIDE_EXTERN_STRING) == 0)
        return data_type_enum_extern;
    else if (strcmp(input_word, GUIDE_ASCIZ_STRING) == 0)
        return data_type_enum_asciz;
    else if (strcmp(input_word, GUIDE_DB_STRING) == 0)
        return data_type_enum_db;
    else if (strcmp(input_word, GUIDE_DH_STRING) == 0)
        return data_type_enum_dh;
    else if (strcmp(input_word, GUIDE_DW_STRING) == 0)
        return data_type_enum_dw;
    else
        return -1;
}





void firstPass(FILE* file_pointer, int* IC_PTR, int* DC_PTR)
{
    char line[MAX_LINE_LENGTH];
    int line_count = 0;
    /*each time we get a line from the input file*/
    while (fgets(line, MAX_LINE_LENGTH, file_pointer))
    {
        char* each_word_in_line = NULL;
        char* label=NULL;
        each_word_in_line = strtok(line, "\n\t ");
        line_count++;
        /*if we got an empty line - which is allowed - continue to next line*/
        if (*line == '\n')
            continue;
        /*if the line is a comment line - continue to next one */
        if (checkIfStringIsComment(each_word_in_line))
            continue;
        /*if we found a valid label, we assign the pointer to it, and add a null terminator
        we also advance using strtok to the next word*/
        if (checkIfLabelStringIsValidInStart(each_word_in_line))
        {
            label = each_word_in_line;
            label[strlen(label) - 1] = '\0';
            ifCondAddError((checkIfStringIsOpcode(label) || checkIfStringIsRegister(label) || checkIfStringIsReservedWord(label)), "Label cannot be operation or register or reserved word", label, line_count);
            if(!(each_word_in_line = strtok(NULL, "\n\t ")))
                addNewError("Label cannot be empty", NULL, line_count);
        }
        /*we check if the current word is a guide word,
        we also check if we found a label on each of these guide words, 
        and if we have one we add it*/
        if (checkIfStringIsGuideData(each_word_in_line))
        {
            /*if it is, we check which kind of the guide words it is*/
            switch (whichGuideWord(each_word_in_line))
            {
            case(-1):
            {
                addNewError("Problem with guide word", each_word_in_line,line_count);
                continue;
            } 
            /*if its a asciz sting we add it to the guide data list*/
            case(data_type_enum_asciz):
            {
                each_word_in_line = strtok(NULL, " \t\r\n");
                if((!each_word_in_line))
                addNewError("No asciz data ", NULL, line_count);
                if (label)
                    addSymbolToList(label, *DC_PTR , guide_data, line_count);
                addAsciz(each_word_in_line, line_count, DC_PTR);
                continue;
            }
            /*if its a entry guide word we add it to the entry and externals list*/
            case(data_type_enum_entry):
            {
                if(label)
                    printf("Warning @ Line %d: label %s before entry is ignored ", line_count, label);
                if (!(each_word_in_line = strtok(NULL, " \t\r\n"))) {
                    addNewError("Entry must be followed by a label", NULL, line_count);
                      continue;
                }
                addENTandEXT(each_word_in_line,*IC_PTR, line_count, data_type_enum_entry,definition);
                if ((each_word_in_line = strtok(NULL, "\n")))
                    addNewError("Entry must be followed only by a label", each_word_in_line, line_count);
                continue;
            }
            /*if its a extern guide word we add it to the entry and externals list*/
            case(data_type_enum_extern):
            {
                if (label)
                    printf("Warning @ Line %d: label %s before extern is ignored\n", line_count,label);
                if (!(each_word_in_line = strtok(NULL, " \t\r\n"))) {
                    addNewError("Extern directive must have a label parameter", NULL, line_count);
                    continue;
                }
                addENTandEXT(each_word_in_line, *IC_PTR,line_count, data_type_enum_extern,definition);
                if ((each_word_in_line = strtok(NULL, "\n"))) {
                    addNewError("Extern directive can only take one parameter", NULL, line_count);
                }
                continue;
            }
            /*if its a byte guide word then we know a list is ahead, so we add it to the guide word list */
            case(data_type_enum_db):
            {
                if (label)
                    addSymbolToList(label, *DC_PTR, guide_data, line_count);
                AddGuideWordList(each_word_in_line, data_type_enum_db, line_count, DC_PTR);
                continue;
            }
            /*if its a half word guide word then we know a list is ahead, so we add it to the guide word list */
            case(data_type_enum_dh):
            {
                if (label)
                    addSymbolToList(label, *DC_PTR, guide_data, line_count);
                AddGuideWordList(each_word_in_line, data_type_enum_dh, line_count, DC_PTR);
                continue;
            }
            /*if its a word guide word then we know a list is ahead, so we add it to the guide word list */
            case(data_type_enum_dw):
            {
                if (label)
                    addSymbolToList(label, *DC_PTR, guide_data, line_count);
                AddGuideWordList(each_word_in_line, data_type_enum_dw,line_count, DC_PTR);
                continue;
            }
            }
        }
        else {
            /*if its not a guide word then we have a command ahead, if we have a label add it*/
            if (label)
                addSymbolToList(label,*IC_PTR, code, line_count);
            /*process the instruction*/
            processInstruction(each_word_in_line, line_count, IC_PTR);
        }
    }
    if (line_count == 0)
        addNewError("No data in input file!", NULL,0);
}

void secondPass(int IC)
{
    instruction_struct* instruction = NULL;
    entries_and_externs_struct* ent_and_ext = NULL;
    symbol_struct* symbol = NULL;
    /*now that we have completed the first pass,
    we can go over all the instructions that have no label and add the data accordingly*/
    while ((instruction = findInstructionWithoutLabelData()))
    {
        /*we search for the missing label in the symbol table and entries and externals table*/
        ent_and_ext = findInENTandEXTList(instruction->instruction_label);
        symbol = findSymbolInList(instruction->instruction_label);
        /*if we have not found it in either list, add error*/
        if (!symbol && !ent_and_ext)
            addNewError("Label in instruction not defined,label -", instruction->instruction_label, instruction->instruction_line);
        /*if we found it in the symbol list*/
        if(symbol)
        {
            /*if its a J instruction assign the address*/
        if (instruction->which_instruction == J)
            instruction->instructions.J_instruction.address =  symbol->symbol_address;
        if (instruction->which_instruction == I) {
            /*if its one of the branch instructions add the IC distance between them*/
            if (instruction->instructions.I_instruction.opcode == beq_opcode_enum || instruction->instructions.I_instruction.opcode == bne_opcode_enum || instruction->instructions.I_instruction.opcode == blt_opcode_enum || instruction->instructions.I_instruction.opcode == bgt_opcode_enum)
                instruction->instructions.I_instruction.immediate = symbol->symbol_address - instruction->instruction_address;
            else
                /*if its one of the other I instructions add the address*/
                instruction->instructions.I_instruction.immediate = symbol->symbol_address;
        }
        }
        /*if its one of the entries or externals add it to the list*/
        if (ent_and_ext) 
            addENTandEXT(instruction->instruction_label, instruction->instruction_address, instruction->instruction_line, ent_and_ext->type, occurance);
        /*we finished handling the label, remove the label so that we wont address it again*/
        free(instruction->instruction_label);
        instruction->instruction_label = NULL;
    }
}
