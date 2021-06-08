/*MMN14 Project -
By - Alon Gruber
ID - 312528615
Information for all of the different sections and functions is mainley in the header files
some big functions also have comments within them -such as the first pass and the final file creation*/

#define IC_START 100

#include "utils.h"
#include "passes.h"
#include "error_handling.h"
#include "files_output.h"

int main(int argc, char* argv[])
{
    FILE* inputfile = NULL;
    int i;

    printf("Assembler running\n");
    if (argc == 1)
        printf("No files in input.\n");
    else
    {   
        /*we go over each of the files provided in input */
        for (i = 1; i < argc; i++)
        {
            int IC = IC_START;
            int DC = 0;
            printf("Generating files for %s: ", argv[i]);
            if ((inputfile = fopen(argv[i], "r")) && checkFileIsAssemblerAndRemoveExtension(argv[i]))
            {
                /*run the first pass*/
                firstPass(inputfile, &IC, &DC);
                /*if no errors, update guide data and symbols,needed
                for second pass*/
                if (!foundErrors())
                {
                    addICToAllGuideDataSymbols(IC);
                    addICToAllGuideData(IC);
                }
                /*run second pass*/
                secondPass(IC);
                /*if no errors write files to outpus*/
                if (!foundErrors())
                {
                    writeAllFiles(IC, DC, argv[i]);
                }
                /*if error found, print them all*/
                else
                {
                    printf("Errors found! cannot complete operation\n");
                    printErrorList();
                    deleteErrorList();
                }
                /*free all mallocs*/
                freeENTandEXTList();
                freeGuideDataList();
                deleteSymbolList();
                freeInstructionList();
            }
            else
                printf("Problem opening file - %s", argv[i]);
        }

    }
    return 0;
}
