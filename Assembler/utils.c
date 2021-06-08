#include "utils.h"

bool checkIfLabelStringIsValidInInstruction(char* input_word)
{
	while (*input_word) {
		if (!isdigit(*input_word) && !isalpha((*input_word)))
			return false;
		input_word++;
	}
	return true;
}

bool checkIfLabelStringIsValidInStart(char* input_word) {
	int count = 0;
	int check = strlen(input_word)-1;
	if (input_word[strlen(input_word) - 1] == ':') {
		if (!isalpha(*input_word))
			return false;
		while ((*input_word)) {
			if ((*input_word) == ':' && count == check)
				return true;
			if (!isalpha((*input_word)) || isdigit((*input_word)))
				return false;
			count++;
			input_word++;
		}
	}
	return false;
}

bool checkIfImmediateInRange(char* input_word) {
	int num;
	num = strtol(input_word, NULL, 10);
	return ((num > INT16_MIN) && (num < INT16_MAX));
}

bool checkIfStringIsRegister(char* input_word)
{
	if (strlen(input_word) == 2) {
		if (input_word[0] == '$' && isdigit(input_word[1]))
			return true;
	}
	if (strlen(input_word) == 3) {
		if (input_word[0] == '$' && isdigit(input_word[1]) && isdigit(input_word[2]))
			return true;
	}
		return false;
}


bool checkIfStringIsImmediateNumber(char* input_word)
{
	if (isdigit(*input_word) || (*input_word) == '+' || (*input_word) == '-') {
		input_word++;
		while (*input_word) {
			if (!isdigit(*input_word))
				return false;
			input_word++;
		}
		return true;
	}
	else
		return false;
}



bool checkIfStringIsGuideData(char* input_word)
{
	return(*input_word == '.');
}



