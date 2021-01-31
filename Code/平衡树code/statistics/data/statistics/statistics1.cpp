#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define LL long long

const	int N=200010,mod=1000000007;

int		n;
int		f[N];
int		heap1[N],heap2[N],tot1,tot2;
LL		ans,a,b,c;

bool cmp(int x,int y,int z){
	if (!z)		return	x<y;
	return		x>y;
}

inline void Insert(int heap[],int &tot,int t,int d){
	int i;
	for (i=++tot;i>1;i>>=1)
	if (cmp(heap[i>>1],d,t))
		heap[i]=heap[i>>1];
	else
		break;
	heap[i]=d;
}

inline void Down(int heap[],int &tot,int t){
	int i,j,d=heap[1];
	for (i=1,j;(j=i<<1)<=tot;i=j){
		if (j<tot && cmp(heap[j],heap[j+1],t))
			j++;
		if (cmp(d,heap[j],t))
			heap[i]=heap[j];
		else
			break;
	}
	heap[i]=d;
}

int main(){
	freopen("statistics.in","r",stdin);
	freopen("statistics.out","w",stdout);
	
	cin >> a >> b >> c >> n;
	
	f[1]=1;
	
	Insert(heap1,tot1,0,f[1]);
	
	for (int i=2;i<=n;i++){
		f[i]=(a*heap1[1]+b*i+c)%mod;
		if (i&1)
			Insert(heap1,tot1,0,f[i]);
		else
			Insert(heap2,tot2,1,f[i]);
		while (heap2[1]<heap1[1]){
			swap(heap2[1],heap1[1]);
			Down(heap1,tot1,0);
			Down(heap2,tot2,1);
		}
	}
	
	ans=0;
	for (int i=1;i<=n;i++)
		ans+=f[i];
	cout << ans << endl;
	
	return 0;
}
