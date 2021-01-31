#if !defined maxn
#define maxn 500000
#define maxt 50
int testtmp[maxt+10];
int deep[maxn+10],sumdep,sigma;
double t1;

void print(int x)
{
	if (x==0) return;
	print(a.a[x].l);
	printf("%d\n",a.a[x].key);
	print(a.a[x].r);
}

void calc(int x,int dep)
{
	int i;
	if (x==0) return;
	deep[dep]++;sumdep+=dep;
	calc(a.a[x].l,dep+1);
	calc(a.a[x].r,dep+1);
}

void test1()
{
	int i,j,tmp;
	a.clear();
	sumdep=0,sigma=0;memset(deep,0,sizeof(deep));
	printf("testing...\n");
	for (i=1;i<=maxt;i++)testtmp[i]=i;
	for (i=1;i<=maxt;i++){
		j=rand()%maxt+1;
		tmp=testtmp[j];testtmp[j]=testtmp[i];testtmp[i]=tmp;
	}
	for (i=1;i<=maxt;i++)a.insert(a.root,testtmp[i]);
	print(a.root);
	calc(a.root,1);
	for (i=1;deep[i];i++) sigma+=deep[i];
	printf("nodes=%d\n",sigma);
	system("pause");
	//exit(0);
}

void test()
{  
	int i;
	a.clear();
	sumdep=0,sigma=0;memset(deep,0,sizeof(deep));
	srand(time(0));
	printf("start\n");
	t1=clock();
	for (i=1;i<=maxn;i++)a.insert(a.root,rand()*32768+rand());
	calc(a.root,1);
	for (i=1;deep[i];i++){
		sigma+=deep[i];
		printf("%d:%d\n",i,deep[i]);
	}
	printf("ave=%.5f\n",double(sumdep)/double(maxn));
	printf("%d\n",sigma);
	printf("%.4f\n",(clock()-t1)/CLOCKS_PER_SEC);
	system("pause");
}

void test2()
{  
	int i;
	a.clear();
	sumdep=0,sigma=0;memset(deep,0,sizeof(deep));
	srand(time(0));
	printf("start\n");
	t1=clock();
	for (i=1;i<=maxn;i++)a.insert(a.root,i);
	calc(a.root,1);
	for (i=1;deep[i];i++){
		sigma+=deep[i];
		printf("%d:%d\n",i,deep[i]);
	}
	printf("ave=%.5f\n",double(sumdep)/double(maxn));
	printf("%d\n",sigma);
	printf("%.4f\n",(clock()-t1)/CLOCKS_PER_SEC);
	system("pause");
}

#endif


