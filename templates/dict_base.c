// START HEADER TEMPLATE //
#ifndef <<LABEL>>_DICT_H
#define <<LABEL>>_DICT_H

#include <stdlib.h>
#include <string.h>
#include "misc.h"

#define dict_entry <<LABEL>>_dict_entry
#define dict_entry_t <<LABEL>>_dict_entry_t
#define dict <<LABEL>>_dict
#define dict_t <<LABEL>>_dict_t
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

#define dict_clear <<LABEL>>_dict_clear
#define dict_free <<LABEL>>_dict_free
#define dict_insert <<LABEL>>_dict_insert
#define dict_insert_or_update <<LABEL>>_dict_insert_or_update
#define dict_new <<LABEL>>_dict_new
#define dict_retrieve <<LABEL>>_dict_retrieve
#define dict_update <<LABEL>>_dict_update

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

Internal functions
------------------
entry_get_by_key(char *key, dict_t *d) : dict_entry_t
entry_delete(dict_entry_t *entry) : void
entry_new(char* key, <<TYPE>> value, dict_t *d) : *entry_t

**/

#include "<<LABEL>>_dict.h"

const int HASH_STR_POLYNOMIAL_X = 19;

#define dict_entry <<LABEL>>_dict_entry
#define dict_entry_t <<LABEL>>_dict_entry_t
#define dict <<LABEL>>_dict
#define dict_t <<LABEL>>_dict_t
#define CONTENT_TYPE <<TYPE>>


// PRIVATE FUNCTION DECLARATIONS //
dict_entry_t *entry_get_by_key(char *, dict_t *);
void entry_delete(dict_entry_t *);
dict_entry_t *entry_new(char* key, int value, dict_t *d);


#define dict_clear <<LABEL>>_dict_clear
#define dict_free <<LABEL>>_dict_free
#define dict_insert <<LABEL>>_dict_insert
#define dict_insert_or_update <<LABEL>>_dict_insert_or_update
#define dict_new <<LABEL>>_dict_new
#define dict_retrieve <<LABEL>>_dict_retrieve
#define dict_update <<LABEL>>_dict_update

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


void dict_insert(char *key, CONTENT_TYPE value, dict_t *d) {
  int key_idx = d->hash_fn(key);
  blarghh!
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
      <<TYPE>>
          The value of the entry for the given key.
  **/
  return entry_get_by_key(key, d)->value;
}


void dict_update(char *key, <<TYPE>> value, dict_t *d) {
  /** Updates the entry with the given key to the given value.

      Parameters
      ----------
      key : *char
          Pointer to the key string of the entry to update.
      value : <<TYPE>>
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