#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{

	FILE *fp1 = fopen(argv[1], "r");

	char *token;
	char buf[128];
	//char word_array[128][32];
	int index = 0;
	char *tmp;
	char **word_array = malloc((1 + index) * sizeof(*word_array));
	// print lines from the file
	// FILE *stdin
	while(fgets(buf, sizeof(buf), fp1)) {
		token = strtok(buf, " \n\t");
		word_array = realloc(word_array, (1 + index) * sizeof(*word_array));
		tmp = malloc(strlen(token) + 1);
		strncpy(tmp, token, strlen(token) + 1);
		word_array[index] = tmp;
		++index;
		while(token != NULL){
			token = strtok(NULL, " \n\t");
			if (token != NULL){
				word_array = realloc(word_array, (1 + index) * sizeof(*word_array));
				tmp = malloc(strlen(token) + 1);
				strncpy(tmp, token, strlen(token) + 1);
				word_array[index] = tmp;
				++index;
			}
			else {
				break;
			}
		}
	}
	for(int i = 0; i < index; ++i){
		printf("%s\n", word_array[i]);
		free(word_array[i]);
	}
	fclose(fp1);
	free(word_array);
}

