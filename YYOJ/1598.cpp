#include<bits/stdc++.h>
using namespace std;

const int N = 2005;

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
    inline IO& operator >> (char &x) {
        while ((c = gc()) < 33);
        x = c; return *this;
    }
    inline bool operator ~ () const { return ~c; }
} io;

struct XY {
    int x, y;
};
vector<XY > d[2*N];

int n, m;
bool vis[N][N];
char a[N][N];

int main() {
    io >> n >> m;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            io >> a[i][j];
        }
    }
    
    d[1].push_back({1, 1}); vis[1][1] = 1;
    for (int i = 1; i <= n + m - 1; ++i) {
        char c = 'z';
        for (auto &e : d[i]) {
            c = min(c, a[e.x][e.y]);
        }
        putchar(c);
        for (auto &e : d[i]) if (a[e.x][e.y] == c) {
            int x = e.x, y = e.y;
            if (x < n && !vis[x + 1][y]) d[i + 1].push_back({x + 1, y}), vis[x + 1][y] = 1; 
            if (y < m && !vis[x][y + 1]) d[i + 1].push_back({x, y + 1}), vis[x][y + 1] = 1; 
        }
    }
    
    return 0; 
} 
