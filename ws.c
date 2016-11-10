#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int print_limiter = -1;
	
	char sort_flag_str[8];
	int sort_flag_str_ind = 0;
	bool unique_words_only = false;
	bool non_alphanum_strip = false;

	int c;
	while(-1 < (c = getopt(argc,argv, "c:rnlsauhp"))) {
		char *err;
		switch(c) {
			case 'c':
				//strtol value to print_limiter
			case 'r':
				//Flag for reverse order
				//Test for repeat cases
			case 'n':
				//Flag for sort by numeric value
			case 'l':
				//Flag for sort by length
			case 's':
				//Flag for sort by scrabble score
			case 'a':
				//Flag for sorting words lexicographically (The default)
				//Flag is still here despite being default
				//Because user may want to sort with a -a afterwards
			case 'u':
				//Flag for not printing out duplicates
				//Probably going to be a flag affecting print so needs it's own flag
			case 'h':
				//Prints out help options
			case 'p':
				//florish
				//Flag for striping out non-alphanumeric characters from end of words
		}
	}
		
}
