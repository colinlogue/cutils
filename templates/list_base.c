// HEADER

#ifndef <<LABEL>>_LIST_H
#define <<LABEL>>_LIST_H

#include <stdbool.h>

#define list_item <<LABEL>>_list_item
#define list_item_t <<LABEL>>_list_item_t
#define list <<LABEL>>_list
#define list_t <<LABEL>>_list_t
#define CONTENT_TYPE <<TYPE>>

typedef struct list_item {
  struct list_item *next;
  struct list_item *previous;
  CONTENT_TYPE content;
} list_item_t;

typedef struct list {
  list_item_t *head;
  list_item_t *tail;
  void (*append_item)(CONTENT_TYPE, struct list *);
  void (*clear_list)(struct list *);
  void (*combine_lists)(struct list *, struct list *);
  int (*count_item)(CONTENT_TYPE, struct list *);
  void (*delete_list)(struct list *);
  int (*find_item)(CONTENT_TYPE, struct list *);
  CONTENT_TYPE (*get_item_at)(int, struct list *);
  int (*get_length)(struct list *);
  void (*insert_item_at)(CONTENT_TYPE, int, struct list *);
  bool (*is_empty)(struct list *);
  void (*prepend_item)(CONTENT_TYPE, struct list *);
  void (*remove_item)(CONTENT_TYPE, struct list *);
  void (*remove_item_at)(int, struct list *);
} list_t;

list_t *<<LABEL>>_list_new();

#undef list_item
#undef list_item_t
#undef list
#undef list_t
#undef CONTENT_TYPE

#endif

// <<SPLIT>> //


#include <stdlib.h>
#include "<<LABEL>>_list.h"

#define list_item_t <<LABEL>>_list_item_t
#define list_t <<LABEL>>_list_t
#define CONTENT_TYPE <<TYPE>>


static void append_item(CONTENT_TYPE x, list_t *el) {
  /** Inserts the item after the final item in the list.

      Parameters
      ----------
      x : <<TYPE>>
          Value of the new item to be added to the list.
      el : *list_t
          Pointer to the list to append the item to.
  **/
  list_item_t *new_item = malloc(sizeof(list_item_t));
  list_item_t *previous_tail = el->tail;
  new_item->previous = previous_tail;
  new_item->next = NULL;
  new_item->content = x;
  if (!previous_tail) {
    el->head = new_item;
  }
  else {
    previous_tail->next = new_item;
  }
  el->tail = new_item;
}


static void clear_list(list_t *el) {
  /** Frees memory for all list items and sets list head to NULL. **/
  list_item_t *current_item = el->head;
  list_item_t *next_item = NULL;
  while (current_item) {
    next_item = current_item->next;
    free(current_item);
    current_item = next_item;
  }
  el->head = NULL;
  el->tail = NULL;
}


static void combine_lists(list_t *list1, list_t *list2) {
  /** Adds list2 to the end of list1.

      Parameters
      ----------
      list1 : *list_t
          Pointer to the list that will be added to and become the new list.
      list2 : *list_t
          Pointer to the list that will have its items appended to list1 and
          then be deleted.
  **/
  if (!list2->head) {
    // if the second list is empty, exit function
    return;
  }
  if (!list1->head) {
    // if the first list is empty, replace its values with those of the second
    // list, free the second list and exit the function
    *list1 = *list2;
    free(list2);
    return;
  }
  // if both lists have items
  list1->tail->next = list2->head;
  list2->head->previous = list1->tail;
  list1->tail = list2->tail;
  free(list2);
}


static int count_item(CONTENT_TYPE x, list_t *el) {
  /** Returns the number of times the item appears in the list.
  
      Paramters
      ---------
      x : <<TYPE>>
          Items with this value will be counted.
      el : *list_t
          Pointer to the list to count the occurance of value x in.

      Returns
      -------
      count : int
          Number of times the value x appears in the list.
  **/
  int count = 0;
  list_item_t *current_item = el->head;
  while (current_item) {
    if (current_item->content == x) {
      count++;
    }
    current_item = current_item->next;
  }
  return count;
}


static void delete_list(list_t *el) {
  /** Frees memory for all items in list and the list itself. **/
  clear_list(el);
  free(el);
}


static int find_item(CONTENT_TYPE x, list_t *el) {
  /** Returns the index of the given item in the list.

      Parameters
      ----------
      x : <<TYPE>>
          The value to search for in the list.
      el : *list_t
          Pointer to the list to search for x in.

      Returns
      -------
      int
          Index of x in the list, or -1 if it is not found.
  **/
  list_item_t *current_item = el->head;
  int i = 0;
  while(current_item->next) {
    if (x == current_item->content) {
      return i;
    }
    current_item = current_item->next;
    i++;
  }
  return -1;
}


static CONTENT_TYPE get_item_at(int pos, list_t *el) {
  /** Traverses the list to the given index and returns the value of that item.

      Parameters
      ----------
      pos : int
          Index of the list item to return the value for.
      el : *list_t
          Pointer to the list to search.

      Returns
      -------
      CONTENT_TYPE
          The value of the content of the item at the given list index.
  **/
  list_item_t *current_item = el->head;
  for (int i=0; i<pos; i++) {
    current_item = current_item->next;
  }
  return current_item->content;
}


static int get_length(list_t *el) {
  /** Counts the total number of items in the list.

      Paramters
      ---------
      el : *list_t
          Pointer to the list.

      Returns
      -------
      count : int
          Number of items in the list.
  **/
  int count = 0;
  list_item_t *current_item = el->head;
  while (current_item) {
    current_item = current_item->next;
    count++;
  }
  return count;
}


static void insert_item_at(CONTENT_TYPE x, int pos, list_t *el) {
  /** Adds a new item into the list at the given position.

      Parameters
      ----------
      x : <<TYPE>>
          The value of the item to be added.
      pos : int
          Index in the list where the new item will be placed.
      el : *list_t
          Pointer to the list to add the item to.
  **/

  // TODO: error handling if index not found

  // create new item
  list_item_t *new_item = malloc(sizeof(list_item_t));
  new_item->content = x;
  // traverse list to insert position
  list_item_t *current_item = el->head;
  list_item_t *previous_item = NULL;  
  for (int i=0; i<pos; i++) {
    previous_item = current_item;
    current_item = current_item->next;
  }
  // set connections with previous item
  new_item->previous = previous_item;
  if (previous_item) {
    previous_item->next = new_item;
  }
  else {
    el->head = new_item;
  }
  // set connections with displaced item
  new_item->next = current_item;
  if (current_item) {
    current_item->previous = new_item;
  }
  else {
    el->tail = new_item;
  }
}


static bool is_empty(list_t *el) {
  /** Returns true if there are zero items in the list, false otherwise. **/
  if (el->head) return true; else return false;
}


static void prepend_item(CONTENT_TYPE x, list_t *el) {
  /** Inserts the item before the initial item in the list.

      Parameters
      ----------
      x : <<TYPE>>
          Value of the new item to be added to the list.
      el : *list_t
          Pointer to the list to prepend the item to.
  **/
  list_item_t *new_item = malloc(sizeof(list_item_t));
  list_item_t *previous_head = el->head;
  new_item->next = previous_head;
  new_item->previous = NULL;
  new_item->content = x;
  if (!previous_head) {
    el->tail = new_item;
  }
  else {
    previous_head->previous = new_item;
  }
  el->head = new_item;
}


static void remove_item(CONTENT_TYPE x, list_t *el) {
  /** Deletes the first occurance of the value from the list.

      Parameters
      ----------
      x : <<TYPE>>
          The value of the item to be removed from the list.
      el : *list_t
          Pointer to the list to remove the item from.
  **/

  // TODO: error handling if value not found

  // traverse list to delete position
  list_item_t *current_item = el->head;
  while (current_item->content != x) {
    current_item = current_item->next;
  }
  // create connections around item to be removed
  list_item_t *previous_item = current_item->previous;
  list_item_t *following_item = current_item->next;
  if (previous_item) {
    previous_item->next = following_item;
  }
  else {
    el->head = following_item;
  }
  if (following_item) {
    following_item->previous = previous_item;
  }
  else {
    el->tail = previous_item;
  }
  // free memory
  free(current_item);
}


static void remove_item_at(int pos, list_t *el) {
  /** Deletes the item at the given list index.

      Parameters
      ----------
      pos : int
          The index of the item to be removed from the list.
      el : *list_t
          Pointer to the list to remove the item from.
  **/

  // TODO: error handling if index not found

  // traverse list to delete position
  list_item_t *current_item = el->head;
  for (int i=0; i<pos; i++) {
    current_item = current_item->next;
  }
  // create connections around item to be removed
  list_item_t *previous_item = current_item->previous;
  list_item_t *following_item = current_item->next;
  if (previous_item) {
    previous_item->next = following_item;
  }
  else {
    el->head = following_item;
  }
  if (following_item) {
    following_item->previous = previous_item;
  }
  else {
    el->tail = previous_item;
  }
  // free memory
  free(current_item);
}


list_t *<<LABEL>>_list_new() {
  /** Allocates memory for and initializes a new list.

      Returns
      -------
      el : *list_t
          Pointer to the newly created list.
  **/
  list_t *el = malloc(sizeof(list_t));
  el->head = NULL;
  el->tail = NULL;
  el->append_item = append_item;
  el->clear_list = clear_list;
  el->combine_lists = combine_lists;
  el->count_item = count_item;
  el->delete_list = delete_list;
  el->find_item = find_item;
  el->get_item_at = get_item_at;
  el->get_length = get_length;
  el->insert_item_at = insert_item_at;
  el->is_empty = is_empty;
  el->prepend_item = prepend_item;
  el->remove_item = remove_item;
  el->remove_item_at = remove_item_at;
  return el;
}


#undef list_item
#undef list_item_t
#undef list
#undef list_t
#undef CONTENT_TYPE