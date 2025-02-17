#include<bits/stdc++.h>
using namespace std;

struct IO {
    static const int BufS=1<<21;
    char buf[BufS], *S, *T, c, f;
#define gc() ((S==T && (T=(S=buf)+fread(buf, 1, BufS, stdin)), S==T)? EOF: *S++)
    template<class C>
    inline IO& operator >> (C &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc(); x *= f; return *this;
    }
    inline IO& operator >> (char *x){
        while(c<33) c=gc();
        for(; c>32; c=gc()) *x++=c; *x=0;
        return *this;
    }
    inline bool operator ~ () const { return ~c; }
}io;

int T, n, o, f[3][3] = {{1, 24, 27}, {1, 7, 8}, {1, 1, 1}};
char k[4];

int main() {
    io >> T;
    while (T--) {
        io >> k >> n;
        n = min(n, 2);
        if (k[0] == k[1] && k[1] == k[2]) o = 2;
        else if (k[0] == k[1] || k[1] == k[2] || k[0] == k[2]) o = 1;
        else o = 0;
        printf("%d\n", f[o][n]);
    } 
    
    return 0;
} 

