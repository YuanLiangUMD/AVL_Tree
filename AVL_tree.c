#include"./AVL_tree.h"
/*
 *fix double rotation bug
 *advice: only use pointer to pointer for argument,reset pointer by return value 2/27/2016
 */
static long
max(long a, long b)
{
	return (((a) > (b)) ? a : b);
}
static long
balance_factor(struct vertex *v)
{
	if (v->l == NULL && v->r == NULL)
		return 0;
	else if (v->l == NULL)
		return (-1) - v->r->height;
	else if (v->r == NULL)
		return v->l->height - (-1);

	return (v->l->height - v->r->height);
}
static void
update_height(struct vertex *v)
{
	if (v->l == NULL
	    && v->r == NULL) {
		v->height = 0;
		return;
	} else if (v->l == NULL) {
		v->height = v->r->height + 1;
		return;
	} else if (v->r == NULL) {
		v->height = v->l->height + 1;
		return;
	}
	v->height = max(v->l->height, v->r->height) + 1;
}
static void
right_rotate(struct vertex **v)
{

	if ((*v)->p != NULL) {
		if ((*v)->p->l == (*v))
			(*v)->p->l = (*v)->l;
		else
			(*v)->p->r = (*v)->l;
	}
	struct vertex  *tmp = (*v)->l->r;
	(*v)->l->r = (*v);
	(*v)->l->p = (*v)->p;
	(*v)->p = (*v)->l;
	(*v)->l = tmp;
	if (tmp != NULL)
		tmp->p = (*v);

	update_height(*v);
	(*v) = (*v)->p;
	update_height(*v);
}
static void left_rotate();
void test_left_rotate(){
	struct vertex* v = malloc(sizeof(struct vertex) );
	struct vertex* r = malloc(sizeof(struct vertex) );
	struct vertex* p = malloc(sizeof(struct vertex) );
	p->p = NULL;
	p->l = v;
	p->r = NULL;
	p->height = 2;
	p->data = 3;

	v->p = p;
	v->data = 1;
	v->l = NULL;
	v->r = r;
	v->height = 1;

	r->p = v;
	r->data = 2;
	r->r = NULL;
	r->l = NULL;
	r->height = 0;

	printf("v->r->p->data = %d v->p->l->data = %d\n",v->r->p->data,v->p->l->data);
	printf("v->data = %d v->p->data = %d v->r->data = %d\n",v->data,v->p->data,v->r->data);
	printf("v->height = %ld v->r->height = %ld v->p->height = %ld \n",v->height,v->r->height,v->p->height);
	left_rotate(&v);

	printf("v->data = %d v->p->data = %d v->l->data = %d\n",v->data,v->p->data,v->l->data);
	printf("v->l->p->data = %d v->p->l->data = %d\n",v->l->p->data,v->p->l->data);
	printf("v->height = %ld v->l->height = %ld v->p->height = %ld \n",v->height,v->l->height,v->p->height);
	free(v);
	free(v->l);
	free(p);

}
static void
left_rotate(struct vertex **v)
{


	if ((*v)->p != NULL) {
		if ((*v)->p->r == (*v))
			(*v)->p->r = (*v)->r;
		else if ((*v)->p->l == (*v)) {
//			printf("p's l  == v\n");




/*			if ((*v)->r != NULL)
				printf("WTF r != NULL r = %p p = %p p->l = %p (*v) = %p \n",(*v)->r,(*v)->p,(*v)->p->l,(*v));
                       
			printf(" r->data = %d p->data = %d (*v)->data = %d \n",(*v)->r->data,(*v)->p->data, (*v)->data);
	printf("v->r->p->data = %d v->p->l->data = %d\n",(*v)->r->p->data,(*v)->p->l->data);
	printf("v->data = %d v->p->data = %d v->r->data = %d\n",(*v)->data,(*v)->p->data,(*v)->r->data);
	printf("v->height = %ld v->r->height = %ld v->p->height = %ld \n",(*v)->height,(*v)->r->height,(*v)->p->height);
*/
			(((*v)->p)->l) =  ((*v)->r);
//			printf(" *v is %p \n",*v);
			/*
			printf("after (((*v)->p)->l) = ((*v)->r) is executed\n");
			if ((*v)->r == NULL)
				printf("WTF r == NULL r = %p p = %p p->l = %p (*v) = %p \n",(*v)->r,(*v)->p,(*v)->p->l,(*v));
	printf("v->l->p->data = %d v->p->l->data = %d\n",(*v)->l->p->data,(*v)->p->l->data);
	printf("v->data = %d v->p->data = %d v->l->data = %d\n",(*v)->data,(*v)->p->data,(*v)->l->data);
	printf("v->height = %ld v->l->height = %ld v->p->height = %ld \n",(*v)->height,(*v)->l->height,(*v)->p->height);
*/
		} else {
			printf("error case \n");
		}
	}


	struct vertex  *tmp = (*v)->r->l;
	(*v)->r->l = (*v);
	(*v)->r->p = (*v)->p;
	(*v)->p = (*v)->r;
	(*v)->r = tmp;
	if (tmp != NULL)
		tmp->p = (*v);
	update_height(*v);
	(*v) = (*v)->p;
	update_height(*v);
}

static void
insert_fixup(struct vertex *new_vertex)
{
	while ((new_vertex->p != NULL)
	       && ((new_vertex->height + 1) > new_vertex->p->height)) {
		update_height(new_vertex->p);
		new_vertex = new_vertex->p;
		if (balance_factor(new_vertex) == 2) {
			if (balance_factor(new_vertex->l) == -1) {
				struct vertex* l = new_vertex->l;
				left_rotate(&(l));
			}
			right_rotate(&new_vertex);
			return;
		} else if (balance_factor(new_vertex) == -2) {
			if (balance_factor(new_vertex->r) == 1) {
				struct vertex* r = new_vertex->r;
				right_rotate(&(r));
			}
			left_rotate(&new_vertex);
			return;
		}
	}
}
void
insert(struct vertex **tree, int data)
{
	struct vertex  *new_vertex = malloc(sizeof(struct vertex));
	new_vertex->data = data;
	new_vertex->height = 0;
	new_vertex->l = NULL;
	new_vertex->r = NULL;
	new_vertex->p = NULL;

	if (tree == NULL){
	   free(new_vertex);
		return;
	}else if (*tree == NULL) {
		*tree = new_vertex;
		return;
	}
	struct vertex  *root = *tree;
	while (1) {
		if (root->data < data) {
			if (root->r != NULL)
				root = root->r;
			else {
				root->r = new_vertex;
				new_vertex->p = root;
				break;
			}
		} else {
			if (root->l != NULL)
				root = root->l;
			else {
				root->l = new_vertex;
				new_vertex->p = root;
				break;
			}
		}
	}
	insert_fixup(new_vertex);
	while ((*tree)->p != NULL) {
		(*tree) = (*tree)->p;
	}
}
void           *
find(struct vertex *v, int data)
{
	while (v != NULL && v->data != data)
		if (v->data < data)
			v = v->r;
		else
			v = v->l;

	return v;


}
static void
free_tree(struct vertex *root)
{
	if (root->l != NULL)
		free_tree(root->l);
	if (root->r != NULL)
		free_tree(root->r);

	free(root);
	return;
}
void
clear_tree(struct vertex **root)
{
	free_tree(*root);
	*root = NULL;
}
/*
 * void print_tree(struct vertex *root) { int           **arr =
 * malloc((root->height + 1) * sizeof(int *)); int i; for (i = root->height;
 * i >= 0; i--){ arr[i] = malloc( (1<<i) * sizeof(int) ); }
 * 
 * find_all_data(root,arr,0);
 * 
 * free(arr);
 * 
 * } static void find_all_data(struct vertex *root, int **arr, int col) {
 * 
 * 
 * 
 * } */
