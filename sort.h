#include <string.h>

char **sort_word_array(char **, char *, int);

char **sort_word_array(char **word_array, char *flag_str, int index)
{
	size_t num_of_sorts = strlen(flag_str);

	int c;

	//Starting at end of array so the flags are run in reverse order
	for(size_t i = num_of_sorts; i > 0; --i) {
		c = flag_str[i-1];
		switch(c) {
			default:
				printf("DEBUG: Running the %c argument now! \n", c);
				break;
		}
	}

	return word_array;	
}
