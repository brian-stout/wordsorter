#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	char s[6];
	s[0] = 'h';
	s[1] = 'e';
	s[2] = 'l';
	s[3] = '';
	s[4] = 'o';
	s[5] = '\0';
	printf("%s\n", s);

}

	

