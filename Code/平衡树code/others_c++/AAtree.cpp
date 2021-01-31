#include<cstdio>
#include<iostream>
using namespace std;
struct AAtree
{
//private:
	struct AANode
	{
		int data;
		AANode *left;
		AANode *right;
		int level;
		AANode(const int &thedata, AANode *lt, AANode *rt, int lv = 1)
			: data(thedata), left(lt), right(rt), level(lv) {}
	};
	AANode *root;
	void insert(const int &x, AANode*& t);
	void remove(const int &x, AANode*& t);
	bool find(const int &x, AANode *t) const;
	void makeEmpty(AANode*& t);
	void LL(AANode*& t);
	void RR(AANode*& t);
public:
	AAtree(AANode *t = NULL)
	{
		root = t;
	}
	~AAtree()
	{
		makeEmpty(root);
		root = NULL;
	}
	bool find(const int &x) const
	{
		return find(x, root);
	}
	void insert(const int &x)
	{
		insert(x, root);
	}
	void remove(const int &x)
	{
		remove(x, root);
	}
};
bool AAtree::find(const int &x, AANode *t) const
{
	if(t == NULL) return false;
	else if(t->data < x) return find(x, t->left);
	else if(t->data > x) return find(x, t->right);
	else return true;
}
void AAtree::makeEmpty(AANode*& t)
{
	if(t != NULL)
	{
		makeEmpty(t->left);
		makeEmpty(t->right);
		delete t;
	}
}
void  AAtree::LL(AANode*& t)
{
	if(t->left != NULL && t->left->level == t->level)
	{
		AANode *tl = t->left;
		t->left = tl->left;
		tl->right = t;
		t = tl;
	}
}
void AAtree::RR(AANode*& t)
{
	if(t->right != NULL && t->right->right != NULL && t->right->right->level == t->level)
	{
		AANode *tr = t->right;
		t->right = tr->left;
		tr->left = t;
		t = tr;
		++t->level;
	}
}
void AAtree::insert(const int &x, AANode*& t)
{
	if(t == NULL)
		t = new AANode(x, NULL, NULL);
	else if(x < t->data)
		insert(x, t->left);
	else if(x > t->data)
		insert(x, t->right);
	else return;
	//LL(t);
	//RR(t);
}
void AAtree::remove(const int &x, AANode*& t)
{
	if(t == NULL) return;
	else if(x < t->data) remove(x, t->left);
	else if(x > t->data) remove(x, t->right);
	else if(t->left != NULL && t->right != NULL)
	{
		AANode *tmp = t->right;
		while(tmp->left != NULL) tmp = tmp->left;
		t->data = tmp->data;
		remove(t->data, t->right);
	}
	else
	{
		AANode *oldNode = t;
		if(t->left != NULL) t = t->left;
		else t = t->right;
		delete oldNode;
		return ;
	}
	LL(t);
	if(t->right != NULL) LL(t->right);
	if(t->right != NULL && t->right->right != NULL) LL(t->right->right);
	RR(t);
	if(t->right != NULL) RR(t->right);
}
AAtree a;
int main()
{
	int t1 = clock();
	a.makeEmpty(a.root);
	for (int i = 1; i <= 10000000; ++i){
		//printf("%d\n",i);
		int x=rand();
		if (!a.find(x))a.insert(x);
	}
	printf("%d\n", clock() - t1);
	system("pause");
}


