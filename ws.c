#define _XOPEN_SOURCE

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>
#include <unistd.h>

#include "sort.h"


/** argument_check() uses argv and argv to test for common
*		user input pitfalls.  It also contains the logic
*		for looking for -h and runs the print_help()
*		when it sees it
*/
bool argument_checker(int argc, char *argv[]);


/**	input_read() either uses stdin or a FILE * for the second
*		argument.  It passes in a pointer to an integer so that
*		it can keep appending to the array passed to it with
*		multiple files
*/
char **input_read(char **, FILE *, int *);


/**
*
*
*/
void print_words(char **, int, bool, bool, int);

void print_help(void);

int main(int argc, char *argv[])
{
	if(argument_checker(argc, argv)) {
		return EX_USAGE;
	}

	//Set to -1 so when called to function later it is not zero
	//print_words() does not print word if print_limiter is 0
	int print_limiter = -1;

	//Default sorting flag
	char sort_flag = 'a';

	//Flags for print_words later on
	bool unique_words_only = false;
	bool reverse_print = false;

	int c;
	while(-1 < (c = getopt(argc, argv, "c:ahlnrsu"))) {
		char *err;

		switch(c) {
			case 'c':
				//Grabs the string following c and turns it to a number
				print_limiter = strtol(optarg, &err, 10);
				//if strtol fails it's likely because of this error
				if(*err) {
					printf("Error: -c must be followed by a valid number \n");
					return EX_USAGE;
				}
				//avoids weird negative numbers as user input
				if(print_limiter < 0) {
					printf("Error: -c can not be followed by a negative number \n");
					return EX_USAGE;
				}
				break;
			case 'u':
				//Flag for not printing out duplicates
				unique_words_only = true;
				break;
			case 'r':
				//Flag for printing out results in reverse
				if(!reverse_print) {
					reverse_print = true;
				}
				else {
					reverse_print = false;
				}
				break;
			case '?':
				return EX_USAGE;
			default:
				sort_flag = c;
				break;
		}
	}
	//Initialization for word storage
	int index = 0;
	char **word_array = malloc((1 + index) * sizeof(*word_array));

	//If the user only inputed options then use stdin as the read
	if(optind == argc) {
			word_array = input_read(word_array, stdin, &index);
	}
	//If the user inputed more arguments than options, treat them as file paths
	else {
		for(int i = optind; i < argc; ++i) {
			FILE *fp = fopen(argv[i], "r");
			//If file can not be opened, error out
			if(!fp) {
				printf("Error: Could not open %s!\n", argv[i]);
				return EX_NOINPUT;
			}
			word_array = input_read(word_array, fp, &index);
			fclose(fp);
		}
	}
	//Takes in the word_array and sorts it based on the sort_flag
	word_array = sort_word_array(word_array, sort_flag, index);
	//Handles the logic on what words to print based on the
	//the flags and additional options
	print_words(word_array, index, reverse_print, unique_words_only, print_limiter);
	
}

bool argument_checker(int argc, char *argv[])
{
	bool r = false;
	
	for(int i = 0; i < argc; ++i) {
		if(argv[i][0] == '-') {
			//Checks to see if a tack option is followed by a space
			if(argv[i][1] == ' ' || argv[i][1] == '\0') {
				printf("Usage: [-rnlsauhp] [-c <word limit>] *[files]\n");
				r = true;
			}
			//Checks to see if non option arguments exist before the options
			else if(argv[1][0] != '-') {
				printf("Usage: [-rnlsauhp] [-c <word limit>] *[files]\n");
				r = true;
			}
		}
	}
	//Checks for -h option so it can display the help message
	for(int i = 1; i < argc; ++i) {
		if((strncmp(argv[i], "-h", 2) == 0)) {
			print_help();
			r = true;
		}
	}
	return r;
}

char **input_read(char **word_array, FILE *fp, int *index)
{
	char buf[128];
	char *tmp;
	char *token;

	//If the function was run with FP being stdin
	//give instructions to the user
	if(fp == stdin) {
		printf("Please enter a list of words.\n");
		printf("Entering nothing will sort the files!\n\n");
	}
	
	while(fgets(buf, sizeof(buf), fp)) {
		if(buf[0] == '\n') {
			if(fp == stdin) {
				//If the function using stdin a newline should stop
				//the function o the program can continue to run
				break;
			}
			else {
				//If input is being read from a file
				//the function just skips the loop to avoid
				//the newline crashing the program
				continue;
			}
		}
		token = strtok(buf, " \n\t");
		//Preps the word array for an additional pointer
		word_array = realloc(word_array, (1 + *index) * sizeof(*word_array));
		//Allocates memory to copy the token into
		tmp = malloc(strlen(token) + 1);
		strncpy(tmp, token, strlen(token) + 1);
		//Assigns the pointer to memory to our array index
		word_array[*index] = tmp;
		++*index;
		while(token != NULL) {
			token = strtok(NULL, " \n\t");
			//Since the loop is already running and strtok might return a NULL
			//Checks to seei f there is a null so it doesn't crash on strlen
			if (token != NULL) {
				word_array = realloc(word_array, (1 + *index) * sizeof(*word_array));
				tmp = malloc(strlen(token) + 1);
				strncpy(tmp, token, strlen(token) + 1);
				word_array[*index] = tmp;
				++*index;
			}
			else {
				break;
			}
		}
	}
	return word_array;	
}

void print_words(char **word_array, int index, bool reverse_print, bool unique, int print_limiter)
{	
	char prev_word[64];
	prev_word[0] = '\0';

	if(!reverse_print) {
		for(int i = 0; i < index; ++i) {
			//By default print_limiter is set to -1
			//If user implemented a number it will decrement till it hits zero
			if(print_limiter != 0) {
				//If the unique flag isn't set the program will print normally
				if(!unique) {
					printf("%s\n", word_array[i]);
					--print_limiter;
				}
				//Checks to see if the previous word printed is next in the array
				//If it is, it doesn't get printed
				else if(strncmp(word_array[i], prev_word, strlen(word_array[i]) + 1) != 0) {
					strncpy(prev_word, word_array[i], sizeof(prev_word));
					printf("%s\n", word_array[i]);
					--print_limiter;
				}
			}
			//Set outside all the logic so the loop always frees the memory
			free(word_array[i]);
		}
	}
	else {
		//Sets i to the top of the increment and decrements to go in reverse order
		//index - 1 because index is what you print up to
		//word_array[index] is out of range
		for(int i = index-1; i >= 0; --i) {
			if(print_limiter != 0) {
				if(!unique){
					printf("%s\n", word_array[i]);
					--print_limiter;
				}
				else if(strncmp(word_array[i], prev_word, strlen(word_array[i]) + 1) != 0) {
					strncpy(prev_word, word_array[i], sizeof(prev_word));
					printf("%s\n", word_array[i]);
					--print_limiter;
				}
			}
			free(word_array[i]);
		}
	}
	//After the function is done with the word_array it frees up all the memory
	//allocated in the array for pointers
	free(word_array);
}

void print_help(void)
{
			printf("\nUsage: [-rnlsauhp] [-c <word limit>] *[files]\n\n");
			printf("<<Explanation of options>>\n");
			printf("[Sorting methods]\n");
			printf("-a: sorts words alphabetically\n");
			printf("-l: sorts words by their length\n");
			printf("-n: sorts words by leading numbers\n");
			printf("-s: sorts words by their scrabble score\n");
			printf("[Additional options]\n");
			printf("-u: Prevents duplicate entries from being shows\n");
			printf("-c: Will only print out <number> of lines\n");
			printf("-h: Prints out help message\n");
			printf("\n\n");
}

