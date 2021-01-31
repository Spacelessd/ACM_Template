#include <iostream>
#include <cstring>
using namespace std;

const int L = 100010, D = 72;
char s1[L+L]={0}, s2[L+L]={0};
int n;

int main(){
    char *cp = s1;int T;
    cin >>T;
    while (T--){
    cin>>n;cin >>cp;
    memcpy( s1+n, s1, sizeof(char)*n );
    memcpy( s2, s1+1, sizeof(char)*n*2-1 );
    s2[n+n-1] = s1[0];

    int i=0, j=0, k=0;
    while( (i<n) && (j<n) ){
           while( (s1[i+k]==s2[j+k]) && (k<n) ) ++k;
           if( k == n ) break;
           if( s1[i+k] > s2[j+k] ) i += k + 1;
           else                    j += k + 1;
           if( j + 1 == i ) ++j;
           k = 0;
    }
    cout <<i <<endl;
}
    //for (;;);
    return 0;
}


