#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<iostream>
#include<algorithm>
using namespace std;
#define N 100005
#define ll long long
struct line{int x,y,id;};
line a[N];int stack[N],ans[N];
bool cmp(line x,line y){
	return x.x!=y.x?x.x<y.x:x.y<y.y;
}
double cross(int x1,int y1,int x2,int y2){return 1.0*(y2-y1)/(x1-x2);}
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	int n,_n;scanf("%d",&n);
	for (int i=1;i<=n;++i)scanf("%d%d",&a[i].x,&a[i].y),a[i].id=i;
	sort(a+1,a+1+n,cmp);_n=n;n=0;
	for (int i=1;i<=_n;++i)
		if (i>1&&a[i].x==a[i-1].x)a[n]=a[i];
		else a[++n]=a[i];
	int top=0;
	for (int i=1;i<=n;++i){
		while (top>1&&(ll)(a[i].y-a[stack[top]].y)*(a[stack[top-1]].x-a[stack[top]].x)<=
			(ll)(a[stack[top]].x-a[i].x)*(a[stack[top]].y-a[stack[top-1]].y))--top;
		stack[++top]=i;
	}
	for (int i=1;i<=top;++i)ans[a[stack[i]].id]=1;
	for (int i=1;i<=_n;++i)if (ans[i])--top,printf("%d%c",i,top?' ':'\n');
	system("pause");for (;;);
	return 0;
}


