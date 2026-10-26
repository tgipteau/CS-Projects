#include "hashmap.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define LOAD_FACTOR 0.7

enum hashType {NULL_TYPE, INT_TYPE, UINT_TYPE, VPTR_TYPE, STR_TYPE};

struct hashEntry {
	int key;
	enum hashType entry_type;
	union {
		intptr_t i;
	} data;
};

struct hashMap {
	int size;
	int nb_elmts;
	struct hashEntry *data;
};

struct hashMap * hm_create(void){
	struct hashMap *hm = calloc(1, sizeof(*hm));
	return hm;
}

void hm_init(struct hashMap *hm, int nb_entries){
	hm->size = (int)(nb_entries / LOAD_FACTOR) + 1;
	printf("hm size :%d", hm->size);
	hm->data = calloc(hm->size, sizeof(struct hashEntry));
}

void hm_show(struct hashMap *hm){
	// show in lines of 15 elements
	const int line_width = 15;

	printf("\nSHOWING HM :\n");
	for (int i=0; i<hm->size; i++){

		if (i%line_width==0)
			printf("[%d->%d]\t\t", i, i+line_width);

		printf("%d  ", (int)hm->data[i].data.i);
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
	printf("END\n\n");
}

void hm_insert(struct hashMap *hm, int val){
	// -> add checkup for full hm
	int hash_idx = val % hm->size;
	printf("hash idx : %d\n", hash_idx);
	while(1){
		if (hm->data[hash_idx].entry_type == NULL_TYPE){
			hm->data[hash_idx].entry_type = INT_TYPE;
			hm->data[hash_idx].data.i = val;
			hm->nb_elmts++;
			break;
		}
		else hash_idx++;
	}
}
