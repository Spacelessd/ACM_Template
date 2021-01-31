#include <iostream>
#include <algorithm>
#include <cstdio>
#include <stdlib.h>
using namespace std; 
long long S;
int N;
//ÇóA*B mod C
long long OAS_Mult(long long A,long long B,long long C){
	long long Ans=0,P=A;
	for (;B>0;B=B/2){
		if (B%2!=0){
			Ans+=P;
			if (Ans>=C) Ans-=C;
		}
		P+=P;
		if (P>=C) P-=C;
	}
	return(Ans);
}
//ÇóA^B mod C
long long OAS_Exp(long long A,long long B,long long C){
	long long Ans=1,P=A;
	for (;B>0;B=B/2){
		if (B%2!=0)
			Ans=OAS_Mult(Ans,P,C);
		P=OAS_Mult(P,P,C);
	}
	return Ans;
}
bool Check(long long x){return (OAS_Exp(x,S-1,S)==1);}
bool Judge(long long x){
	for (int i=2;i<1000 && i<x;i++)
	if (x%i==0) return false;
	if (!Check(2)) return false;
	if (!Check(3)) return false;
	if (!Check(5)) return false;
	if (!Check(7)) return false;
	return true;
}
int main(){
	scanf("%d",&N);
	for (int i=1;i<=N;i++){
		scanf("%I64d",&S);   
		if (Judge(S))
		printf("%s\n","It's a prime.");
		else printf("%s\n","It isn't a prime."); 
	}
	return 0;   
}


