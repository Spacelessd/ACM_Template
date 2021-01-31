#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
struct BlockList{
	struct Block{
		static int Lim;
		int *a,size;
		Block *pre,*next;
		Block(int len){
			a=new int[len+2];size=0;
		}
		void split(){
			Block *x=new Block(Lim*2);int mid=size>>1;
			for (int i=mid+1;i<=size;++i)
				x->a[i-mid]=a[i];
			x->size=size-mid;size=mid;
			x->next=next;x->pre=this;next=x;
		}
		void merge(Block *x){
			for (int i=1;i<=x->size;++i)
				a[++size]=x->a[i];
			next=x->next;
		}
		void insert(int key){
			int p;
			for (p=1;p<=size;++p)
				if (a[p]>=key)break;
			for (int i=size+1;i>p;--i)a[i]=a[i-1];
			a[p]=key;++size;
			if (size>Lim*2)split();
		}
		void del(int key){
			int p;
			for (p=1;p<=size;++p)
				if (a[p]==key)break;
			if (p>size)return;
			for (int i=p;i<size;++i)a[i]=a[i+1]; --size;
			if (pre&&size+pre->size<=Lim) pre->merge(this);
			if (next&&size+next->size<=Lim) merge(next);
		}
	};
	int Lim;Block *root;
	void set(int n){
		BlockList::Block::Lim=Lim=(int)sqrt(n)+1;root=new Block(Lim*2);
		root->pre=root->next=NULL;
	}
	void insert(int key){
		for (Block *x=root;x;x=x->next)
			if (x->size&&x->a[x->size]>=key||!x->next){
				x->insert(key);return;
			}
		root->insert(key);
	}
	void del(int key){
		for (Block *x=root;x;x=x->next)
			if (x->size&&x->a[1]<=key&&x->a[x->size]>=key){
				x->del(key);return;
			}
	}
	int findkth(int k){
		for (Block *x=root;x;x=x->next)
			if (x->size>=k)
				return x->a[k];
			else k-=x->size;
	}
	void print(){
		for (Block *x=root;x;x=x->next){
			for (int i=1;i<=x->size;++i)printf("%d ",x->a[i]);
			if (x->next)printf("|");
		}
		printf("Pend\n");
	}
};int BlockList::Block::Lim;
BlockList a;
int main()
{
	long long n,A,b,c,m,i,tmp,key,ans=1;
	freopen("statistics.in","r",stdin);
	freopen("statistics.out","w",stdout);
	scanf("%I64d%I64d%I64d%I64d",&A,&b,&c,&n);
	a.set(n);a.insert(1);
	for (i=2;i<=n;++i){
		if ((i-1)&1)tmp=((i-1)>>1)+1;else tmp=(i-1)>>1;
		m=a.findkth(tmp);
		key=(A*m+b*i+c)%1000000007;
		a.insert((int)key);
		ans+=key;
	}
	printf("%I64d\n",ans);
	//system("pause");for (;;);
	return 0;
}


