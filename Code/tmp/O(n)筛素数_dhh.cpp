	for (int i=2;i<=N;i++){
		if (!f[i]) f[i]=i,p[++len]=i;
		for (int j=1;j<=len && p[j]<=f[i] && p[j]<=N/i;j++) f[p[j]*i]=p[j];
		}
