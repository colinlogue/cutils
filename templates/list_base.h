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