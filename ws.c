#define _XOPEN_SOURCE

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>
#include <unistd.h>

size_t flag_append(char [], char, size_t);

int main(int argc, char *argv[])
{
	int print_limiter = -1;
	
	//The flag_ind will always be the last value in the str which should be a null byte
	//It's initially set to 0 so the default value gets overwritten
	size_t flag_ind = 0;

	//Memory for two characters, the default value and a null byte
	char *flag_str = malloc(2);
	flag_str[0] = 'a';
	flag_str[1] = '\0';

	bool unique_words_only = false;
	bool non_alphanum_strip = false;

	int c;

	for(int i = 1; i < argc; ++i) {
		if((strncmp(argv[i], "-h", 2) == 0)) {
			//TODO: write an actual help message, put it in a function to save space
			printf("The help message goes here!\n");
			return 1;
		}
	}
	while(-1 < (c = getopt(argc, argv, "c:rnlsauhp"))) {
		char *err;
		printf("%c ", c);
		printf("\n");

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
				flag_ind = flag_append(flag_str, 'r', flag_ind);
				break;
			case 'n':
				//Flag for sort by numeric value
				flag_ind = flag_append(flag_str, 'n', flag_ind);
				break;
			case 'l':
				//Flag for sort by length
				flag_ind = flag_append(flag_str, 'l', flag_ind);
				break;
			case 's':
				//Flag for sort by scrabble score
				flag_ind = flag_append(flag_str, 's', flag_ind);
				break;
			case 'a':
				//Flag for sorting words lexicographically (The default)
				//Flag is still here despite being default
				//Because user may want to sort with a -a afterwards
				flag_ind = flag_append(flag_str, 'a', flag_ind);
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
	printf("DEBUG: print limiter is %d \n", print_limiter);
	printf("DEBUG: The flag string is now %s \n", flag_str);
	printf("DEBUG: The strlen of flag_str is %zd \n", strlen(flag_str));
	
	//TODO: Put in more relevant location
	free(flag_str);
}

size_t flag_append(char str[], char flag, size_t ind)
{
	str[ind] = flag;
	//The length of the string plus one for the null byte
	str = realloc(str, (strlen(str) + 1));

	//Error handles if realloc fails
	if(!str) {
		return -1;
	}
	else {
		++ind;
		str[ind] = '\0';
		return ind;
	}
}
