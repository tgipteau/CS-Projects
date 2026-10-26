#include "hashmap.h"
#include <stdio.h>
#include <stdlib.h>


int main(void){

	hashMap *hm = hm_create();
	hm_init(hm, 10);

	while(1){

		hm_show(hm);
		char cmd;
		int val;
		scanf("%c %d", &cmd, &val);
		printf("\e[1;1H\e[2J");
		printf("cmd : %c\n", cmd);
		printf("val : %d\n", val);


		switch (cmd) {
			case 'i':
				printf("inserting %d\n", val);
				hm_insert(hm, val);
				break;
			default:
				printf("invalid cmd.\n");
		}
	}


	return EXIT_SUCCESS;

}
