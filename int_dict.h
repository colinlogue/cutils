// START HEADER TEMPLATE //
#ifndef int_DICT_H
#define int_DICT_H

#include <stdlib.h>
#include <string.h>
#include "misc.h"

#define dict_entry int_dict_entry
#define dict_entry_t int_dict_entry_t
#define dict int_dict
#define dict_t int_dict_t
#define CONTENT_TYPE int

// TYPE DEFINITIONS
typedef struct dict_entry {
	char *key;
	CONTENT_TYPE value;
} dict_entry_t;

typedef struct dict {
	size_t size;
	int (*hash_fn)(char *key);
	dict_entry_t **entries;
} dict_t;

#define dict_clear int_dict_clear
#define dict_free int_dict_free
#define dict_insert int_dict_insert
#define dict_insert_or_update int_dict_insert_or_update
#define dict_new int_dict_new
#define dict_retrieve int_dict_retrieve
#define dict_update int_dict_update

// PUBLIC FUNCTION DECLARATIONS //
void dict_clear(dict_t *);
void dict_free(dict_t *);
void dict_insert(char *, CONTENT_TYPE, dict_t *);
void dict_insert_or_update(char *, CONTENT_TYPE, dict_t *);
dict_t *dict_new(int, int (*hash_fn)(char *));
CONTENT_TYPE dict_retrieve(char *, dict_t *);
void dict_update(char *, CONTENT_TYPE, dict_t *);

#undef dict_clear
#undef dict_free
#undef dict_insert
#undef dict_insert_or_update
#undef dict_new
#undef dict_retrieve
#undef dict_update

#undef dict_entry
#undef dict_entry_t
#undef dict
#undef dict_t
#undef CONTENT_TYPE

#endif
// END HEADER TEMPLATE//

