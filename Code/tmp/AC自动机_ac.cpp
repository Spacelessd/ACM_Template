#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define CH 26
#define maxlen 500010
#define maxn 1000010
class Trie{
	public:
	int c[CH],fail,flag;
	void clear(){
		memset(c,0,sizeof(c));
		fail=0;flag=0;
	}
};
Trie node[maxlen];
int q[maxlen];
char a[maxn];
int n,i,len,ans,t;
inline int get(char ch){
	return ch-'a';
}
void insert(char *str){
	int x=0,i,son;
	for (i=0;str[i];++i){
		son=get(str[i]);
		if (!node[x].c[son])x=node[x].c[son]=++len,node[x].clear();
			else x=node[x].c[son];
	}
	node[x].flag++;
}
void bfs(){
	int l=1,r=1,ch,fail; q[1]=0;
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
void find(char *str){
	int ch,i,x=0,y,son,len=strlen(str);
	for (i=0;i<len;i++){
		ch=get(str[i]);
		while (x&&!node[x].c[ch])x=node[x].fail;
		x=node[x].c[ch];
		y=x;
		while (y){ans+=node[y].flag;node[y].flag=0;y=node[y].fail;}
	}
}
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	scanf("%d",&t);gets(a);
	while (t--){
          ans=0;len=0;node[0].clear();
	      scanf("%d",&n);gets(a);
	      for (i=1;i<=n;i++)gets(a),insert(a);
	      gets(a);
	      bfs();
	      find(a);
	      printf("%d\n",ans);
          }
	//system("pause");
	//for(;;);
	return 0;
}









