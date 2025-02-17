#include<bits/stdc++.h>
using namespace std;

template<class C> inline bool chkmax(C &x, const C &y) { return x<=y? x=y, 1: 0; }

typedef __int128 ll;

const int N = 105;

struct IO {
    static const int BufS=1<<21;
    char buf[BufS], *S, *T, c, f;
#define gc() ((S==T && (T=(S=buf)+fread(buf, 1, BufS, stdin)), S==T)? EOF: *S++)
    template<class C>
    inline IO& operator >> (C &x){
        for(f=1; !isdigit(c); c=gc()) if(!(c^45)) f=-1;
        for(x=0; isdigit(c); c=gc()) x=(x*10)+(c^48); x*=f;
        return *this;
    }
    inline bool operator ~ (){while(c<33 && c^EOF) c=gc(); return c^EOF;}
}io;

ll n, m, a[N], f[N][N], ans, _2[N];

void init() {
    _2[0] = 1;
    for (int i = 1; i <= m; i++) 
        _2[i] = _2[i - 1] * 2;
}

void clean() {
    memset(f, 0, sizeof f);
}

void write(ll x) {
    if(!x) putchar(48);
    else {
        if(x/10) write(x/10);
        putchar((x%10)^48);
    }
}

int main() {
    io >> n >> m;
    init();
    
    while (n--) {
        for (int i = 1; i <= m; i++)
            io >> a[i];
            
        clean();
        ll res = 0;
        
        for (int i = 1; i <= m; i++) {
            for (int j = 0; j <= i; j++) {
                int k = i - j;
                if (j) chkmax(f[i][j], f[i - 1][j - 1] + a[j]*_2[i]);
                if (k) chkmax(f[i][j], f[i - 1][j] + a[m-k+1]*_2[i]);
            }
        }
        
        for (int i = 0; i <= m; i++) 
            chkmax(res, f[m][i]);
        ans += res; 
    }
    
    write(ans);
    return 0; 
}
