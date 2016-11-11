#define _POSIX_C_SOURCE 200112L

#include <string.h>
#include <ctype.h>

char **sort_word_array(char **, char, int);

int a_sort(const void *, const void *);

int l_sort(const void *, const void *);

int n_sort(const void *, const void *);

int s_sort(const void *, const void *);

int scrabble_score(const char s[]);

int scrabble_chart(char c);

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
			qsort(word_array, index, sizeof(*word_array), s_sort);
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

	int first;
	int second;

	char *c = *(const char **)a;
	char *d = *(const char **)b;
	
	if(isdigit(c[0]) == 0 && isdigit(d[0]) == 0){
		return strcmp(c, d);
	}

	char *token, *saveptr1;
	char *subtoken, *saveptr2;
	
	char delim[] = "aAbBcDdDeEfFgGhHiIjJkKlLmMnNoOpPqQrRsStTuUvVwWxXyYzZ";


	if(isdigit(c[0]) && (isdigit(d[0]) == false)){
		return -1;
	} else if ((isdigit(c[0]) == false) && isdigit(d[0])){
		return 1;
	} else if (isdigit(c[0]) && isdigit(d[0])){
		token = strtok_r(c, delim, &saveptr1);
		first = strtol(token, NULL, 10);
		subtoken = strtok_r(d, delim, &saveptr2);
		second = strtol(subtoken, NULL, 10);
		return first - second;
	}
	return 0;
}

int s_sort(const void *a, const void *b)
{
	return scrabble_score(*(const char **)a) - scrabble_score(*(const char **)b);
}

int scrabble_score(const char s[])
{
	int score = 0;	
	size_t end = strlen(s);
	for(size_t i = 0; i < end; ++i){
		score += scrabble_chart(s[i]);	
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



