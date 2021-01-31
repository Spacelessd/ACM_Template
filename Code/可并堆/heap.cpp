#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
const int N=1000005;
struct heap{
	#define N 1000005
	typedef int value;
	value a[N];int len;
	heap(){len=0;}
	void up(int x){
		int i=x;value j;
		while (i>1&&a[i]<a[i>>1]){
			j=a[i];a[i]=a[i>>1];a[i>>1]=j;i>>=1;
		}
	}
	void down(int x){
		int i=x,j;value k;
		while (i<<1<=len){
			j=i; if (a[i<<1]<a[i])j=i<<1;
			if ((i<<1)+1<=len&&a[(i<<1)+1]<a[j])j=(i<<1)+1;
			if (j==i)break;
			k=a[i];a[i]=a[j];a[j]=k; i=j;
		}
	}
	void build(int *tmp,int n){
		len=n;
		for (int i=n;i;--i)a[i]=tmp[i];
		for (int i=n>>1;i;--i)down(i);
	}
	void insert(value x){a[++len]=x;up(len);}
	bool empty(){return len==0;}
	value top(){return a[1];}
	void pop(){a[1]=a[len--];down(1);}
	void clear(){len=0;}
	#undef N
};
heap Q;int tmp[N];
void test_time(){
	printf("input n:");
	int n;scanf("%d",&n);
	int t1=clock();
	for (int x=13251325,i=1;i<=n;++i,x+=(x<<2)+1)
		Q.insert(x&0x7fffffff);
	for (int i=1;i<=n;++i){
		//printf("%d\n",Q.top());
		Q.pop();
	}
	printf("time=%d\n",(int)clock()-t1);
	Q.clear();
	srand(time(0));
	for (int i=1;i<=n;++i)tmp[i]=rand()*rand();
	t1=clock();
	Q.build(tmp,n);
	printf("build time=%d\n",(int)clock()-t1);
	system("pause");
}
void testOK(){
	Q.clear();
	for (int i=1;i<=10;++i)Q.insert(i);
	for (int i=20;i>10;--i)Q.insert(i);
	while (!Q.empty())printf("%d\n",Q.top()),Q.pop();
}
int main(){
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	test_time();
	testOK();
	system("pause");for (;;);
	return 0;
}


