#include "hashmap.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(void){

	char *key = calloc(16, sizeof(*key));
	key = "ÿÿÿÿÿÿÿÿÿÿÿ";
	uint32_t hash = fnv_key(key);

	printf("Key %s, hash 0x%x", key, hash);

	return EXIT_SUCCESS;
}
