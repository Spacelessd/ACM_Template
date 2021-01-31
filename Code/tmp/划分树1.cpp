#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<algorithm>
#include<time.h>
#define maxn 200010
int n,m,i,x,y,z;
struct tree{
    int key[maxn],num[maxn];
}T[20];
int a[maxn];
void build(int l,int r,int dep){
     if (l==r)return;
     int i,mid=(l+r)>>1,ll=l-1,rr=mid,sum=0,equal=0,*Key=T[dep].key,*KEY=T[dep+1].key,*NUM=T[dep].num+l-1;
     for (i=l;i<=r;++i)if (T[dep].key[i]<a[mid])++equal;
     equal=mid-l-1-equal;
     for (i=l;i<=r;++i)
         if (Key[i]<a[mid]){
            KEY[++ll]=Key[i];*(++NUM)=++sum;
            }
         else if (Key[i]==a[mid]&&equal){
              --equal;KEY[++ll]=Key[i];*(++NUM)=++sum;
              }
         else {
              KEY[++rr]=Key[i];*(++NUM)=sum;
              }
     build(l,mid,dep+1);
     build(mid+1,r,dep+1);
}
int Query(int l,int r,int ll,int rr,int k,int dep){
    if ((l==ll)&&(r==rr))return a[l+k-1];
    int mid=(l+r)>>1,sx=l==ll?0:T[dep].num[ll-1],sy=T[dep].num[rr];
    if (sy-sx>=k)return Query(l,mid,l+sx,l+sy-1,k,dep+1);
       else return Query(mid+1,r,mid+ll-l-sx+1,mid+rr-l+1-sy,k-(sy-sx),dep+1);
}
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	scanf("%d%d",&n,&m);
	for (i=1;i<=n;++i)scanf("%d",&a[i]);
	memcpy(T[0].key,a,sizeof(int)*(n+1));
	std::sort(a+1,a+1+n);
	build(1,n,0);
	for (i=1;i<=m;++i){
        scanf("%d%d%d",&x,&y,&z);
        printf("%d\n",Query(1,n,x,y,z,0));
        }
	//system("pause");
	return 0;
}














