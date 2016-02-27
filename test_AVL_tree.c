#include"./AVL_tree.h"
#include<stdio.h>
#include<time.h>

int main(){

   time_t t;
   srand(time(&t));
   struct vertex* root = NULL;
   int i,j,limit = 1000000,increment = 500000;
   printf("starting insert %d elements with increment %d in next round\n",limit,increment); 
   for (j = 0; j <= 100; j++){
      clock_t start,end;
      start = clock();
      for (i = 0; i < limit;i++){
	 int random = rand() % 10;
	 insert(&root,random);
      }
      end = clock();
      double total = (double)(end - start)/CLOCKS_PER_SEC;
      printf("height of tree is %ld \n",root->height);
      printf("%f\n",total);
      clear_tree(&root);
      limit += increment;
   }

}
