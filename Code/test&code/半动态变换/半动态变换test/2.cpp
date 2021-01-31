#include <fstream>
using namespace std;
ifstream fin("pro1.in");
ofstream fout("pro2.out");

const long maxn=1000010;
const int k=4;
double A[maxn],tmp[maxn];
long a[k+1],C[k+1];
long n=0;

void Init()
{  for (int i=1; i<=k; i++)
   {  a[i]=i-1; C[i]=0; }
}

void Merge(long p,long q,long r)
{  long t,i=p,j=q;
   for (t=p; t<r; t++)
      if ( (i<q) && ((j==r) || (A[i]<A[j])) ) tmp[t]=A[i++];
      else tmp[t]=A[j++];
   for (t=p; t<r; t++)
      A[t]=tmp[t];
}

void Insert(double x)
{  int i=1;
   A[n++]=x; Merge(n-C[1]-1,n-1,n);
   a[1]++; C[1]++;
   while ( (i<k) && (a[i]==a[i+1]) )
   {  Merge(n-C[i]-C[i+1],n-C[i],n);
      a[i+1]++; C[i+1]+=C[i];
      a[i]=i-1; C[i]=0;
      i++;
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
{  long st=n,ans=0;
   for (int i=1; i<=k; i++)
      if (C[i]>0)
      {  st-=C[i];
	      ans+=Q(st,st+C[i]-1,r,t);
      }
   return ans;
}


main()
{  char com;
   double x,r,t;
   Init();
   while (!fin.eof())
   {  fin>>com;
      if (com=='I')
      {  fin>>x; Insert(x); }
      else if (com=='Q')
      {  fin>>r>>t; fout<<Query(r,t)<<endl; }
   }
   fin.close(); fout.close();
   return 0;
}

