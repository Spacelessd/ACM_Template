#include<cstdio>
#include<algorithm>
#define NMax 30000
#define INF 100000000
using namespace std;
struct edge{
	int e;
	edge *next;
}epool[NMax+NMax],*E[NMax],*etop=epool;
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
				if (c[j]=='#')r.b[i][j]=-INF;
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
	bool operator==(const rec &c){
		for (int i=0;i<2;i++)
			for (int j=0;j<2;j++){
				if (a[i][j]!=c.a[i][j] && a[i][j]>-10000 && c.a[i][j]>-10000)return 0;
				if (b[i][j]!=c.b[i][j] && b[i][j]>-10000 && c.b[i][j]>-10000)return 0;
			}
		return 1;
	}
};
int N,fa[NMax],depth[NMax],head[NMax],sz[NMax];
int L;
rec R[NMax],su[NMax];
char Map[NMax][10];
void update(int a){
	if (head[a]==a)su[a]=R[a];
	else su[a]=R[a]+su[fa[a]];
	for (edge *p=E[a];p && head[p->e]==head[a];p=p->next)if (p->e!=fa[a])
		update(p->e);
}
void dfs(){
	static pair<int,edge*> Q[NMax];
	for (int i=0;i<N;i++)fa[i]=-1;
	int top=1;
	Q[0]=make_pair(0,E[0]);depth[0]=0;
	sz[head[0]=0]=1;
	while (top){
		int x=Q[top-1].first;
		edge *p=Q[top-1].second;
		if (!p){
			top--;
		}else{
			Q[top-1].second=p->next;
			if (p->e!=fa[x]){
				if (sz[head[x]]<L){
					sz[head[p->e]=head[x]]++;
				}else sz[head[p->e]=p->e]=1;
				fa[p->e]=x;
				depth[p->e]=depth[x]+1;
				Q[top++]=make_pair(p->e,E[p->e]);
			}
		}
	}
	for (int i=0;i<N;i++)if (head[i]==i)
		update(i);
}
int Ask(int x,int y){
	rec left=rec::empty(),right=rec::empty();
	while (head[x]!=head[y]){
		if (depth[head[x]]>depth[head[y]]){
			left=left+su[x];
			x=fa[head[x]];
		}else{
			right=su[y].reverse()+right;
			y=fa[head[y]];
		}
	}
	while (x!=y){
		if (depth[x]>depth[y]){
			left=left+R[x];
			x=fa[x];
		}else{
			right=R[y]+right;
			y=fa[y];
		}
	}
	rec ret=left+R[x]+right;
	return max(ret.b[0][0],ret.b[0][1]);
}
int main()
{
	int Q;
	scanf("%d%d",&N,&Q);
	L=1;
	while (L*L<N)L++;
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
	dfs();
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
			R[x]=rec::ini(Map[x]);
			update(x);
		}
	}
	return 0;
}


