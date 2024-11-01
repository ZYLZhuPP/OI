#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e3 + 5;

struct IO {
    char c; int f;
#define gc() getchar()
    template<class C>
    inline IO& operator >> (C &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
        x *= f; return *this;
    }
    inline bool operator ~ () const { return ~c; }
} io;

int n, m, fa[N], co[N], vis[N], no[N][N];
vector<int > dif[N];

inline int find(int x) { return fa[x]^x? fa[x] = find(fa[x]): x; }

int main() {
    memset(co, -1, sizeof co);
    io >> n >> m;
    For (i, 1, n) fa[i] = i;
    while (m--) {
        int x, y, z;
        io >> x >> y >> z;
        For (i, 0, z - 1) {
            int a = x + i, b = y + i;
            fa[find(a)] = find(b);
        }
        dif[x + z].pb(y + z); dif[y + z].pb(x + z);
    }
    For (i, 1, n) find(i);
    For (i, 1, n) for (auto &j : dif[i]) if (fa[i] == fa[j]) { puts("-1"); return 0; } else no[fa[i]][fa[j]] = 1;
    For (i, 1, n) if (!~co[fa[i]]) {
        int x = fa[i];
        For (j, 1, n) if (no[x][j] && ~co[j]) vis[co[j]] = 1;
        For (j, 0, n) if (!vis[j]) { co[x] = j; break; }
        For (j, 0, n) vis[j] = 0;
    }
    For (i, 1, n) printf("%d ", co[fa[i]]);

    return 0;
}
