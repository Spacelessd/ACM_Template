#include <iostream>  
#include <string.h>  
#include <stdio.h>  
  
using namespace std;  
const int N = 1005;  
  
int a[N],tmp[N];  
int ans;  
  
void Merge(int l,int m,int r)  
{  
    int i = l;  
    int j = m + 1;  
    int k = l;  
    while(i <= m && j <= r)  
    {  
        if(a[i] > a[j])  
        {  
            tmp[k++] = a[j++];  
            ans += m - i + 1;  
        }  
        else  
        {  
            tmp[k++] = a[i++];  
        }  
    }  
    while(i <= m) tmp[k++] = a[i++];  
    while(j <= r) tmp[k++] = a[j++];  
    for(int i=l;i<=r;i++)  
        a[i] = tmp[i];  
}  
  
void Merge_sort(int l,int r)  
{  
    if(l < r)  
    {  
        int m = (l + r) >> 1;  
        Merge_sort(l,m);  
        Merge_sort(m+1,r);  
        Merge(l,m,r);  
    }  
}  
  
int main()  
{  
    int n,T,tt=1;  
    scanf("%d",&T);  
    while(T--)  
    {  
        scanf("%d",&n);  
        for(int i=0;i<n;i++)  
            scanf("%d",&a[i]);  
        ans = 0;  
        Merge_sort(0,n-1);  
        printf("Scenario #%d:\n%d\n\n",tt++,ans);  
    }  
    return 0;  
}  
