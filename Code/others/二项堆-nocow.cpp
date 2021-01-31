//二项堆的介绍参考<<数据结构>>Ellis Horowitz等著，李建中等译（c语言版）P289
/*
* 2008/07/08 By YaoJianming
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct element {
	int key;
};
struct bheap {
	element data;
	bheap *child;
	bheap *left_link;
	bheap *right_link;
	int degree;
};
#define TREELEN 8
void join_min_trees(bheap *&a, bheap *b)
{
	if(a->data.key < b->data.key) {
		if(a->child == NULL) {
			a->right_link = a->left_link = a;
			b->right_link = b->left_link = b;
		} else {
			bheap *temp = a->child->left_link;
			a->child->left_link = b;
			b->right_link = a->child;
			b->left_link = temp;
			temp->right_link = b;
		}
		a->child = b;
		a->degree++;
	} else {
		if(b->child == NULL) {
			a->right_link = a->left_link = a;
			b->right_link = b->left_link = b;
		} else {
			bheap *temp = b->child->left_link;
			b->child->left_link = a;
			a->right_link = b->child;
			a->left_link = temp;
			temp->right_link = a;
		}
		b->child = a;
		b->degree++;
		a = b;
	}
}
element del(bheap *&a)
{
	element temp = a->data;
	bheap *tree[TREELEN];
	for(int i=0; i<TREELEN; ++i) {
		tree[i] = NULL;
	}
	bheap *p1, *p2;
	if(a->left_link != a) {
		p1 = a->left_link;
		p1->right_link = a->right_link;
		a->right_link->left_link = p1;
	}
	p2 = a->child;
	bheap *m1 = p1;
	bheap *m2 = p2;
	do {
		if(m1 == NULL) break;
//		  printf("%d\n", m1->data.key);
		int degree;
		bheap *w = m1->right_link;
		for(degree=m1->degree; tree[degree]; ++degree) {
			join_min_trees(m1, tree[degree]);
			tree[degree] = NULL;
		}
		tree[degree] = m1;
		m1 = w;
	} while (m1 != p1);
	do {
		if(m2 == NULL) break;
//		  printf("%d\n", m2->data.key);
		int degree;
		bheap *w = m2->right_link;
		for(degree=m2->degree; tree[degree]; ++degree) {
			join_min_trees(m2, tree[degree]);
			tree[degree] = NULL;
		}
		tree[degree] = m2;
		m2 = w;
	} while (m2 != p2);
	int k = 0;
	for(int i=0; i<TREELEN; ++i) {
		if(tree[i] == NULL) continue;
		k++;
		if(k == 1) {
			tree[i]->right_link = tree[i]->left_link = tree[i];
			a = tree[i];
		} else if(k > 1) {
			bheap *temp = a->right_link;
			a->right_link = tree[i];
			temp->left_link = tree[i];
			tree[i]->right_link = temp;
			tree[i]->left_link = a;
			if(a->data.key > tree[i]->data.key) a = tree[i];
		}
	}
	return temp;
}
void insert(bheap *&a, bheap *b)
{
	if(a == NULL) {
		a = b;
		return;
	}
	bheap *temp = a->right_link;
	a->right_link = b;
	b->right_link = temp;
	temp->left_link = b;
	b->left_link = a;
	if(a->data.key > b->data.key) {
		a = b;
	}
}
void merge(bheap *&a, bheap *b)
{
	if(a == NULL) {
		a = b;
		return;
	}
	bheap *p1 = a->right_link;
	bheap *p2 = b->left_link;
	a->right_link = b;
	b->left_link = a;
	p1->left_link = p2;
	p2->right_link = p1;
	if(a->data.key > b->data.key) {
		a = b;
	}
}
void traverse(bheap *a)
{
	bheap *p = a;
	do {
		printf("%d %d\n", p->data.key, p->degree);
		if (p->child != NULL) {
			traverse(p->child);
		}
		p = p->right_link;
	} while(p != a);
}
int main()
{
	bheap *a = NULL;
	for(int i=1; i<=8; ++i) {
		bheap *p = new bheap;
		p->right_link = p->left_link = p;
		p->child = NULL;
		p->data.key = i;
		p->degree = 0;
		insert(a, p);
	}
	bheap *b = NULL;
	for(int i=9; i<=17; ++i) {
		bheap *p = new bheap;
		p->right_link = p->left_link = p;
		p->child = NULL;
		p->data.key = i;
		p->degree = 0;
		insert(b, p);
	}
	del(a);
	del(b);
	merge(a, b);
	traverse(a);
}


