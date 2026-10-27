#pragma once
#include <stdint.h>

typedef struct hashMap hashMap;

typedef union {
		intptr_t i;
	} hm_value;

struct hashMap * hm_init(void);
void hm_state(struct hashMap *hm);
int hm_insert(struct hashMap *hm, int key, hm_value val);
int hm_read(struct hashMap *hm, int key, hm_value *val);
int hm_delete(struct hashMap *hm, int key);
