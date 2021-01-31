#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <ctime>

using namespace std;

const int P = 1000000007;

int N = 1000;

int main()
{
	srand(time(0));
	freopen("statistics.in", "w", stdout);
	cout << rand() % P << " " << rand() % P << " " << rand() % P << " " << N << endl;
	return 0;
}
