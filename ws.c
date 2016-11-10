#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int print_limiter = -1;
	
	char flag_str[8];
	int flag_str_ind = 0;

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
			case 's':
			case 'a':
			case 'u':
			case 'h':
			case 'p':
				//florish
		}
	}
		
}
