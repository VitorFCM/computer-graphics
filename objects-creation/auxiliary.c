#include <stdlib.h>
#include <stdio.h>

void readline(char* string, int max){
	char c = 0;

	do{
		c = (char) getchar();

	} while(c == '\n' || c == '\r');

	int i = 0;
	do{
		string[i] = c;
		i++;
		c = getchar();
	} while(c != '\n' && c != '\r' && i < max - 1);

	string[i]  = '\0';
}
