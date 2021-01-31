#include <fstream>
using namespace std;
ifstream fin("pro1.in");
ofstream fout("pro1.out");

const long maxn=1000010;
double A[maxn],tmp[maxn];
long n=0;

void Merge(long p,long q,long r)
{  long t,i=p,j=q;
   for (t=p; t<r; t++)
      if ( (i<q) && ((j==r) || (A[i]<A[j])) ) tmp[t]=A[i++];
      else tmp[t]=A[j++];
   for (t=p; t<r; t++)
      A[t]=tmp[t];
}

void Insert(double x)
{  int k=1;
   A[n++]=x;
   while ( ((n-1)&k)>0 )
   {  Merge(n-k-k,n-k,n);
      k<<=1;
   }
}

long Q(long start,long end,double R,double T)
{  long p,r,q,tmp;

   p=start; r=end;
   while (p<r)
   {  q=(p+r)/2;
      if (A[q]>=R) r=q;
      else p=q+1;
   }
   if (A[p]<R) tmp=p+1;
   else tmp=p;

   p=start; r=end;
   while (p<r)
   {  q=(p+r+1)/2;
      if (A[q]<=T) p=q;
      else r=q-1;
   }
   if (A[p]>T) return p-1-tmp+1;
   else return p-tmp+1;
}

long Query(double r,double t)
{  long st=n,k=1,ans=0;
   while (k<=st)
   {  if ((n&k)>0)
      {  st-=k;
	      ans+=Q(st,st+k-1,r,t);
      }
      k<<=1;
   }
   return ans;
}

main()
{  
	int t1=clock();
	char com;
   double x,r,t;
   while (!fin.eof())
   {  fin>>com;
      if (com=='I')
      {  fin>>x; Insert(x); }
      else if (com=='Q')
      {  fin>>r>>t; fout<<Query(r,t)<<endl; }
   }
   //printf("%d\n",clock()-t1);
   fout<<clock()-t1<<endl;
   fin.close(); fout.close();
   return 0;
}



