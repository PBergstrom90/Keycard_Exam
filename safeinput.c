#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include "safeinput.h"

// Functions to help with handling user inputs, throughout the program.

bool parseLong(const char *str, long *val)
{
    char *temp;
    bool rc = true;
    errno = 0;
    *val = strtol(str, &temp, 0);

    if (temp == str || *temp != '\0' ||
        ((*val == LONG_MIN || *val == LONG_MAX) && errno == ERANGE))
        rc = false;

    return rc;
}
bool parseFloat(const char *str, float *val)
{
    char *temp;
    bool rc = true;
    errno = 0;
    *val = strtof(str, &temp);

    if (temp == str || *temp != '\0' )
        rc = false;

    return rc;
}


bool GetInputInt(char* prompt, int* value)
{
	char buff[255];
	if (GetInput(prompt, buff, sizeof(buff)) != INPUT_RESULT_OK)
		return false;
	long l = LONG_MIN;
    if(!parseLong(buff,&l)) return false;
	*value = l;
	return true;
}



bool GetInputFloat(char* prompt, float* value)
{
	char buff[255];
	if (GetInput(prompt, buff, sizeof(buff)) != INPUT_RESULT_OK)
		return false;
	float l = -100000000.0f;

    if(!parseFloat(buff,&l)) return false;
	*value = l;
	return true;
}


bool GetInputChar(char* prompt, char* value)
{
	char buff[255];
	if (GetInput(prompt, buff, sizeof(buff)) != INPUT_RESULT_OK)
		return false;
	*value = buff[0];
	return true;
}


INPUT_RESULT GetInput(char* prompt, char* buff, int maxSize)
{

	if (prompt != NULL && strlen(prompt) > 0)
	{
		printf("%s", prompt);
	}
	if (fgets(buff, maxSize, stdin) == NULL || (strlen(buff) == 1 && buff[0] == '\n'))
		return INPUT_RESULT_NO_INPUT; 
    
	// If it was too long, there'll be no newline. In that case, we flush
	// to end of line so that excess doesn't affect the next call.
	if (buff[strlen(buff) - 1] != '\n') {
		int extra = 0;
		char ch;
		while (((ch = getchar()) != '\n') && (ch != EOF))
			extra = 1;
		return (extra == 1) ? INPUT_RESULT_TOO_LONG : INPUT_RESULT_OK;
	}

	// Otherwise remove newline and give string back to caller.
	buff[strlen(buff) - 1] = '\0';
	return INPUT_RESULT_OK;
}

// Testing if the user wants an input to be true or false. Use case: accessGranted.
bool GetBooleanInput(const char* prompt) {
    char input[10]; // Adjusted size for "yes" or "no" input
    while (1) {
        printf("%s", prompt);
        if (fgets(input, sizeof(input), stdin) == NULL) {
            // Handle error or "end of life".
            exit(EXIT_FAILURE);
        }
        // Remove newline character from input
        input[strcspn(input, "\n")] = '\0';
		// Convert the input to lowercase
        for (int i = 0; input[i]; i++) {
            input[i] = tolower(input[i]);
        }
        if (strcmp(input, "yes") == 0) {
            return true;
        } else if (strcmp(input, "no") == 0) {
            return false;
        } else {
            printf("Invalid input. Please enter 'yes' or 'no'.\n");
        }
    }
}