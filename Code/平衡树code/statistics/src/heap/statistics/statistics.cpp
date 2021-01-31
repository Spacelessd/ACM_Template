#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
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
	void insert(value x){a[++len]=x;up(len);}
	bool empty(){return len==0;}
	value top(){return a[1];}
	void pop(){a[1]=a[len--];down(1);}
};
heap a1;
struct heap1{
	#define N 1000005
	typedef int value;
	value a[N];int len;
	heap1(){len=0;}
	void up(int x){
		int i=x;value j;
		while (i>1&&a[i]>a[i>>1]){
			j=a[i];a[i]=a[i>>1];a[i>>1]=j;i>>=1;
		}
	}
	void down(int x){
		int i=x,j;value k;
		while (i<<1<=len){
			j=i; if (a[i<<1]>a[i])j=i<<1;
			if ((i<<1)+1<=len&&a[(i<<1)+1]>a[j])j=(i<<1)+1;
			if (j==i)break;
			k=a[i];a[i]=a[j];a[j]=k; i=j;
		}
	}
	void insert(value x){a[++len]=x;up(len);}
	bool empty(){return len==0;}
	value top(){return a[1];}
	void pop(){a[1]=a[len--];down(1);}
};
heap1 a;
int main()
{
	long long n,A,b,c,key,ans=1;
	freopen("statistics.in","r",stdin);
	freopen("statistics.out","w",stdout);
	scanf("%I64d%I64d%I64d%I64d",&A,&b,&c,&n);
	a.insert(1);
	for (int i=2;i<=n;++i){
		key=(A*a.top()+b*i+c)%1000000007;
		if (i&1)a.insert(key);
			else a1.insert(key);
		while (a.top()>a1.top()){
			int tmp=a.a[1];a.a[1]=a1.a[1];a1.a[1]=tmp;
			a.down(1);a1.down(1);
		}
		ans+=key;
	}
	printf("%I64d\n",ans);
	//system("pause");for (;;);
	return 0;
}


