#include <string.h>

char **sort_word_array(char **, char *, int);

char **sort_word_array(char **word_array, char *flag_str, int index)
{
	size_t num_of_sorts = strlen(flag_str);
	//Starting at end of array so the flags are run in reverse order
	for(size_t i = num_of_sorts; i > 0; --i){
		printf("Running %c sort right now\n", flag_str[i-1]);
	}

	return word_array;	
}
