#include <stdio.h>
#include <string.h>


int main(void){
	char str[] = "je suis thibaut gipteau";
	char *buf = str;
	printf("%s\n", str);
	char *token;

	while ((token = strsep(&buf, " ")) != NULL){
		printf("%s\n", token);
	}
	return 0;
}