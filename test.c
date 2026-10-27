#include "hashmap.h"
#include <stdio.h>
#include <stdlib.h>

#define HM_LOAD 40

int main(void){

	hashMap *hm = hm_create();
	printf("Creating hm of capacity %d\n", HM_LOAD);
	hm_init(hm, HM_LOAD);
	printf("Size is : %d\n", (int)(HM_LOAD / 0.75));

	printf("Showing HM\n");
	hm_show(hm);

	printf("Performing random inserts until max load.\n");
	for (int i=0; i<HM_LOAD ; i++){
		int key = rand() % 200;
		int val = key;

		printf("key: %4d, val: %4d ", key, val);
		int hash_idx = hm_insert(hm, key, val);
		printf("-> inserted at idx: %4d\n", hash_idx);
	}

	printf("Showing hm state.\n");
	hm_show(hm);


	return EXIT_SUCCESS;

}
