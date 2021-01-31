#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<algorithm>
#define rep(i,n) for(int i=0;i<n;i++)
using namespace std;
const int maxn=100000*2+1;
int n,m,sa[maxn],ta[maxn],tb[maxn],*x=ta,*y=tb;
char C[maxn];
bool cmp(int i,int j,int l){return y[i]==y[j]&&y[i+l]==y[j+l];}
void Sort()
{
	static int w[maxn];
	rep(i,m)w[i]=0;rep(i,n)w[x[y[i]]]++;
	rep(i,m-1)w[i+1]+=w[i];
	for(int i=n-1;i>=0;i--)sa[--w[x[y[i]]]]=y[i];
}
void Da()
{
	int i,j,p;
	rep(i,n)x[i]=C[i],y[i]=i;Sort();
	for(p=1,j=1;p<n;m=p,j*=2)
	{
		for(p=0,i=n-j;i<n;i++)y[p++]=i;
		rep(i,n)if(sa[i]>=j)y[p++]=sa[i]-j;Sort();
		for(swap(x,y),i=1,p=1,x[sa[0]]=0;i<n;i++)
			x[sa[i]]=cmp(sa[i-1],sa[i],j)?p-1:p++;
	}
}
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	gets(C);n=strlen(C);
	rep(i,n)C[n+i]=C[i];n<<=1;C[n++]=0;m=256;
	Da();int s=n/2;
	rep(i,n)if(sa[i]<s)printf("%c",C[s+sa[i]-1]);
	printf("\n");
	return 0;
}


