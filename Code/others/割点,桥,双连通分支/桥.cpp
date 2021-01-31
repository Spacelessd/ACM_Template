void CutEdge(int v, int fa)//dhh nie
{
	dfn[v] = low[v] = ++cnt;
	st[++top] = v;
	for(int i = p[v]; i != -1; i = edge[i].pre)
	{
		int u(edge[i].d);
		if(u == fa)continue;
		if(!dfn[u])
		{
			CutEdge(u, v);
			GetMin(low[v], low[u]);
			if(low[u] > dfn[v]) // 边 v->u 为一条割边
			{
				cutE[++numE] = E(v, u);
				// 将 u 及与它形成的连通分量的所有点存起来
				++numB;
				while(1)
				{
					id[st[top]] = numB;
					if(st[top--] == u)break;
				}
			}
		}
		else GetMin(low[v], dfn[u]);
	}
}


