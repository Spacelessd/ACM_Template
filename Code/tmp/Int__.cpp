#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<iostream>
#include<algorithm>
using namespace std;
class Int{
	public:
	typedef long long value;
	value *a;int len;
	Int():a(NULL){clear();}
	void clear(){
		delete[] a;
		a=new value[1];
		len=1;a[0]=0;
	}
	
	void print(){
		printf("%d",int(a[len-1]));
		for (int i=len-2;i>=0;--i){
			for (int j=base/10;j>=10;j/=10)
				if (a[i]<j)putchar('0');
					else break;
			printf("%d",(int)a[i]);
		}
	}
	private:
	value base;
}a;
int main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	a.print();
	system("pause");
	return 0;
}


