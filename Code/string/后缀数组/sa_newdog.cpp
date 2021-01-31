#include <ctime>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const	int N=200005;
int		n,m,Max;
int		a[N],b[N];
int		sa[N],rank[N],tmp[N],h[N],last[20],cnt[N];
int		Right[N];
char	ch[N];

inline bool check(int d){
	int st=1,cnt=0;
	memset(last,0,sizeof(last));
	if (sa[1]+d-1<=Right[b[sa[1]]])
		last[b[sa[1]]]=1,cnt=1;
	for (int i=2;i<=m;i++){
		if (h[i]>=d){
			if (last[b[sa[i]]]<st && sa[i]+d-1<=Right[b[sa[i]]])
				cnt++;
			if (cnt>=n)
				return	1;
		}
		else{
			st=i,cnt=0;
			if (sa[i]+d-1<=Right[b[sa[i]]])
				cnt=1;
		}
		if (sa[i]+d-1<=Right[b[sa[i]]])
			last[b[sa[i]]]=i;
	}
	return 0;
}

int main(){
	freopen("s.in","r",stdin);
	freopen("s.out","w",stdout);
	
	int test;
	for (scanf("%d",&test);test--;){
		scanf("%d",&n);
		m=Max=0;
		memset(a,0,sizeof(a));
		memset(rank,0,sizeof(rank));
		for (int i=1;i<=n;i++){
			scanf("%s",ch);
			if (strlen(ch)>Max)
				Max=strlen(ch);
			for (int j=0,L=strlen(ch);j<L;j++){
				a[++m]=ch[j]-'a'+1;
				b[m]=i;
			}
			Right[i]=m;
		}
		
		if (n==1){
			printf("%d\n",Max);
			continue;
		}
		
		for (int i=0;i<=26;i++)	cnt[i]=0;
		for (int i=1;i<=m;i++)	cnt[a[i]]++;
		for (int i=1;i<=26;i++)	cnt[i]+=cnt[i-1];
		for (int i=1;i<=m;i++)	sa[cnt[a[i]]--]=i;
		rank[sa[1]]=1;
		for (int i=2;i<=m;i++)
		if (a[sa[i]]==a[sa[i-1]])
			rank[sa[i]]=rank[sa[i-1]];
		else
			rank[sa[i]]=rank[sa[i-1]]+1;
			
		for (int k=1;k<m;k*=2){
			
			memset(tmp,0,sizeof(tmp));
			for (int i=0;i<=m;i++)	cnt[i]=0;
			for (int i=1;i<=m;i++)	cnt[rank[i+k]]++;
			for (int i=1;i<=m;i++)	cnt[i]+=cnt[i-1];
			for (int i=m;i;i--)		tmp[cnt[rank[i+k]]--]=i;
			
			for (int i=0;i<=m;i++)	cnt[i]=0;
			for (int i=1;i<=m;i++)	cnt[rank[tmp[i]]]++;
			for (int i=1;i<=m;i++)	cnt[i]+=cnt[i-1];
			for (int i=m;i;i--)		sa[cnt[rank[tmp[i]]]--]=tmp[i];
			
			for (int i=1;i<=m;i++)
				tmp[i]=rank[i];
			
			rank[sa[1]]=1;
			
			for (int i=2;i<=m;i++)
			if (tmp[sa[i]]==tmp[sa[i-1]] && tmp[sa[i]+k]==tmp[sa[i-1]+k])
				rank[sa[i]]=rank[sa[i-1]];
			else
				rank[sa[i]]=rank[sa[i-1]]+1;
			
			if (rank[sa[m]]==m)break;
		}
		
		for (int i=1;i<=m;i++){
			int t=h[rank[i-1]]-1;
			if (t<0)	t=0;
			t=min(t,min(m-i+1,m-sa[rank[i]-1]+1));
			if (rank[i]==1)
				t=0;
			else
			while (i+t<=m && sa[rank[i]-1]+t<=m && a[i+t]==a[sa[rank[i]-1]+t])
				++t;
			h[rank[i]]=t;
		}
		
		int head=0,tail=Max+1,mid;
		while (head+1<tail){
			mid=head+tail>>1;
			if (check(mid))	head=mid;
			else			tail=mid;
		}
		printf("%d\n",head);
	}
	return 0;
}


