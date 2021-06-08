assembler: main.o files_output.o passes.o error_handling.o symbol_handling.o utils.o guide_data_handling.o  instruction_handling.o entries_and_extern_handling.o
	gcc -g -Wall -ansi -pedantic main.o files_output.o passes.o error_handling.o symbol_handling.o utils.o guide_data_handling.o instruction_handling.o entries_and_extern_handling.o -o assembler

main.o:	main.c
	gcc -g -c -Wall -ansi -pedantic main.c -o main.o

files_output.o: files_output.c
	gcc -g -c -Wall -ansi -pedantic files_output.c -o files_output.o

passes.o: passes.c
	gcc -g -c -Wall -ansi -pedantic passes.c -o passes.o

error_handling.o: error_handling.c
	gcc -g -c -Wall -ansi -pedantic error_handling.c -o error_handling.o

symbol_handling.o: symbol_handling.c
	gcc -g -c -Wall -ansi -pedantic symbol_handling.c -o symbol_handling.o

utils.o: utils.c
	gcc -g -c -Wall -ansi -pedantic utils.c -o utils.o

guide_data_handling.o: guide_data_handling.c
	gcc -g -c -Wall -ansi -pedantic guide_data_handling.c -o guide_data_handling.o

instruction_handling.o: instruction_handling.c
	gcc -g -c -Wall -ansi -pedantic instruction_handling.c -o instruction_handling.o
	
entries_and_extern_handling.o: entries_and_extern_handling.c
	gcc -g -c -Wall -ansi -pedantic entries_and_extern_handling.c -o entries_and_extern_handling.o
