#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define CH 26
#define N 1000005
#define root 1
struct Trie{
	int c[CH],fail,flag;
	void clear(){
		memset(c,0,sizeof(c));flag=0;
	}
};
Trie node[N];
char a[N]; int len,ans;
inline int get(char ch){return ch-'a';}
void insert(char *str){
	int x=root,i,son;
	for (i=0;str[i];++i){
		son=get(str[i]);
		if (!node[x].c[son])x=node[x].c[son]=++len,node[x].clear();
			else x=node[x].c[son];
	}
	++node[x].flag;
}
void bfs(){
	static int q[N];
	int l=1,r=1,ch,fail,j; q[1]=root;node[root].fail=0;
	while (l<=r){
		int x=q[l++];
		for (ch=0;ch<CH;++ch)
			if (j=node[x].c[ch]){
				fail=node[x].fail;
				while (fail&&!node[fail].c[ch])fail=node[fail].fail;
				node[j].fail=node[fail].c[ch];
				q[++r]=j;
			}
	}
}
void find(char *str){
	int ch,i,x=root,y,len=strlen(str);
	for (i=0;i<len;++i){
		ch=get(str[i]);
		while (x&&!node[x].c[ch])x=node[x].fail;
		x=node[x].c[ch];y=x;
		while (y&&node[y].flag>=0){ans+=node[y].flag;node[y].flag=-1;y=node[y].fail;}
	}
}
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	for (int i=0;i<CH;++i)node[0].c[i]=root;
	int T;scanf("%d",&T);gets(a);
	while (T--){
		ans=0;len=root;node[root].clear();
		int n;scanf("%d",&n);gets(a);
		for (int i=1;i<=n;++i)gets(a),insert(a);
		gets(a); bfs(); find(a);
		printf("%d\n",ans);
	}
	system("pause");for(;;);
	return 0;
}


