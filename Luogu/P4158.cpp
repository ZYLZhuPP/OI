#include<bits/stdc++.h>
using namespace std;

template<class C> inline void chkmax(C &x, const C &y) { x = x < y? y: x; }

const int N = 55;

struct IO {
    static const int BufS=1<<21;
    char buf[BufS], *S, *T, c, f;
#define gc() ((S==T && (T=(S=buf)+fread(buf, 1, BufS, stdin)), S==T)? EOF: *S++)
    template<class C>
    inline IO& operator >> (C &x){
        for(f=1; !isdigit(c); c=gc()) if(!(c^45)) f=-1;
        for(x=0; isdigit(c); c=gc()) x=(x<<3)+(x<<1)+(c^48); x*=f;
        return *this;
    }
    inline IO& operator >> (char &x){
        while(c<33) c=gc(); x=c; c=gc();
        return *this;
    }
    inline bool operator ~ (){while(c<33 && c^EOF) c=gc(); return c^EOF;}
}io;

int n, m, T, f[N][N][N], g[N][N * N], s[N][N];

int main() {
    io >> n >> m >> T;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            char x;
            io >> x;
            s[i][j] = s[i][j-1] + (x ^ 48);
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int t = 1; t <= m; t++) {
            for (int j = 1; j <= m; j++) {
                for (int k = 0; k < j; k++)
                    chkmax(f[i][t][j], f[i][t-1][k] + max(s[i][j]-s[i][k], (j-k) - (s[i][j]-s[i][k])));
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            for (int t = j; t <= T; t++)
                chkmax(g[i][t], g[i-1][t-j] + f[i][j][m]);
        }
    }

    printf("%d", g[n][T]);
    return 0;
}
