#include<bits/stdc++.h>
using namespace std;

template<class C> inline bool chkmax(C &x, const C &y) { return x<=y? x=y, 1: 0; }

const int N = 5e3 + 5, Mo = 1e8;

struct IO {
    static const int BufS=1<<21;
    char buf[BufS], *S, *T, c, f;
#define gc() ((S==T && (T=(S=buf)+fread(buf, 1, BufS, stdin)), S==T)? EOF: *S++)
    inline IO& operator >> (char *x){
        while(c<33) c=gc();
        for(; c>32; c=gc()) (*x++)=c; (*x++)=0;
        return *this;
    }
    inline bool operator ~ (){while(c<33 && c^EOF) c=gc(); return c^EOF;}
}io;

int la, lb, f[2][N], s[2][N];
int *f0 = f[0], *f1 = f[1], *s0 = s[0], *s1 = s[1];
char a[N], b[N];


int main() {
    io >> a+1 >> b+1;
    la = strlen(a+1) - 1;
    lb = strlen(b+1) - 1;
    
    fill(s1, s1+lb+1, 1);
    s0[0] = 1;
    
    for (int i = 1; i <= la; i++) {
        swap(f0, f1); swap(s0, s1);
        for (int j = 1; j <= lb; j++) {
            f1[j] = max(f0[j], f1[j-1]); s1[j] = 0;
            if (a[i] == b[j]) 
                if (chkmax(f1[j], f0[j-1]+1)) s1[j] += s0[j-1];
            if (f1[j] == f1[j-1]) s1[j] += s1[j-1];
            if (f1[j] == f0[j]) s1[j] += s0[j];
            if (f1[j] == f0[j-1]) s1[j] -= s0[j-1];
            s1[j] %= Mo;
        }
    } 
    printf("%d\n%d", f1[lb], s1[lb]);
    return 0;
}
