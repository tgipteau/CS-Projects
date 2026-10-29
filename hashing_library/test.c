/*
 Differential testing of hashmap.c library
*/

#include "hashmap.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NB_INSERTS 200000
#define NB_DELETES 50000
#define NB_SEARCHES 50000

typedef struct List{
	int *dat;
	int *key;
	int len;
} List;

int list_read(List l, int k, int *result);
int list_delete(List *l, int k);
int list_upsert(List *l, int k, int dat);

int main(void){

	// reference is an unordered array of size 2500
	List l = {
		.dat = malloc(NB_INSERTS*sizeof(int)),
		.key = malloc(NB_INSERTS*sizeof(int)),
		.len = 0,
	};

	// Creating hashmap
	hashMap *hm = hm_init();
	int r1, r2; // return values for hm and l operations

	for (int seed=0 ; seed<20 ; seed++){
		// Random inserts, deletes and reads
		srand(seed);
		printf("\nPerforming %d random inserts.\n", NB_INSERTS);

		for (int i=0 ; i<NB_INSERTS; i++){

			if (i%(NB_INSERTS/10)==0) printf("Performing inserts... %d/%d.\n",
				i, NB_INSERTS); // progress print

			int dat = rand()%3000;
			int key = rand()%100;
			hm_value hdat = { .i = dat};

			// upsert
			r1 = hm_upsert(hm, key, hdat);
			r2 = list_upsert(&l, key, dat);
			if (r1!=r2){
				printf("Upsert error at iter %d.\n", i);
				printf("Key: %d, Dat: %d\n", key, dat);
				printf("Incoherent update vs insert. r_hm: %d, r_list: %d\n", r1, r2);
				printf("(insert->0, update->1)\n");
				printf("Error seed : %d\n", seed);
				return EXIT_FAILURE;
			}
		}

		printf("\nPerforming %d random deletes.\n", NB_INSERTS);

		for (int i=0 ; i<NB_DELETES; i++){

			if (i%(NB_DELETES/10)==0) printf("Performing deletes... %d/%d.\n",
				i, NB_DELETES); // progress print

			int key = rand()%100;

			// delete
			r1 = hm_delete(hm, key);
			r2 = list_delete(&l, key);
			if (r1!=r2){
				printf("Delete error at iter %d.\n", i);
				printf("Key: %d\n", key);
				printf("Key not found. r_hm: %d, r_list: %d\n", r1, r2);
				printf("(not_found->0, found->1)\n");
				printf("Error seed : %d\n", seed);
				return EXIT_FAILURE;

			}
		}

		printf("\nPerforming %d random searches.\n", NB_INSERTS);

		for (int i=0 ; i<NB_SEARCHES; i++){

			int dat = rand()%3000;
			int key = rand()%100;
			hm_value hdat = { .i = dat};

			if (i%(NB_SEARCHES/10)==0) printf("Performing searches... %d/%d.\n",
				i, NB_SEARCHES); // progress print

			// read
			r1 = hm_read(hm, key, &hdat);
			r2 = list_read(l, key, &dat);
			if (r1!=r2){
				printf("Read error at iter %d.\n", i);
				printf("Key not found. r_hm: %d, r_list: %d\n", r1, r2);
				printf("(not_found->0, found->1)\n");
				printf("Error seed : %d\n", seed);
				return EXIT_FAILURE;

			}
			if (hdat.i!=dat){
				printf("Read error at iter %d.\n", i);
				printf("Key: %d\n", key);
				printf("Incoherent read. r_hm: %d, r_list: %d\n", (int)hdat.i, dat);
				printf("Error seed : %d\n", seed);
				return EXIT_FAILURE;
			}
		}

	}

	hm_free(hm);
	return EXIT_SUCCESS;

}

int list_read(List l, int k, int *result){
	for (int i=0 ; i<l.len ; i++){
		if(l.key[i]==k) {
			*result = l.dat[i];
			return 1;
		}
	}
	return 0;
}

int list_delete(List *l, int k){

	int idx = -1;

	for (int i=0 ; i<l->len ; i++){
		if (l->key[i]==k) idx = i;
	}

	if (idx==-1) return 0;

	for (int i=idx ; i<l->len-1 ; i++){
		l->dat[i] = l->dat[i+1];
		l->key[i] = l->key[i+1];
	}
	l->len--;
	return 1;
}

int list_upsert(List *l, int k, int dat){

	//update scenario
	for (int i=0 ; i<l->len ; i++){
		if (l->key[i]==k){
			l->dat[i] = dat;
			return 1;
		}
	}

	// insert scenario
	assert(l->len<NB_INSERTS);
	l->key[l->len] = k;
	l->dat[l->len] = dat;
	l->len++;
	return 0;
}
