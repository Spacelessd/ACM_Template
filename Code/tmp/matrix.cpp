#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define N 300010
#define size 2
#define P 1000000007LL
struct matrix{
	long long key[size][size];
	void clear(){
		for (int i=0;i<size;++i)
			for (int j=0;j<size;++j)key[i][j]=0;
	}
};
matrix operator +(matrix a,matrix b){
	matrix T;T.clear();
	for (int i=0;i<size;++i)
		for (int j=0;j<size;++j)T.key[i][j]=(a.key[i][j]+b.key[i][j])%P;
	return T;
}
matrix operator *(matrix a,matrix b){
	matrix T;T.clear();
	for (int k=0;k<2;++k)
		for (int i=0;i<2;++i)
			for (int j=0;j<2;++j)
				T.key[i][j]=(T.key[i][j]+a.key[i][k]*b.key[k][j]);
	for (int i=0;i<2;++i)
		for (int j=0;j<2;++j)T.key[i][j]=T.key[i][j]%P;
	return T;
}

struct node{
	matrix sum,cover;
	int num;
};
node a[N];
int n,m,i,x,y;
char zzy[110];
matrix C,tmp;
void down(int t){
	if (a[t].num!=0){
		a[t*2].cover=a[t*2].cover*a[t].cover;
		a[t*2+1].cover=a[t*2+1].cover*a[t].cover;
		a[t*2].sum=a[t*2].sum*a[t].cover;
		a[t*2+1].sum=a[t*2+1].sum*a[t].cover;
		a[t*2].num+=a[t].num;a[t*2+1].num+=a[t].num;
		a[t].num=0;a[t].cover.clear();a[t].cover.key[0][0]=a[t].cover.key[1][1]=1;
	}
}
void build(int t,int l,int r){ 
	a[t].num=0;a[t].cover.clear();a[t].cover.key[0][0]=a[t].cover.key[1][1]=1;
	if (l==r){
		a[t].sum.clear();a[t].sum.key[0][0]=1;
		return;
	}
	int mid=(l+r)>>1;
	build(t*2,l,mid);
	build(t*2+1,mid+1,r);
	a[t].sum=a[t*2].sum+a[t*2+1].sum;
}
void Cover(int t,int l,int r,int ll,int rr){
	if (l==ll && r==rr){
	++a[t].num;a[t].cover=a[t].cover*C;a[t].sum=a[t].sum*C;
	return;
	}
	int mid=(l+r)>>1; down(t); 
	if (rr<=mid) Cover(t*2,l,mid,ll,rr);  
	else if (ll>mid) Cover(t*2+1,mid+1,r,ll,rr); 
		else Cover(t*2,l,mid,ll,mid),Cover(t*2+1,mid+1,r,mid+1,rr);  
	a[t].sum=a[t*2].sum+a[t*2+1].sum;
}
matrix Query(int t,int l,int r,int ll,int rr){
	if (l==ll && r==rr){ 
		return a[t].sum;
	}
	int mid=(l+r)>>1; down(t);  
	if (rr<=mid) return Query(t*2,l,mid,ll,rr);  
	else if (ll>mid) return Query(t*2+1,mid+1,r,ll,rr); 
		else return Query(t*2,l,mid,ll,mid)+Query(t*2+1,mid+1,r,mid+1,rr);  
}
void print(int t,int l,int r){
	//printf("%d %d   %d %d\n",l,r,a[t].sum.key[0][0],a[t].sum.key[0][1]);
	if (l==r){
		return;
	}
	int mid=(l+r)>>1;down(t);
	print(t*2,l,mid);
	print(t*2+1,mid+1,r);
}
int main()
{
	//freopen("fib.in","r",stdin);
	//freopen("fib.out","w",stdout);
	C.key[0][0]=C.key[0][1]=C.key[1][0]=1;C.key[1][1]=0;
	scanf("%d%d",&n,&m);
	build(1,1,n);
	for (i=1;i<=m;++i){
		scanf("%s%d%d",zzy,&x,&y);
		if (zzy[0]=='D')Cover(1,1,n,x,y);
		else {
			tmp=Query(1,1,n,x,y);
			printf("%d\n",int(tmp.key[0][1]));
		}
	}
	system("pause");
	//for (;;);
	return 0;
}




