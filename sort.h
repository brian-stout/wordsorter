#define _POSIX_C_SOURCE 200112L

#include <string.h>
#include <ctype.h>

/**	sort_word_array() handles the qsort logic based on the
*		sort_flag passed into it. Additional sorts can
*		easily be added.
*/
char **sort_word_array(char **, char, int);


/**	a_sort() using a basic strcmp to sort files alphabetically
*		a_sort() is also the default sort
*/
int a_sort(const void *, const void *);


/**	l_sort() handles the logic to sort by length of word
*		it sorts by a_sort first to keep things tidy.
*/
int l_sort(const void *, const void *);

int n_sort(const void *, const void *);

int s_sort(const void *, const void *);

int scrabble_score(const char s[]);

int scrabble_chart(char c);

char **sort_word_array(char **word_array, char sort_flag, int index)
{
	//TODO: set a pointer to the function and run q sort with that pointer
	switch(sort_flag) {
		case 'a':
			qsort(word_array, index, sizeof(*word_array), a_sort);
			break;
		case 'l':
			qsort(word_array, index, sizeof(*word_array), a_sort);
			qsort(word_array, index, sizeof(*word_array), l_sort);
			break;
		case 'n':
			qsort(word_array, index, sizeof(*word_array), n_sort);
			break;
		case 's':
			qsort(word_array, index, sizeof(*word_array), s_sort);
			break;
		default:
			break;
		}
	return word_array;	
}

int a_sort(const void *a, const void *b)
{
	return strcmp(*(const char **)a, *(const char **)b);
}

int l_sort(const void *a, const void *b)
{
	return strlen(*(const char **)a) - strlen(*(const char **)b);
}

int n_sort(const void *a, const void *b)
{

	char const *c = *(const char **)a;
	char const *d = *(const char **)b;

	char str1[64];
	char str2[64];

	//If the first word starts with a digit and the second one doesn't
	//it takes precedence in sort
	if(isdigit(c[0]) && (isdigit(d[0]) == false)) {
		return -1;
	//If the reverse is true the second word takes precedence
	}
	else if ((isdigit(c[0]) == false) && isdigit(d[0])) {
		return 1;
	//If both words start with digits, take the actual value of the numbers
	}
	else if (isdigit(c[0]) && isdigit(d[0])) {
		strncpy(str1, c, strlen(c)+1);
		strncpy(str2, d, strlen(c)+1);
		int first = strtol(c, NULL, 10);
		int second = strtol(d, NULL, 10);
		return first - second;
	}
	//If neither words start with digits, compare normally
	else {
		return strcmp(c, d);
	}
}

int s_sort(const void *a, const void *b)
{
	return scrabble_score(*(const char **)a) - scrabble_score(*(const char **)b);
}

int scrabble_score(const char s[])
{
	int score = 0;	
	size_t end = strlen(s);
	//For each character in the string, find the value of that character
	for(size_t i = 0; i < end; ++i) {
		if(!isdigit(s[i])){
			score += scrabble_chart(s[i]);
		}	
	}
	return score;
}

int scrabble_chart(char c)
{
	int score;
	c = tolower(c);
	switch(c) {
		case 'e':
		case 'a':
		case 'i':
		case 'o':
		case 'n':
		case 'r':
		case 't':
		case 'l':
		case 's':
		case 'u':
			score = 1;
			break;
		case 'd':
		case 'g':
			score = 2;
			break;
		case 'b':
		case 'c':
		case 'm':
		case 'p':
			score = 3;
			break;
		case 'f':
		case 'h':
		case 'v':
		case 'w':
		case 'y':
			score = 4;
			break;
		case 'k':
			score = 5;
			break;
		case 'j':
		case 'x':
			score = 8;
			break;
		case 'q':
		case 'z':
			score = 10;
			break;
		default:
			score = 0;
			break;
	}
	return score;
}



