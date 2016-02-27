#if !defined AVL_TREE_H
#define AVL_TREE_H
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
struct vertex{
   int data;
   long height;
   struct vertex *l,*r,*p;

};
void insert(struct vertex** root, int data);
void* find(struct vertex* root, int data);
void clear_tree(struct vertex** root);
void print_tree(struct vertex* root);

void test_left_rotate();
#endif
