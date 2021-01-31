#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>

using namespace std;

struct  Node
{
	int key, value, size, l, r;
}treap[500005];
int N, M, root = 0, MIN, MAX, tot = 0, key[500005];

void 	Renew(int x)
{
	treap[x].size = treap[treap[x].l].size + treap[treap[x].r].size + 1;
}

void	Right_Rotate(int &x)
{
	int k = treap[x].l;
	treap[x].l = treap[k].r;
	treap[k].r = x;
	Renew(x); Renew(k);
	x = k;
}

void	Left_Rotate(int &x)
{
	int k = treap[x].r;
	treap[x].r = treap[k].l;
	treap[k].l = x;
	Renew(x); Renew(k);
	x = k;
}

void	Insert(int &x, int y, int z)
{
	if (x == 0)
	{
		x = z;
		treap[x].key = y;
		treap[x].value = rand();
		treap[x].size = 1;
		treap[x].l = 0; 
		treap[x].r = 0;
		return;
	}
	if (y < treap[x].key)
	{
		Insert(treap[x].l, y, z);
		if (treap[treap[x].l].value < treap[x].value) Right_Rotate(x);
	} else
	{
		Insert(treap[x].r, y, z);
		if (treap[treap[x].r].value < treap[x].value) Left_Rotate(x);
	}
	Renew(x);
}
double t1;
int main()
{	
	srand(time(0));
	treap[0].value = 1000000000;
	t1=clock();
	for (int i=1;i<=500000;i++) key[i]=rand()*32768+rand();
	for (int i=1;i<=500000;i++) Insert(root, key[i], i);
	printf("%.4f\n",(clock()-t1)/CLOCKS_PER_SEC);
	system("pause");
	return 0;
}


