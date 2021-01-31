#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<iostream>
#include<algorithm>
using namespace std;
#define N 200005
int f[N],a[N],Q[N];
int find(int x){
	if (f[x]==x)return x;
	else return f[x]=find(f[x]);
}
char str[2000005],*p=str;
inline void read(int &x){
	int bo=0;x=0;
	while(*p<'0'||*p>'9')if (*p++=='-')bo=1;
	while(*p>='0'&&*p<='9')x=x*10+*p++-'0';
	if (bo)x=-x;
}
char buf[15],out[2000005],*o=out;
inline void print(int x){
	char *b=buf;if (!x)*b++='0';//if (x<0)x=-x,*b++='-';
	while(x){*b++=x%10+48;x/=10;}
	while(b--!=buf)*o++=*b;
	*o++='\n';
}
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	fread(p,1,2000000,stdin);
	int n,D,x,pre=0,t=0,tot=0;read(n);read(D);
	for (int i=1;i<=n;++i)f[i]=i;
	for (int i=1;i<=n;++i){
		while (*p!='A'&&*p!='Q')++p;char ch=*p++; read(x);
		if (ch=='A'){
			x=(x+pre)%D;a[++tot]=x;
			for (;t&&x>=a[Q[t]];--t)f[Q[t]]=tot;
			Q[++t]=tot;
		}
		else {
			pre=a[find(tot-x+1)];
			print(pre);
		}
	}
	if (o>out)*--o=0;puts(out);
	system("pause");for (;;);
	return 0;
}


