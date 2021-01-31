/*
 * Problem: NOI1997 satellitecover
 * Author: Guo Jiabao
 * Time: 2009.2.11 21:17
 * State: Solved
*/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
using namespace std;
const int MAXN=201;
struct cube{int x1,y1,z1,x2,y2,z2;};
int N;
cube Cubes[MAXN];
void init()
{
	int i,a,b,c,r;
	freopen("satellitecover.in","r",stdin);
	freopen("satellitecover.out","w",stdout);
	scanf("%d",&N);
	for (i=1;i<=N;i++)
	{
		scanf("%d%d%d%d",&a,&b,&c,&r);
		Cubes[i].x1=a-r; Cubes[i].y1=b-r; Cubes[i].z1=c-r;
		Cubes[i].x2=a+r; Cubes[i].y2=b+r; Cubes[i].z2=c+r;
	}
}
inline bool cross(cube A,cube B)
{
	return A.x1 < B.x2 && A.y1 < B.y2 && A.z1 < B.z2 && B.x1 < A.x2 && B.y1 < A.y2 && B.z1 < A.z2;
}
cube mcube(int x1,int y1,int z1,int x2,int y2,int z2)
{
	cube A;
	A.x1=x1;A.y1=y1;A.z1=z1;A.x2=x2;A.y2=y2;A.z2=z2;
	return A;
}
int devide(cube A,int pos)
{
	cube B;
	int volume=0;
	while (pos<=N && !cross(A,B=Cubes[pos])) pos++;
	if (pos>N)
		volume=(A.x2-A.x1)*(A.y2-A.y1)*(A.z2-A.z1);
	else
	{
		if (A.x1 < B.x1)
		{
			volume+=devide(mcube(A.x1,A.y1,A.z1,B.x1,A.y2,A.z2),pos+1);
			A.x1=B.x1;
		}
		if (A.x2 > B.x2)
		{
			volume+=devide(mcube(B.x2,A.y1,A.z1,A.x2,A.y2,A.z2),pos+1);
			A.x2=B.x2;
		}
		if (A.y1 < B.y1)
		{
			volume+=devide(mcube(A.x1,A.y1,A.z1,A.x2,B.y1,A.z2),pos+1);
			A.y1=B.y1;
		}
		if (A.y2 > B.y2)
		{
			volume+=devide(mcube(A.x1,B.y2,A.z1,A.x2,A.y2,A.z2),pos+1);
			A.y2=B.y2;
		}
		if (A.z1 < B.z1)
			volume+=devide(mcube(A.x1,A.y1,A.z1,A.x2,A.y2,B.z1),pos+1);
		if (A.z2 > B.z2)
			volume+=devide(mcube(A.x1,A.y1,B.z2,A.x2,A.y2,A.z2),pos+1);
	}
	return volume;
}
int main()
{
	int i,totalvolume=0;
	init();
	for (i=N;i>-1;i--)
		totalvolume+=devide(Cubes[i],i+1);
	printf("%dn",totalvolume);
	return 0;
}


