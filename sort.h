#include <string.h>

char **sort_word_array(char **, char *, int);

int a_sort(const void *, const void *);

void l_sort(void);

void n_sort(void);

void r_sort(void);

void s_sort(void);

char **sort_word_array(char **word_array, char *flag_str, int index)
{
	size_t num_of_sorts = strlen(flag_str);

	int c;

	//Starting at end of array so the flags are run in reverse order
	for(size_t i = num_of_sorts; i > 0; --i) {
		c = flag_str[i-1];
		//DEBUG: Case statements for the a l n r s flags
		switch(c) {
			case 'a':
				qsort(word_array, index, sizeof(*word_array), a_sort);
				break;
			case 'l':
				l_sort();
				break;
			case 'n':
				n_sort();
				break;
			case 'r':
				r_sort();
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
void l_sort(void)
{
	printf("Running the l sort function\n");
}

void n_sort(void)
{
	printf("Running the n sort function\n");
}

void r_sort(void)
{
	printf("Running the r sort function\n");
}

void s_sort(void)
{
	printf("Running the s sort function\n");
}



