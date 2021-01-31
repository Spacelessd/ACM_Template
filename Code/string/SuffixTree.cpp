#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define ll long long
#define N 2500005
#define CH 28
struct Node{
	int s,dep,trans,son[CH];
	Node(){}
	Node (int _s,int _dep,int _trans):s(_s),dep(_dep),trans(_trans){
		memset(son,0,sizeof(son));
	}
	int& operator [](int x){return son[x];}
};
#define P 3000007
int v[P],next[P],l,ans;ll key[P];
void insert(ll x){
	int x1=x%P,exist=0;
	for (int p=v[x1];p;p=next[p])if (key[p]==x)exist=1;
	if (!exist){
		++ans;++l;key[l]=x;next[l]=v[x1];v[x1]=l;
	}
}
int a[N];
struct SuffixTree{
	Node T[N];int node,first,last,tot;
	int Newnode(int s,int d,int trans){
		T[++tot]=Node(s,d,trans);
		return tot;
	}
	void Find(int &node,int first,int end){
		for (;;){
			int x=T[node][a[first+T[node].dep]];
			if (x&&T[x].dep+first-1<=end)node=x;
			else break;
		}
	}
	void Add_New_Letter(int ){
		
	}
	void Build(int n){
		tot=-1;Newnode(0,0,0);
		for (int i=1;i<=n;++i)Add_New_Letter(i,a[i]);
	}
	void print(int x,int top){
		bool flag=0;
		for (int i=0;i<CH;++i)
			if (T[x].son[i]!=NULL){
				int top1=top;flag=1;
				for (int j=T[x].son[i]->start;j<=T[x].son[i]->end;++j)Sprint[++top1]=a[j];Sprint[++top1]=' ';
				print(T[x].son[i]->link,top1);
			}
		if (!flag){
			for (int i=1;i<=top;++i)printf("%c",Sprint[i]);printf("\n");
		}
	}
};
SuffixTree T;
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	int len;scanf("%s",str);len=strlen(str);
	for (int i=0;i<=len;++i)a[i]=str[i];
	T.build(len);
	system("pause");for (;;);
	return 0;
}


