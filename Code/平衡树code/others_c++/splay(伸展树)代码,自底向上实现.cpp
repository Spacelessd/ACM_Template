/*
*splay基本操作
*不考虑相同元素,若存在相同元素,则增加一个域来记录元素个数
*/
#include <cstdlib>
#include <cstdio>
using namespace std;

const int maxn=10001;
int lc[maxn],rc[maxn],data[maxn],pr[maxn],size[maxn],tot=0,root;

void zig(int x)//右旋
{
	int y=pr[x],z=pr[y];
	if(lc[z]==y)lc[z]=x;else rc[z]=x;
	pr[x]=z;
	pr[y]=x;
	lc[y]=rc[x];
	rc[x]=y;
	size[x]=size[y];
	size[y]=size[lc[y]]+size[rc[y]]+1;
}

void zag(int x)//左旋
{
	int y=pr[x],z=pr[y];
	if(lc[z]==y)lc[z]=x;else rc[z]=x;
	pr[x]=z;
	pr[y]=x;
	rc[y]=lc[x];
	lc[x]=y;
	size[x]=size[y];
	size[y]=size[lc[y]]+size[rc[y]]+1;
}

void splay(int &root,int x)//把x伸展到root所在的位置
{
	int y,z;
	while(pr[x])
	{
		y=pr[x];
		z=pr[y];
		if(z&&z!=root)
		{
			if(lc[z]==y)
			{
				if(lc[y]==x)
				{
					zig(y);
					zig(x);
				}else{
					zag(x);
					zig(x);
				}
			}else{
				if(rc[y]==x)
				{
					zag(y);
					zag(x);
				}else{
					zig(x);
					zag(x);
				}
			}
		}else if(lc[y]==x)zig(x);else zag(x);
	}
	root=x;
}

void ins(int &k,int key,int p)//插入值为key的元素
{
	if(!k)
	{
		k=++tot;
		size[k]=1;
		lc[k]=rc[k]=0;
		data[k]=key;
		pr[k]=p;
		return;
	}
	++size[k];
	if(key<data[k])ins(lc[k],key,k);else ins(rc[k],key,k);
}

/*
int find(int k,int key)//在以k为根的树中查找值为key的元素
{
	int temp=k;
	while(k)
		if(data[k]==key)break;
		else if(key<data[k])k=lc[k];
		else k=rc[k];
	if(k)splay(temp,k);
	return k;
}

void del(int fa,int i,int &k,int key)//在以k为根的树中删除值为key的元素
{
	int x=find(k,key),temp=lson=lc[x],rson=rc[x];
	pr[lson]=pr[rson]=0;
	lc[x]=rc[x]=0;
	if(lson==0)k=rson;
	else{
		while(rc[lson])lson=rc[lson];
		splay(temp,lson);
		rc[lson]=rson;
		pr[rson]=lson;
		k=lson;
	}
	if(fa&&i==1)rc[fa]=k;else if(fa&&i==0)lc[fa]=k;
}*/

int find(int key)
{
	int k=root;
	while(k)
		if(data[k]==key)break;
		else if(key<data[k])k=lc[k];
		else k=rc[k];
	if(k)splay(root,key);
	return 0;
}

void del(int key)
{
	int x=find(key),lson=lc[x],rson=rc[x];
	pr[lson]=pr[rson]=lc[x]=rc[x]=0;
	if(lson==0)root=rson;
	else{
		while(rc[lson])lson=rc[lson];
		splay(root,lson);
		rc[lson]=rson;
		pr[rson]=lson;
	}
}

int getmin()//返回最小值的下标
{
	int k=root;
	while(lc[k])k=lc[k];
	return k;
}

int getmax()//返回最大值的下标
{
	int k=root;
	while(rc[k])k=rc[k];
	return k;
}

int findkth(int k)//返回第k大值的下标
{
	int t=root;
	while(t)
	{
		if(size[lc[t]]+1==k)break;
		if(k<=size[lc[t]])k=lc[k];
		else{
			k-=size[lc[t]]+1;
			k=rc[t];
		}
	}
	splay(root,t);
	return t;
}

/*递归版
int findpre(int k,int key)//返回值为key的前驱的下标
{
	if(!k)return 0;
	if(key<data[k])return findpre(lc[k],key);
	else{
		int temp=findpre(rc[k],key);
		if(!temp)return k;else return temp;
	}
}*/

int findpre(int key)//返回值为key的前驱的下标
{
	int k=root,ans=0;
	while(k)
		if(key<data[k])k=lc[k];
		else{
			ans=k;
			k=rc[k];
		}
	return ans;
}

/*递归版
int findnex(int k,int key)//返回值为key的后继的下标
{
	if(!k)return 0;
	if(key>data[k])return findnex(rc[k],key);
	else{
		int temp=findnex(lc[k],key);
		if(!temp)return k;else return temp;
	}
}*/

int findnex(int key)//返回值为key的后继的下标
{
	int k=root,ans=0;
	while(k)
		if(key>data[k])k=rc[k];
		else{
			ans=k;
			k=lc[k];
		}
	return ans;
}

int main()
{
	//your main progarm here
	return 0;
}

