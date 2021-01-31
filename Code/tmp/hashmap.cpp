#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
using namespace std;

struct hash{
      int *key,*v,*next,*e,len,pp,size;
      void build(int ll=9,int p=11)  //ll¸öÊý  hashsize=p
      {
           pp=p;len=0;size=ll;ll++;
           v=new int[p];memset(v,0,4*p);
           key=new int[ll];memset(key,0,4*ll);
           next=new int[ll];memset(next,0,4*ll);
           e=new int[ll];memset(e,0,4*ll);
      }
      hash(int ll=0,int p=11){
			if (ll==0)return;
			build(ll,p);
	  }
      int gethash(int x){return x%pp;} 
      void insert(int x,int y=0){
           int x1=gethash(x);
           e[++len]=x;key[len]=y;
           next[len]=v[x1];
           v[x1]=len;
      }
      void del(int x){
           int x1=gethash(x),pre=0;
	       int i=v[x1];
	       while(i){
	       	 if (e[i]==x){
				if (pre==0)v[x1]=next[i];
				  else next[pre]=next[i];
				}
		     pre=i;i=next[i];
	         }
	  }
      int find(int x){
  	       int x1=gethash(x);
	       int i=v[x1];
	       while(i){
	       	 if (e[i]==x)return key[i];
		     i=next[i];
	         }
           return -1;
      }
      void inc(int x,int y=1){
  	       int x1=gethash(x);
	       int i=v[x1];
	       while(i){
	       	 if (e[i]==x){key[i]+=y;return;}
		     i=next[i];
	         }
      }
      int operator [](int x){return find(x);}   
};

hash a(1000,2000);
int main()
{
	//freopen("hash.in","r",stdin);
	//freopen("hash.out","w",stdout);
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



