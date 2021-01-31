#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define N 100010
#define p 16384  //  1/2
#define Maxlevel 50
struct SkipList{
	struct node{
		node *r,*d;
		int key,size;
	};
	int rand(){
		static unsigned int nie=123456789;
		nie=nie<<5+nie>>2+1;
		return nie&32767;
	}
	void insert(int x){
		
	}
	int findkth(int x){
		
	}
};
int min;
void Ins(){
	
}
void Add(){
	
}
void Dec(){
	
}
void Findkth(){
	
}
int main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	char ch;int n,x;
	scanf("%d%d",&n,&min);
	for (int i=1;i<=min;++i){
		scanf("%c%d",&ch,&x);
		switch (ch){
			case 'I':Ins();
			break;
			case 'A':Add();
			break;
			case 'S':Dec();
			break;
			case 'F':Findkth();
		}
	}
	system("pause");
	return 0;
}




