/*
ID:zhjshar1
PROG:ditch
LANG:C++
*/
#include <fstream>
using namespace std;

ifstream  in( "ditch.in" );
ofstream out( "ditch.out" );

const int N = 3011, OO = 2000000010;
int c[N][N]={0}, f[N][N] = {0}, nv, sq, tq;
inline int Ziabs( int x ){
       return ( x >= 0 ? x : -x );
}
void Input( void );          // c, nv, sq, tq
void Ff( void );
void Output( void );

int main(){
    Input();
    Ff();
    Output();
    return 0;
}

void Input( void ){
     int ne, i, j, k, tc;
     in >>ne >>nv;
     sq=1; tq=nv;
     for( k=0; k<ne; ++k ){
          in >>i >>j >>tc;
          c[i][j] += tc;
     }
     return;
}

void Ff( void ){
     int pre[N], d, q[N], h, t, i, j, k;
     bool inq[N];
     pre[tq] = 1;
     while( pre[tq] != 0 ){
            memset( pre, 0, sizeof(pre) );
            memset( inq, 0, sizeof(inq) );
            h = t = 0;
            q[h] = sq;
            inq[sq] = true;
            while( (h<=t) && (pre[tq]==0) ){
                   i = q[h];
                   for( j=nv; j>0; --j )
                        if( !inq[j] ){
                            if( (c[i][j]) && (f[i][j]<c[i][j]) ){
                                q[++t] = j;
                                inq[j] = true;
                                pre[j] = i;
                            }
                            else if( (c[j][i]) && (f[j][i]>0) ){
                                 q[++t] = j;
                                 inq[j] = true;
                                 pre[j] = -i;
                            }
                        }
                   h++;
            }
                        
            if( pre[tq] != 0 ){
                d = OO;
                j = tq; i = Ziabs( pre[j] );
                while( i ){
                       if( pre[j] > 0 ) k = c[i][j] - f[i][j];
                       else             k = f[j][i];
                       if( k < d ) d = k;
                       j = i; i = Ziabs( pre[j] );
                }
                
                j = tq; i = Ziabs( pre[j] );
                while( i ){
                       if( pre[j] > 0 ) f[i][j] += d;
                       else             f[j][i] -= d;
                       j = i; i = Ziabs( pre[j] );
                }
            }
     }
     return;
}

void Output( void ){
     int maxflow = 0;
     for( int i=nv; i>0; --i )
          maxflow += f[sq][i];
     out <<maxflow <<endl;
     return;
}
