#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string>
#include<map>
#include<ext/hash_map>
using namespace std;
using namespace __gnu_cxx;
//hash_map<int,int,hash<int>,equal_to<int>,allocator<int> > H;
hash_map<int,int> H;
//map<int,int> H;
int main(){
	int n=10000000;
	int t1=clock();
	//hash<int> x;cout<<x(-1)<<endl;
    //H[1]=2;
    for (int i=1;i<=n;++i){
		int x=rand()*rand(),y=rand()*rand();//H.insert(make_pair(x,y));
		H[x]=y;
	}
	//for (hash_map<int,int>::iterator i=H.begin();i!=H.end();++i) 
	//	printf("%d %d\n",i->first,i->second);
	//H[i]=i*i;//,printf("%d\n",H[i]);
    //printf("%d %d\n",H[1],H[2]);
    printf("time=%d\n",clock()-t1);
    system("pause");
    return 0;
}


