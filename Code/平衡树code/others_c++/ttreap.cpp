#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>

using namespace std;

class tTreap
{
	private:
		class tNode
		{
			public:
				tNode *left,*right;
				int v,fix;
				tNode(int tv): v(tv),left(0),right(0)
				{
					fix=rand()*32768+rand();
				}
		};
		tNode *root;
		int R;
		void rot_r(tNode *&P)
		{
			tNode *Q=P->left;
			P->left=Q->right;
			Q->right=P;
			P=Q;
		}
		void rot_l(tNode *&P)
		{
			tNode *Q=P->right;
			P->right=Q->left;
			Q->left=P;
			P=Q;
		}
		void _ins(tNode *&P,int v)
		{
			if (!P)
				P=new tNode(v);
			else if (v<P->v)
			{
				_ins(P->left,v);
				if (P->left->fix < P->fix)
					rot_r(P);
			}
			else
			{
				_ins(P->right,v);
				if (P->right->fix < P->fix)
					rot_l(P);
			}
		}
		void _delete_max(tNode *&P)
		{
			if (P->right)
				_delete_max(P->right);
			else
			{
				R=P->v;
				tNode *T=P;
				P=P->left;
				delete T;
			}
		}
		void _delete_min(tNode *&P)
		{
			if (P->left)
				_delete_min(P->left);
			else
			{
				R=P->v;
				tNode *T=P;
				P=P->right;
				delete T;
			}
		}
	public:
		tTreap():root(0){}
		void ins(int v){_ins(root,v);}
		int delete_max() {_delete_max(root);return R;}
		int delete_min() {_delete_min(root);return R;}
};
 tTreap Treap;
int n,i,x,sigma=0;
double t1;
int maxn=500000;
int main()
{
	printf("start\n");
	t1=clock();
	for (i=1;i<=maxn;i++) Treap.ins(rand()*32768+rand());
	//a.print(a.root);
	/*a.calc(a.root,1);
	for (i=1;deep[i];i++){
		sigma+=deep[i];
		printf("%d:%d\n",i,deep[i]);
	}
	printf("ave=%.5f\n",double(sumdep)/double(maxn));
	printf("%d\n",sigma);*/
	printf("%.4f\n",(clock()-t1)/CLOCKS_PER_SEC);
	system("pause");
}
