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
	for (int i=l;i<=r;++i){
		printf("%d ",a[i]);
		if (i>l&&a[i]<a[i-1])printf("WA");
	}
	printf("\n");
}
void check(){
	for (int i=1;i<n;++i)if (a[i]>a[i+1]){
		printf("error\n");
		print(a,1,n);
		system("pause");for (;;);
		exit(0);
	}
}
//基数排序 n log W
void radix_sort(int A[],int l,int r){  //a[i]>=0
	#define base 65535
	#define W 16
	static int B[N],s[base+1];
	A+=l-1;r-=l-1;l=1;
	int *a=A,*b=B,x=0;
	for (int i1=1;i1<=2;++i1){
		for (int i=0;i<=base;++i)s[i]=0;
		for (int i=1;i<=r;++i)++s[a[i]>>x&base];
		for (int i=1;i<=base;++i)s[i]+=s[i-1];
		for (int i=r;i>=1;--i)b[s[a[i]>>x&base]--]=a[i];
		int *tmp=a;a=b;b=tmp;
		x+=W;
	}
	if (a!=A)for (int i=1;i<=r;++i)A[i]=a[i];
	#undef W
	#undef base
}
//快速排序 n log n
void Q(int s,int t){
	int p,i=s,j=t,m=a[(i+j)>>1];//m=a[s+rand()*rand()%(t-s+1)];
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
//快速排序+rand n log n
void insert_sort(int a[],int l,int r);
void Q_plus(int s,int t){
	if (s+15>t){insert_sort(a,s,t);return;}
	int p,i=s,j=t,m=a[s+rand()*rand()%(t-s+1)];//m=a[(s+t)>>1];
	do {
		while (a[i]<m) ++i;
		while (a[j]>m) --j;
		if (i<=j){
			p=a[i]; a[i]=a[j]; a[j]=p;
			++i; --j;
		}
	}while (i<=j);
	if (i<t) Q_plus(i,t);
	if (s<j) Q_plus(s,j);
}
//快速排序+array n log n
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
//平衡树排序 n log n
#include<set>
void multiset_sort(int a[],int l,int r){
	multiset<int> S;S.clear();
	for (int i=l;i<=r;++i)S.insert(a[i]);
	for (multiset<int>::iterator zzy=S.begin();zzy!=S.end();++zzy)a[l++]=*zzy;
}
//堆排序 n log n
#include<queue>
void heap_sort(int a[],int l,int r){
	priority_queue<int> Q;
	for (int i=l;i<=r;++i)Q.push(a[i]);
	for (int i=r;i>=l;--i)a[i]=Q.top(),Q.pop();
}
//归并排序 n log n
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
//字母树排序 n log W
void Trie_sort(int a[],int l,int r){
	#define maxn 1000005
	#define W 31
	struct node{
		node* son[2];
		int cnt;
	};
	static node T[maxn*(W+1)],*root=T;
	int len=0;
	root->son[0]=root->son[1]=NULL;root->cnt=0;
	struct func{
		void operator ()(int key,int &len){
			node *x=root;int id;
			for (int i=W;i>=0;--i){
				id=(key>>i)&1;
				if (!x->son[id]){
					node *son=T+(++len);son->son[0]=son->son[1]=NULL;
					son->cnt=0;x->son[id]=son;
				}
				x=x->son[id];
			}
			++x->cnt;
		}
	}insert;
	for (int i=l;i<=r;++i)insert(a[i],len);
	struct print{
		void operator ()(node *x,int key,int *a,int &l){
			if (!x->son[0]&&!x->son[1]){
				for (int i=1;i<=x->cnt;++i)a[l++]=key;return;
			}
			if (x->son[0])(*this)(x->son[0],key<<1,a,l);
			if (x->son[1])(*this)(x->son[1],(key<<1)+1,a,l);
		}
	}print;
	print(root,0,a,l);
	#undef W
	#undef maxn
}
//希尔排序 n^1.5
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
//希尔排序++ n^1.5
void shell_sort_plus(int a[],int l,int r){
	int delta[]={  //Sedgewick增量
	1073643521, 603906049, 268386305, 150958081, 67084289,
	37730305, 16764929, 9427969, 4188161, 2354689,
	1045505, 587521, 260609, 146305, 64769,
	36289, 16001, 8929, 3905, 2161,
	929, 505, 209, 109, 41,
	19, 5, 1, 0 };
	int delta1=0,d;
	while (1){
		d=delta[delta1++];
		if (d==0)break;
		for (int j=l+d;j<=r;++j){
			int t=a[j],i=j-d;
			while (i>=l&&a[i]>t)a[i+d]=a[i],i-=d;
			a[i+d]=t;
		}
	}
}
//冒泡排序  n^2
void bubble_sort(int a[],int l,int r){
	for (int i=1;i<=r-l;++i)
		for (int j=l;j<r;++j)
			if (a[j]>a[j+1]){
				int tmp=a[j];a[j]=a[j+1];a[j+1]=tmp;
			}
}
//插入排序 n^2
void insert_sort(int a[],int l,int r){
	for (int i=l+1;i<=r;++i){
		int tmp=a[i],j;
		for (j=i-1;j>=l&&a[j]>tmp;--j)a[j+1]=a[j];
		a[j+1]=tmp;
	}
}
//选择排序 n^2
void select_sort(int a[],int l,int r){
	for (int i=l;i<r;++i){
		int id=i;
		for (int j=i+1;j<=r;++j)if (a[j]<a[id])id=j;
		int tmp=a[id];a[id]=a[i];a[i]=tmp;
	}
}
//鸡尾酒排序  n^2
void cocktail_sort(int a[],int l,int r){
	int bottom=1,top=n;bool sorted=0;
	while (!sorted){
		sorted=true;
		for (int i=bottom;i<top;++i)if (a[i]>a[i+1])swap(a[i],a[i+1]),sorted=0;
		--top;
		for (int i=top;i>bottom;--i)if (a[i]<a[i-1])swap(a[i],a[i-1]),sorted=0;
		++bottom;
	}
}
//地精排序 n^2
void gnome_sort(int a[],int l,int r){
	int i=l;
	while (i<=r){
		if (i==l||a[i-1]<=a[i])++i;
		else {int tmp=a[i];a[i]=a[i-1];a[--i]=tmp;}
	}
}
//stooge排序 n^2.7
 void stooge_sort(int a[],int l,int r){
	if (a[l]>a[r])swap(a[l],a[r]);
	if (l+1>=r)return;
	int k=(r-l+1)/3;
	stooge_sort(a,l,r-k);
	stooge_sort(a,l+k,r);
	stooge_sort(a,l,r-k);
}
//猴子排序 n!*n
 void bogo_sort(int a[],int l,int r){
	bool can=0;
	while (!can){
		random_shuffle(a+l,a+r+1);can=1;
		for (int i=l+1;i<=r;++i)if (a[i]<a[i-1]){can=0;break;}
	}
}
//图书馆排序 n log n
/*
* length：待排序元素个数
* elements：待排序数组
* factor：常数因子
*/
void library_sort(int elements[], int length, float factor){
	int i, j;
	//扩展后的数组长度
	int expandedLen = (int)((1 + factor) * length);
	int *orderedElem = (int *) malloc(expandedLen * sizeof(int));

	//标志gap
	int flag = 1 << 31;
	for(i = 0; i < expandedLen; i++)
	{
		orderedElem[i] = flag;
	}

	int index = 1;
	int numOfIntercalatedElem = 1;
	orderedElem[0] = elements[0];

	while(length > numOfIntercalatedElem)
	{
		//第i次插入2^(i-1)个元素
		for(j = 0; j < numOfIntercalatedElem; j++)
		{
			//待插入元素为elements[index]
			//------------折半插入---------------
			int mid;
			int low = 0;
			int high = 2 * numOfIntercalatedElem - 1;
			while(low <= high)
			{
				mid = (low + high) / 2;

				int savedMid = mid;
				//如果mid所在位置为gap
				while(orderedElem[mid] == flag)
				{
					if(mid == high)
					{
						//当向右遍历没有找到元素值时，改成向左遍历
						mid = savedMid - 1;
						while(orderedElem[mid] == flag)
						{
							mid--;
						}
						break;
					}
					mid++;
				}

				if(elements[index] > orderedElem[mid])
				{
					low = mid + 1;
					//缩小范围
					while(orderedElem[low] == flag)
					{
						low = low + 1;
					}
				}
				else
				{
					high = mid - 1;
				}
			}

			//把elements[index]插入到orderedElem[high+1]
			//当位置为空，没有存储元素值时...
			if(orderedElem[high+1] == flag)
			{
				orderedElem[high+1] = elements[index];
			}
			else
			{
				//位置非空，首先往前挪动元素，如果前面已满，向后挪动元素
				int temp = high + 1;
				while(orderedElem[temp] != flag)
				{
					temp--;
					if(temp < 0)
					{
						temp = high + 1;
						break;
					}
				}

				//向后移动
				while(orderedElem[temp] != flag)
				{
					temp++;
				}

				while(temp < high)
				{
					orderedElem[temp] = orderedElem[temp+1];
					temp++;
				}

				while(temp > high + 1)
				{
					orderedElem[temp] = orderedElem[temp-1];
					temp--;
				}

				orderedElem[temp] = elements[index];
			}
			//---------------------------------
			index++;
			if(index == length)
			{
				break;
			}
		}

		numOfIntercalatedElem *= 2;
		int generatedIndex;
		//Rebalance...
		for(j = numOfIntercalatedElem; j > 0; j--)
		{
			if(orderedElem[j] == flag)
			{
				continue;
			}
			//原数组元素从i处移到2i处
			generatedIndex = j * 2;
			if(generatedIndex >= expandedLen)
			{
				generatedIndex = expandedLen - 1;
				if(orderedElem[generatedIndex] != flag)
				{
					break;
				}
			}
			orderedElem[generatedIndex] = orderedElem[j];
			orderedElem[j] = flag;
		}
	}
	//测试输出
	/*for(i = 0; i < expandedLen; i++)
	{
		if (orderedElem[i]>=0)printf("%d\n", orderedElem[i]);
	}*/
	int a1=0;
	for (int i=0;i<expandedLen;++i)
		if (orderedElem[i]!=1<<31)a[++a1]=orderedElem[i];
	delete[] orderedElem;
}
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	srand(time(0));static int t1;
	//n log n
	init(8200000);t1=clock(); radix_sort(a,1,n);
	printf("radix sort:time=%d\n",clock()-t1);check();
	init(2800000);t1=clock(); Q_plus(1,n);
	printf("Q_plus:time=%d\n",clock()-t1);check();
	init(2700000);t1=clock(); Q(1,n);
	printf("Q:time=%d\n",clock()-t1);check();
	init(2800000);t1=clock(); std::sort(a+1,a+1+n);
	printf("STL sort:time=%d\n",clock()-t1);check();
	init(2550000);t1=clock(); Qsort(a,1,n);
	printf("Qsort+array:time=%d\n",clock()-t1);check();
	init(280000);t1=clock(); multiset_sort(a,1,n);
	printf("multiset sort:time=%d\n",clock()-t1);check();
	init(360000);t1=clock(); heap_sort(a,1,n);
	printf("heap(priority_queue) sort:time=%d\n",clock()-t1);check();
	init(1400000);t1=clock(); merge_sort(a,1,n);
	printf("merge sort:time=%d\n",clock()-t1);check();
	init(430000);t1=clock(); Trie_sort(a,1,n);
	printf("Trie sort:time=%d\n",clock()-t1);check();
	init(250000);t1=clock(); library_sort(a,n+1,2.5);
	printf("library sort:time=%d\n",clock()-t1);check();
	//n^1.5
	init(835000);t1=clock(); shell_sort(a,1,n);
	printf("shell sort:time=%d\n",clock()-t1);check();
	init(1200000);t1=clock(); shell_sort_plus(a,1,n);
	printf("shell sort_plus:time=%d\n",clock()-t1);check();
	//n^2
	init(8500);t1=clock(); bubble_sort(a,1,n);
	printf("bubble sort:time=%d\n",clock()-t1);check();
	init(19500);t1=clock(); insert_sort(a,1,n);
	printf("insert sort:time=%d\n",clock()-t1);check();
	init(16000);t1=clock(); select_sort(a,1,n);
	printf("select sort:time=%d\n",clock()-t1);check();
	init(11000);t1=clock(); cocktail_sort(a,1,n);
	printf("cocktail sort:time=%d\n",clock()-t1);check();
	init(11700);t1=clock(); gnome_sort(a,1,n);
	printf("gnome sort:time=%d\n",clock()-t1);check();
	//n^2.7
	init(1000);t1=clock(); stooge_sort(a,1,n);
	printf("stooge sort:time=%d\n",clock()-t1);check();
	//n!*n
	init(10);t1=clock(); bogo_sort(a,1,n);
	printf("bogo sort:time=%d\n",clock()-t1);check();
	system("pause");for (;;);
	return 0;
}
/*
radix sort:time=453
Q_plus:time=500
Q:time=500
STL sort:time=516
Qsort+array:time=516
multiset sort:time=500
heap(priority_queue) sort:time=500
merge sort:time=500
Trie sort:time=578
library sort:time=406
shell sort:time=484
shell sort_plus:time=485
bubble sort:time=485
insert sort:time=500
select sort:time=515
cocktail sort:time=532
gnome sort:time=547
stooge sort:time=656
bogo sort:time=797
*/


