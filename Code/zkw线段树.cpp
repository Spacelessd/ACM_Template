#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
void read(int &x)
{
	x = 0; char ch; bool y = 0;
	for (ch = getchar(); ch < '0' || ch > '9'; ch = getchar()) if (ch == '-') y = 1;
	for (; ch >= '0' && ch <= '9'; x = x * 10 + ch - 48, ch = getchar());
	if (y) x = -x;
}
inline int abs(int a){return a > 0 ? a : -a;}
inline int max(int a, int b){return a > b ? a : b;}
struct node{
	int m;
};
struct tree{
	#define oo (1<<30)
	node *a; int M,top;
	void make(int len){
		for (M=1;M-2<len;M<<=1);
		a=new node[M*2];memset(a,0,sizeof(node)*M*2);
	}
	tree(int len=5){make(len);}
	void build(){
		for (int i=M-1;i;--i)
			a[i].m=max(a[i*2].m,a[i*2+1].m);
	}
	void change(int x,int key){
		x+=M;a[x].m=key;
		for (x>>=1;x;x>>=1)a[x].m=max(a[x*2].m,a[x*2+1].m);
	}
	int query(int l,int r){
		l=l+M-1;r=r+M+1;int ans=-oo,tmp;
		for (;l^r^1;l>>=1,r>>=1){
			if (~l&1)ans=max(ans,a[l^1].m);
			if (r&1)ans=max(ans,a[r^1].m);
		}
		return ans;
	}
	#undef oo
};
tree T;
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	int test, Case, n, m, q, x, y, first = 1;
	read(test);
	for (Case = 0; Case < test; ++Case)
	{
		if (first) first = 0;
		else printf("\n");
		printf("Testcase %d:\n", Case);
		read(n), read(m);
		T.make(n+1);
		for (int i=1;i<=n;++i)read(T.a[i+T.M].m);
		T.build();
		read(q);
		while (q--)
		{
			char ch = getchar();
			while (ch != 'A' && ch != 'B' && ch != 'C') ch = getchar();
			read(x);
			if (ch != 'A') read(y);
			if (ch == 'A') m += x;
			if (ch == 'B') T.change(x + 1, y);
			if (ch == 'C') printf("%d\n", abs(m - T.query(x + 1, y + 1)));
		}
	}
	system("pause");for (;;);
	return 0;
}


