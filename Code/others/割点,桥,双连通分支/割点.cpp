void CutBlock(int v)
{
	dfn[v] = low[v] = ++cnt;
	st[++top] = v;
	for(int i = p[v]; i != -1; i = edge[i].pre)
	{
		int u(edge[i].d);
		if(dfn[u] == 0)
		{
			CutBlock(u);
			GetMin(low[v], low[u]);
			if(low[u] >= dfn[v]) //V 是一个割点
			{
				block[0] = 0;
				while (true)
				{
					block[++block[0]] = st[top];
					if (st[top--] == u) // 只能弹到 u 为止， v 还可以在其他块中
						break;
				}
				block[++block[0]] = v; // 割点属于多个块 ， 一定要补进去
				Count(block);
			}
		}
		else GetMin(low[v], dfn[u]);
	}
}


