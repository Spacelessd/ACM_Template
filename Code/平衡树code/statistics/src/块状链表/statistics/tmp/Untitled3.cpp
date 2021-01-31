#include<stdio.h>
struct T{
struct Block{
		static int Lim;
		int *a,size;
		Block *pre,*next;
		Block(int len){
			a=new int[len+2];size=0;
		}
		void split(int Lim){
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
		}
		void del(int key){
			int p;
			for (p=1;p<=size;++p)
				if (a[p]==key)break;
			if (p>size)return;
			for (int i=p;i<size;++i)a[i]=a[i+1];
			--size;
		}
	};
};

int main(){
	printf("%d\n",T::Block::Lim);
	for (;;);
}
