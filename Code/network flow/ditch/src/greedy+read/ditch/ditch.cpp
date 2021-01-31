/*
ID:hqztrue1
LANG:C++
TASK:ditch
*/
#include<stdio.h>
int n,m,i,x,y,z,sums,sumt,S,T;
inline void read(int &x){
	int ch;x=0;
	for (ch=getchar();!(ch>='0' && ch<='9');ch=getchar());
	for (;ch>='0' && ch<='9';x=x*10+ch-'0',ch=getchar());
}

int main()
{
	freopen("ditch.in","r",stdin);
	freopen("ditch.out","w",stdout);
	scanf("%d%d",&m,&n);S=1;T=n;
	for (i=1;i<=m;i++)
	{
		//scanf("%d%d%d",&x,&y,&z);
		read(x);read(y);read(z);
		if (x!=y){
			if (x==S)sums+=z;
			if (y==T)sumt+=z;
		}
	}
	printf("%d\n",sums<sumt?sums:sumt);
	//system("pause");
	//for(;;);
	return 0;
}


