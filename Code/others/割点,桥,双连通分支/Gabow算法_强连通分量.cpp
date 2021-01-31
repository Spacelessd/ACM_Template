#include<iostream>
using namespace std;
const int MAXN = 110;
typedef int AdjTable[MAXN] ; // 邻接表类型
int n;
int intm[MAXN] ; // 标记进入顶点时间
int belg[MAXN] ; // 存储强连通分量 , 其中 belg[i] 表示顶点 i 属于第 belg[ i] 个强连通分量
int stk1[MAXN] ; // 辅助堆栈
int stk2[MAXN] ; // 辅助堆栈
AdjTable adj[MAXN] ; // 邻接表
// 深搜过程 , 该算法的主体都在这里
void Visit(int cur, int &sig, int &scc_num)
{
	int i;
	intm[cur ] = ++sig;
	stk1[++stk1[0]] = cur ;
	stk2[++stk2[0]] = cur ;
	for ( i = 1; i <= adj[cur][0]; ++i )
	{
		if ( 0 == intm[adj[cur][ i] ] )
		{
			Visit(adj[cur ][i], sig, scc_num);
		}
		else if ( 0 == belg[adj[cur][ i]] )
		{
			while ( intm[stk2[stk2[0] ]] > intm[adj[cur][ i]] )
			{
				-- stk2[0];
			}
		}
	}
	if ( stk2[stk2[0] ] == cur )
	{
		-- stk2[0];
		++ scc_num;
		do
		{
			belg[stk1[stk1[0] ]] = scc_num;
		}
		while ( stk1[stk1[0]--] != cur );
	}
}
//Gabow 算法,求解 belg[1..n],且返回强连通分量个数
int Gabow_StronglyConnectedComponent()
{
	int i, sig, scc_num;
	memset(belg + 1, 0, sizeof(int)*n) ;
	memset( intm + 1, 0, sizeof(int)*n) ;
	sig = 0;
	scc_num = 0;
	stk1[0] = 0;
	stk2[0] = 0;
	for ( i = 1; i <= n; ++i )
	{
		if ( 0 == intm[i] )
		{
			Visit(i, sig, scc_num) ;
		}
	}
	return scc_num;
}
int main(){
	system("pause");
	return 0;
}


