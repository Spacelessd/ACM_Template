#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
using namespace std;
struct trie{
	typedef int rp[2];
	int *t;
	rp *a;
	int ll,len,t1,oo;
	trie(int x,int y=25,int lenlen=-1)
	{
		oo=2147483647;
		t=new int[y+2];
		if (lenlen==-1) lenlen=(x+1)*y;
		a=new rp[lenlen];
		a[0][0]=a[0][1]=0;
		ll=0;len=y;
		t[0]=0;
	}
	~trie()
	{
		delete[] t;
		delete[] a;
	}
	void insert(int key)
	{
		int i,x=0;
		char tmp;
		for (i=len-1;i>=0;i--)
		{
			if (key&(1<<i))tmp=1;
				else tmp=0;
			if (!a[x][tmp]){
				ll++;a[ll][0]=a[ll][1]=0;
				a[x][tmp]=ll;
			}
			x=a[x][tmp];
		}
		a[x][0]++;
	}
	void del(int key)
	{
		int i,x=0;
		char tmp;
		t1=0;
		for (i=len-1;i>=0;i--)
		{
			if (key&(1<<i))tmp=1;
				else tmp=0;
			x=a[x][tmp];
			t[++t1]=x;
		}
		a[x][0]--;
		if (a[x][0]==0){
			for(i=t1-1;i>=1;i--)
			if ((a[t[i]][0]!=0)&&(a[t[i]][1]!=0)){
				break;
			}
			if (a[t[i]][0]==t[i+1])a[t[i]][0]=0;
			else a[t[i]][1]=0;
		}
	}
	int pred(int key)
	{
		int i,x=0,ans=0;
		char tmp;
		bool bo=0;
		t1=0;
		for (i=len-1;i>=0;i--)
		{
			if (key&(1<<i))tmp=1;
				else tmp=0;
			ans=(ans<<1)+tmp;
			x=a[x][tmp];
			t[++t1]=x;
		}
		if (a[x][0]>1)return key;
		ans>>=1;
		for(i=t1-1;i>=0;i--)
			if ((a[t[i]][0])&&(a[t[i]][0]!=t[i+1])){
				bo=1;break;
			}
			else ans>>=1;
		if (bo==0)return oo;
		x=a[t[i]][0];ans<<=1;
		for(i=i+2;i<=t1;i++)
		{
			if (a[x][1]){
				ans<<=1;ans++;
				x=a[x][1];
			}
			else {
				ans<<=1;
				x=a[x][0];
			}
		}
		return ans;
	}
	int succ(int key)
	{
		int i,x=0,ans=0;
		char tmp;
		bool bo=0;
		t1=0;
		for (i=len-1;i>=0;i--)
		{
			if (key&(1<<i))tmp=1;
				else tmp=0;
			ans=(ans<<1)+tmp;
			x=a[x][tmp];
			t[++t1]=x;
		}
		if (a[x][0]>1)return key;
		ans>>=1;
		for(i=t1-1;i>=0;i--)
			if ((a[t[i]][1])&&(a[t[i]][1]!=t[i+1])){
				bo=1;break;
			}
			else ans>>=1;
		if (bo==0)return oo;
		x=a[t[i]][1];ans<<=1;ans++;
		for(i=i+2;i<=t1;i++)
		{
			if (a[x][0]){
				ans<<=1;
				x=a[x][0];
			}
			else {
				ans<<=1;ans++;
				x=a[x][1];
			}
		}
		return ans;
	}
	int min(){
		int i,x=0,ans=0;
		for (i=1;i<=len;i++)
			if (a[x][0]){
				ans<<=1;
				x=a[x][0];
			}
			else {
				ans<<=1;ans++;
				x=a[x][1];
			}
		return ans;
	}
	int max(){
		int i,x=0,ans=0;
		for (i=1;i<=len;i++)
			if (a[x][1]){
				ans<<=1;ans++;
				x=a[x][1];
			}
			else {
				ans<<=1;
				x=a[x][0];
			}
		return ans;
	}
	void dfs(int deep,int x,int ans)
	{
		if (deep==len){
			printf("%d\n",ans);
			return;
		}
		if (a[x][0])dfs(deep+1,a[x][0],ans<<1);
		if (a[x][1])dfs(deep+1,a[x][1],(ans<<1)+1);
	}
	void print(){dfs(0,0,0);}
	void empty(){
		ll=0;
		a[0][0]=a[0][1]=0;
	}
	int isempty()
	{
		if ((a[0][0]==0)&&(a[0][1]==0)) return 1;
		else return 0;
	}
};
const int N=10;
int tmp[N+5];
trie a(N+5,30);
int i;
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	srand(time(0));
	//for(i=1;i<=nn;i++) tmp[i]=rand()*32768+rand();
	for(i=1;i<=N;++i)tmp[i]=i;
	printf("start\n");
	int t1=clock();
	for(i=1;i<=N;++i) a.insert(tmp[i]);
	a.print();
	printf("rp\n");
	printf("min=%d\n",a.min());
	printf("max=%d\n",a.max());
	printf("pred(4)=%d\n",a.pred(4));
	printf("succ(4)=%d\n",a.succ(4));
	printf("pred(1)=%d\n",a.pred(1));
	a.del(3);a.del(5);
	printf("pred(4)=%d\n",a.pred(4));
	printf("succ(4)=%d\n",a.succ(4));
	printf("time=%d\n",clock()-t1);
	system("pause");for (;;);
	return 0;
}


