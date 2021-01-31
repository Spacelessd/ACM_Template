#include<stdio.h>
#include<math.h>
struct BlockList{
	struct Block{
		int *a,size;
		Block *pre,*next;
		Block(int len){
			a=new int [len+2];size=0;
		}
	};
	int Lim;Block *root;
	void set(int n){root=NULL;Lim=(int)sqrt(n)+1;}
	void insert(int key){
		if (!root){
			root=new Block(Lim*2);
			root->pre=root->next=NULL;
			return;
		}
	}
};
BlockList a;
int main(){
	for (;;);
}



