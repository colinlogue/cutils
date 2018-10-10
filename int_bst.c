

// START BASE TEMPLATE //
#include "int_bst.h"

#define bst_node int_bst_node
#define bst_node_t int_bst_node_t
#define list_t int_list_t
#define CONTENT_TYPE int


// STATIC FUNCTIONS
static bst_node_t *add_node(bst_node_t *, bst_node_t *, bst_node_t *);
static int get_height(bst_node_t *);
static CONTENT_TYPE get_nth_item(int, bst_node_t *);
static bst_node_t *insert(int, CONTENT_TYPE, bst_node_t *);
static void in_order(bst_node_t *, list_t *);
// static bool is_leaf(bst_node_t *);
static bst_node_t *rebalance(int, bst_node_t *, bst_node_t *);
static int size(bst_node_t *);


bst_node_t *add_node(bst_node_t *new_node, bst_node_t *tree, bst_node_t *parent) {
  bst_node_t **next_ptr;
  // sort direction
  if (new_node->sort_val < tree->sort_val) {
  	next_ptr = &(tree->left);
  	tree->n_left += size(new_node);
  }
  else {
  	next_ptr = &(tree->right);
  	tree->n_right += size(new_node);
  }
  // check if end of branch
  if (*next_ptr) {
    // if next_ptr doesn't point to NULL then recursively call add_node 
  	add_node(new_node, *next_ptr, tree);
  }
  else {
    // if next_ptr does point to NULL, point it to new_node instead
    *next_ptr = new_node;
  }
  int balance = tree->n_right - tree->n_left;
  if (balance < -1 || balance > 1) {
  	return rebalance(balance, tree, parent);
  }
  else {
    return tree;
  }
}


CONTENT_TYPE get_height(bst_node_t *tree) {
  if (!tree) {
    return 0;
  }
  else {
    return 1 + max_int(get_height(tree->left), get_height(tree->right));
  }
}


CONTENT_TYPE get_nth_item(int n, bst_node_t *tree) {
  list_t *items = int_bst_in_order(tree);
  CONTENT_TYPE value = items->get_item_at(n, items);
  items->delete_list(items);
  return value;
}


bst_node_t *insert(int sort_val, CONTENT_TYPE content, bst_node_t *tree) {
  bst_node_t *node = int_bst_new(sort_val, content);
  return add_node(node, tree, NULL);
}


void in_order(bst_node_t *root, list_t *results) {
  if (root->left) {
    in_order(root->left, results);
  }
  results->append_item(root->content, results);
  if (root->right) {
    in_order(root->right, results);
  }
}


// bool is_leaf(bst_node_t *tree) {
//   if (tree->right || tree->left) {
//     return false;
//   }
//   else {
//     return true;
//   }
// }


bst_node_t *rebalance(int balance, bst_node_t *tree, bst_node_t *parent) {
  bst_node_t *new_pivot;
  if (balance < -1) {
  	// overwighted to left
  	new_pivot = tree->left;
    tree->left = NULL;
  	tree->n_left = 0;
  }
  else if (balance > 1) {
  	// overweighted to right
  	new_pivot = tree->right;
    tree->right = NULL;
  	tree->n_right = 0;
  }
  if (parent) {
  	// if tree is not root node for whole tree
  	if (parent->left == tree) {
  		// if on parent's left
  		parent->left = new_pivot;
  	}
  	else {
  		parent->right = new_pivot;
  	}
  }
  return add_node(tree, new_pivot, parent);
}


int size(bst_node_t *node) {
	return node->n_left + node->n_right + 1;
}


// PUBLIC FUNCTIONS
bst_node_t *int_bst_new(int sort_val, CONTENT_TYPE content) {
  bst_node_t *node = malloc(sizeof(bst_node_t));
  node->sort_val = sort_val;
  node->content = content;
  node->left = NULL;
  node->right = NULL;
  node->n_left = 0;
  node->n_right = 0;
  return node;
}


bst_node_t *int_bst_insert(int sort_val, CONTENT_TYPE content, bst_node_t *tree) {
	return insert(sort_val, content, tree);
}


list_t *int_bst_in_order(bst_node_t *root) {
  list_t *results = int_list_new();
  in_order(root, results);
  return results;
}


int int_bst_get_height(bst_node_t *root) {
  return get_height(root);
}


CONTENT_TYPE int_bst_get_item_at(int n, bst_node_t *tree) {
  return get_nth_item(n, tree);
}


#undef bst_node
#undef bst_node_t
#undef list_t
#undef CONTENT_TYPE

// END BASE TEMPLATE //