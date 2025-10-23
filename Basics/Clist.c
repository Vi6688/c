#include "Clist.h"
#include "Memory.h"

Clist *createClist(int data) {
  Clist *newClist = (Clist *)newAlloc(sizeof(Clist));
  newClist->data = data;
  newClist->next = newClist;
  return newClist;
}
void insertEnd(Clist **head, int data) {
  Clist *newClist = createClist(data);
  if (*head == NULL) {
    *head = newClist;
    newClist->next = *head; // points to itself
    return;
  }

  Clist *temp = *head;
  while (temp->next != *head)
    temp = temp->next;

  temp->next = newClist;
  newClist->next = *head;
}

void display(Clist *head) {
  if (head == NULL)
    return;
  Clist *temp = head;
  do {
    printf("%d -> ", temp->data);
    temp = temp->next;
  } while (temp != head);
  printf("(back to head)\n");
}

void deleteClist(Clist **head, int key) {
  if (*head == NULL)
    return;

  Clist *curr = *head, *prev = NULL;

  // If head Clist is to be deleted
  if (curr->data == key) {
    while (curr->next != *head)
      curr = curr->next; // reach last Clist
    if (*head == (*head)->next) {
      free(*head);
      *head = NULL;
      return;
    }
    curr->next = (*head)->next;
    free(*head);
    *head = curr->next;
    return;
  }

  // For non-head Clists
  curr = (*head)->next;
  prev = *head;
  while (curr != *head && curr->data != key) {
    prev = curr;
    curr = curr->next;
  }

  if (curr == *head)
    return; // not found

  prev->next = curr->next;
  free(curr);
}
