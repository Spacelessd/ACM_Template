#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <time.h>

int n, m;

int main()
{
	srand(time(0));
	freopen("a.in", "w", stdout);
	//scanf("%d%d", &n, &m);
	n=200;m=300;
	printf("%d %d\n", n, m);
	for(int i=0; i<n; i++)
		printf("%d ", (1 << 14)-rand());
	printf("\n");
	for(int i=0; i<m; i++)
	{
		for(int j=0; j<n; j++)
			printf("%d ", (1 << 14)-rand());
		printf("%d\n", rand());
	}
}
