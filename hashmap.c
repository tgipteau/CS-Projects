#include "hashmap.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define LOAD_FACTOR 0.75

enum hashType {NULL_TYPE, INT_TYPE, UINT_TYPE, VPTR_TYPE, STR_TYPE};

struct hashEntry {
	int key;
	enum hashType entry_type;
	union {
		intptr_t i;
	} data;
};

struct hashMap {
	size_t size;
	int load;
	struct hashEntry *data;
};

struct hashMap * hm_create(void){
	struct hashMap *hm = calloc(1, sizeof(*hm));
	return hm;
}

void hm_init(struct hashMap *hm, int nb_entries){
	hm->size = (int)(nb_entries / LOAD_FACTOR) + 1;
	hm->data = calloc(hm->size, sizeof(struct hashEntry));
}

int hm_insert(struct hashMap *hm, int key, int dat){
	// -> add checkup for full hm
	int hash_idx = key % hm->size;
	while(1){
		if (hm->data[hash_idx].entry_type == NULL_TYPE){
			hm->data[hash_idx].key = key;
			hm->data[hash_idx].entry_type = INT_TYPE;
			hm->data[hash_idx].data.i = dat;
			hm->load++;
			break;
		}
		else hash_idx++;
	}
	return hash_idx;
}

void hm_resize(struct hashMap *old_hm){
	// create new hm
	size_t new_size = old_hm->size*2;
	struct hashMap *new_hm = hm_create();
	new_hm->size = new_size;
	new_hm->data = calloc(new_size, sizeof(struct hashEntry));

	// copy into new_hm
	for (size_t n=0 ; n<old_hm->size ; n++){
		hm_insert(new_hm, old_hm->data[n].key, old_hm->data[n].data.i);
	}
	// free old hm
	free(old_hm);
	// update old_hm
	old_hm = new_hm;

}

void hm_show(struct hashMap *hm){
	// show in lines of 15 elements
	const int line_width = 15;

	for (size_t i=0; i<hm->size; i++){

		if (i%line_width==0)
			printf("[%3d->%3d]%-6c", (int)i, (int)i+line_width-1, ' ');

		if ((int)hm->data[i].entry_type == NULL_TYPE)
			printf("%4c ", '.');
		else
			printf("%4d ", (int)hm->data[i].data.i);
		/*
		switch (hm->data[i].entry_type) {
			case INT_TYPE:
				printf("%d  ", (int)hm->data[i].data.i);
				break;
			case UINT_TYPE:
				printf("%d  ", (int)hm->data[i].data.u);
				break;
			case VPTR_TYPE:
				printf("X  ");
				break;
			case STR_TYPE:
				printf("%s  ", hm->data[i].data.s);
				break;
				}*/

		if ((i+1)%line_width==0)
			printf("\n");
	}
	printf("END\n");
	printf("LOAD: %4d / %4d\t LOAD_FACTOR: %4f\n",
	 	hm->load, (int)hm->size, (float)hm->load/hm->size);

}
