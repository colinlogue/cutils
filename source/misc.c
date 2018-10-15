#include "misc.h"

int hash_str_polynomial(char *key) {
  /** Hashes the string using a polynomial method.

      Parameters
      ----------
      key : *char
          Pointer to the string to hash.

      Returns
      -------
      int
          Results of the hash function on the string key.
  **/
  int hash_val = 0;
  int key_len = strlen(key);
  for (int i = 0; i < key_len; i++) {
    hash_val = hash_val*HASH_STR_POLYNOMIAL_X + (int)key[i];
  }
  return hash_val;
}
