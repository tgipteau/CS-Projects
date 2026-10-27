#pragma once

typedef struct hashMap hashMap;

struct hashMap * hm_create(void);
void hm_init(struct hashMap *hm, int nb_entries);
void hm_show(struct hashMap *hm);
int hm_insert(struct hashMap *hm, int key, int dat);
void hm_resize(struct hashMap *old_hm);
