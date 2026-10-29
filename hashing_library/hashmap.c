#include "hashmap.h"
#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define LOAD_FACTOR 0.75
#define INIT_SIZE 16

#define MAX_STATE_SHOW 256
#define LINE_W 12

enum hashType {EMPTY_TYPE, OCCUPIED_TYPE, DEL_TYPE};

struct hashEntry {
	int key;
	enum hashType entry_type;
	hm_value val;
};

struct hashMap {
	size_t size;
	int load;
	struct hashEntry *data;
};

static int hm_find(struct hashMap *hm, int key){

	assert(key>=0);
	int idx = key % hm->size;
	while(1){
		if (hm->data[idx].entry_type == EMPTY_TYPE)
			return -1; // search fail
		if (hm->data[idx].key == key && hm->data[idx].entry_type == OCCUPIED_TYPE)
			return idx; // match
		else{
			//loop over end
			idx++;
			idx %= hm->size;
		}

	}
}

static void hm_resize(struct hashMap *hm){

	size_t new_size = hm->size*2;
	int new_load = 0; // load is freed of tombstones
	struct hashEntry *new_data = calloc(new_size, sizeof(*new_data));

	for (size_t n=0 ; n<hm->size ; n++){
		struct hashEntry *e = &hm->data[n];

		if (e->entry_type != OCCUPIED_TYPE) continue;

		int h_idx = e->key % new_size;
		//linear probing
		while(new_data[h_idx].entry_type == OCCUPIED_TYPE){
			h_idx++;
			h_idx %= new_size;
		}
		new_data[h_idx] = *e;
		new_load++;
	}

	free(hm->data);
	hm->data = new_data;
	hm->size = new_size;
	hm->load = new_load;

}

struct hashMap * hm_init(void){
	struct hashMap *hm = calloc(1, sizeof(*hm));
	hm->size = INIT_SIZE;
	hm->data = calloc(hm->size, sizeof(struct hashEntry));
	hm->nb_empty_slots = hm->size;
	return hm;
}

void hm_state(struct hashMap *hm){
	const int nb_show = (int)hm->size>MAX_STATE_SHOW? MAX_STATE_SHOW:(int)hm->size;

	for (int i=0; i<nb_show; i++){

		if (i%LINE_W==0)
			printf("\n[%3d->%3d]%-6c", i, i+LINE_W-1, ' ');

		if ((int)hm->data[i].entry_type == EMPTY_TYPE)
			printf("%4c ", '.');
		else if ((int)hm->data[i].entry_type == DEL_TYPE)
			printf("%4c ", 'x');
		else
			printf("%4d ", (int)hm->data[i].val.i);
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

	}
	printf("\nLOAD: %4d / %4d\t LOAD_FACTOR: %4f\n",
	 	hm->load, (int)hm->size, (float)hm->load/hm->size);

}

int hm_upsert(struct hashMap *hm, int key, hm_value val){

	// checkup load and resize if needed
	if ((float)(hm->load+1) / hm->size > LOAD_FACTOR)
		hm_resize(hm);

	// replace if existing key

	assert(key>=0);


	int found_idx = hm_find(hm, key);

	if (found_idx==-1){
		// insert
		int hash_idx = key % hm->size;
		while(1){
			if (hm->data[hash_idx].entry_type != OCCUPIED_TYPE){
				hm->data[hash_idx].key = key;
				hm->data[hash_idx].entry_type = OCCUPIED_TYPE;
				hm->data[hash_idx].val = val;
				hm->load++;
				return 0; // insert indicator
				}
			else {
				hash_idx++;
				hash_idx %= hm->size; // loop over end
			}
		}
	}
	else {
		// update
		hm->data[found_idx].val = val;
		return 1; // update indicator
	}
}

int hm_read(struct hashMap *hm, int key, hm_value *val){

	assert(key>=0);
	int idx = hm_find(hm, key);
	if (idx==-1) return 0; // no match.
	else
	{
		*val = hm->data[idx].val;
		return 1;
	}

}

int hm_delete(struct hashMap *hm, int key){

	assert(key>=0);
	int idx = hm_find(hm, key);
	if (idx==-1) return 0;

	hm->data[idx].entry_type=DEL_TYPE;
	return 1;
}

void hm_free(struct hashMap *hm){
	free(hm->data);
	free(hm);
}
