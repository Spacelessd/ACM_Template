#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define ll long long
template<class Tkey,class Tvalue>
struct hash{
	Tkey *key; Tvalue *value;
	int *v,*next,len,P,size;
	void build(int Len=9,int p=11)  //len¸öÊý  hashsize=p
	{
		P=p;len=0;size=Len;++Len;
		v=new int[p];memset(v,0,sizeof(int)*p);
		value=new Tvalue[Len];memset(value,0,sizeof(Tvalue)*Len);
		next=new int[Len];memset(next,0,sizeof(int)*Len);
		key=new Tkey[Len];memset(key,0,sizeof(Tkey)*Len);
	}
	hash(int Len=0,int p=11){
		if (Len==0)return;build(Len,p);
	}
	void clear(){len=0;memset(v,0,sizeof(int)*P);}
	Tkey gethash(Tkey x){return x%P;}
	void insert(Tkey x,Tvalue y=0){
		Tkey x1=gethash(x);
		key[++len]=x;value[len]=y;
		next[len]=v[x1];v[x1]=len;
	}
	void del(Tkey x){
		Tkey x1=gethash(x);int i=v[x1],pre=0;
		while(i){
			if (key[i]==x){
				if (pre==0)v[x1]=next[i];
					else next[pre]=next[i];
			}
			pre=i;i=next[i];
		}
	}
	Tvalue& find(Tkey x){
		Tkey x1=gethash(x);int i=v[x1];
		while(i){
			if (key[i]==x)return value[i];
			i=next[i];
		}
		Tvalue *null=NULL;return *null;
	}
	void inc(Tkey x,Tvalue y=1){
		Tkey x1=gethash(x);int i=v[x1];
		while(i){
			if (key[i]==x){value[i]+=y;return;}
			i=next[i];
		}
	}
	Tvalue& operator [](Tkey x){return find(x);}
};
hash<ll,ll> a(1000,2000);
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	a.insert(1,3);//a[1]=3;
	a.insert(3,0);
	if (&a[1])printf("%d\n",a[1]);else printf("not exist\n");
	if (&a[2])printf("%d\n",a[2]);else printf("not exist\n");
	if (&a[3])printf("%d\n",a[3]);else printf("not exist\n");
	a.del(1);
	if (&a[1])printf("%d\n",a[1]);else printf("not exist\n");
	system("pause");for (;;);
	return 0;
}


