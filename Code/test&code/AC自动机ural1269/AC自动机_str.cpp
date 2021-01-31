#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<time.h>
#include<iostream>
using namespace std;
#define CH 256
#define maxlen 500010
#define maxn 1000010
#define root 1
#define oo (1<<30)
class Trie{
	public:
	int c[CH],fail,flag,len;
	string str;
	void clear(){
		memset(c,0,sizeof(c));flag=0;str="";
	}
};
Trie node[maxlen];
int q[maxlen];
char a[maxn];
int n,m,i,len,ans;
inline int get(char ch){
	return ch;
}
void insert(char *str){
	int x=root,i,son;
	string tmp="";
	for (i=0;str[i];++i){
		son=get(str[i]);tmp=tmp+str[i];
		if (!node[x].c[son])x=node[x].c[son]=++len,node[x].clear();
			else x=node[x].c[son];
		node[x].str=tmp;
	}
	node[x].flag++;node[x].len=i;
}
void bfs(){
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
			else node[x].c[ch]=node[node[x].fail].c[ch];
	}
}
void find(char *str){
	int ch,i,x=root,y,len=strlen(str);
	for (i=0;i<len;i++){
		ch=get(str[i]);
		x=node[x].c[ch];y=x;
		cout<<str[i]<<" "<<node[x].str<<endl;
		while (y/*&&node[y].flag>=0*/){
              if (node[y].flag>0&&i-node[y].len+1<ans)ans=i-node[y].len+1;
              //node[y].flag=-1;
              y=node[y].fail;
              }
	}
}
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	for (i=0;i<CH;i++)node[0].c[i]=root;
	ans=0;len=root;node[root].clear();
    scanf("%d",&n);gets(a);
    for (i=1;i<=n;i++)gets(a),insert(a);
    bfs();ans=oo;
    scanf("%d",&m);gets(a);
    for (i=1;i<=m;i++){
        gets(a);find(a);
        if (ans<oo){
                    printf("%d %d\n",i,ans);
                    break;
                    }
        }
    if (ans==oo)printf("Passed\n");
	system("pause");
	//for(;;);
	return 0;
}









