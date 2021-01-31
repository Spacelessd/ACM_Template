#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<iostream>
using namespace std;

template <typename tname,typename tkey>
class hash{
      int *key,*v,*next,*e,ll,pp,maxlen;
      hash(int p,int size)
      {
            key=new int[2];
            v=new int[2];
            next=new int[2];
            e=new int[2];
            pp=2;
            ll=0;
            maxlen=2;
      }
      void insert(int x,int y)
      {
           int x1=x%pp;
           ll++;
           e[ll]=x;key[ll]=y;
           next[ll]=v[x1];
           v[x1]=ll;
      }
      void insert(int x,int y)
      {
      	   int x1=x%pp;
       	   ll++;
     	   e[ll]=x;key[ll]=y;
     	   next[ll]=v[x1];
	       v[x1]=ll;
       }
int find(int x)
{
	int x1=x%pp;
	int i=v[x1];
	while(i!=0){
		if (e[i]==x)return key[i];
		i=next[i];
	}
	return -1;
}
};

hash<int,int> a;
int main()
{
	//freopen("hash.in","r",stdin);
	//freopen("hash.out","w",stdout);
	system("pause");
	return 0;
}

