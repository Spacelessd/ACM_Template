#ifndef PAIRH

#define PAIRH

class pairingheap
{
	private:
		int *key,*prev,*next,*child,*trees;
		int size,root;
		int compareandlink(int a,int b)
		{
			if(a==0)return b;
			if(b==0)return a;
			if(key[a]<=key[b])
			{
				next[a]=next[b];next[b]=child[a];child[a]=b;prev[b]=a;
				if(next[a]!=0)prev[next[a]]=a;
				if(next[b]!=0)prev[next[b]]=b;
				return a;
			}
			next[b]=next[a];next[a]=child[b];child[b]=a;prev[a]=b;
			if(next[a]!=0)prev[next[a]]=a;
			if(next[b]!=0)prev[next[b]]=b;
			return b;
		}
		int combsib(int a)
		{
			if(a==0)return a;
			if(next[a]==0)return a;
			int num=0,i;
			while(a)
			{
				trees[++num]=a;
				next[prev[a]]=0;
				a=next[a];
			}
			for(i=1;i<=num-1;i+=2)trees[i]=compareandlink(trees[i],trees[i+1]);
			if(i>num)i-=2;
			for(;i>1;i-=2)trees[i-2]=compareandlink(trees[i-2],trees[i]);
			return trees[1];
		}
	public:
		pairingheap(int s=500):size(s),root(0){key=new int [size+1];child=new int [size+1];prev=new int [size+1];next=new int [size+1];trees=new int [size+1];}
		void insert(int i,int newkey)
		{
			key[i]=newkey;
			child[i]=prev[i]=next[i]=0;
			root=compareandlink(root,i);
		}
		int delmin(void)
		{
			if(root==0)return -1;
			int tmpkey=key[root];
			root=combsib(child[root]);
			return tmpkey;
		}
		int findmin(void)
		{
			if(root==0)return -1;
			return key[root];
		}
		int findminpos(void)
		{
			return root;
		}
		int getkey(int a)
		{
			return key[a];
		}
		void decreasekey(int a,int obj)
		{
			if(a==0)return;
			if(key[a]<=obj)return;
			key[a]=obj;
			if(a==root)return;
			if(next[a]!=0)prev[next[a]]=prev[a];
			if(child[prev[a]]==a)child[prev[a]]=next[a];
			else next[prev[a]]=next[a];
			next[a]=0;
			root=compareandlink(root,a);
		}
		bool isempty(void){return root==0?true:false;}
		~pairingheap(){delete [] key;delete [] prev;delete [] next;delete [] child;}
};

#endif
