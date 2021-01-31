#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define N 1000005
/*
SD(n)=O(SS(n))
QD(n)=O(QS(n)logn)
I'D(n)=O((PS(n)/n)logn)
*/
int A[N],T[N];
char zzy[10];
int n;
void Merge(int l,int mid,int r){
	int i=l,j=mid;
	for (int k=l;k<=r;++k)
		if (i<mid&&(j>r||A[i]<A[j]))T[k]=A[i++];
			else T[k]=A[j++];
	for (int k=l;k<=r;++k)A[k]=T[k];
}
void Insert(int x){
	A[++n]=x;
	for (int k=1;(n-1)&k;k<<=1)Merge(n-k-k+1,n-k+1,n);
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
	int ans=0;
	for (int k=1,st=n;k<=st;k<<=1)
		if (n&k)st-=k,ans+=Q(st+1,st+k,L,R);
	return ans;
}
int main()
{
	int t1=clock();
	freopen("1.in","r",stdin);
	freopen("1.out","w",stdout);
	int x,L,R;
	while (scanf("%s",&zzy)!=EOF){
		if (zzy[0]=='I')scanf("%d",&x),Insert(x);
		if (zzy[0]=='Q')scanf("%d%d",&L,&R),printf("%d\n",Query(L,R));
	}
	printf("%d\n",clock()-t1);
	//system("pause");for (;;);
	return 0;
}






