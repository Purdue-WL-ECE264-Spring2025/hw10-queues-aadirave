#include "linked_list.h"

#include <stddef.h>
#include <stdlib.h>

struct list_node *new_node(size_t value) {
  struct list_node *nnode = calloc(1, sizeof(struct list_node));
  if (nnode == NULL) {
    return NULL;
  }

  nnode->value = value;

  return nnode;
}

void insert_at_head(struct linked_list *list, size_t value) {
  struct list_node *head = list->head;

  struct list_node *new_head = new_node(value);
  if (new_head == NULL) {
    return;
  }

  new_head->next = head;
  list->head = new_head;
}

void insert_at_tail(struct linked_list *list, size_t value) {
  if (list->head == NULL) {
    list->head = new_node(value);

    return;
  }

  struct list_node *curr = list->head;
  while (curr->next != NULL) {
    curr = curr->next;
  };

  curr->next = new_node(value);
}

size_t remove_from_head(struct linked_list *list) {
  struct list_node *head = list->head;

  size_t ret_val = head->value;
  list->head = head->next;

  free(head);

  return ret_val;
}

size_t remove_from_tail(struct linked_list *list) {
  struct list_node *head = list->head;
  struct list_node *curr = head, *prev = NULL;

  while (curr->next != NULL) {
    prev = curr;
    curr = curr->next;
  }

  if (prev == NULL) {
    // first node
    return remove_from_head(list);
  }

  prev->next = NULL;
  size_t to_ret = curr->value;

  free(curr);

  return to_ret;
}

void free_list(struct linked_list list) {
  struct list_node *head = list.head;
  struct list_node *curr = head;

  while (curr != NULL) {
    struct list_node *next = curr->next;
    free(curr);

    curr = next;
  }
}

// Utility function to help you debugging, do not modify
void dump_list(FILE *fp, struct linked_list list) {
  fprintf(fp, "[ ");
  for (struct list_node *cur = list.head; cur != NULL; cur = cur->next) {
    fprintf(fp, "%zu ", cur->value);
  }
  fprintf(fp, "]\n");
}
