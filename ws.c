#define _XOPEN_SOURCE

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>
#include <unistd.h>

int flag_append(char [], char, int);

bool argument_checker(int argc, char *argv[]);

char **file_read(char **, FILE *, int *);

char **sort_word_array(char **, char *, int);

int main(int argc, char *argv[])
{
	if(argument_checker(argc, argv)) {
		return EX_USAGE;
	}

	int print_limiter = -1;
	
	//The flag_ind will always be the last value in the str which should be a null byte
	//It's initially set to 0 so the default value gets overwritten
	int flag_ind = 0;

	//Memory for two characters, the default value and a null byte
	char *flag_str = malloc(2);
	flag_str[0] = 'a';
	flag_str[1] = '\0';

	bool unique_words_only = false;
	bool non_alphanum_strip = false;

	int c;

	while(-1 < (c = getopt(argc, argv, "c:rnlsauhp"))) {
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
			case '?':
				return EX_USAGE;
			default:
				flag_ind = flag_append(flag_str, c, flag_ind);
				flag_str = realloc(flag_str, flag_ind + 2);
				break;
		}

	}
	//Initialization for word storage
	int index = 0;
	char **word_array = malloc((1 + index) * sizeof(*word_array));

	if(optind == argc) {
		//TODO: Remove debug line
		printf("DEBUG: User did not input files \n");
	} else {
		for(int i = optind; i < argc; ++i) {
			printf("DEBUG: File to be opened: %s \n", argv[i]);
			FILE *fp = fopen(argv[i], "r");
			word_array = file_read(word_array, fp, &index);
			fclose(fp);
		}
		printf("Now running sort_word_array function\n");
		word_array = sort_word_array(word_array, flag_str, index);
		for(int i = 0; i < index; ++i){
			free(word_array[i]);
		}
		free(word_array);
	}
	printf("DEBUG: print limiter is %d \n", print_limiter);
	printf("%s \n", flag_str);
	
	//TODO: Put in more relevant location
	free(flag_str);
}

int flag_append(char str[], char flag, int ind)
{
	str[ind] = flag;
	++ind;
	str[ind] = '\0';
	return ind;
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

	while(fgets(buf, sizeof(buf), fp)) {
		token = strtok(buf, " \n\t");
		word_array = realloc(word_array, (1 + *index) * sizeof(*word_array));
		tmp = malloc(strlen(token) + 1);
		strncpy(tmp, token, strlen(token) + 1);
		word_array[*index] = tmp;
		++*index;
		while(token != NULL){
			token = strtok(NULL, " \n\t");
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

char **sort_word_array(char **word_array, char *flag_str, int index)
{
	printf("%d\n", index);
	printf("%s\n", flag_str);
	for(int i = 0; i < index; ++i){
		printf("%s\n", word_array[i]);
	}

	return word_array;	
}
