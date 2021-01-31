#include<stdio.h>
#include<string.h>
#include<stdlib.h>
//#include<math.h>
#define MAX 300
int wx[MAX],wy[MAX],bar[MAX],nrank[MAX];
int sa[MAX],height[MAX];
//int query[MAX][30];
int cmp(int *in,int a,int b,int l)
{
	return in[a] == in[b]&&in[a+l] == in[b+l];
}
int min(int x,int y)
{
	return x > y ? y : x;
}
/*void get_query(int *ai,int len)
{
	int i,k;
	for (i = 0; i< len; i++)
		query[i][0] = ai[i];
	for (k = 1;(int)pow(2.0,k) - 1 < len; k++)
		for (i = 0; i < len; i++)
			if (i + (int)pow(2.0,k) - 1 < len)
				query[i][k] = min(query[i][k-1],query[i+(int)pow(2.0,k-1)][k-1]);
			else break;
}*/
void get_sa(char *s,int *sa)
{
	int len = strlen(s)-1,*rank = wx,*sa_y = wy,*t,i,m = 255;
	for (i = 0; i<= m; i++) bar[i] = 0;
	for (i = 0; i< len; i++) bar[rank[i] = s[i]]++;
	for (i = 0; i< m; i++) bar[i+1] += bar[i];
	for (i = len-1; i>= 0; i--)	sa[--bar[rank[i]]] = i;
	//sa数组保存的是某个名词的后缀的起始位置，对k=1时的排序用的是桶排序，先一个一个进桶，然后再倒出来
	for (int p = 1,k = 1; p < len; k *= 2,m = p)
	{
		for (p = 0,i = len-k; i < len; i++) sa_y[p++] = i;
		for (i = 0; i< len; i++) if (sa[i] >= k) sa_y[p++] = sa[i] - k;
		//要求2k-前缀的sa，需用k-前缀倍增得到，用y数组保存2k-前缀时第二关键字的排序结果，即k-前缀时某位置+k的sa排名
		//容易得到k-前缀时某位置+k有一些已经超出了s的范围，还有一些位置不能作为第二关键字起始位置，可以看出，他们的数目是相等的
		for (i = 0; i< len; i++) nrank[i] = rank[sa_y[i]];
		for (i = 0; i<= m; i++) bar[i] = 0;
		for (i = 0; i< len; i++) bar[nrank[i]] ++;
		for (i = 0; i< m; i++) bar[i+1] += bar[i];
		for (i = len-1; i>= 0; i--) sa[--bar[nrank[i]]] = sa_y[i];
		//对关于第二关键字排好序的序列再按第一关键字排序，用的还是桶排序，nrank[i]纪录的是按第二关键字排好序以后的序列的第一关键字名次序列
		for (t = sa_y,sa_y = rank,rank = t,p = 1,rank[sa[0]] = 0,i = 1; i < len; i++)
			rank[sa[i]] = cmp(sa_y,sa[i-1],sa[i],k)?p-1:p++;
		//这段代码求新的rank数组，原来的rank用sa_y来保存，比较排名相邻的两个后缀的第一和第二关键字是否完全一样，确定不同后缀的数目，用p纪录
	}
}
void get_height(char *s,int *sa,int *height)
{
	int len = strlen(s),*rank = wx,i,j,k = 0;
	for (i = 0; i < len; i++) rank[sa[i]] = i;
	for (i = 0; i < len-1; height[rank[i++]] = k)
		for (k?k--:0,j = sa[rank[i] - 1]; s[i+k] == s[j+k]; k++) printf("%d %d %d\n",k,i,j);
	//计算height用到了辅助数组h，这段代码中没有保留h，只是按照h从0到len-2的顺序计算的，这段代码非常精简，for循环用的出神入化
	//h数组的定义为h[i] = height[rank[i]],所以代码中用后者直接代替了前者，h数组有一个规律 h[i] >= h[i-1] - 1，证明论文里有
	//根据规律，就可以按照顺序计算h数组，计算方法分三种情况，老罗的论文里有
	return;
}
int main()
{
	
	char str[MAX]; int len,i;
	memset(str,0,sizeof(str));
	scanf ("%s",&str);
	len = strlen(str);
	str[len] = '$';str[len+1]='\0';
	get_sa(str,sa);
	 
    //打印sa数组
	printf ("****sa****\n");
	for (i = 0; i< len; i++)
		printf ("%d %d\n",i,sa[i]);
	printf ("**********\n");

	system("pause");
	get_height(str,sa,height);
	//get_query(height,len);
	for (;;);
	return 0;
}
