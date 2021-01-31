#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<iostream>
#include<algorithm>
using namespace std;
#define N 500005
#define CH 128
typedef unsigned int value;
const value mul=910047571;
value hash[N],power[N];
char str[N];int sa[N],n;
inline value get_hash(int start,int end){
	return hash[end]-hash[start-1]*power[end-start+1];
}
inline int LCP(int x,int y){
	int l=0,r=min(n-x+1,n-y+1);
	while (l<r){
		int mid=(l+r+1)>>1;
		if (get_hash(x,x+mid-1)!=get_hash(y,y+mid-1))r=mid-1;
		else l=mid;
	}
	return l;
}
inline bool cmp(int x,int y){
	int len=LCP(x,y);return str[x+len]<str[y+len];
}
inline bool cmp_bl(int x,int y){
	for (int i=0;i<n;++i){
		if (str[x+i]<str[y+i])return 1;
		if (str[x+i]>str[y+i])return 0;
	}
	return 0;
}
void Q(int a[],int s,int t){
	int p,i=s,j=t,m=a[(i+j)>>1];
	do {
		while (cmp(a[i],m)) ++i;
		while (cmp(m,a[j])) --j;
		if (i<=j){
			p=a[i]; a[i]=a[j]; a[j]=p;
			++i; --j;
		}
	}while (i<=j);
	if (i<t) Q(a,i,t);
	if (s<j) Q(a,s,j);
}
void build_LCP(char str[],int n){
	power[0]=1;for (int i=1;i<=n;++i)power[i]=power[i-1]*mul;
	hash[0]=1;for (int i=1;i<=n;++i)hash[i]=hash[i-1]*mul+str[i];
}
void Buildsa(char str[],int n){
	build_LCP(str,n);
	for (int i=1;i<=n;++i)sa[i]=i;
	Q(sa,1,n);
}
int main(){
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	int t1=clock();
	//scanf("%s",str);
	for (int i=1;i<=200000;++i)str[i]=rand()%(CH-1)+1;
	n=strlen(str+1);
	Buildsa(str,n);
	//printf("sa=");for (int i=1;i<=n;++i)printf("%d ",sa[i]-1);printf("\n");
	printf("time=%d\n",clock()-t1);
	system("pause");for (;;);
	return 0;
}


