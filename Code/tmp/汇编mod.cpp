#include<cstdio>
#include<ctime>
#include<algorithm>
using namespace std;

const int base[4][4]={{0,0,0,1},{0,1,0,1},{1,2,0,1},{0,0,3,1}};
const int mod=1000000007;
const int maxn=1000000+10;
struct node
{
	int ID,n,res;
} p[maxn];
int power[31][4][4];
int n,t;
int c[4][4];

inline int MOD(int a,int b)
{
	int div, res;
    asm("mul %3; div %4": "=a" (div), "=&d" (res): "a" (a), "r" (b), "r" (mod));
    return res;
}

void mul(int a[][4],int b[][4])
{
	for (int k=0;k<4;k++)
	for (int i=0;i<4;i++)
	if (a[i][k])
	for (int j=0;j<4;j++)
	if (b[k][j])
	{
		c[i][j]+=MOD(a[i][k],b[k][j]);
		if (c[i][j]>=mod) c[i][j]-=mod;
	}
	for (int i=0;i<4;i++)
	for (int j=0;j<4;j++)
	{
		a[i][j]=c[i][j];c[i][j]=0;
	}
}

bool cmp1(const node &a,const node &b)
{
	return a.n<b.n;
}

bool cmp2(const node &a,const node &b)
{
	return a.ID<b.ID;
}

int main()
{
	//freopen("input.txt","r",stdin);

	for (int i=0;i<4;i++)
	for (int j=0;j<4;j++)
		power[0][i][j]=base[i][j];
	for (int i=1;i<31;i++)
	{
		for (int j=0;j<4;j++)
		for (int k=0;k<4;k++)
			power[i][j][k]=power[i-1][j][k];
		mul(power[i],power[i-1]);
	}

	scanf("%d",&t);
	for (int i=0;i<t;i++)
	{
		scanf("%d",&p[i].n);
		p[i].ID=i;
	}
	sort(p,p+t,cmp1);

	int res[4]={0,0,0,1};
	for (int i=0,prev=0;i<t;prev=p[i++].n)
	{
		for (int j=0,k=p[i].n-prev;k;k=(k>>1),j++)
		if (k&1)
		{
			int tmp[4]={res[0],res[1],res[2],res[3]};
			res[0]=res[1]=res[2]=res[3]=0;
			for (int u=0;u<4;u++)
			for (int v=0;v<4;v++)
			{
				res[v]+=MOD(tmp[u],power[j][u][v]);
				if (res[v]>=mod) res[v]-=mod;
			}
		}
		int a=0;
		for (int k=0;k<4;k++) {a+=res[k];if (a>=mod) a-=mod;}
		p[i].res=a;
	}
	sort(p,p+t,cmp2);
	for (int i=0;i<t;i++) printf("%d\n",p[i].res);
	//printf("%0.9lf\n",(double)clock()/CLOCKS_PER_SEC);
}

