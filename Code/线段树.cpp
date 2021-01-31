#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define N 100005
struct node{
	int sum;
};
node a[N*4];
void change(int t,int l,int r,int x,int y){
	if (l==r){
		a[t].sum=y;return;
	}
	int mid=(l+r)>>1;
	if (x<=mid)change(t*2,l,mid,x,y);
		else change(t*2+1,mid+1,r,x,y);
	a[t].sum=a[t*2].sum+a[t*2+1].sum;
}
int sum(int t,int l,int r,int ll,int rr){
	if (l==ll&&r==rr)return a[t].sum;
	int mid=(l+r)>>1;
	if (rr<=mid)return sum(t*2,l,mid,ll,rr);
		else if (ll>mid)return sum(t*2+1,mid+1,r,ll,rr);
		else return sum(t*2,l,mid,ll,mid)+sum(t*2+1,mid+1,r,mid+1,rr);
}
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	
	system("pause");for (;;);
	return 0;
}


