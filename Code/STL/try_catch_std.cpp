#include<iostream.h>                                 //包含头文件
#include<stdlib.h>
double fuc(double x, double y)                        //定义函数
{
	if(y == 0)
	{
		throw y;                                    //除数为0，抛出异常
	}
	return x / y;                                  //否则返回两个数的商
}
int main()
{
	double res;
	try                                            //定义异常
	{
		res = fuc(2, 3);
		cout << "The result of x/y is : " << res << endl;
		res = fuc(4, 0);                             //出现异常
	}
	catch(double)                                    //捕获并处理异常
	{
		cerr << "error of dividing zero.\n";
		system("pause");                                   //异常退出程序
	}
	system("pause");
	return 0;
}


