#pragma once
#include <stdint.h>

typedef struct hashMap hm_hashMap;

typedef union {
		intptr_t i;
	} hm_value;

struct hashMap * hm_init(void);
uint32_t fnv_key(char *key);


void hm_free(struct hashMap *hm);
