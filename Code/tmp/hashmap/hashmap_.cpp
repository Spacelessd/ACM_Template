#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define ll long long
template<class Tkey,class Tvalue>
struct hash{
	Tvalue *value;Tkey *key;
	int *v,*next,len,P,size;
	void build(int len=9,int p=11)	//len¸öÊý  hashsize=p
	{
		P=p;len=0;size=len;++len;
		v=new int[p];memset(v,0,sizeof(int)*p);
		value=new Tvalue[len];memset(value,0,sizeof(Tvalue)*len);
		next=new int[len];memset(next,0,sizeof(int)*len);
		key=new Tkey[len];memset(key,0,sizeof(Tkey)*len);
	}
	hash(int len=0,int p=11){
		if (len==0)return;build(len,p);
	}
	int gethash(Tkey x){return x%P;}
	void insert(Tkey x,Tvalue y=0){
		int x1=gethash(x);
		key[++len]=x;value[len]=y;
		next[len]=v[x1];v[x1]=len;
	}
	void del(Tkey x){
		int x1=gethash(x),i=v[x1],pre=0;
		while(i){
			if (key[i]==x){
				if (pre==0)v[x1]=next[i];
					else next[pre]=next[i];
			}
			pre=i;i=next[i];
		}
	 }
	int find(Tkey x){
		int x1=gethash(x),i=v[x1];
		while(i){
			if (key[i]==x)return value[i];
			i=next[i];
		}
		return -1;
	}
	void inc(Tkey x,Tvalue y=1){
		int x1=gethash(x),i=v[x1];
		while(i){
			if (key[i]==x){value[i]+=y;return;}
			i=next[i];
		}
	}
	Tvalue operator [](Tkey x){return find(x);}
};
hash<int,int> a(1000,2000);
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	a.insert(1,3);
	a.insert(3);
	printf("%d\n",a[1]);
	printf("%d\n",a[2]);
	printf("%d\n",a[3]);
	a.del(1);
	printf("%d\n",a[1]);
	system("pause");
	return 0;
}


