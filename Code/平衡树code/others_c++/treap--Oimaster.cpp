#include<iostream>
using namespace std;
#define maxn 100005
struct node{
	int key,pri;
	node *ch[2];
}*root,*Null,tree[maxn];
int n,tot=0;
node *New_Node(int x){
	node *p=&tree[tot++];
	p->key=x,p->pri=rand()*rand(),p->ch[0]=p->ch[1]=Null;
	return p;
}
void Rotate(node* &x,int c){
	node *y=x->ch[c];
	x->ch[c]=y->ch[!c];
	y->ch[!c]=x,x=y;
}
void Insert(node* &now,node* new_node){
	if (now==Null){
		now=new_node;
		return;
	}
	int t=new_node->key>now->key;
	Insert(now->ch[t],new_node);
	if (now->ch[t]->pri>now->pri) Rotate(now,t);
}
void print(node* x){
	if (x==Null) return;
	print(x->ch[0]),cout<<x->key<<" ",print(x->ch[1]);
}
int main(){
	srand(time(NULL));
	cin>>n;
	Null=New_Node(0),root=Null;
	for (int i=0;i<n;i++){
		int x;
		cin>>x;
		Insert(root,New_Node(x));
	}
	print(root);
	cout<<"\n";
	system("pause");
	return 0;
}
