#include <iostream>
#include <complex>
using namespace std;
int main()
{
	complex<double> x(1, 2.1), y;
	cout << "x = " << x << endl;
	y = x + complex<double>(1.0, 4);
	cout << "\ny = " << y << endl;
	//if (x < y) not allowed - no standard definition
	//cout << "x less than y" << endl;
	system("pause");
	return 0;
}


