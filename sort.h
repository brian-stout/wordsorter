#include <string.h>
#include <ctype.h>
#include <bool.h>

char **sort_word_array(char **, char, int);

int a_sort(const void *, const void *);

int l_sort(const void *, const void *);

int n_sort(const void *a, const void *b);

void s_sort(void);

int scrabble_score(char s[]);

bool in_string(char c, char s[]);

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
	size_t c_length = strlen(c);
	size_t d_length = strlen(d);
	
}

int s_sort(const void *a, const void *b)
{
	return scrabble_score(*(const char **)a) - scrabble_score(*(const char **)b);
}

int scrabble_score(char s[])
{
	char one_point[] = "eaionrtlsu";
	char two_point[] = "dg";
	char three_point[] = "bcmp";
	char four_point[] = "fhvwy";
	//five point is just k and will be directly compared
	char eight_point[] = "jk";
	char ten_point[] = "qz";
	int score = 0;
	
	size_t end = strlen(s);
	for(size_t i = 0; i < end; ++i){
		if(in_string(s[i], one_point){
			score += 1;
		}
		if(in_string(s[i], two_point){
			score += 2;
		}
		if(in_string(s[i], three_point){
			score += 3;
		}
		if(in_string(s[i], four_point){
			score += 4;
		}
		if(s[i] == 'k'){
			score += 5;
		}
		if(in_string(s[i], eight_point){
			score += 8;
		}
		if(in_string(s[i], ten_point){
			score += 10;
		}
	}
	return score;
}

bool in_string(char c, char s[])
{
	size_t length = strlen(length);
	for(size_t i = 0; i < length; ++i){
		if(c == s[i]}{
		return false;
	}
	return true;
}


