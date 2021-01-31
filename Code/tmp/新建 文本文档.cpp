
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
#define M 20000050

char str1[M],str[2*M];//start from index 1
int rad[M],nn,n;

void Manacher(int *rad,char *str,int n)/*str是这样一个字符串（下标从1开始）：
举例：若原字符串为"abcd"，则str为"$#a#b#c#d#"，最后还有一个终止符。
n为str的长度，若原字符串长度为nn，则n=2*nn+2。
rad[i]表示回文的半径，即最大的j满足str[i-j+1...i] = str[i+1...i+j]，
而rad[i]-1即为以str[i]为中心的回文子串在原串中的长度*/
{
    int i;
    int mx = 0;
    int id;
    for(i=1; i<n; i++)
    {
        if( mx > i )
			rad[i] = rad[2*id-i]<mx-i?rad[2*id-i]:mx-i;        
        else
            rad[i] = 1;
        for(; str[i+rad[i]] == str[i-rad[i]]; rad[i]++)
            ;
        if( rad[i] + i > mx )
        {
            mx = rad[i] + i;
            id = i;
        }
    }
}

n#a#a#e
int main()
{
	int i,ans,Case=1;
	while(scanf("%s",str1)!=EOF)
	{
		nn=strlen(str1);
		n=2*nn+2;
		str[0]='$';
		printf("nie%d\n",nn);
		for(i=0;i<=nn;i++)
		{
			str[2*i+1]='#';
			str[2*i+2]=str1[i];
		}
		Manacher(rad,str,n);
		ans=1;
		for(i=0;i<n;i++)
			ans=rad[i]>ans?rad[i]:ans;
		printf("%d\n",ans-1);
	}
return 0;
}
