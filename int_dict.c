

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
dict_insert(char *key, int value, dict_t *d) : void
    Adds the key-value pair to the dict.
dict_insert_or_update(char *key, int value, dict_t *d) : void
    Inserts of updates the entry depending on if the key is present.
dict_new(int table_size) : *dict_t
    Creates a new dict and returns a pointer to it.
dict_retrieve(char *key, dict_t *d) : int
    Searches the dict for the key and returns the value of its entry.
dict_update(char *key, int value, dict_t *d) : void
    Updates the entry with the given key to the given value.

Internal functions
------------------
entry_get_by_key(char *key, dict_t *d) : dict_entry_t
entry_delete(dict_entry_t *entry) : void
entry_new(char* key, int value, dict_t *d) : *entry_t

**/

#include "int_dict.h"

const int HASH_STR_POLYNOMIAL_X = 19;

#define dict_entry int_dict_entry
#define dict_entry_t int_dict_entry_t
#define dict int_dict
#define dict_t int_dict_t
#define CONTENT_TYPE int


// PRIVATE FUNCTION DECLARATIONS //
dict_entry_t *entry_get_by_key(char *, dict_t *);
void entry_delete(dict_entry_t *);
dict_entry_t *entry_new(char* key, int value, dict_t *d);


#define dict_clear int_dict_clear
#define dict_free int_dict_free
#define dict_insert int_dict_insert
#define dict_insert_or_update int_dict_insert_or_update
#define dict_new int_dict_new
#define dict_retrieve int_dict_retrieve
#define dict_update int_dict_update

// PUBLIC FUNCTIONS //
void dict_clear(dict_t *d) {
  /** Frees memory for all entries and sets entry pointers to NULL.

      Parameters
      ----------
      d : *dict_t
          Pointer to the dict to clear the entries of.
  **/
  dict_entry_t *current_entry = d->entries[0];
  for (int current_idx = 0; current_idx < d->size; current_idx++) {
  entry_delete(current_entry);
  current_entry = NULL;
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


dict_t *dict_new(int table_size, int (*hash_fn)(char *)) {
  /** Creates a new dict and returns a pointer to it.

      Returns
      -------
      *dict_t
          Pointer to the newly created dict_t.
  **/
  dict_t *d = malloc(sizeof(dict_t));
  d->size = table_size;
  d->hash_fn = hash_fn;
  d->entries = malloc(sizeof(dict_entry_t *) * table_size);
  dict_clear(d);
  return d;
}


CONTENT_TYPE dict_retrieve(char *key, dict_t *d) {
  /** Searches the dict for the key and returns the value of its entry.

      Parameters
      ----------
      key : *char
          Pointer to the key string.
      d : *dict_t
          Pointer to the dict to retrieve the data from.

      Returns
      -------
      int
          The value of the entry for the given key.
  **/
  return entry_get_by_key(key, d)->value;
}


void dict_update(char *key, int value, dict_t *d) {
  /** Updates the entry with the given key to the given value.

      Parameters
      ----------
      key : *char
          Pointer to the key string of the entry to update.
      value : int
          Value to set the key's entry to.
      d : *dict_t
          Pointer to the dictionary to update the entry in.
  **/
  entry_get_by_key(key, d)->value = value;
}


// INTERNAL FUNCTIONS //
void entry_delete(dict_entry_t *entry) {
  free(entry);
}


dict_entry_t *entry_get_by_key(char *key, dict_t *d) {
  dict_entry_t **entry_ptr = d->entries + d->hash_fn(key);
  while (strcmp(key, (*entry_ptr)->key)) {
    entry_ptr++;
  }
  return *entry_ptr;
}

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

// END BASE TEMPLATE //