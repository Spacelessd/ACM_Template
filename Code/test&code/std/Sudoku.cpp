#include<cstdio>
#include<cstdlib>
#include<cstring>
#define N 3250
int l[N],r[N],d[N],u[N],c[N],p[N];
int l1[N],r1[N],d1[N],u1[N];
int o[325],b[730],s[325],a[9][9];
char st[100];

void remove(int x)
{
	l[r[x]]=l[x]; r[l[x]]=r[x];	
	for (int i=d[x];i!=x;i=d[i])
		for (int j=r[i];j!=i;j=r[j]){
			u[d[j]]=u[j];
			d[u[j]]=d[j];
			s[c[j]]--;
			}
}
void resume(int x)
{	
	for (int i=u[x];i!=x;i=u[i])
		for (int j=l[i];j!=i;j=l[j]){
			u[d[j]]=j;
			d[u[j]]=j;
			s[c[j]]++;
			}
	l[r[x]]=x; r[l[x]]=x;
}
bool dfs(int t)
{
	if (!r[0]){
		return 1;
		}
	int x=0,min=10000;
	for (int i=r[0];i;i=r[i])
		if (s[i]<min) min=s[i],x=i;
	remove(x);
	for (int i=d[x];i!=x;i=d[i]){
		for (int j=r[i];j!=i;j=r[j]) remove(c[j]);
		o[t]=p[i];
		if (dfs(t+1)) return 1;
		for (int j=l[i];j!=i;j=l[j]) resume(c[j]);
		}
	resume(x);
	return 0;
}
int main()
{
	//freopen("sd.in","r",stdin);
	//freopen("sd.out","w",stdout);
	int x=325,y=0;
	for (int i=0;i<9;i++)
		for (int j=0;j<9;j++)
		 for (int k=0;k<9;k++){
			y++;
			p[x]=y,c[x]=1+i*9+j,x++;
			p[x]=y,c[x]=82+i*9+k,x++;
			p[x]=y,c[x]=163+j*9+k,x++;
			p[x]=y,c[x]=244+((i/3)*3+j/3)*9+k,x++;
			}
	for (int i=0;i<=324;i++) r[i]=i+1,l[i+1]=i;
	r[324]=0; l[0]=324;
	for (int i=81;i<810;i++){
		int x1=i*4+1,x2=x1+1,x3=x2+1,x4=x3+1;
		r[x1]=x2; r[x2]=x3; r[x3]=x4; r[x4]=x1;
		l[x4]=x3; l[x3]=x2; l[x2]=x1; l[x1]=x4;
		}
	for (int i=1;i<=324;i++) o[i]=i;
	for (int i=325;i<=3240;i++){
		y=c[i]; d[o[y]]=i; u[i]=o[y]; o[y]=i;
		}
	for (int i=1;i<=324;i++) u[i]=o[i],d[o[i]]=i;

	memcpy(l1,l,sizeof(l1));
	memcpy(r1,r,sizeof(r1));
	memcpy(u1,u,sizeof(u1));
	memcpy(d1,d,sizeof(d1));
	gets(st);
	while (st[0]!='e'){
		memcpy(l,l1,sizeof(l));
		memcpy(r,r1,sizeof(r));
		memcpy(u,u1,sizeof(u));
		memcpy(d,d1,sizeof(d));
		for (int i=1;i<=324;i++) s[i]=9;
		memset(o,0,sizeof(o));
		for (int i=0;i<9;i++)
			for (int j=0;j<9;j++)
				if (st[i*9+j]=='.') a[i][j]=0;
				else a[i][j]=st[i*9+j]-48;
		for (int i=0;i<9;i++)
			for (int j=0;j<9;j++) if (a[i][j]){
				int k=a[i][j]-1;
				remove(1+i*9+j);
				remove(82+i*9+k);
				remove(163+j*9+k);
				remove(244+((i/3)*3+j/3)*9+k);
				}
		dfs(0);
		memset(b,0,sizeof(b)); x=0;
		for (int i=0;i<81;i++) b[o[i]]=1;
		for (int i=0;i<9;i++)
			for (int j=0;j<9;j++)
				for (int k=0;k<9;k++){
				 x++; if (b[x]) a[i][j]=k+1;
				 }
		for (int i=0;i<9;i++) for (int j=0;j<9;j++) printf("%d",a[i][j]); printf("\n");
		gets(st);
		}
	return 0;
}


