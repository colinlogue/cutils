// START HEADER TEMPLATE //
#ifndef <<LABEL>>_DICT_H
#define <<LABEL>>_DICT_H

#define dict_entry <<label>>_dict_entry
#define dict_entry_t <<label>>_dict_entry_t
#define dict <<label>>_dict
#define dict_t <<label>>_dict_t
#define CONTENT_TYPE <<TYPE>>

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

const int HASH_STR_POLYNOMIAL_X = 19;

#endif
// END HEADER TEMPLATE//

// <<SPLIT>> //

// START BASE TEMPLATE //


/**

For all functions dealing with a pointer to a dict_t, that pointer is called d.

All public functions include a dict_t as the *final* parameter except for new,
which takes only setup parameters as arguments and returns a pointer to an
initialized dict_t.

Public functions
----------------
dict_clear(dict_t *d) : void
    Frees memory for all entries and sets entry pointers to NULL.
dict_free(dict_t *d) : void
    Frees memory for the dict and all of its entries.
dict_insert(char *key, <<TYPE>> value, dict_t *d) : void
    Adds the key-value pair to the dict.
dict_insert_or_update(char *key, <<TYPE>> value, dict_t *d) : void
    Inserts of updates the entry depending on if the key is present.
dict_new(int table_size) : *dict_t
    Creates a new dict and returns a pointer to it.
dict_retrieve(char *key, dict_t *d) : <<TYPE>>
    Searches the dict for the key and returns the value of its entry.
dict_update(char *key, <<TYPE>> value, dict_t *d) : void
    Updates the entry with the given key to the given value.
hash_str_polynomial(char *key) : int
    Hashes the string using a polynomial method.

Internal functions
------------------
entry_get_by_key(char *key, dict_t *d) : dict_entry_t
entry_delete(dict_entry_t *entry) : void
entry_new(char* key, <<TYPE>> value, dict_t *d) : *entry_t

**/


// PUBLIC FUNCTIONS //
void dict_clear(dict_t *d) {
	/** Frees memory for all entries and sets entry pointers to NULL.

	    Parameters
	    ----------
	    d : *dict_t
	        Pointer to the dict to clear the entries of.
	**/
	dict_entry_t **current_entry = d->entries;
	for (int current_idx = 0; current_idx < d->size; current_idx++) {
		entry_delete(*current_entry);
		*current_entry = NULL;
		current_entry++;
	}
}


void dict_free(dict_t *d) {
	/** Frees memory for the dict and all of its entries.

	    Parameters
	    ----------
	    d : *dict_t
	        Pointer to the dict to be deleted.
	**/
	dict_clear(d);
	free(d);
}

dict_t *dict_new(int table_size, int (*hash_fn)(CONTENT_TYPE)) {
	/** Creates a new dict and returns a pointer to it.

	    Returns
	    -------
	    *dict_t
	        Pointer to the newly created dict_t.
	**/
	dict_t *d = malloc(sizeof(dict_t));
	d->size = table_size;
	d->hash_fn = hash_fn;
	d->entries = malloc(sizeof(*dict_entry_t) * table_size);
	dict_clear(d);
	return d;
}

dict_retrieve(char *key, dict_t *d) : <<TYPE>>
    Searches the dict for the key and returns the value of its entry.
dict_update(char *key, <<TYPE>> value, dict_t *d) : void
    Updates the entry with the given key to the given value.
hash_str_polynomial(char *key) : int
    Hashes the string using a polynomial method.

int hash_str_polynomial(char *key) {

  int hash_val = 0;
  int key_len = strlen(key);
  for (int i = 0; i < key_len; i++) {
    hash_val = hash_val*HASH_STR_POLYNOMIAL_X + (int)key[i];
  }
  return hash_val;
}


// INTERNAL FUNCTIONS //
void entry_delete(dict_entry_t *entry) {
	free(entry);
}

// END BASE TEMPLATE //