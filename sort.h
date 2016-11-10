#include <string.h>
#include <ctype.h>

char **sort_word_array(char **, char, int);

int a_sort(const void *, const void *);

int l_sort(const void *, const void *);

int n_sort(const void *a, const void *b);

void s_sort(void);

char **sort_word_array(char **word_array, char sort_flag, int index)
{
	//DEBUG: Case statements for the a l n s flags
	//TODO: Set a pointer to a function and qsort that out of switch statement
	switch(sort_flag) {
		case 'a':
			qsort(word_array, index, sizeof(*word_array), a_sort);
			break;
		case 'l':
			qsort(word_array, index, sizeof(*word_array), l_sort);
			break;
		case 'n':
			qsort(word_array, index, sizeof(*word_array), n_sort);
			break;
		case 's':
			s_sort();
			break;
		default:
			break;
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

int n_sort(const void *a, const void *b)
{
	const char *c = *(const char **)a;
	const char *d = *(const char **)b;
	if(isdigit(c[0]) && (isdigit(d[0]) == false)){
		printf("C has a digit, d does not\n");
		return -1;
	} else if ((isdigit(c[0]) == false) && isdigit(d[0])){
		printf("D has a digit, C does not \n");
		return 1;
	} else if (isdigit(c[0]) && isdigit(d[0])){
		printf("C and D are digits\n");
		return 0;
	}
	return 0;
}

void s_sort(void)
{
	printf("Running the s sort function\n");
}



