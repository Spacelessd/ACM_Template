#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
#define N 110005

char tmp1[N],tmp2[N],s[N],tt[N];
int tmp[N],ans,ne1[N],ne2[N];

char *rev(char *str,int ll)
{
	for(int i=0;i<ll;i++)
		tt[i]=str[ll-i-1];
	tt[ll]=0;
	return tt;
}

void getA(char *pat,int *aa)
{
	int j=0;
	while(pat[1+j] && pat[j]==pat[1+j])
		j++;
	aa[1]=j;
	int k=1;
	int len,l;
	for(int i=2;pat[i];i++)
	{
		len=k+aa[k];
		l=aa[i-k];
		if(l<len-i)
			aa[i]=l;
		else
		{
			j=(0>len-i)?0:len-i;
			while(pat[i+j] && pat[j]==pat[i+j])
				j++;
			aa[i]=j;
			k=i;
		}
	}
}

void getB(char *pat,char *str,int *bb,int length)
{
	getA(pat,tmp);
	int j=0;
	while(pat[j] && str[j] && pat[j]==str[j])
		j++;
	bb[0]=j;
	int k=0;
	int len,l;
	for(int i=1;i<length;i++)
	{
		len=k+bb[k];
		l=tmp[i-k];
		if(l<len-i)
			bb[i]=l;
		else
		{
			j=(0>len-i)?0:len-i;
			while(i+j<length && pat[j] && pat[j]==str[i+j])
				j++;
			bb[i]=j;
			k=i;
		}
	}
}

void find(int l,int r)
{
	if(r-l+1<=ans)
		return;
	int x;
	int mid=(l+r)/2;
	strncpy(tmp1,s+l,mid-l+1);
	tmp1[mid-l+1]=0;
	strncpy(tmp2,s+mid+1,r-mid);
	tmp2[r-mid]=0;
	getB(tmp2,rev(s+l,r-l+1),ne1,r-l+1);
	getB(rev(tmp1,mid-l+1),s+l,ne2,r-l+1);
	ne1[r-l+1]=ne2[r-l+1]=0;
	for(int i=l;i<=mid;i++)
	{
		if(ne2[i-l]*2>=mid-i+1)
		{
			x=mid-i+1+ne1[r-i+1]*2;
			if(ans<x)
				ans=x;
		}
	}
	if(ans<2*ne2[mid+1-l])
		ans=2*ne2[mid+1-l];
	for(int i=mid+1;i<=r;i++)
	{
		if(ne1[r-i]*2>=i-mid)
		{
			x=i-mid+ne2[i-l+1]*2;
			if(ans<x)
				ans=x;
		}
	}
	find(l,mid);
	find(mid+1,r);
}

int main()
{
	while(scanf("%s",s)!=EOF)
	{
		ans=1;
		find(0,strlen(s)-1);
		printf("%d\n",ans);
	}
return 0;
}


