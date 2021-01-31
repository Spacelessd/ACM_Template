#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
struct heap{
	int* a;
	int len;
	void resize(int x=100){
		x+=5;len=0;
		a=new int[x];
	}
	void up(int x){
		int i=x,j;
		while ((i>1)&&(a[i]<a[i>>1])){
			j=a[i];a[i]=a[i>>1];a[i>>1]=j;
			i>>=1;
		}
	}
	void down(int x){
		int i=x,j,k;
		while (i<<1<=len){
			j=i;
			if (a[i<<1]<a[i])j=i<<1;
			if (((i<<1)+1<=len)&&(a[j]>a[(i<<1)+1]))j=(i<<1)+1;
			if (j==i)break;
			k=a[i];a[i]=a[j];a[j]=k;
			i=j;
		}
	}
	void insert(int x){a[++len]=x;up(len);}
	void build(int *tmp,int n){
		int i;len=n;
		for (i=n;i;i--)a[i]=tmp[i];
		for (i=n/2;i;i--)down(i);
	}
	int min(){return a[1];}
	int delmin(){
		int tmp=a[1];a[1]=a[len--];
		down(1);return tmp;
	}
	void clear(){len=0;}
	int isempty(){
		if (len==0)return 1;
		else return 0;
	}
};
heap a;
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	int n;scanf("%d",&n);
	a.resize(n);
	int x=13251325;
	int t1=clock();
	for (int i=1;i<=n;++i){
		a.insert(x&0x7fffffff);
		//a.insert(i);
		x+=(x<<2)+1;
	}
	for (int i=1;i<=n;++i){
		a.delmin();
		//printf("%d\n",a.delmin());
	}
	printf("time=%d\n",(int)clock()-t1);
	system("pause");for (;;);
	return 0;
}


