#include "hashmap.h"
#include <stdio.h>
#include <stdlib.h>


int main(void){

	printf("Creating hm.\n");
	hashMap *hm = hm_init();

	printf("Showing HM\n");
	hm_state(hm);

	printf("Performing random inserts.\n");
	for (int i=0; i<8 ; i++){
		int key = i;
		hm_value val = { .i = rand() % 100};


		int hash_idx = hm_insert(hm, key, val);
		printf("key: %4d, val: %4d ", key, (int)val.i);
		printf("-> h(key): %4d\n", hash_idx);
	}

	printf("Showing hm state.\n");
	hm_state(hm);

	printf("Random readings.\n");
	for (int i=0 ; i<5 ; i++){
		int key = rand() % 20;
		hm_value val;
		int match = hm_read(hm, key, &val);
		if (match)
			printf("Found key %4d, val: %4d.\n", key, (int)val.i);
	}

	printf("Testing delete.\n");
	hm_value addval =  {.i = 200};
	hm_insert(hm, 17, addval); // 17 % 16 = 1 (occupied) -> goes to 9th idx
	hm_state(hm);
	hm_delete(hm, 3);
	hm_delete(hm, 10);
	hm_read(hm, 20, &addval); // can it fetch over deleted slots ?
	printf("Fetched : %d", (int)addval.i);


	return EXIT_SUCCESS;

}
