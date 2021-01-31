#include<cstdio>
#include<cstring>
#define CH getchar()
int n,t,q,map[605][605];
char s[605];
struct Tree{
	int c[605];
	void pre(){memset(c,0,sizeof(c));}
	void add(int x,int v){for (;x<=n;x+=x&-x) c[x]+=v;}
	int get(int x){
		int res=0;
		for (;x;x-=x&-x) res+=c[x];
		return res;
		}
} a[605];
inline void read(int &x)
{
	x=0; char ch;
	for (ch=CH;ch<'0' || ch>'9';ch=CH);
	for (;ch>='0' && ch<='9';x=x*10+ch-48,ch=CH);
}
int main()
{
	read(t);
	while (t--){
		read(n),read(q); for (int i=1;i<=n;i++) a[i].pre();
		for (int i=1;i<=n;i++){
			scanf("%s",s);
			for (int j=1;j<=n;j++)
				map[i][j]=s[j-1]-64,a[i].add(j,map[i][j]);		
			}
		while (q--){
			int z,x,y,x1,y1,x2,y2; read(z);
			if (z){
				read(x1),read(y1),read(x2),read(y2);
				x1++,y1++,x2++,y2++; int ans=0;
				for (int i=x1;i<=x2;i++)
					ans+=a[i].get(y2)-a[i].get(y1-1);
				printf("%d\n",ans);
				}
			else{
				read(x),read(y); y++; scanf("%s",s);
				if (x) for (int i=1;i<=n;i++){
					int v=s[i-1]-64;
					a[i].add(y,v-map[i][y]);
					map[i][y]=v;
					}
				else for (int i=1;i<=n;i++){
					int v=s[i-1]-64;
					a[y].add(i,v-map[y][i]);
					map[y][i]=v;
					}
				}
			}		
		}
	return 0;
}
