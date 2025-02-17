#include<bits/stdc++.h>
using namespace std;

template<class C> inline void chkmax(C &x, C y){x = x < y? y: x;}

const int N = 2e3+5;

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
    inline bool operator ~ (){while(c<33 && c^EOF) c=gc(); return c^EOF;}
}io;

int n, q, h[N][N], f[N][N];
int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};

int dfs(int x, int y) {
    if(x < 1 || x > n || y < 1 || y > n)
        return -1;
    
    if(~f[x][y])
        return f[x][y];
        
    f[x][y]=0;
        
    for(int i = 0; i < 4; i++)
        if(h[x][y] > h[x + dx[i]][y + dy[i]])
            chkmax(f[x][y], dfs(x + dx[i], y + dy[i]) + 1);
        
    return f[x][y];
}

int main() {
    io >> n >> q;
    
    memset(f, -1, sizeof(f));
    
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
            io >> h[i][j];
            
    while(q--) {
        int x, y;
        io >> x >> y;
        printf("%d\n", dfs(x, y));
    }
    
    return 0;
}
