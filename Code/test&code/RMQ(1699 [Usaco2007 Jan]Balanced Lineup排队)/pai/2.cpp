#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define N 50005
#define oo 100000000
int amax[N*4],amin[N*4]; int M,top;
inline int max(int x,int y){int m=(x-y)>>31;return y&m|x&~m;}
inline int min(int x,int y){int m=(y-x)>>31;return y&m|x&~m;}
inline void make(int len=10){for (M=1;M-2<len;M<<=1);}
inline void build(){
	for (int i=M-1;i;--i){
		amax[i]=max(amax[i*2],amax[i*2+1]);
		amin[i]=min(amin[i*2],amin[i*2+1]);
	}
}
inline int query(int l,int r){
	l=l+M-1;r=r+M+1;int ans_max=-oo,ans_min=oo,tmp;
	for (;l^r^1;l>>=1,r>>=1){
		if (~l&1)ans_max=max(ans_max,amax[l^1]),ans_min=min(ans_min,amin[l^1]);
		if (r&1)ans_max=max(ans_max,amax[r^1]),ans_min=min(ans_min,amin[r^1]);
	}
	return ans_max-ans_min;
}
char str[3000005],*p=str;
inline void read(int &x){
	int bo=0;x=0;
	while(*p<'0'||*p>'9')if (*p++=='-')bo=1;
	while(*p>='0'&&*p<='9')x=x*10+*p++-'0';
	if (bo)x=-x;
}
int main()
{
	freopen("1.in","r",stdin);
	freopen("2.out","w",stdout);
	int t1=clock();
	fread(str,1,3000000,stdin);
	int n,m,x,y;read(n);read(m);
	make(n);
	for (int i=1;i<=n;++i)read(amax[M+i]),amin[M+i]=amax[M+i];
	build();
	while (m--){
		read(x);read(y);
		printf("%d\n",query(x,y));
	}
	printf("time=%d\n",clock()-t1);
	//system("pause");for (;;);
	return 0;
}


