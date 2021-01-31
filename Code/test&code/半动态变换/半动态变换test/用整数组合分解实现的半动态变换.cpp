#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define N 1000005
#define K 2
/*
QD(n)=O(QS(n)*k)
I'D(n)=O(kn^(1/k)PS(n)/n)
*/
int a[K+1],c[K+1],A[N],T[N];
char zzy[10];
int n;
int gua;
void init(){
	for (int i=1;i<=K;++i)a[i]=i-1,c[i]=0;
}
void Merge(int l,int mid,int r){
	int i=l,j=mid;
	gua+=r-l+1;
	for (int k=l;k<=r;++k)
		if (i<mid&&(j>r||A[i]<A[j]))T[k]=A[i++];
			else T[k]=A[j++];
	for (int k=l;k<=r;++k)A[k]=T[k];
}
void Insert(int x){
	A[++n]=x;Merge(n-c[1],n,n);
	++a[1];++c[1];
	for (int i=1;i<K&&a[i]==a[i+1];++i){
		Merge(n-c[i]-c[i+1]+1,n-c[i]+1,n);
		++a[i+1];c[i+1]+=c[i];
		a[i]=i-1;c[i]=0;
	}
}
int Q(int l,int r,int L,int R){
	int ll=l-1,rr=r,mid,pre;
	while (ll<rr){
		mid=(ll+rr+1)>>1;
		if (A[mid]>=L)rr=mid-1;
			else ll=mid;
	}
	pre=ll;ll=l-1,rr=r;
	while (ll<rr){
		mid=(ll+rr+1)>>1;
		if (A[mid]>R)rr=mid-1;
			else ll=mid;
	}
	return ll-pre;
}
int Query(int L,int R){
	int ans=0,st=n+1;
	for (int i=1;i<=K;++i)
		if (c[i])
			st-=c[i],ans+=Q(st,st+c[i]-1,L,R);
	return ans;
}
int main()
{
	int t1=clock();
	int x,L,R;init();
	for (int i=1;i<=1000000;++i)Insert(i);
	//for (int i=1;i<=1000000;++i)Query(1,rand()+1);
	printf("%d\n",clock()-t1);
	printf("gua%d\n",gua);
	system("pause");
	return 0;
}






