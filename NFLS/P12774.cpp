#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 5e5 + 5;

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

int n, m, fa[N << 1];
vector<array<int, 2 > > L;

inline int find(int x) { return fa[x]^x? fa[x] = find(fa[x]): x; }

namespace Seg {
    vector<int > a[N << 2], b[N << 2];
#define ls p << 1
#define rs p << 1 | 1
#define M int m = (l + r) >> 1
#define goL ls, l, m
#define goR rs, m + 1, r
    inline void upd(int p, int l, int r, int x, const int &u) {
        a[p].pb(u); b[p].pb(u + m);
        if (l == r) return;
        M; x<=m? upd(goL, x, u): upd(goR, x, u);
    }
    inline void link(int p, int l, int r, int x, int y, const int &u) {
        if (l > y || r < x) return;
        if (x <= l && r <= y) {
            if ((int)a[p].size() > 1) {
                int x = find(a[p][0]);
                for (auto &v : a[p]) fa[find(v)] = x;
                vector<int >().swap(a[p]);
                a[p].pb(x);
                x = find(b[p][0]);
                for (auto &v : b[p]) fa[find(v)] = x;
                vector<int >().swap(b[p]);
                b[p].pb(x);
            }
            if (!a[p].empty()) fa[find(a[p][0])] = find(u + m), fa[find(b[p][0])] = find(u);
            return;
        }
        M; link(goL, x, y, u); link(goR, x, y, u);
    }
}
using namespace Seg;

int main() {
    freopen("paint.in", "r", stdin);
    freopen("paint.out", "w", stdout);
    io >> n >> m;
    int u, v;
    For (i, 1, m) {
        io >> u >> v;
        if (u > v) swap(u, v);
        if (v - u <= 1 || (u == 1 && v == n)) continue;
        L.pb({u, -v});
    }
    sort(L.begin(), L.end()); L.erase(unique(L.begin(), L.end()), L.end());
    m = L.size();
    For (i, 1, m) fa[i] = i, fa[i + m] = i + m;
    For (i, 0, m - 1) {
        u = i + 1;
        auto [x, y] = L[i]; y = -y;
        link(1, 1, n, x + 1, y - 1, u);
        upd(1, 1, n, y, u);
    }
    For (i, 1, m) if (find(i) == find(i + m)) return puts("No"), 0;
    puts("Yes");

    fclose(stdin); fclose(stdout);
    return 0;
}
