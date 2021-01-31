
int c[100010];
int n,i;
int lowbit(int x){return x& -x;}
void add(int x,int y)  //将点x的值加上y
{
	for (;x<=n;x+=lowbit(x)) c[x]+=y;
}

int sum(int x)  //统计1-x的总和
{
    int tmp=0;
    for (;x;x-=lowbit(x))tmp+=c[x];
    return tmp;
}

int findkth(int k)  //求第K小的值
{
    int ans=0,cnt=0,i;
    for (i=20;i>=0;i--)
    {
        ans+=(1<<i);
        if (ans>=n||cnt+c[ans]>=k)ans-=(1<<i);
          else cnt+=c[ans];
    }
    return ans+1;
}

int main()
{
    //scanf("%d",&n);
}

