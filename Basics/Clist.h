#pragma once
#include <stdio.h>
#include <stdlib.h>

typedef struct Clist {
    int data;
    struct Clist* next;
} Clist;

Clist *createClist(int data);
void insertEnd(Clist **head, int data);
void display(Clist *head);
void deleteClist(Clist **head, int key);