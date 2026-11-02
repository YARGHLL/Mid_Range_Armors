#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define ASSERT(expr)                                                                               \
  {                                                                                                \
    if (!(expr)) {                                                                                 \
      fprintf(stderr, "Assertion failed: %s\n", #expr);                                            \
      fprintf(stdout, "Assertion failed at line: %d and file: %s\n", __LINE__, __FILE__);          \
      exit(1);                                                                                     \
    }                                                                                              \
  }

#define TEST(expr)                                                                                 \
  {                                                                                                \
    if (!(expr)) {                                                                                 \
      fprintf(stderr, "Test failed: %s\n", #expr);                                                 \
      exit(1);                                                                                     \
    }                                                                                              \
  }

typedef struct node {
  uint64_t data;
  struct node *next;
} node_t;

typedef struct info {
  uint64_t sum;
} info_t;

node_t *head = NULL;
info_t info = {0};

void insert_sorted(uint64_t data) {
  node_t *new_node = malloc(sizeof(node_t));
  new_node->data = data;
  new_node->next = NULL;

  info.sum += data;

  if (head == NULL) {
    head = new_node;

  } else {
    node_t *Iterator = head;
    node_t *prev = head;

    while (Iterator != NULL) {

      if (prev->data < new_node->data && new_node->data < Iterator->data) {

        prev->next = new_node;
        new_node->next = Iterator;
        break;

      } else if (Iterator == head && Iterator->data > new_node->data) {
        head = new_node;
        new_node->next = Iterator;

      } else if (Iterator->data < new_node->data && Iterator->next == NULL) {
        Iterator->next = new_node;
        break;
      }

      prev = Iterator;
      if (Iterator->next != NULL) {
        Iterator = Iterator->next;
      } else {
        break;
      }
    }
  }
}

int index_of(uint64_t data) {
  node_t *curr = head;
  int index = 0;

  while (curr != NULL) {
    if (curr->data == data) {
      return index;
    }

    curr = curr->next;
    index++;
  }

  return -1;
}

int main() {
  insert_sorted(1);
  insert_sorted(3);
  insert_sorted(5);
  insert_sorted(2);

  TEST(info.sum == 1 + 3 + 5 + 2);
  TEST(index_of(2) == 1);
  ASSERT(info.sum == (1 + 3 + 5 + 2));
  return 0;
}
