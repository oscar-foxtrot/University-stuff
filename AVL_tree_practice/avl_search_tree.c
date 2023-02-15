#include <stdio.h>
#include <stdlib.h>

#define AVL 1 // replace 1 with 0 if you want a bit of practice with non-AVL trees

struct Tree
{
	struct Tree* left, * right;
	int elem;
};

void init_tree(struct Tree** tr)
{
	*tr = (struct Tree*)malloc(sizeof(struct Tree));
	(*tr)->left = (*tr)->right = NULL;
}

void add_elem(int b, struct Tree* tr)
{
	if (tr->elem < b)
		if (tr->right != NULL)
			add_elem(b, tr->right);
		else
		{
			tr->right = (struct Tree*)malloc(sizeof(struct Tree));
			tr->right->left = tr->right->right = NULL;
			tr->right->elem = b;
		}
	else if (tr->elem > b)
	{
		if (tr->left != NULL)
			add_elem(b, tr->left);
		else
		{
			tr->left = (struct Tree*)malloc(sizeof(struct Tree));
			tr->left->left = tr->left->right = NULL;
			tr->left->elem = b;
		}
	}
	return;
}

int height(struct Tree* tr)
{
	if (tr == NULL) return 0;
	if (tr->left == NULL && tr->right == NULL)
		return 1;
	else if (tr->left == NULL && tr->right != NULL)
		return 1 + height(tr->right);
	else if (tr->right == NULL)
		return 1 + height(tr->left);
	else
	{
		int l = height(tr->left);
		int r = height(tr->right);
		if (r >= l) return 1 + r;
		else return 1 + l;
	}
}

void balance_tree(struct Tree **tr)
{
	int hr = height((*tr)->right);
	int hl = height((*tr)->left);
	if (hr - hl == 2)
	{
		if (height((*tr)->right->left) <= height((*tr)->right->right)) //right right
		{
			struct Tree *tmp = (*tr);
			(*tr) = (*tr)->right;
			tmp->right = (*tr)->left;
			(*tr)->left = tmp;
		}
		else //right left
		{
			struct Tree *tmp1 = (*tr);
			struct Tree *tmp2 = (*tr)->right;
			(*tr) = (*tr)->right->left;
			tmp2->left = (*tr)->right;
			tmp1->right = (*tr)->left;
			(*tr)->right = tmp2;
			(*tr)->left = tmp1;
		}
	}
	else if (hl - hr == 2)
	{
		if (height((*tr)->left->right) <= height((*tr)->left->left)) //left left
		{
			struct Tree *tmp = (*tr);
			(*tr) = (*tr)->left;
			tmp->left = (*tr)->right;
			(*tr)->right = tmp;
		}
		else //left right
		{
			struct Tree *tmp1 = (*tr);
			struct Tree *tmp2 = (*tr)->left;
			(*tr) = (*tr)->left->right;
			tmp2->right = (*tr)->left;
			tmp1->left = (*tr)->right;
			(*tr)->left = tmp2;
			(*tr)->right = tmp1;
		}
	}
	if ((*tr)->right != NULL) balance_tree(&((*tr)->right));
	if ((*tr)->left != NULL) balance_tree(&((*tr)->left));
	return;
}

void print_tree(struct Tree* tr)
{
	if (tr->left != NULL) print_tree(tr->left);
	printf("%d ", tr->elem);
	if (tr->right != NULL) print_tree(tr->right);
}

void delete_tree(struct Tree** tr)
{
	if ((*tr)->right != NULL) delete_tree(&(*tr)->right);
	if ((*tr)->left != NULL) delete_tree(&(*tr)->left);
	free(*tr);
	*tr = NULL;
}

int main()
{
	int num;
	printf("AVL tree is initialized. Enter the values\n");
	printf("When you're done, just hit Ctrl+D\n");
	printf("Values in the nodes of the tree will be printed on the screen from left to right\nYour values: ");
	scanf("%d", &num);
	struct Tree* tree1;
	init_tree(&tree1);
	tree1->elem = num;
	if (!AVL)
		while (scanf("%d", &num) > 0)
			add_elem(num, tree1);
	else 
		while (scanf("%d", &num) > 0)
		{
			add_elem(num, tree1);
			balance_tree(&tree1);
		}
	print_tree(tree1);
	printf("\nHeight: %d\nHeight difference: %d\n", height(tree1), height(tree1->right) - height(tree1->left));
	delete_tree(&tree1);

	return 0;
}
