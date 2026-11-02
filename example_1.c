#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define ASSERT(expr)                                                                               \
  {                                                                                                \
    if (!(expr)) {                                                                                 \
      fprintf(stderr, "Assertion failed: %s\n", #expr);                                            \
      exit(1);                                                                                     \
    }                                                                                              \
  }

#define TEST(expr)                                                                                 \
  {                                                                                                \
    if (!(expr)) {                                                                                 \
      fprintf(stderr, "Test failed: %s\n", #expr);                                                 \
      exit(1);                                                                                     \
    } else {                                                                                       \
      printf("Test passed: %s\n", #expr);                                                          \
    }                                                                                              \
  }

typedef struct node {
  uint64_t data;
  struct node *next;
} node_t;

node_t *head = NULL;

// Function to insert a node containing: data into the sorted linked list
// I can infer that the linked list is sorted from least (at beginning) to greatest (at end)
void insert_sorted(uint64_t data) {
  node_t *new_node = malloc(sizeof(node_t));
  new_node->data = data;
  new_node->next = NULL;

  if (head == NULL) { // If the linked list was previously empty, the we insert the new_node at the
                      // head of the linked list
    head = new_node;

  } else {                   // If the linked list wasn't previously empty
    node_t *Iterator = head; // To iterate over the linked list
    node_t *prev = head;
    // What I need to do is iterate element-by-element over the linked list, until I find the
    // element whose->next value has data greater than data, but who is pointed to by a node with
    // data lesser than data
    // bool inserted = false;  //Will store true once new_node has been inserted

    while (Iterator != NULL) { // Iterate over the entire linked list, from beginning to end

      if (prev->data < new_node->data && new_node->data < Iterator->data) { // If the desired node
        prev->next = new_node; // node location is between a prev and a next node
        new_node->next = Iterator;
        break;

      } else if (Iterator == head && Iterator->data > new_node->data) { // If we are inserting
        head = new_node; // at beginning of linked list
        new_node->next = Iterator;

      } else if (Iterator->data < new_node->data &&
                 Iterator->next == NULL) { // If we're inserting at the end of the
        Iterator->next = new_node;         // linked list
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
  insert_sorted(2);
  insert_sorted(5);
  insert_sorted(3);

  TEST(index_of(3) == 2);

  insert_sorted(0);
  insert_sorted(4);

  TEST(index_of(4) == 4);

  return 0;
}
