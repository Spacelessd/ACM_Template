#include<cstdio>
#include<algorithm>
#include<vector>
#define NMax 30000
#define INF 100000000
using namespace std;
struct edge{
	int e;
	edge *next;
}epool[NMax+NMax],*E[NMax],*etop=epool;
char Map[NMax][10];
struct rec{
	int a[2][2],b[2][2];
	static rec ini(char *c){
		rec r;
		for (int i=0;i<2;i++)
			for (int j=0;j<2;j++){
				if (c[i]!='#' && c[j]!='#')
					r.a[i][j]=1+(i!=j);
				else r.a[i][j]=-INF;
			}
		for (int i=0;i<2;i++)
			for (int j=0;j<2;j++){
				if (c[j]=='#')r.b[i][j]=0;
				else r.b[i][j]=(c[1-j]!='#')+1;
			}
		return r;
	}
	static rec empty(){
		rec r;
		for (int i=0;i<2;i++)for (int j=0;j<2;j++){
			r.b[i][j]=0;
			r.a[i][j]=(i==j?0:-INF);
		}
		return r;
	}
	rec operator+(const rec &c)const{
		rec r;
		for (int i=0;i<2;i++)
			for (int j=0;j<2;j++){
				int s=a[i][0]+c.a[0][j];
				int t=a[i][1]+c.a[1][j];
				if (s<t)s=t;
				if (s<-INF)s=-INF;
				r.a[i][j]=s;
			}
		for (int j=0;j<2;j++){
			int s=b[0][j];
			for (int k=0;k<2;k++){
				int t=a[j][k]+c.b[0][k];
				if (s<t)s=t;
			}
			r.b[0][j]=s;
			s=c.b[1][j];
			for (int k=0;k<2;k++){
				int t=b[1][k]+c.a[k][j];
				if (s<t)s=t;
			}
			r.b[1][j]=s;
		}
		return r;
	}
	rec reverse()const{
		rec r;
		for (int i=0;i<2;i++)
			for (int j=0;j<2;j++)
				r.a[i][j]=a[j][i],
				r.b[1-i][j]=b[i][j];
		return r;
	}
};
int N;
int sz[NMax],sz2[NMax],fa[NMax],lc[NMax],rc[NMax],tf[NMax],spc[NMax],depth[NMax],head[NMax],dep2[NMax];
rec R[NMax],S[NMax];
void update(int a){
	S[a]=R[a];
	if (lc[a]!=-1)S[a]=S[a]+S[lc[a]];
	if (rc[a]!=-1)S[a]=S[rc[a]]+S[a];
}
int build(int a,int s,int he,int de){
	if (!s)return -1;
	int u=sz2[a],k=a;
	while (u+u<s){
		k=spc[k];
		u+=sz2[k];
	}
	dep2[k]=de;head[k]=he;tf[k]=-1;
	if ((lc[k]=build(a,u-sz2[k],he,de+1))!=-1)tf[lc[k]]=k;
	if ((rc[k]=build(spc[k],s-u,he,de+1))!=-1)tf[rc[k]]=k;
	update(k);
	return k;
}
void bfs(){
	static int Q[NMax];
	for (int i=0;i<N;i++)depth[i]=-1;
	int bot=1;
	Q[0]=0;depth[0]=0;
	fa[0]=-1;
	for (int i=0;i<bot;i++){
		int x=Q[i];
		for (edge *p=E[x];p;p=p->next)if (p->e!=fa[x]){
			fa[p->e]=x;
			depth[Q[bot++]=p->e]=depth[x]+1;
		}
	}
	for (int i=bot-1;i>=0;i--){
		int x=Q[i];
		sz[x]=1;spc[x]=-1;
		for (edge *p=E[x];p;p=p->next)if (p->e!=fa[x]){
			sz[x]+=sz[p->e];
			if (spc[x]==-1 || sz[p->e]>sz[spc[x]])spc[x]=p->e;
		}
		sz2[x]=sz[x];
		if (spc[x]!=-1)sz2[x]-=sz[spc[x]];
	}
	for (int i=0;i<N;i++)if (fa[i]==-1 || spc[fa[i]]!=i)
		build(i,sz[i],i,0);
}
void Change(int a){
	R[a]=rec::ini(Map[a]);
	while (a!=-1){
		update(a);
		a=tf[a];
	}
}
int Ask(int x,int y){
	rec left=rec::empty(),right=rec::empty();
	while (head[x]!=head[y]){
		if (depth[head[x]]>depth[head[y]]){
			for (int b=rc[x],i=x;i!=-1;i=tf[i]){
				if (b==rc[i]){
					left=left+R[i];
					if (lc[i]!=-1)left=left+S[lc[i]];
				}
				b=i;
			}
			x=fa[head[x]];
		}else{
			for (int b=rc[y],i=y;i!=-1;i=tf[i]){
				if (b==rc[i]){
					right=right+R[i];
					if (lc[i]!=-1)right=right+S[lc[i]];
				}
				b=i;
			}
			y=fa[head[y]];
		}
	}
	int bx,by,flg=depth[x]<depth[y];
	if (flg)bx=lc[x],by=rc[y];
	else bx=rc[x],by=lc[y];
	while (x!=y){
		if (dep2[x]>dep2[y]){
			if (flg && bx==lc[x]){
				left=left+R[x];
				if (rc[x]!=-1)left=left+S[rc[x]].reverse();
			}else if (!flg && bx==rc[x]){
				left=left+R[x];
				if (lc[x]!=-1)left=left+S[lc[x]];
			}
			bx=x;
			x=tf[x];
		}else{
			if (flg && by==rc[y]){
				right=right+R[y];
				if (lc[y]!=-1)right=right+S[lc[y]];
			}else if (!flg && by==lc[y]){
				right=right+R[y];
				if (rc[y]!=-1)right=right+S[rc[y]].reverse();
			}
			by=y;
			y=tf[y];
		}
	}
	rec ret=left+R[x]+right.reverse();
	return max(ret.b[0][0],ret.b[0][1]);
}
int main()
{
	int Q;
	scanf("%d%d",&N,&Q);
	for (int i=0;i<N;i++)E[i]=NULL;
	for (int i=0;i<N-1;i++){
		int x,y;
		scanf("%d%d",&x,&y);x--;y--;
		etop->e=y;etop->next=E[x];E[x]=etop++;
		etop->e=x;etop->next=E[y];E[y]=etop++;
	}
	for (int i=0;i<N;i++){
		scanf("%s",Map[i]);
		R[i]=rec::ini(Map[i]);
	}
	bfs();
	while (Q--){
		char cmd[10];
		int x,y;
		scanf("%s",cmd);
		if (cmd[0]=='Q'){
			scanf("%d%d",&x,&y);x--;y--;
			printf("%d\n",Ask(x,y));
		}else{
			scanf("%d",&x);x--;
			scanf("%s",Map[x]);
			Change(x);
		}
	}
	return 0;
}


