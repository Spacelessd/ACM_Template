#include<cstdio>
#include<cstring>
#include<iostream>
int n,x,y;
char s[15];
struct note {int x,y;} a[500005];
int main()
{
	freopen("1.in","r",stdin);
	freopen("bl.out","w",stdout);
	scanf("%d",&n); int m=0;
	for (int i=1;i<=n;i++){
		scanf("%s%d%d",s,&x,&y);
		if (s[0]=='+') a[++m].x=x,a[m].y=y;
		else{
			int ans=0;
			for (int j=1;j<=m;j++) if (a[j].x<=x && a[j].y>=y) ans++;
			printf("%d\n",ans);
			}
		}
	return 0;
}
