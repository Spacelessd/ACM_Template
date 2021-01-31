#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define CH 26
#define maxlen 500005
#define maxn 1000005
#define root 1
struct Trie{
	int c[CH],fail,flag;
	void clear(){
		memset(c,0,sizeof(c));flag=0;
	}
};
Trie node[maxlen];
int q[maxlen];
char a[maxn];
int n,i,len,ans,t;
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
	int l=1,r=1,ch,fail,j; q[1]=root;node[root].fail=0;
	for (ch=0;ch<CH;++ch)if (!node[root].c[ch])node[root].c[ch]=root;
	while (l<=r){
		int x=q[l++];
		for (ch=0;ch<CH;++ch){
			j=node[x].c[ch];
			if (j!=root&&j!=0){
				q[++r]=j;
				node[j].fail=node[node[x].fail].c[ch];
			}
			else node[x].c[ch]=node[node[x].fail].c[ch];
		}
	}
}
void find(char *str){
	int ch,i,x=root,y,len=strlen(str);
	for (i=0;i<len;++i){
		ch=get(str[i]); x=node[x].c[ch]; y=x;
		while (y&&node[y].flag>=0){ans+=node[y].flag;node[y].flag=-1;y=node[y].fail;}
	}
}
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	for (i=0;i<CH;i++)node[0].c[i]=root;
	scanf("%d",&t);gets(a);
	while (t--){
		ans=0;len=root;node[root].clear();
		scanf("%d",&n);gets(a);
		for (i=1;i<=n;i++)gets(a),insert(a);
		gets(a);
		//printf("%d\n",node[root].c[0]);
		bfs();
		//printf("%d\n",node[root].c[0]);
		find(a);
		printf("%d\n",ans);
	}
	//system("pause");
	//for(;;);
	return 0;
}


