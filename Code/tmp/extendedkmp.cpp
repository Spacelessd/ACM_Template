#include <iostream>
using namespace std;

char A[105],B[105];
int Ans[105],T[105];
int N,M;

int GetMax(int a,int b){if (a>b) return a;else return b;}

void ExKmp(){
     for (int i=0;i<=N+1 || i<=M+1;i++) T[i]=Ans[i]=0;
     T[1]=T[2]=0;
     while (T[2]+2<=N && A[T[2]+1]==A[T[2]+2]) T[2]++;
     for (int i=3,k=2;i<=N;i++){
         int len=k+T[k]-1,l=T[i-k+1];
         if (l<len-i+1) T[i]=l;
         else{
              int j=GetMax(0,len-i+1);
              while (i+j<=N && A[1+j]==A[i+j]) j++;
              T[i]=j;       k=i;     
         }    
     }
     while (1+Ans[1]<=N && 1+Ans[1]<=M && A[Ans[1]+1]==B[Ans[1]+1]) Ans[1]++;
     for (int i=2,k=1;i<=M;i++){
         int len=k+Ans[k]-1,l=T[i-k+1];
         if (l<len-i+1) Ans[i]=l;
         else{
              int j=GetMax(0,len-i+1);
              while (i+j<=M && 1+j<=N && A[1+j]==B[i+j]) j++;
              Ans[i]=j;       k=i;    
         }    
     }
}

int main(){
    scanf("%s",A+1);
    scanf("%s",B+1);
    N=strlen(A+1);
    M=strlen(B+1);
    ExKmp();
    for (int i=1;i<=M;i++) printf("%d\n",Ans[i]);
    
    return 0;   
}
