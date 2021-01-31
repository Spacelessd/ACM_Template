//0 ¡ü 1 ¡ý 2 ¡û 3 ¡ú  1:1+2 ©·  2:1+3©³  3:0+3©»  4:0+2 ©¿
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define maxn 105
#define N 40005
const int dx[]={-1,1,0,0},dy[]={0,0,-1,1};
int id[maxn][maxn][4],shot[maxn][maxn][2];
int judge[N],opp[N];
bool take[N];
char a[maxn][maxn],str[maxn];
int dfn[N],low[N],stack[N],num[N],instack[N],D,now,top;
struct Edge{
	#define Mx 40005
	int link[Mx],next[Mx],son[Mx],l;
	void clear(){l=0;memset(son,0,sizeof(son));}
	void addedge(int x,int y){
		link[++l]=y;next[l]=son[x];son[x]=l;
	}
};
Edge e1,e2;
inline int min(int x,int y){return x<y?x:y;}
void tarjan(int x){
	dfn[x]=low[x]=++D;stack[++top]=x;instack[x]=1;
	for (int p=e1.son[x];p;p=e1.next[p]){
		int j=e1.link[p];
		if (!dfn[j]) tarjan(j),low[x]=min(low[x],low[j]);
		else if (instack[j]) low[x]=min(low[x],dfn[j]);
	}
	if (low[x]==dfn[x]){
		int k;++now;
		do k=stack[top--],instack[k]=0,num[k]=now; while (k!=x);
	}
}
int f[N],in[N];
void toposort(int n){
	int h=0,t=0;
	for (int i=1;i<=n;++i) if (!in[i]) f[++t]=i;
	while (h<t){
		int i=f[++h]; if (take[i]) take[opp[i]]=0;
		for (int p=e2.son[i];p;p=e2.next[p]){
			int j=e2.link[p]; --in[j]; if (!take[i]) take[j]=0;
			if (!in[j]) f[++t]=j;
		}
	}
}
int main(){
	//freopen("tornjevi.in","r",stdin);
	//freopen("tornjevi.out","w",stdout);
	int n,m,i,j,k,tot=1;
	scanf("%d%d",&n,&m);e1.clear();e2.clear();
	memset(a,'#',sizeof(a));
	for (i=1;i<=n;++i){
		scanf("%s",str+1);
		for (j=1;j<=m;++j)
			a[i][j]=str[j];
		}
	for (i=1;i<=n;++i)
		for (j=1;j<=m;++j) if (a[i][j]=='T')
			for (k=0;k<4;++k) id[i][j][k]=++tot;
	for (i=1;i<=n;++i){
		int x=-1,y=-1;
		for (j=1;j<=m;++j)
			if (a[i][j]=='T'){
				if (x!=-1)judge[id[x][y][3]]=judge[id[i][j][2]]=-1,
						  judge[id[x][y][2]]=judge[id[i][j][3]]=1;
				else x=i,y=j;
				}
			else if (a[i][j]=='#') x=-1;
		}
	for (j=1;j<=m;++j){
		int x=-1,y=-1;
		for (i=1;i<=n;++i)
			if (a[i][j]=='T'){
				if (y!=-1)judge[id[x][y][1]]=judge[id[i][j][0]]=-1,
						  judge[id[x][y][0]]=judge[id[i][j][1]]=1;
				else x=i,y=j;
				}
			else if (a[i][j]=='#') y=-1;
		}
	for (i=1;i<=n;++i)
		for (j=1;j<=m;++j) if (a[i][j]=='T')
			for (k=0;k<4;++k) if (judge[id[i][j][k]]>=0)
				for (int x=i,y=j;a[x][y]!='#';x+=dx[k],y+=dy[k])
					if (a[x][y]=='n')
						if (shot[x][y][0]) shot[x][y][1]=id[i][j][k];
						else shot[x][y][0]=id[i][j][k];
	for (i=1;i<=n;++i)
		for (j=1;j<=m;++j) if (a[i][j]=='n')
			if (!shot[i][j][1]) judge[shot[i][j][0]]=1,judge[shot[i][j][0]^1]=-1;
			else {
			e1.addedge(shot[i][j][0]^1,shot[i][j][1]);
			e1.addedge(shot[i][j][1]^1,shot[i][j][0]);
			}
	memset(dfn,0,sizeof(dfn));
	for (i=2;i<=tot;++i) if (!judge[i] && !dfn[i]) tarjan(i);
	for (i=2;i<=tot;++i) if (!judge[i])
		for (int p=e1.son[i];p;p=e1.next[p]){
			int j=e1.link[p];
			if (num[i]!=num[j]) e2.addedge(num[j],num[i]),++in[num[i]];
			}
	memset(take,1,sizeof(take));
	for (i=1;i<=n;++i)
		for (j=1;j<=m;++j) if (a[i][j]=='T'){
			if (!judge[id[i][j][0]] && num[id[i][j][0]]!=num[id[i][j][1]])
				opp[num[id[i][j][0]]]=num[id[i][j][1]],
				opp[num[id[i][j][1]]]=num[id[i][j][0]];
			if (!judge[id[i][j][2]] && num[id[i][j][2]]!=num[id[i][j][3]])
				opp[num[id[i][j][2]]]=num[id[i][j][3]],
				opp[num[id[i][j][3]]]=num[id[i][j][2]];
			for (int k=0;k<4;++k)
				if (judge[id[i][j][k]]<0) take[num[id[i][j][k]]]=0;
			}
	toposort(now);
	for (i=1;i<=n;++i){
		for (j=1;j<=m;++j)
			if (a[i][j]=='T'){
				int x=0;
				if (judge[id[i][j][0]]>0 || !judge[id[i][j][0]]
					&& take[num[id[i][j][0]]]) x+=1; else x+=2;
				if (judge[id[i][j][2]]>0 || !judge[id[i][j][2]]
					&& take[num[id[i][j][2]]]) x+=4; else x+=8;
				if (x==6) x=1; else if (x==10) x=2;
				else if (x==9) x=3; else if (x==5) x=4;
				printf("%d",x);
				}
			else printf("%c",a[i][j]);
		printf("\n");
		}
	system("pause");
	return 0;
}






