#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<algorithm>
#define N 100005
struct Query{
	int L,R,p,ans1,ans2;
};
Query Q[N];
int C[N],ans1[N],ans2[N];
int n,m,i,j,Lim,start,end;
int count[N],num[N],max1,max2;
int now[N],now1,Qnow;
struct Edge{
	#define Mx 100005
	int link[Mx],next[Mx],son[Mx],l;
	void clear(){l=0;memset(son,0,sizeof(son));}
	void addedge(int x,int y){
		link[++l]=y;next[l]=son[x];son[x]=l;
	}
};
Edge e;
bool cmp(const Query x,const Query y){return x.L<y.L;}
void add(int l,int r){
	int now;
	for (int i=l;i<=r;++i){
		now=num[C[i]];
		if (now==max1)++max1;
			else if (now==max2)++max2;
		--count[now];++num[C[i]];++count[now+1];
	}
}
void del(int l,int r){
	int now;
	for (int i=l;i<=r;++i){
		now=num[C[i]];
		if (max1==max2){
			if (now==max1&&count[now]==2)--max2;
		}
		else {
			if (now==max1)--max1;
			else if (now==max2&&count[max2]==1)--max2;
		}
		--count[now];--num[C[i]];++count[now-1];
	}
}
int main(){
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	scanf("%d%d",&n,&m);
	for (i=1;i<=n;++i)scanf("%d",&C[i]);
	for (i=1;i<=m;++i)
		scanf("%d%d",&Q[i].L,&Q[i].R),++Q[i].L,++Q[i].R,Q[i].p=i;
	std::sort(Q+1,Q+1+m,cmp);
	Lim=(int)(sqrt(n)+1);
	start=1;Qnow=1;
	while (start<=n){
		memset(count,0,sizeof(count));count[0]=n;
		memset(num,0,sizeof(num));
		end=start+Lim-1;now1=0;e.clear();max1=max2=0;
		while (Qnow<=m&&Q[Qnow].L<=end){
			if (Q[Qnow].R<=end){
				add(Q[Qnow].L,Q[Qnow].R);
				Q[Qnow].ans1=max1;Q[Qnow].ans2=max2;
				del(Q[Qnow].L,Q[Qnow].R);
				++Qnow;
			}
			else now[++now1]=Qnow++;
		}
		for (i=1;i<=now1;++i)e.addedge(Q[now[i]].R,now[i]);
		for (i=end+1;i<=n;++i){
			add(i,i);
			for (j=e.son[i];j;j=e.next[j]){
				add(Q[e.link[j]].L,end);
				Q[e.link[j]].ans1=max1;Q[e.link[j]].ans2=max2;
				del(Q[e.link[j]].L,end);
			}
		}
		start+=Lim;
	}
	for (i=1;i<=m;++i)ans1[Q[i].p]=Q[i].ans1,ans2[Q[i].p]=Q[i].ans2;
	for (i=1;i<=m;++i)printf("%d %d\n",ans1[i],ans2[i]);
	system("pause");for (;;);
	return 0;
}


