#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<iostream>
#include<algorithm>
using namespace std;
#define N 100005
template<class T>
struct zzy{
	/*struct rp{
		int l;
	};
	struct node:public rp{
		void go(){
			l=0;
		}
	}a;*/
	//typedef int T;
	struct node{
		node *l,*r;T key;
		node(){l=(node*)123;}
		node* modify(size_t x,const T& key,size_t size)const{
		}
	};
	struct root_node:public node{
		root_node *next;size_t size;
		root_node* modify(const T& key,size_t x)const{
			/*if (x<size){
				node *tmp=node::modify(x,key,size>>1);
				return Newroot_node(tmp->key,tmp->l,tmp->r,next,size);
			}
			else */
			node *z=node::l;
			printf("%d\n",z);
			//return Newroot_node(key,node::l,node::r,next->modify(node::key,x-size),size);
		}
	}a;
};
zzy<int> A;
int main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	A.a.modify(1,1);
	system("pause");
	return 0;
}


