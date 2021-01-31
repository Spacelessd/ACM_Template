#include <algorithm>
#include <cstdio>
#define rep(i,n) for(int i=0;i<n;i++)
const int inf=~0U>>2,maxn=1000000;
using namespace std;
int S0[maxn],S1[maxn],n,C[16]={};int*A=S0,*B=S1;
int main(){    
    scanf("%d",&n);rep(i,n)scanf("%d",A+i);    
    rep(x,4)    {        int d=x*4;rep(i,16)C[i]=0;        
    rep(i,n)C[(A[i]>>d)&15]++;rep(i,16)if(i)C[i]+=C[i-1];        
    for(int i=n-1;i>=0;i--)B[--C[(A[i]>>d)&15]]=A[i];       
     swap(A,B);    }
     }

	 