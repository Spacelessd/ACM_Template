struct node{
	node *l,*r;
	int min;
	node(node *_l,node *_r,int _min){l=_l,r=_r,min=_min;}
};
#define BUFFER_SIZE 10000
node *buffer=0,*cur;
node *get(){
	if (!buffer||cur==buffer+BUFFER_SIZE)
		cur=buffer=new node[BUFFER_SIZE];
	return ++cur;
}
node* modify(node *t,int x,int min){
}
int main(){
	
}




