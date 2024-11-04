#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 256, M = 1e5 + 5, Mo = 1e9 + 7;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, const int &y) { x = mo(x + y); }
inline int ml(const int &x, const int &y) { return 1ll * x * y % Mo; }
inline void mul(int &x, const int &y) { x = ml(x, y); }

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

int f[N][M], a[N], b[N], c[N], ans = 1;
vector<int > G[N];
char tmp[M];

inline void dfs(int u) {
    for (auto &v : G[u]) dfs(v);
    For (i, 1, 1e5) {
        f[u][i] = 1;
        for (auto &v : G[u]) {
            int l = a[v]<0? i: a[v], r = b[v]<0? i: b[v], d = c[v];
            if (d > 0) {
                r--;
                if (l <= r) r -= (r - l) % d;
            } else {
                r++; d = -d;
                if (l >= r) r += (l - r) % d;
                swap(l, r);
            }
            if (l > r) { f[u][i] = 0; continue; }
            mul(f[u][i], mo(f[v][r] - (l>=d? f[v][l - d]: 0)));
        }
    }
    For (i, abs(c[u]), 1e5) add(f[u][i], f[u][i - abs(c[u])]);
}

int main() {
    scanf("%*s%*s");
    while (1) {
        scanf("%s", tmp);
        if (tmp[0] ^ 'f') break;
        scanf("%s", tmp);
        int u = tmp[0];
        scanf("%*s%s", tmp);
        int p1 = 5, p2 = p1 + 1, p3;
        while (tmp[p2] ^ ',') p2++;
        p3 = p2 + 1;
        while (tmp[p3] && tmp[p3] ^ ',') p3++;
        if (!tmp[p3]) c[u] = 1;
        else {
            int p4 = p3 + 1;
            while (tmp[p4]) p4++;
            tmp[p4 - 1] = 0;
            sscanf(tmp + p3 + 1, "%d", &c[u]);
        }
        tmp[p2] = tmp[p3] = 0;
        if (isalpha(tmp[p1 + 1])) {
            a[u] = -tmp[p1 + 1];
            G[-a[u]].pb(u);
        } else sscanf(tmp + p1 + 1, "%d", &a[u]);
        if (isalpha(tmp[p2 + 1])) {
            b[u] = -tmp[p2 + 1];
            G[-b[u]].pb(u);
        } else sscanf(tmp + p2 + 1, "%d", &b[u]);
        if (a[u] > 0 && b[u] > 0) G[0].pb(u);
    }
    for (auto &u : G[0]) {
        dfs(u);
        int l = a[u], r = b[u], d = c[u];
        if (d > 0) {
            r--;
            if (l <= r) r -= (r - l) % d;
        } else {
            r++; d = -d;
            if (l >= r) r += (l - r) % d;
            swap(l, r);
        }
        if (l > r) return puts("0"), 0;
        mul(ans, mo(f[u][r] - (l>=d? f[u][l - d]: 0)));
    }
    printf("%d", ans);

    return 0;
}
