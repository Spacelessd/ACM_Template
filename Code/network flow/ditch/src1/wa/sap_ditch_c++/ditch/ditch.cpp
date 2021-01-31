#include <cstdio>
#include <cstring>
const int MAXN=1511,INF=(1<<30)-1;
int c[MAXN][MAXN];			//残留网络
int d[MAXN],vd[MAXN];		//d[]:距离标号, vd[]:标号为i的结点个数
int n,m,flow;
inline int min(int x,int y){return x<y?x:y;}
void init()
{
	scanf("%d%d",&m,&n);
	for(int i=1;i<=m;i++)
	{
		int j,k,wt;
		scanf("%d%d%d",&j,&k,&wt);
		c[j][k]+=wt;
	}
}
int Min(int a,int b) {return a<b?a:b;}
int aug(int i,int augco)   //i:顶点, augco:从i为起点的最大增广容量     
{
	int j, augc = augco, mind = n-1, delta;
	if(i==n) 			   //到达汇点
	  return augco;
	
	for(j = 1;j <= n; j++) //枚举i的邻接点
		if(c[i][j]>0)	   //如果有边到j	
		{
			if(d[i]==d[j]+1)  //(i,j)为可进入弧
			{
				delta = min(augc,c[i][j]);  //求出经(i,j)的可增广最大值
				delta = aug(j,delta);       //递归增广，返回沿(i,j)的实际增广量
				c[i][j] -= delta;			//更新残留网络
				c[j][i] += delta;			
				augc -= delta;				//augc记录剩下的需要增广的量
				if(d[1]>=n)					//结束，向上一层返回经过i的实际增广量
					return augco-augc;
				if(augc == 0) break;        //已经到达可增广上界，提前跳出
			}
			if (mind<d[j])  mind = d[j];    //更新最小的邻接点标号
		}
	if(augco==augc)                         //如果从i点无法增广 
	{
		vd[d[i]]--;							//标号为d[i]的结点数-1
		if(vd[d[i]] ==0 )					//GAP优化
    		d[1] = n;
		d[i] = mind + 1;					//更新标号
		vd[d[i]]++;							//新标号的结点数+1
    }
	return augco-augc;			//向上一层返回经过i的实际增广量					
}
void sap()
{
	memset(d,0,sizeof(d));
	memset(vd,0,sizeof(vd));
	vd[0] = n;
	while(d[1] < n)
		flow+=aug(1,INF);
}
int main()
{
	freopen("ditch.in","r",stdin);
    freopen("ditch.out","w",stdout);
	init();
	sap();
	printf("%d\n",flow);
	return 0;
}
