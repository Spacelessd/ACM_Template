#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define maxn 100010
#define ll long long
ll f[maxn],queue[maxn],sum[maxn],L;
int h,t;
inline ll sqr(ll x){return x*x;}
inline ll calc(ll x,ll y){
	return f[x]+sqr(sum[y]-sum[x]+y-x-1-L);
}
inline ll cha(ll x1,ll y1,ll x2,ll y2){return x1*y2-x2*y1;}
inline int canpop(int x,int y,int z){
	ll x1=sum[x]+x,x2=sum[y]+y,x3=sum[z]+z,
	y1=x1*x1+f[x],y2=x2*x2+f[y],y3=x3*x3+f[z];
	if (cha(x3-x2,y3-y2,x2-x1,y2-y1)>=0)return 0;
		else return 1;
}
int main(){
	int n;
	scanf("%d%I64d",&n,&L);
	for (int i=1;i<=n;++i)scanf("%I64d",&sum[i]),sum[i]+=sum[i-1];
	h=t=1;queue[h]=0;
	for (int i=1;i<=n;++i){
		while (h<t&&calc(queue[h],i)>=calc(queue[h+1],i))++h;
		queue[++t]=i;f[i]=calc(queue[h],i);
		while (h+1<t&&!canpop(queue[t-2],queue[t-1],queue[t]))
			queue[--t]=queue[t+1];
	}
	printf("%I64d\n",f[n]);
	//system("pause"); 
}




