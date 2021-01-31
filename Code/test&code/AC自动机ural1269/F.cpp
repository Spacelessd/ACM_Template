#include <cstdio>
#include <cstring>
const int maxm = 100010 ;
int i , j , k , y , n , m , tot , head , tail , first = maxm * 10;
int l[maxm] , r[maxm] , p[maxm] , q[maxm] , len[maxm] ;
char *pos , ch , s[maxm] , c[maxm] ;
void add( char& ch , int& x)
{
    x = ++ tot ;
    c[tot] = ch ;
}
int max( int& a , int& b)
{
    if (a > b)  return a ;
    return b ;
}
int child( int x , char& ch)
{
    for (y = 1 ; x != 1 || y ; x = p[x])
    {
        for (y = l[x] ; y && c[y] != ch ; y = r[y]) ;
        if (y)  return y ;
    }
    return 1 ;
}
int main()
{
    for (c[tot = 1] = -1 , scanf ("%d%*c" , &n) ; n ; -- n)
    {
        gets (pos = s) ;
        for (i = 1 ; *pos != '\0' ; ++ pos)
            if (!l[i])  add(*pos , l[i]) , i = tot ;
            else
            {
                for (j = l[i] ; c[j] != *pos && r[j] ; j = r[j]) ;
                c[j] != *pos ? add(*pos , r[j]) , i = tot : i = j ;
            }
        len[i] = strlen(s) ;
    }
    for (head = 0 , tail = p[1] = q[0] = 1 ; head < tail ; )
    {
        for (k = tail , j = l[ i = q[head ++] ] ; j ; j = r[j])
            q[tail ++] = j ;
        for (; k < tail ; ++ k)
        {
            if (i == 1)  p[ q[k] ] = 1 ;
            else  p[ q[k] ] = child(p[i] , c[ q[k] ]) ;
            len[ q[k] ] = max(len[ q[k] ] , len[ p[ q[k] ] ]) ;
        }
    }
    for (i = 1 , scanf ("%d%*c" , &m) ; i <= m ; ++ i)
    {
        for (tot = j = 1 , ch = getchar() ; ; ch = getchar() , ++tot)
        {
            j = child(j , ch) ;
            if (len[j] && tot - len[j] + 1 < first)
                first = tot - len[j] + 1 ;
            if (ch == 0 || ch == 10 || ch == 13)  break;
        }
        if (ch == 10 && first < maxm * 10)
        {
            printf ("%d %d\n" , i , first) ;
            return 0 ;
        }
    }
    printf ("Passed\n") ;
    return 0;
}
