#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<algorithm>
using namespace std;
#define N 310
int n,m;
int lly,rry,y;
struct node;
node *get();
struct node{
	int l,r;int sum;
	node *lson,*rson,*T;
	node *set(int _l,int _r,node *_lson,node *_rson,node *_T,int _sum){
		l=_l;r=_r;lson=_lson;rson=_rson;T=_T;sum=_sum;
		return this;
	}
	node *set(int _l,int _r,node *_lson,node *_rson,node *_T){
		l=_l;r=_r;lson=_lson;rson=_rson;T=_T;sum=0;
		if (lson!=NULL)sum+=lson->sum;
		if (rson!=NULL)sum+=rson->sum;
		return this;
	}
	node *add1(int y){
		if (l==r&&l==y)return get()->set(l,r,NULL,NULL,NULL,sum+1);
		int mid=(l+r)>>1;node *tmp;
		if (y<=mid){
			if (lson==NULL)tmp=get()->set(l,mid,NULL,NULL,NULL);
				else tmp=lson;
			return get()->set(l,r,tmp->add1(y),rson,NULL);
		}
		else {
			if (rson==NULL)tmp=get()->set(mid+1,r,NULL,NULL,NULL);
				else tmp=rson;
			return get()->set(l,r,lson,tmp->add1(y),NULL);
		}
	}
	node *add(int x){
		node *tmp,*tmp1;
		if (l==r&&l==x){
			if (T==NULL)tmp=get()->set(1,m,NULL,NULL,NULL);
				else tmp=T;
			return get()->set(l,r,lson,rson,tmp->add1(y));
		}
		int mid=(l+r)>>1;
		if (x<=mid){
			if (lson==NULL)tmp=get()->set(l,mid,NULL,NULL,NULL);
				else tmp=lson;
			if (T==NULL)tmp1=get()->set(1,m,NULL,NULL,NULL);
				else tmp1=T;
			printf("rprp %d\n",tmp1->add1(y)->T);
			return get()->set(l,r,tmp->add(x),rson,get()->set(l,r,lson,rson,tmp1->add1(y)));
		}
		else {
			if (rson==NULL)tmp=get()->set(mid+1,r,NULL,NULL,NULL);
				else tmp=rson;
			if (T==NULL)tmp1=get()->set(1,m,NULL,NULL,NULL);
				else tmp1=T;
			return get()->set(l,r,lson,tmp->add(x),get()->set(l,r,lson,rson,tmp1->add1(y)));
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
#define BUFFER_SIZE 10000
node *buffer=NULL,*cur;
node *get(){
	if (!buffer||cur==buffer+BUFFER_SIZE)
		buffer=new node[BUFFER_SIZE],cur=buffer;
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
int key[N*N];
void init(){
	scanf("%d%d",&n,&m);ll=0;
	for (int i=1;i<=n;++i)
		for (int j=1;j<=m;++j){
			scanf("%d",&a[i][j]);
			++ll;Q[ll].x=i;Q[ll].y=j;Q[ll].key=a[i][j];
			key[ll]=a[i][j];
		}
	sort(Q+1,Q+ll+1,cmp);sort(key+1,key+ll+1);
	root[0]=get()->set(1,n,NULL,NULL,NULL);
	for (int i=1;i<=1;++i){
		y=Q[i].y;root[i]=root[i-1]->add(Q[i].x);
		printf("rprp %d %d\n",root[1]->T,root[1]->T->T);
		
	}
}
int main(){
	freopen("cheat.in","r",stdin);
	//freopen("cheat.out","w",stdout);
	init();
	scanf("%d",&q);
	for (int i=1;i<=q;++i){
		int x1,x2,y1,y2,l,r;
		scanf("%d%d%d%d%d%d",&x1,&y1,&x2,&y2,&l,&r);
		if (l>r)swap(l,r);
		lly=y1;rry=y2;
		int tmp=0;
		int L=1,R=ll;
		while (L<R){
			int mid=(L+R+1)>>1;
			if (key[mid]<l)L=mid;
				else R=mid-1;
		}
		if (key[L]>=l)--L;
		tmp-=root[L]->query(x1,x2);
		printf("-%d %d\n",L,root[L]->query(x1,x2));
		L=1,R=ll;
		while (L<R){
			int mid=(L+R+1)>>1;
			if (key[mid]<=r)L=mid;
				else R=mid-1;
		}
		//tmp+=root[L]->query(x1,x2);
		//printf("+%d %d\n",L,root[L]->query(x1,x2));
		ans^=tmp;
	}
	printf("%d\n",ans);
	system("pause");for (;;);
	return 0;
}




