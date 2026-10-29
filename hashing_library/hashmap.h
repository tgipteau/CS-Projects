#pragma once
#include <stdint.h>

typedef struct hashMap hm_hashMap;

typedef union {
		intptr_t i;
	} hm_value;

struct hashMap * hm_init(void);
void hm_state(struct hashMap *hm);
int hm_upsert(struct hashMap *hm, int key, hm_value val);
int hm_read(struct hashMap *hm, int key, hm_value *val);
int hm_delete(struct hashMap *hm, int key);
int hm_len(struct hashMap *hm);

void hm_free(struct hashMap *hm);
