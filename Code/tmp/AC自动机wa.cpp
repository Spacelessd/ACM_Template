#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define CH 26
#define maxn 100010
class Trie{
	public:
	int c[CH];
	int fail;
	bool flag;
	Trie(){
		memset(c,0,sizeof(c));
		fail=0;flag=0;
	}
};
Trie node[maxn];
int q[maxn];
char a[maxn],b[maxn];
int n,i,len=0;
int ans=0;
inline int get(char ch){
	return ch-'a';
}
void insert(char *str){
	int x=0,i,son;
	for (i=0;str[i];++i){
		son=get(str[i]);
		if (!node[x].c[son])x=node[x].c[son]=++len;
			else x=node[x].c[son];
	}
	node[x].flag=1;
}
void bfs(){
	int l=1,r=1,ch,fail;
	q[1]=0;
	while (l<=r){
		int x=q[l++];
		for (ch=0;ch<CH;++ch)
			if (node[x].c[ch]){
				q[++r]=node[x].c[ch];
				fail=node[x].fail;
				while (fail&&!node[fail].c[ch])fail=node[fail].fail;
				if (x)node[q[r]].fail=node[fail].c[ch];
					else node[q[r]].fail=0;
			}
	}
}
void Find(char *str){
	int ch,i,x=0,son;
	for (i=0;str[i];){
		son=node[x].c[get(str[i])];
		if (son){
			x=son;++i;
			if (node[x].flag)ans++;
		}else {
			if (!x)++i;
			x=node[x].fail;
		}
	}
}
int main()
{
	freopen("1.in","r",stdin);
	//freopen(".out","w",stdout);
	scanf("%d",&n);gets(a);
	for (i=1;i<=n;i++)gets(a),insert(a);
	gets(b);
	bfs();
	Find(b);
	printf("%d\n",ans);
	system("pause");
	for(;;);
	return 0;
}









