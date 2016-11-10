#include <string.h>

char **sort_word_array(char **, char *, int);

int a_sort(const void *, const void *);

int l_sort(const void *, const void *);

void n_sort(void);

void s_sort(void);

char **sort_word_array(char **word_array, char *flag_str, int index)
{
	size_t num_of_sorts = strlen(flag_str);

	int c;

	//Starting at end of array so the flags are run in reverse order
		c = flag_str[i-1];
		//DEBUG: Case statements for the a l n s flags
		switch(c) {
			case 'a':
				qsort(word_array, index, sizeof(*word_array), a_sort);
				break;
			case 'l':
				qsort(word_array, index, sizeof(*word_array), l_sort);
				break;
			case 'n':
				n_sort();
				break;
			case 's':
				s_sort();
				break;
			default:
				printf("DEBUG: Running the %c argument now! \n", c);
				break;
		}
	}

	return word_array;	
}
//Alphabetically
int a_sort(const void *a, const void *b)
{
	return strcmp(*(const char **)a, *(const char **)b);
}
//Length
int l_sort(const void *a, const void *b)
{
	return strlen(*(const char **)a) - strlen(*(const char **)b);
}

void n_sort(void)
{
	printf("Running the n sort function\n");
}

void s_sort(void)
{
	printf("Running the s sort function\n");
}



