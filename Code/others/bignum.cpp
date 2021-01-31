#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<iostream>
#include<algorithm>
using namespace std;
#ifndef BIGNUM_H_INCLUDED
#define BIGNUM_H_INCLUDED
#include <iostream>
#include <sstream>
#include <list>
using namespace std;
typedef long long LL;
class bignum{
          friend istream& operator>>(istream&, bignum&);
          friend ostream& operator<<(ostream&, const bignum&);
          friend bignum operator +(const bignum&, const bignum&);
          friend bignum operator -(const bignum&, const bignum&);
          friend bignum operator *(const bignum&, const bignum&);
          friend bignum operator /(const bignum&, const bignum&);
          friend bignum operator %(const bignum&, const bignum&);
          friend bignum operator +(const bignum&, const int&);
          friend bignum operator -(const bignum&, const int&);
          friend bignum operator *(const bignum&, const int&);
          friend bignum operator /(const bignum&, const int&);
          friend bignum operator %(const bignum&, const int&);
          friend bool operator ==(const bignum&, const bignum&);
          friend bool operator !=(const bignum&, const bignum&);
          friend bool operator <(const bignum&, const bignum&);
          friend bool operator >(const bignum&, const bignum&);
          friend bool operator <=(const bignum&, const bignum&);
          friend bool operator >=(const bignum&, const bignum&);
          friend bool operator ==(const bignum&, const int&);
          friend bool operator !=(const bignum&, const int&);
          friend bool operator <(const bignum&, const int&);
          friend bool operator >(const bignum&, const int&);
          friend bool operator <=(const bignum&, const int&);
          friend bool operator >=(const bignum&, const int&);
          friend int do_comp(const bignum&, const int&);
          friend int do_comp(const bignum&, const bignum&);
          friend void divide(const bignum&, const bignum&, bignum&, bignum&);
          friend bignum pow(bignum, int);
    public:
        inline bignum(){};
        inline bignum(int s){
            while (s!=0){
                data.push_back(s%100000000); s/=100000000;
            }
            if (data.empty()) data.push_back(0);
        }
    inline bignum(long long s){
        while (s!=0){
            data.push_back(int(s%100000000)); s/=100000000;
        }
        if (data.empty()) data.push_back(0);
    }
        inline bignum(string s){
            int t, i; data.clear();
            for (i=int(s.size())-8;i>0;i-=8){
                istringstream(s.substr(i, 8)) >> t;
                data.push_back(t);
            }
            istringstream(s.substr(0, i+8)) >> t;
            data.push_back(t);
        }
        void operator =(const int);
        void operator =(const string);
        void operator =(const bignum);
        bignum& operator +=(const bignum&);
        bignum& operator -=(const bignum&);
        bignum& operator *=(const bignum&);
        bignum& operator /=(const bignum&);
        bignum& operator %=(const bignum&);
        bignum& operator +=(const int&);
        bignum& operator -=(const int&);
        bignum& operator *=(const int&);
        bignum& operator /=(const int&);
        bignum& operator %=(const int&);
        bignum& operator %=(const LL&);
        bool undefined();
        int do_try(const int&);
        int do_try(const bignum&);
        void do_trim();
        list<int> data;

    void add (const int a){
        list<int>::iterator it = data.end();
        it --;
        if ( (*it) < 10 ) (*it) = a ;
        else if ( (*it) < 100 ) (*it) = (*it) % 10 + 10*a ;
        else if ( (*it) < 1000 ) (*it) = (*it) % 100 + 100*a ;
        else if ( (*it) < 10000 ) (*it) = (*it) % 1000 + 1000*a ;
        else if ( (*it) < 100000 ) (*it) = (*it) % 10000 + 10000*a ;
        else if ( (*it) < 1000000 ) (*it) = (*it) % 100000 + 100000*a ;
        else if ( (*it) < 10000000 ) (*it) = (*it) % 1000000 + 1000000*a ;
        else if ( (*it) < 100000000 ) (*it) = (*it) % 10000000 + 10000000*a ;

        /*
        list<int>::iterator it = data.end();
        it --;

        if (*it >= 10000) {
            if ( (*it) >= 1000000) {if (*it >=10000000) data.push_back(a); else (*it) += a * 10000000;}
            else {if ((*it) >= 100000) (*it) += a * 1000000; else (*it) += a * 100000;}
        }
        else
            if ( (*it) >= 100) {if (*it >=1000) (*it) += a * 10000; else (*it) += a * 1000;}
            else {if ((*it) >= 10) (*it) += a * 100; else (*it) += a * 10;} */
    }

    void clear(){
        data.clear();
    }

    LL t(){
        if (data.size() == 1) return *data.begin();
        else {
            list<int>::iterator it = data.begin(), jt = data.begin(); ++it;
            return (LL)(*it) * 100000000 + (*jt);
        }
    }

    int size(){
        list<int>::iterator it; int res = 0;
        for (it=data.begin(); it!=data.end();it++)
            res += 8;
        it--;
        if (*it >= 10000) {
            if ( (*it) >= 1000000) {if (*it >=10000000) ; else res--;}
            else {if ((*it) >= 100000) res-=2; else res-=3;}
        }
        else
            if ( (*it) >= 100) {if (*it >=1000) res-=4; else res-=5;}
            else {if ((*it) >= 10) res-=6; else res-=7;}

        return res;
    }

    void do_reserve(int a){
        if (a <= 0) return;
        list<int>::iterator it;
        for (it=data.begin(); it!=data.end() && a>0; it++) a-=8;
        if (it == data.end() && a>=0) return;
        a+=8, it--; int f = 1;
        for (int i=0;i<a;i++) f *= 10; (*it) %= f;
        data.erase(++it, data.end());
        do_trim();
    }

    void output(){
        list<int>::reverse_iterator i=data.rbegin();
        printf("%d", *i); for (i++;i!=data.rend();i++)
            printf("%08d", *i);
    }
};

inline void bignum::operator =(const bignum a){
    data.clear();
    for (list<int>::const_iterator i=a.data.begin();i!=a.data.end();i++){
        data.push_back(*i);
    }
}
inline void bignum::operator =(const string a){
    (*this) = bignum(a);
}
inline void bignum::operator =(const int a){
    (*this) = bignum(a);
}


inline istream& operator>>(istream& input, bignum& a){
    string s; int t, i; input >> s; a.data.clear();
    for (i=int(s.size())-8;i>0;i-=8){
        istringstream(s.substr(i, 8)) >> t;
        a.data.push_back(t);
    }
    istringstream(s.substr(0, i+8)) >> t;
    a.data.push_back(t);
    return input;
}

inline ostream& operator<<(ostream& output, const bignum& a){
    list<int>::const_reverse_iterator i=a.data.rbegin();
    output << *i;
    for (i++;i!=a.data.rend();i++){
        if (*i >= 10000) {
            if (*i >= 1000000) {if (*i>=10000000) cout << *i; else cout << 0 << *i;}
            else {if (*i>=100000) cout << "00" << *i; else cout << "000" << *i;}
        }
        else {
            if (*i >= 100) {if (*i>=1000)  cout << "0000" << *i; else cout << "00000" << *i;}
            else { if (*i>=10) cout << "000000" << *i; else cout << "0000000" << *i;}
        }
    }
    return output;
}


inline bool bignum::undefined(){
    return data.empty();
}

inline int do_comp(const bignum& a, const bignum& b){
    if (a.data.size()<b.data.size()) return -1; if (a.data.size()>b.data.size()) return 1;
    list<int>::const_reverse_iterator i; list<int>::const_reverse_iterator j;
    for (i=a.data.rbegin(),j=b.data.rbegin(); j!=b.data.rend(); i++,j++){
        if (*i<*j) return -1;              //!!!!
        if (*i>*j) return 1;
    }
    return 0;
}
inline int do_comp(const bignum& a, const int& b){
    return do_comp(a, bignum(b));
}

inline bool operator ==(const bignum& a, const bignum& b){
    return do_comp(a, b) == 0;
}
inline bool operator !=(const bignum& a, const bignum& b){
    return do_comp(a, b) != 0;
}
inline bool operator <(const bignum& a, const bignum& b){
    return do_comp(a, b) == -1;
}
inline bool operator >(const bignum& a, const bignum& b){
    return do_comp(a, b) == 1;
}
inline bool operator <=(const bignum& a, const bignum& b){
    return do_comp(a, b) != 1;
}
inline bool operator >=(const bignum& a, const bignum& b){
    return do_comp(a, b) != -1;
}

inline bool operator ==(const bignum& a, const int& b){
    return do_comp(a, b) == 0;
}
inline bool operator !=(const bignum& a, const int& b){
    return do_comp(a, b) != 0;
}
inline bool operator <(const bignum& a, const int& b){
    return do_comp(a, b) == -1;
}
inline bool operator >(const bignum& a, const int& b){
    return do_comp(a, b) == 1;
}
inline bool operator <=(const bignum& a, const int& b){
    return do_comp(a, b) != 1;
}
inline bool operator >=(const bignum& a, const int& b){
    return do_comp(a, b) != -1;
}

inline void bignum::do_trim(){
    while (data.size()>1&&data.back()==0) data.pop_back();
}


inline bignum& bignum::operator +=(const bignum& a){
    list<int>::iterator i; list<int>::const_iterator j; int t = 0;
    for (i=data.begin(),j=a.data.begin(); i!=data.end()&&j!=a.data.end(); i++,j++){
        *i+=*j+t; t=*i/100000000; *i%=100000000;
    }
    while (i!=data.end()) {*i+=t; t=*i/100000000; *i%=100000000; i++;}
    while (j!=a.data.end()) {data.push_back(t+*j); t=data.back()/100000000; data.back()%=100000000; j++;}
    if (t!=0) data.push_back(t);
    return *this;
}


inline bignum& bignum::operator -=(const bignum& a){
    list<int>::iterator i; list<int>::const_iterator j; int t = 0;
    for (i=data.begin(),j=a.data.begin(); j!=a.data.end(); i++,j++){
        *i -= t+*j; if (*i>=0) t=0; else *i+=100000000, t=1;
    }
    while (i!=data.end()) {*i-=t; if (*i>=0) t=0;else *i+=100000000, t=1; i++;}
    (*this).do_trim();
    return *this;
}


inline bignum& bignum::operator +=(const int& a){
    return (*this)+=bignum(a);
}

inline bignum& bignum::operator -=(const int& a){
    return (*this)-=bignum(a);
}




inline bignum operator +(const bignum& a, const bignum& b){
    list<int>::const_iterator i, j; bignum c; int t = 0;
    for (i=a.data.begin(),j=b.data.begin(); i!=a.data.end()&&j!=b.data.end(); i++,j++){
        c.data.push_back(t+*i+*j);
        t=c.data.back()/100000000; c.data.back()%=100000000;
    }
    while (i!=a.data.end()) {c.data.push_back(t+*i); t=c.data.back()/100000000; c.data.back()%=100000000; i++;}
    while (j!=b.data.end()) {c.data.push_back(t+*j); t=c.data.back()/100000000; c.data.back()%=100000000; j++;}
    if (t!=0) c.data.push_back(t);
    return c;
}

inline bignum operator -(const bignum& a, const bignum& b){
    list<int>::const_iterator i, j; bignum c; int t = 0;
    for (i=a.data.begin(),j=b.data.begin(); j!=b.data.end(); i++,j++){
        t = *i - t;
        if (t>=*j) c.data.push_back(t-*j), t=0;
        else c.data.push_back(t+100000000-*j), t=1;
    }
    while (i!=a.data.end()) {t=*i-t; if (t>=0) c.data.push_back(t), t=0;else c.data.push_back(t+100000000), t=1; i++;}
    c.do_trim();
    return c;
}

inline bignum operator *(const bignum& a, const bignum& b){
    list<int>::const_iterator i, j; list<int>::iterator k, kk; bignum c; long long t = 0;

    for (int i=0;i<a.data.size()+b.data.size();i++) c.data.push_back(0);
    for (i=a.data.begin(),k=c.data.begin(); i!=a.data.end(); i++,k++){
        for (j=b.data.begin(),kk=k; j!=b.data.end(); j++,kk++){
            t+=(long long)(*i)*(*j)+(*kk);
            *kk=int(t%100000000); t/=100000000;
        }
        *kk+=t; t=0;
    }
    c.do_trim();
    return c;
}

inline int bignum::do_try(const bignum& a){
    int l = 1, r = 99999999, m, t;
    while (l+2<r){
        m = (l + r) / 2;
        t = do_comp(*this, a*bignum(m));
        if (t==0) return m;
        if (t<0) r = m - 1;
        else l = m;
    }
    while (do_comp(*this, a*bignum(r))<0) r--;
    return r;
}

inline void divide(const bignum& a, const bignum& b, bignum& d, bignum& r){
    list<int>::const_reverse_iterator i = a.data.rbegin(); int t;
    d = bignum(0); r = bignum(0);
    do {
        while (r<b&&i!=a.data.rend()){d.data.push_front(0);r.data.push_front(*i);r.do_trim();i++;}
        if (r>=b){
            t = r.do_try(b); d.data.front() = t;
            r-=(b*bignum(t));
        }
    } while (i!=a.data.rend());
    d.do_trim();
}

inline bignum operator /(const bignum& a, const bignum& b){
    bignum d, r;
    divide(a, b, d, r);
    return d;
}

inline bignum operator %(const bignum& a, const bignum& b){
    bignum d, r;
    divide(a, b, d, r);
    return r;
}

inline bignum operator +(const bignum& a, const int& b){
    return a+bignum(b);
}

inline bignum operator -(const bignum& a, const int& b){
    return a-bignum(b);
}

inline bignum operator *(const bignum& a, const int& b){
    return a*bignum(b);
}

inline bignum operator /(const bignum& a, const int& b){
    return a/bignum(b);
}


inline bignum& bignum::operator *=(const bignum& a){
    (*this) = (*this) * a;
    return *this;
}

inline bignum& bignum::operator /=(const bignum& a){
    (*this) = (*this) / a;
    return *this;
}

inline bignum& bignum::operator %=(const bignum& a){
    (*this) = (*this) % a;
    return *this;
}

inline bignum& bignum::operator *=(const int& a){
    return (*this)*=bignum(a);
}

inline bignum& bignum::operator /=(const int& a){
    return (*this)/=bignum(a);
}

inline bignum& bignum::operator %=(const LL& b){
    return (*this)%=bignum(b);
}


inline bignum pow(bignum a,int b){
    bignum c(1);
    while (b!=0) {
        if (b&1) c *= a;
        a = a * a; b >>= 1;
    }
    return c;
}

#endif // BIGNUM_H_INCLUDED

// <<= ' A. Random Event ..

inline int rand32(){return (bool(rand() & 1) << 30) | (rand() << 15) + rand();}
inline int random32(int l, int r){return rand32() % (r - l + 1) + l;}
inline int random(int l, int r){return rand() % (r - l + 1) + l;}
int dice(){return rand() % 6;}
bool coin(){return rand() % 2;}

// <<= ' 0. I/O Accelerator interface .,

template<class T> inline void RD(T &x){
    //cin >> x;
    //scanf("%d", &x);
    char c; for (c = getchar(); c < '0'; c = getchar()); x = c - '0'; for (c = getchar(); c >= '0'; c = getchar()) x = x * 10 + c - '0';
    //char c; c = getchar(); x = c - '0'; for (c = getchar(); c >= '0'; c = getchar()) x = x * 10 + c - '0';
}

template<class T> inline void OT(const T &x){
    printf("%d\n", x);
}

/* .................................................................................................................................. */



int main(){
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	int t1=clock();
	//for (bignum i=1;i<=10;);
	//for (bigint i=1;i<=10;)(++i).print();
	bignum a,b,c,i;a=1234;
	for (i=1;i<=2000;a=a*1243,i=i+1);
	a.output();
	printf("time=%d\n",clock()-t1);
	system("pause");for (;;);
	return 0;
}
