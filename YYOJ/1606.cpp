#include<bits/stdc++.h>
using namespace std;

const int N = 1e7 + 5;

struct IO {
    static const int BufS=1<<21;
    char buf[BufS], *S, *T, c, f;
#define gc() ((S==T && (T=(S=buf)+fread(buf, 1, BufS, stdin)), S==T)? EOF: *S++)
    template<class C>
    inline IO& operator >> (C &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
        x *= f; return *this;
    }
    inline IO& operator >> (char *x) {
        while ((c = gc()) < 33);
        while (c > 32) *x++ = c, c = gc();
        *x = 0; return *this;
    }
    #define pc(c) putchar(c)
    template<class C>
    inline IO& operator << (C *x) {
        while (*x) pc(*x++);
        return *this;
    }
    inline bool operator ~ () const { return ~c; }
} io;

int n, t;
char a[N], b[N], ma;

int main() {
    io >> n;
    io >> a;
    b[t = n] = 0;
    for (int i = n - 1; i >= 0; --i) {
        if (a[i] >= ma) b[--t] = a[i], ma = a[i];
    }
    
    io << b + t; 
    
    return 0;
}

