#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<map>
#define CH 259
#define maxlen 102410
#define maxn 1000010
#define root 1
#define oo (1<<30)
class Trie{
	public:
	int fail,flag,len;
	std::map<int,int> c;
	void clear(){
		c.clear();flag=0;
	}
};
Trie node[maxlen];
int q[maxlen];
char a[maxn];
int n,m,i,len,ans;
inline int get(char ch){
	return ch+2;
}
void insert(char *str){
	int x=root,i,son;
	for (i=0;str[i];++i){
		son=get(str[i]);
		if (!node[x].c.count(son))x=node[x].c[son]=++len,node[x].clear();
			else x=node[x].c[son];
	}
	node[x].flag++;node[x].len=i;
}
void bfs(){
    std::map<int,int>::iterator mm;
	int l=1,r=1,ch,fail,j; q[1]=root;node[root].fail=0;
	while (l<=r){
		int x=q[l++];
		for (mm=node[x].c.begin();mm!=node[x].c.end();++mm)
			{
                ch=mm->first;j=mm->second;
				fail=node[x].fail;
				while (fail&&!node[fail].c.count(ch))fail=node[fail].fail;
				node[j].fail=node[fail].c[ch];
				q[++r]=j;
			}
	}
}
void find(char *str){
	int ch,i,x=root,y,len=strlen(str);
	for (i=0;i<len;i++){
		ch=get(str[i]);
		while (x&&!node[x].c.count(ch))x=node[x].fail;
		x=node[x].c[ch];y=x;
		while (y&&node[y].flag>=0){
              if (node[y].flag>0&&i-node[y].len+2<ans)ans=i-node[y].len+2;
              node[y].flag=-1;
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









