// START HEADER TEMPLATE
#ifndef int_BST_H
#define int_BST_H

#include <stdlib.h>
#include <stdbool.h>
#include "int_list.h"
#include "intmath.h"

#define bst_node int_bst_node
#define bst_node_t int_bst_node_t
#define bst_fns 
#define list_t int_list_t
#define CONTENT_TYPE int

// TYPE DEFINITIONS
typedef struct bst_node {
  int sort_val;
  CONTENT_TYPE content;
  struct bst_node *left, *right;
  int n_left, n_right;
} bst_node_t;

// PUBLIC FUNCTION DECLARATIONS
bst_node_t *int_bst_new(int, CONTENT_TYPE);
bst_node_t *int_bst_insert(int, CONTENT_TYPE, bst_node_t *);
list_t *int_bst_in_order(bst_node_t *);
int int_bst_get_height(bst_node_t *);
CONTENT_TYPE int_bst_get_item_at(int, bst_node_t *);

#undef bst_node
#undef bst_node_t
#undef list_t
#undef CONTENT_TYPE

#endif
// END HEADER TEMPLATE //

