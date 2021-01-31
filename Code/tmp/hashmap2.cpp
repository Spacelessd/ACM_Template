#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<iostream>
using namespace std;

class hash{
      public:
      int *key,*v,*next,*e,maxsize,maxlen,len,pp;
      void newhash(int len)
      {
           delete[]key;
           delete[]v;
           delete[]next;
           delete[]e;
           maxsize=len;maxlen=int(0.75*len);pp=len;size=0;
           key=new int[4];memset(key,0,4*maxsize);
           v=new int[4];memset(v,0,4*maxsize);
           next=new int[4];memset(next,0,4*maxsize);
           e=new int[4];memset(e,0,4*maxsize);
      }
      hash(int p,int size)
      {
            newhash(10);
      }
      
      void insert(int x,int y)
      {
           if (size+1>maxsize)newhash(maxsize
           int x1=x%pp;
           e[++size]=x;key[size]=y;
           next[size]=v[x1];
           v[x1]=size;
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

hash a;
int main()
{
	//freopen("hash.in","r",stdin);
	//freopen("hash.out","w",stdout);
	system("pause");
	return 0;
}



