#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<algorithm>
using namespace std;
#define N 305
int s;
int n,m;
int lly,rry,y;
struct node;
node *get();
struct node{
	int l,r; int sum;
	node *lson,*rson,*T;
	node *update(){
		sum=0;
		if (lson!=NULL)sum+=lson->sum;
		if (rson!=NULL)sum+=rson->sum;
		return this;
	}
	node *sety(int _l,int _r,node *_lson,node *_rson,int _sum){
		l=_l;r=_r;lson=_lson;rson=_rson;sum=_sum;
		return this;
	}
	node *setx(int _l,int _r,node *_lson,node *_rson,node *_T){
		l=_l;r=_r;lson=_lson;rson=_rson;T=_T;
		return this;
	}
	node *add1(int y){
		if (l==r)return get()->sety(l,r,NULL,NULL,sum+1);
		int mid=(l+r)>>1;node *tmp;
		if (y<=mid){
			if (lson==NULL)tmp=get()->sety(l,mid,NULL,NULL,0);
				else tmp=lson;
			return get()->sety(l,r,tmp->add1(y),rson,0)->update();
		}
		else {
			if (rson==NULL)tmp=get()->sety(mid+1,r,NULL,NULL,0);
				else tmp=rson;
			return get()->sety(l,r,lson,tmp->add1(y),0)->update();
		}
	}
	node *add(int x){
		node *tmp,*tmpT;
		if (T==NULL)tmpT=get()->sety(1,m,NULL,NULL,0);
			else tmpT=T;
		tmpT=tmpT->add1(y);
		if (l==r)return get()->setx(l,r,lson,rson,tmpT);
		int mid=(l+r)>>1;
		if (x<=mid){
			if (lson==NULL)tmp=get()->setx(l,mid,NULL,NULL,NULL);
				else tmp=lson;
			return get()->setx(l,r,tmp->add(x),rson,tmpT);
		}
		else {
			if (rson==NULL)tmp=get()->setx(mid+1,r,NULL,NULL,NULL);
				else tmp=rson;
			return get()->setx(l,r,lson,tmp->add(x),tmpT);
		}
	}
	int query1(int lly,int rry){
		if (lly==l&&rry==r)return sum;
		int mid=(l+r)>>1;
		if (rry<=mid)return lson!=NULL?lson->query1(lly,rry):0;
		else if (lly>mid)return rson!=NULL?rson->query1(lly,rry):0;
		else return (lson!=NULL?lson->query1(lly,mid):0)
			+(rson!=NULL?rson->query1(mid+1,rry):0);
	}
	int query(int llx,int rrx){
		if (llx==l&&rrx==r)return T!=NULL?T->query1(lly,rry):0;
		int mid=(l+r)>>1;
		if (rrx<=mid)return lson!=NULL?lson->query(llx,rrx):0;
		else if (llx>mid)return rson!=NULL?rson->query(llx,rrx):0;
		else return (lson!=NULL?lson->query(llx,mid):0)
			+(rson!=NULL?rson->query(mid+1,rrx):0);
	}
};
#define BUFFER_SIZE 1000000
node *buffer=NULL,*cur;
node *get(){
	if (!buffer||cur==buffer+BUFFER_SIZE)
		buffer=new node[BUFFER_SIZE],cur=buffer,s+=BUFFER_SIZE;
	return cur++;
}
struct Query{
	int x,y,key;
};
Query Q[N*N];
bool cmp(const Query x,const Query y){
	return x.key<y.key;
}
node *root[N*N];
int a[N][N];
int q,ll,ans;
void init1(){
	scanf("%d%d",&n,&m);ll=0;
	for (int i=1;i<=n;++i)
		for (int j=1;j<=m;++j){
			scanf("%d",&a[i][j]);
			++ll;Q[ll].x=i;Q[ll].y=j;Q[ll].key=a[i][j];
		}
	sort(Q+1,Q+ll+1,cmp);
	root[0]=get()->setx(1,n,NULL,NULL,NULL);
	for (int i=1;i<=ll;++i){
		y=Q[i].y;root[i]=root[i-1]->add(Q[i].x);
	}
}
#define M 3005
int pa,pb,pc,p;
long long paa[M],pbb[M],pcc[M];
int get(int x,int y,int p){
	return (paa[x%pa+1]+pbb[x%pb+1]+pcc[x%pc+1]
	+paa[y%pa+1]+pbb[y%pb+1]+pcc[y%pc+1])%p;
}
void init(){
	scanf("%d",&pa);
	for (int i=1;i<=pa;++i)scanf("%d",&paa[i]);
	scanf("%d",&pb);
	for (int i=1;i<=pb;++i)scanf("%d",&pbb[i]);
	scanf("%d",&pc);
	for (int i=1;i<=pc;++i)scanf("%d",&pcc[i]);
	scanf("%d%d%d",&n,&m,&p);ll=0;
	for (int i=1;i<=n;++i)
		for (int j=1;j<=m;++j){
			//scanf("%d",&a[i][j]);
			a[i][j]=get(i,j,p)+1;
			++ll;Q[ll].x=i;Q[ll].y=j;Q[ll].key=a[i][j];
		}
	sort(Q+1,Q+ll+1,cmp);
	root[0]=get()->setx(1,n,NULL,NULL,NULL);
	for (int i=1;i<=ll;++i){
		y=Q[i].y;root[i]=root[i-1]->add(Q[i].x);
	}
}
int main(){
	freopen("cheat.in","r",stdin);
	//freopen("cheat.out","w",stdout);
	init();
	scanf("%d",&q);
	for (int i=1;i<=q;++i){
		/*int x1,x2,y1,y2,l,r;
		scanf("%d%d%d%d%d%d",&x1,&y1,&x2,&y2,&l,&r);
		lly=y1;rry=y2;*/
		int x1=get(i,1,n)+1,y1=get(i,2,m)+1,x2=get(i,3,n)+1,y2=get(i,4,m)+1,
		l=get(i,5,p)+1,r=get(i,6,p)+1;
		if (x1>x2)swap(x1,x2);
		if (y1>y2)swap(y1,y2);
		lly=y1;rry=y2;
		if (l>r)swap(l,r);
		int tmp=0;
		int L=0,R=ll;
		while (L<R){
			int mid=(L+R+1)>>1;
			if (Q[mid].key<l)L=mid;
				else R=mid-1;
		}
		tmp-=root[L]->query(x1,x2);
		//printf("query- %d %d\n",L,root[L]->query(x1,x2));
		L=1,R=ll;
		while (L<R){
			int mid=(L+R+1)>>1;
			if (Q[mid].key<=r)L=mid;
				else R=mid-1;
		}
		tmp+=root[L]->query(x1,x2);
		//printf("query+ %d %d\n",L,root[L]->query(x1,x2));
		//printf("tmp=%d\n",tmp);
		ans^=tmp;
	}
	printf("s=%d\n",s);
	printf("%d\n",ans);
	system("pause");for (;;);
	return 0;
}


