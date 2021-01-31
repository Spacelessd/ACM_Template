#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#define N 100005
#define maxLim 2005
#define maxNum 2005
#define LLL long long
#define oo (1LL<<60)
#define eps (0.00001)
inline LLL max(LLL x,LLL y){return x>y?x:y;}
inline LLL min(LLL x,LLL y){return x<y?x:y;}
struct block{
	LLL start,size,add,delta;
	LLL a[maxLim];
	int f[maxLim],f1;
	float cha(float x1,float y1,float x2,float y2){return x1*y2-x2*y1;}
	void ini(){
		f1=0;
		for (int i=1;i<=size;++i){
			while (f1>1&&cha(i-f[f1],a[i]-a[f[f1]],f[f1]-f[f1-1],a[f[f1]]-a[f[f1-1]])<=0)--f1;
			f[++f1]=i;
		}
	}
	LLL getpre(int x){
		if (x==1)return -oo;
		else return -(a[f[x]]-a[f[x-1]])/(f[x]-f[x-1]);
	}
	LLL getnext(int x){
		if (x==f1)return oo;
		else return -(a[f[x+1]]-a[f[x]])/(f[x+1]-f[x]);
	}
};
block kuai[maxNum];
LLL s[N];
LLL n,m,x,y,z,Lim,Num,ch,ans,start;
int i,j;
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	scanf("%I64d",&n);
	Lim=(LLL)(sqrt(n)/1.3+1);
	Num=n/Lim;if (n%Lim)++Num;
	for (i=1;i<=n;++i)scanf("%I64d",&s[i]);
	for (i=1;i<=n;++i)s[i]=s[i-1]+s[i];
	for (i=1;i<=Num;++i){
		LLL l=(i-1)*Lim,r=i*Lim>n?n:i*Lim;
		kuai[i].start=l;kuai[i].size=r-l;
		for (j=1;j<=kuai[i].size;++j)kuai[i].a[j]=s[kuai[i].start+j];
		kuai[i].ini();
	}
	scanf("%I64d",&m);
	while (m--){
		scanf("%I64d%I64d%I64d",&ch,&x,&y);
		if (ch==0){
			scanf("%I64d",&z);start=0;
			for (i=1;i<=Num;++i){
				int ll=max(start+1,x),rr=min(start+kuai[i].size,y);
				if (rr-ll+1==kuai[i].size)kuai[i].delta+=z,kuai[i].add+=z*(kuai[i].start+1-x);
				else if (rr>=ll){
					for (j=ll;j<=rr;++j)kuai[i].a[j-start]+=z*(j-ll+1);
					int A=z*(rr-ll+1);
					for (j=rr+1;j<=start+kuai[i].size;++j)kuai[i].a[j-start]+=A;
					kuai[i].ini();
					if (x<=kuai[i].start)kuai[i].add+=z*(start+1-x);
				}
				else if (start>=y)kuai[i].add+=z*(y-x+1);
				start+=kuai[i].size;
			}
		}
		else {
			ans=-oo;start=0;
			for (i=1;i<=Num;++i){
				int ll=max(start+1,x),rr=min(start+kuai[i].size,y);
				if (rr-ll+1==kuai[i].size){
					LLL l=1,r=kuai[i].f1,mid;
					LLL L,R;
					while (l<=r){
						mid=(l+r)>>1;
						L=kuai[i].getpre(mid),R=kuai[i].getnext(mid);
						if (L<=kuai[i].delta&&R>=kuai[i].delta)break;
						if (kuai[i].delta<L)r=mid-1;
							else l=mid+1;
					}
					ans=max(ans,kuai[i].add+kuai[i].a[kuai[i].f[mid]]+kuai[i].delta*kuai[i].f[mid]);
					if (mid+1<=kuai[i].f1)ans=max(ans,kuai[i].add+kuai[i].a[kuai[i].f[mid+1]]+kuai[i].delta*kuai[i].f[mid+1]);
					if (mid-1>=1)ans=max(ans,kuai[i].add+kuai[i].a[kuai[i].f[mid-1]]+kuai[i].delta*kuai[i].f[mid-1]);
 				}
				else if (rr>=ll)
					for (j=ll;j<=rr;++j)ans=max(ans,kuai[i].add+kuai[i].a[j-start]+kuai[i].delta*(j-start));
				start+=kuai[i].size;
			}
			printf("%I64d\n",ans);
		}
	}
	system("pause");for (;;);
	return 0;
}


