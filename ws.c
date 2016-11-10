#define _XOPEN_SOURCE

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>
#include <unistd.h>

int flag_append(char [], char, int);

bool argument_checker(int argc, char *argv[]);

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
			case 'r':
				//Flag for reverse order
				//Test for repeat cases
				flag_str = realloc(flag_str, flag_ind + 2);
				flag_ind = flag_append(flag_str, 'r', flag_ind);
				break;
			case 'n':
				//Flag for sort by numeric value
				flag_str = realloc(flag_str, flag_ind + 2);
				flag_ind = flag_append(flag_str, 'n', flag_ind);
				break;
			case 'l':
				//Flag for sort by length
				flag_str = realloc(flag_str, flag_ind + 2);
				flag_ind = flag_append(flag_str, 'l', flag_ind);
				break;
			case 's':
				//Flag for sort by scrabble score
				flag_str = realloc(flag_str, flag_ind + 2);
				flag_ind = flag_append(flag_str, 's', flag_ind);
				break;
			case 'a':
				//Flag for sorting words lexicographically (The default)
				//Flag is still here despite being default
				//Because user may want to sort with a -a afterwards
				flag_ind = flag_append(flag_str, 'a', flag_ind);
				flag_str = realloc(flag_str, flag_ind + 2);
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
				//TODO: print to stderror
				printf("DEBUG: I don't know how you got here \n");
		}

	}
	
	if(optind == argc) {
		//TODO: Remove debug line
		printf("DEBUG: User did not input files \n");
	}
	printf("DEBUG: print limiter is %d \n", print_limiter);
	
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
