#include<iostream>
#include<cmath>
#define N 2  // 非线性方程组中方程个数、未知量个数 
#define Epsilon 0.0001  // 差向量1范数的上限
#define Max 100  //最大迭代次数
using namespace std;
const int N2 = 2 * N;
int main()
{
	void ff(float xx[N], float yy[N]); //计算向量函数的因变量向量yy[N]
	void ffjacobian(float xx[N], float yy[N][N]); //计算雅克比矩阵yy[N][N]
	void inv_jacobian(float yy[N][N], float inv[N][N]); //计算雅克比矩阵的逆矩阵inv
	void newdundiedai(float x0[N], float inv[N][N], float y0[N], float x1[N]); //由近似解向量 x0 计算近似解向量 x1
	float x0[N] = {2.0, 0.25}, y0[N], jacobian[N][N], invjacobian[N][N], x1[N], errornorm;
	int i, j, iter = 0;
	//如果取消对x0的初始化，撤销下面两行的注释符，就可以由键盘向x0读入初始近似解向量
	//for( i=0;i<N;i++)
	//	cin>>x0[i];
	cout << "初始近似解向量：" << endl;
	for (i = 0; i < N; i++)
		cout << x0[i] << "  ";
	cout << endl;
	cout << endl;
	do
	{
		iter = iter + 1;
		cout << "第 " << iter << " 次迭代开始" << endl;
		//计算向量函数的因变量向量 y0
		ff(x0, y0);
		//计算雅克比矩阵 jacobian
		ffjacobian(x0, jacobian);
		//计算雅克比矩阵的逆矩阵 invjacobian
		inv_jacobian(jacobian, invjacobian);
		//由近似解向量 x0 计算近似解向量 x1
		newdundiedai(x0, invjacobian, y0, x1);
		//计算差向量的1范数errornorm
		errornorm = 0;
		for (i = 0; i < N; i++)
			errornorm = errornorm + fabs(x1[i] - x0[i]);
		if (errornorm < Epsilon) break;
		for (i = 0; i < N; i++)
			x0[i] = x1[i];
	}
	while (iter < Max);
	system("pause");
	return 0;
}

void ff(float xx[N], float yy[N])
{
	float x, y;
	int i;
	x = xx[0];
	y = xx[1];
	yy[0] = x * x - 2 * x - y + 0.5;
	yy[1] = x * x + 4 * y * y - 4;
	cout << "向量函数的因变量向量是： " << endl;
	for( i = 0; i < N; i++)
		cout << yy[i] << "  ";
	cout << endl;
	cout << endl;
}

void ffjacobian(float xx[N], float yy[N][N])
{
	float x, y;
	int i, j;
	x = xx[0];
	y = xx[1];
	//jacobian have n*n element
	yy[0][0] = 2 * x - 2;
	yy[0][1] = -1;
	yy[1][0] = 2 * x;
	yy[1][1] = 8 * y;
	cout << "雅克比矩阵是： " << endl;
	for( i = 0; i < N; i++)
	{
		for(j = 0; j < N; j++)
			cout << yy[i][j] << "  ";
		cout << endl;
	}
	cout << endl;
}

void inv_jacobian(float yy[N][N], float inv[N][N])
{
	float aug[N][N2], L;
	int i, j, k;
	cout << "开始计算雅克比矩阵的逆矩阵 ：" << endl;
	for (i = 0; i < N; i++)
	{
		for(j = 0; j < N; j++)
			aug[i][j] = yy[i][j];
		for(j = N; j < N2; j++)
			if(j == i + N) aug[i][j] = 1;
			else  aug[i][j] = 0;
	}
	for (i = 0; i < N; i++)
	{
		for(j = 0; j < N2; j++)
			cout << aug[i][j] << "  ";
		cout << endl;
	}
	cout << endl;
	for (i = 0; i < N; i++)
	{
		for (k = i + 1; k < N; k++)
		{
			L = -aug[k][i] / aug[i][i];
			for(j = i; j < N2; j++)
				aug[k][j] = aug[k][j] + L * aug[i][j];
		}
	}
	for (i = 0; i < N; i++)
	{
		for(j = 0; j < N2; j++)
			cout << aug[i][j] << "  ";
		cout << endl;
	}
	cout << endl;
	for (i = N - 1; i > 0; i--)
	{
		for (k = i - 1; k >= 0; k--)
		{
			L = -aug[k][i] / aug[i][i];
			for(j = N2 - 1; j >= 0; j--)
				aug[k][j] = aug[k][j] + L * aug[i][j];
		}
	}
	for (i = 0; i < N; i++)
	{
		for(j = 0; j < N2; j++)
			cout << aug[i][j] << "  ";
		cout << endl;
	}
	cout << endl;
	for (i = N - 1; i >= 0; i--)
		for(j = N2 - 1; j >= 0; j--)
			aug[i][j] = aug[i][j] / aug[i][i];
	for (i = 0; i < N; i++)
	{
		for(j = 0; j < N2; j++)
			cout << aug[i][j] << "  ";
		cout << endl;
		for(j = N; j < N2; j++)
			inv[i][j-N] = aug[i][j];
	}
	cout << endl;
	cout << "雅克比矩阵的逆矩阵： " << endl;
	for (i = 0; i < N; i++)
	{
		for(j = 0; j < N; j++)
			cout << inv[i][j] << "  ";
		cout << endl;
	}
	cout << endl;
}

void newdundiedai(float x0[N], float inv[N][N], float y0[N], float x1[N])
{
	int i, j;
	float sum = 0;
	for(i = 0; i < N; i++)
	{
		sum = 0;
		for(j = 0; j < N; j++)
			sum = sum + inv[i][j] * y0[j];
		x1[i] = x0[i] - sum;
	}
	cout << "近似解向量：" << endl;
	for (i = 0; i < N; i++)
		cout << x1[i] << "  ";
	cout << endl;
	cout << endl;
}

