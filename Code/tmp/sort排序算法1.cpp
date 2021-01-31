#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<algorithm>
using namespace std; 
#define N 10000005
int a[N],n;
void init(int n){
	::n=n;
	//for (int i=1;i<=n;++i)a[i]=10-i;
	//for (int i=1;i<=n;++i)a[i]=rand()%10;
	for (int i=1;i<=n;++i)a[i]=(rand()<<16)+rand();
}
void print(int a[],int l,int r){
	for (int i=l;i<=r;++i)printf("%d ",a[i]);
	printf("\n"); 
} 
//øÏÀŸ≈≈–Ú  n log n
void Q(int s,int t){
	int p,i=s,j=t,m=a[(i+j)>>1];
	do {
		while (a[i]<m) ++i;
		while (a[j]>m) --j;
		if (i<=j){
			p=a[i]; a[i]=a[j]; a[j]=p;
			++i; --j;
		}
	}while (i<=j);
	if (i<t) Q(i,t);
	if (s<j) Q(s,j);
}
//øÏÀŸ≈≈–Ú  n log n
void Qsort(int a[],int s,int t){
	int p,i=s,j=t,m=a[(i+j)>>1];
	do {
		while (a[i]<m) ++i;
		while (a[j]>m) --j;
		if (i<=j){
			p=a[i]; a[i]=a[j]; a[j]=p;
			++i; --j;
		}
	}while (i<=j);
	if (i<t) Qsort(a,i,t);
	if (s<j) Qsort(a,s,j);
}
//∆Ω∫‚ ˜≈≈–Ú n log n
#include<set>
void multiset_sort(int a[],int l,int r){
	multiset<int> S;S.clear(); 
	for (int i=l;i<=r;++i)S.insert(a[i]);
	for (multiset<int>::iterator zzy=S.begin();zzy!=S.end();++zzy)a[l++]=*zzy; 
}
//∂—≈≈–Ú n log n
#include<queue> 
void heap_sort(int a[],int l,int r){
	priority_queue<int> Q; 
	for (int i=l;i<=r;++i)Q.push(a[i]); 
	for (int i=r;i>=l;--i)a[i]=Q.top(),Q.pop(); 
}
//πÈ≤¢≈≈–Ú n log n
void merge(int a[],int l,int mid,int r){
	static int b[N];int i=l,j=mid+1;
	for (int k=l;k<=r;++k)
		if (i<=mid&&(j>r||a[i]<a[j]))b[k]=a[i++];
		else b[k]=a[j++];
	for (int i=l;i<=r;++i)a[i]=b[i];
}
void merge_sort(int a[],int l,int r){
	if (l==r)return;
	int mid=(l+r)>>1;
	merge_sort(a,l,mid);merge_sort(a,mid+1,r);
	merge(a,l,mid,r);
} 
//√∞≈›≈≈–Ú  n^2
void bubble_sort(int a[],int l,int r){
	for (int i=1;i<=r-l;++i)
		for (int j=l;j<r;++j)
			if (a[j]>a[j+1]){
				int tmp=a[j];a[j]=a[j+1];a[j+1]=tmp;
			} 
}
//≤Â»Î≈≈–Ú n^2
void insert_sort(int a[],int l,int r){
	for (int i=l+1;i<=r;++i){
		int tmp=a[i],j;
		for (j=i-1;j>=l&&a[j]>tmp;--j)a[j+1]=a[j];
		a[j+1]=tmp;
	}
}
//—°‘Ò≈≈–Ú n^2
void select_sort(int a[],int l,int r){
	for (int i=l;i<r;++i){
		int id=i;
		for (int j=i+1;j<=r;++j)if (a[j]<a[id])id=j;
		int tmp=a[id];a[id]=a[i];a[i]=tmp;
	}
}
//œ£∂˚≈≈–Ú n^1.5
void shell_sort(int a[],int l,int r){
	int d=r-l+1;
	while (d>1){
		d/=2;
		for (int j=l+d;j<=r;++j){
			int t=a[j],i=j-d;
			while (i>=l&&a[i]>t)a[i+d]=a[i],i-=d;
			a[i+d]=t; 
		} 
	} 
}
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	srand(time(0));static int t1;
	//n log n 
	init(2700000);t1=clock(); Q(1,n);
	printf("Q:time=%d\n",clock()-t1);
	init(2800000);t1=clock(); std::sort(a+1,a+1+n);
	printf("STL:time=%d\n",clock()-t1);
	init(2550000);t1=clock(); Qsort(a,1,n);
	printf("Qsort:time=%d\n",clock()-t1);
	init(300000);t1=clock(); multiset_sort(a,1,n);
	printf("multiset sort:time=%d\n",clock()-t1);
	init(370000);t1=clock(); heap_sort(a,1,n);
	printf("heap sort:time=%d\n",clock()-t1);
	init(1400000);t1=clock(); merge_sort(a,1,n);
	printf("merge sort:time=%d\n",clock()-t1);
	//n^1.5
	init(840000);t1=clock(); shell_sort(a,1,n);
	printf("shell sort:time=%d\n",clock()-t1);
	//n^2
	init(8400);t1=clock(); bubble_sort(a,1,n);
	printf("bubble sort:time=%d\n",clock()-t1);
	init(20000);t1=clock(); insert_sort(a,1,n);
	printf("insert sort:time=%d\n",clock()-t1);
	init(16000);t1=clock(); select_sort(a,1,n);
	printf("select sort:time=%d\n",clock()-t1);
	system("pause");for (;;);
	return 0;
}
/*
Q:time=484
STL:time=515
Qsort:time=500
multiset sort:time=500
heap sort:time=531
merge sort:time=500
shell sort:time=500
bubble sort:time=468
insert sort:time=516
select sort:time=500
*/


