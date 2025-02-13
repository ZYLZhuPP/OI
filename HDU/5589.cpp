#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef bitset<16 > Bit;
const int N = 1e5 + 5;

struct IO {
	char c; int f;
#define gc() (getchar())
	template<class C>
	inline IO& operator >> (C &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
        x *= f; return *this;
	}
	inline bool operator ~ () { return ~c; }
} io;

int n, Q, X, B, val[N], ans[N], s;
vector<pair<int, int > > T[N];
Bit M;

struct Node {
    int l, r, id;
    bool operator < (const Node &a) { return l/B^a.l/B? l<a.l: r<a.r; }
};
vector<Node > qs;

namespace Tire {
    int ch[N][2], tot, sz[N];
    inline void upd(int x, int d) {
        Bit a = x; int u = 1;
        rFor (i, 15, 0) {
            int c = a[i];
            if (!ch[u][c]) ch[u][c] = ++tot;
            u = ch[u][c];
            sz[u] += d;
        }
    }
    inline int query(int x) {
        bitset<16 > a = x; int u = 1, res = 0;
        rFor (i, 15, 0) {
            if (!M[i]) res += sz[ch[u][!a[i]]];
            u = ch[u][a[i] ^ M[i]];
        }
        return res;
    }
}
using namespace Tire;

inline void dfs(int u, int pre) {
    for (auto &[v, w] : T[u]) if (v ^ pre) val[v] = val[u] ^ w, dfs(v, u);
}

int main() {
    while (~(io >> n >> X >> Q)) {
        tot = 1;
        B = sqrt(n); M = X;
        int u, v, w;
        For (i, 1, n - 1) io >> u >> v >> w, T[u].pb({v, w}), T[v].pb({u, w});
        dfs(1, 0);
        int l, r;
        For (i, 1, Q) io >> l >> r, qs.pb({l, r, i});
        sort(qs.begin(), qs.end());
        l = 1, r = 0, s = 0;
        for (auto &[x, y, id] : qs) {
            while (l > x) s += query(val[--l]), upd(val[l], 1);
            while (r < y) s += query(val[++r]), upd(val[r], 1);
            while (l < x) s -= query(val[l]), upd(val[l++], -1);
            while (r > y) s -= query(val[r]), upd(val[r--], -1);
            ans[id] = s;
        }
        For (i, 1, Q) printf("%d\n", ans[i]);

        For (i, 1, tot) sz[i] = ch[i][0] = ch[i][1] = 0;
        For (i, 1, n) T[i].resize(0);
        qs.resize(0);
    }
    
    return 0;
}
