// START HEADER TEMPLATE
#ifndef <<LABEL>>_BST_H
#define <<LABEL>>_BST_H

#include <stdlib.h>
#include <stdbool.h>
#include "<<LABEL>>_list.h"
#include "intmath.h"

#define bst_node <<LABEL>>_bst_node
#define bst_node_t <<LABEL>>_bst_node_t
#define bst_fns 
#define list_t <<LABEL>>_list_t
#define CONTENT_TYPE <<TYPE>>

// TYPE DEFINITIONS
typedef struct bst_node {
  int sort_val;
  CONTENT_TYPE content;
  struct bst_node *left, *right;
  int n_left, n_right;
} bst_node_t;

// PUBLIC FUNCTION DECLARATIONS
bst_node_t *<<LABEL>>_bst_new(int, CONTENT_TYPE);
bst_node_t *<<LABEL>>_bst_insert(int, CONTENT_TYPE, bst_node_t *);
list_t *<<LABEL>>_bst_in_order(bst_node_t *);
int <<LABEL>>_bst_get_height(bst_node_t *);
CONTENT_TYPE <<LABEL>>_bst_get_item_at(int, bst_node_t *);

#undef bst_node
#undef bst_node_t
#undef list_t
#undef CONTENT_TYPE

#endif
// END HEADER TEMPLATE //

// <<SPLIT>> //

// START BASE TEMPLATE //
#include "<<LABEL>>_bst.h"

#define bst_node <<LABEL>>_bst_node
#define bst_node_t <<LABEL>>_bst_node_t
#define list_t <<LABEL>>_list_t
#define CONTENT_TYPE <<TYPE>>

const int REBALANCE_THRESHOLD = 2

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
  /** Adds a node to the tree.

      Parameters
      ----------
      new_node : *bst_node_t
          Pointer ot the node to be added to the tree.
      tree : *bst_node_t
          Pointer to the tree to add the node to.
      parent : *bst_node_t
          Pointer to the parent node of tree, or NULL if tree is the root.

      Returns
      -------
      *bst_node_t
          Pointer to the root node of the tree after rebalancing.

      Notes
      -----
      If adding the node to the tree unbalances it, then the function will call
      the rebalance function and return the result. The threshold for being
      unbalanced is the constant REBALANCE_THRESHOLD.
  **/
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
  if (balance < -REBALANCE_THRESHOLD || balance > REBALANCE_THRESHOLD) {
  	return rebalance(balance, tree, parent);
  }
  else {
    return tree;
  }
}


CONTENT_TYPE get_height(bst_node_t *tree) {
  /** Returns the height of the tree from the given node.

      Parameters
      ----------
      tree : *bst_node_t
          Pointer to the node to calculate the height for.

      Returns
      -------
      height : int
          Height of the tree from the given node.
  **/
  if (!tree) {
    return 0;
  }
  else {
    return 1 + max_int(get_height(tree->left), get_height(tree->right));
  }
}


CONTENT_TYPE get_nth_item(int n, bst_node_t *tree) {
  /** Returns the nth item from the left of the tree.

      Parameters
      ----------
      n: int
          The index of the item to find. Must be less then the number of nodes
          in the tree.

      Returns
      -------
      value : <<TYPE>>
          The value of the content of the located node.
    **/
  list_t *items = <<LABEL>>_bst_in_order(tree);
  CONTENT_TYPE value = items->get_item_at(n, items);
  items->delete_list(items);
  return value;
}


bst_node_t *insert(int sort_val, CONTENT_TYPE content, bst_node_t *tree) {
  /** Inserts a node with the given value and content into the tree.

      Parameters
      ----------
      sort_val : int
          The value that the node will be ordered by.
      content : <<TYPE>>
          The content value of the new node.
      tree : *bst_node_t
          Pointer to the tree to add the node to.

      Returns
      -------
      *bst_node_t
          The root of the tree after any rebalancing triggered by the insert.
  **/
  bst_node_t *node = <<LABEL>>_bst_new(sort_val, content);
  return add_node(node, tree, NULL);
}


void in_order(bst_node_t *root, list_t *results) {
  /** Adds the tree's nodes in increasing order of value to a linked list.

      Parameters
      ----------
      root : *bst_node_t
          The root of the tree to get the list of nodes for.
      results : *list_t
          Pointer to the list to add the nodes to.
  **/
  if (root->left) {
    in_order(root->left, results);
  }
  results->append_item(root->content, results);
  if (root->right) {
    in_order(root->right, results);
  }
}

// /** this function is commented out because it is currently not used
//     by any other functions so the compiler complains about it **/
//
// bool is_leaf(bst_node_t *node) {
//   /** Checks if the node has any children.
//
//       Parameters
//       ----------
//       node : *bst_node_t
//           Pointer to the node to check.
//
//       Returns
//       -------
//       bool
//           Returns `true` if the node has any children, otherwise `false`.
//   **/
//   if (node->right || node->left) {
//     return false;
//   }
//   else {
//     return true;
//   }
// }


bst_node_t *rebalance(int balance, bst_node_t *tree, bst_node_t *parent) {
  /** Adjust the placement of the nodes so that the tree is balanced.

      Parameters
      ----------
      balance : int
          The balance value of the tree.
      tree : *bst_node_t
          Pointer to the tree to be rebalanced.
      parent : *bst_node_t
          Pointer to the parent node of tree. NULL if tree is the root node.

      Returns
      -------
      *bst_node_t
          Pointer to the new root of the tree after balancing.
  **/
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
  /** Returns the number of nodes the in given tree.

      Parameters
      ----------
      node : *bst_node_t
          Pointer to the node to get the size for.

      Returns
      -------
      int
          The size of the node.

      Notes
      -----
      The size of a leaf node is 1, because the tree is just that node. The
      size of a node with children is the size of each of its children's
      trees plus the size of itself (1).
  **/
	return node->n_left + node->n_right + 1;
}


// PUBLIC FUNCTIONS
bst_node_t *<<LABEL>>_bst_new(int sort_val, CONTENT_TYPE content) {
  bst_node_t *node = malloc(sizeof(bst_node_t));
  node->sort_val = sort_val;
  node->content = content;
  node->left = NULL;
  node->right = NULL;
  node->n_left = 0;
  node->n_right = 0;
  return node;
}


bst_node_t *<<LABEL>>_bst_insert(int sort_val, CONTENT_TYPE content, bst_node_t *tree) {
	return insert(sort_val, content, tree);
}


list_t *<<LABEL>>_bst_in_order(bst_node_t *root) {
  list_t *results = <<LABEL>>_list_new();
  in_order(root, results);
  return results;
}


int <<LABEL>>_bst_get_height(bst_node_t *root) {
  return get_height(root);
}


CONTENT_TYPE <<LABEL>>_bst_get_item_at(int n, bst_node_t *tree) {
  return get_nth_item(n, tree);
}


#undef bst_node
#undef bst_node_t
#undef list_t
#undef CONTENT_TYPE

// END BASE TEMPLATE //