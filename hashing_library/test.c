#include "hashmap.h"
#include <stdio.h>
#include <stdlib.h>


int main(void){

	printf("Creating hm.\n");
	hashMap *hm = hm_init();

	printf("\n");
	hm_state(hm);

	printf("\nPerforming inserts.\n");
	for (int i=0; i<6 ; i++){
		int key = i*2+1;
		hm_value val = {.i = key};


		int hash_idx = hm_upsert(hm, key, val);
		printf("key: %4d, val: %4d ", key, (int)val.i);
		printf("-> h(key): %4d\n", hash_idx);
	}

	printf("\nRandom readings.\n");
	for (int i=0 ; i<5 ; i++){
		int key = rand() % 20;
		hm_value val;
		int match = hm_read(hm, key, &val);
		if (match)
			printf("Found key %4d, val: %4d.\n", key, (int)val.i);
	}

	printf("\nTesting delete.\n");
	hm_value addval =  {.i = 100};
	hm_upsert(hm, 27, addval); // 17 % 16 = 1 (occupied) -> goes to 9th idx
	printf("\n");
	hm_state(hm);
	hm_delete(hm, 3);
	hm_delete(hm, 7);
	printf("deleted 3 adn 7.\n");
	hm_state(hm);
	printf("seeking 100, pasing over deleted buckets...\n");
	int r = hm_read(hm, 27, &addval); // can it fetch over deleted slots ?
	if (r) printf("Fetched : %d", (int)addval.i);

	hm_free(hm);

	return EXIT_SUCCESS;

}
