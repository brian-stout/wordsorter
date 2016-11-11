#define _XOPEN_SOURCE

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>
#include <unistd.h>

#include "sort.h"

bool argument_checker(int argc, char *argv[]);

char **file_read(char **, FILE *, int *);

void print_words(char **, int, bool, bool);

int main(int argc, char *argv[])
{
	if(argument_checker(argc, argv)) {
		return EX_USAGE;
	}

	int print_limiter = -1;

	char sort_flag = 'a';

	bool unique_words_only = false;
	bool non_alphanum_strip = false;
	bool reverse_print = false;

	int c;

	while(-1 < (c = getopt(argc, argv, "c:ahlnprsu"))) {
		char *err;

		switch(c) {
			case 'c':
				//strtol value to print_limiter
				print_limiter = strtol(optarg, &err, 10);
				if(*err) {
					//TODO: print to stderror
					printf("Error: -c must be followed by a valid number \n");
					return EX_USAGE;
				}
				break;
			case 'u':
				//Flag for not printing out duplicates
				//Probably going to be a flag affecting print so needs it's own flag
				unique_words_only = true;
				break;
			case 'p':
				//Flag for striping out non-alphanumeric characters from end of words
				non_alphanum_strip = true;
				break;
			case 'r':
				//Flag for printing out results in reverse
				if(!reverse_print) {
					reverse_print = true;
				} else {
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

	if(optind == argc) {
			word_array = file_read(word_array, stdin, &index);
	} else {
		for(int i = optind; i < argc; ++i) {
			FILE *fp = fopen(argv[i], "r");
			word_array = file_read(word_array, fp, &index);
			fclose(fp);
		}
	}
	word_array = sort_word_array(word_array, sort_flag, index);
	print_words(word_array, index, reverse_print, unique_words_only);
	
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
			//TODO: write an actual help message, put it in a function to save space
			printf("Help message goes here!\n");
			r = true;
		}
	}
	return r;
}

char **file_read(char **word_array, FILE *fp, int *index)
{
	char buf[128];
	char *tmp;
	char *token;

	if(fp == stdin){
		printf("Please enter a list of words.\n");
		printf("Entering nothing will sort the files!\n\n");
	}
	
	while(fgets(buf, sizeof(buf), fp)) {
		//Skips new lines to avoid crashes
		if(buf[0] == '\n'){
			if(fp == stdin){
				break;
			} else {
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
		while(token != NULL){
			token = strtok(NULL, " \n\t");
			//Since the loop is already running and strtok might return a NULL
			//Checks to seei f there is a null so it doesn't crash on strlen
			if (token != NULL){
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
//TODO: Implement bit masks for flags
void print_words(char **word_array, int index, bool reverse_print, bool unique)
{	
	char prev_word[64];
	prev_word[0] = '\0';

	if(!reverse_print) {
		for(int i = 0; i < index; ++i){
			if(!unique){
				printf("%s\n", word_array[i]);
			}
			else if(strncmp(word_array[i], prev_word, strlen(word_array[i]) + 1) != 0){
				strncpy(prev_word, word_array[i], sizeof(prev_word));
				printf("%s\n", word_array[i]);	
			}
			free(word_array[i]);
		}
	} else {
		for(int i = index; i > 0; --i){
			if(!unique){
				printf("%s\n", word_array[i]);
			} 
			else if(strncmp(word_array[i], prev_word, strlen(word_array[i]) + 1) != 0){
				strncpy(prev_word, word_array[i], sizeof(prev_word));
				printf("%s\n", word_array[i]);	
			}
			free(word_array[i]);
		}
	}
	
	free(word_array);
}
