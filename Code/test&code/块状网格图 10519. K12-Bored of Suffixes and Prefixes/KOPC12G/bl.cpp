#include<cstdio>
#include<cstring>
#define CH getchar()
#define read(n) scanf("%d",&n)
int n,t,q,map[605][605];
char s[605];
int main()
{
	freopen("1.in","r",stdin);
	freopen("bl.out","w",stdout);
	read(t);
	while (t--){
		read(n); read(q);
		for (int i=1;i<=n;i++){
			scanf("%s",s);
			for (int j=1;j<=n;j++)
				map[i][j]=s[j-1]-64;		
			}
		while (q--){
			int z,x,y,x1,y1,x2,y2; read(z);
			if (z){
				read(x1);read(y1);read(x2);read(y2);
				x1++,y1++,x2++,y2++; int ans=0;
				for (int i=x1;i<=x2;i++)
					for (int j=y1;j<=y2;j++) ans+=map[i][j];
				printf("%d\n",ans);
				}
			else{
				read(x);read(y); y++; scanf("%s",s);
				if (x) for (int i=1;i<=n;i++){
					int v=s[i-1]-64;
					map[i][y]=v;
					}
				else for (int i=1;i<=n;i++){
					int v=s[i-1]-64;
					map[y][i]=v;
					}
				}
			/*printf("\n");
			for (int i=1;i<=n;i++){
				for (int j=1;j<=n;j++) printf("%d ",map[i][j]);
				printf("\n");}*/
			}
				
		}
	return 0;
}
