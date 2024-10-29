#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef double lf;
const int N = 3e5 + 5;
template<class C> inline bool cmin(C &x, const C &y) { return y<x? x=y, 1: 0; }

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

int T, n, fa[N];
set<int > se[N];

inline int find(int x) { return fa[x]^x? fa[x] = find(fa[x]): x; }

inline lf merge(int u, int v) {
    if (se[u].size() < se[v].size()) swap(u, v);
    se[u].insert(se[v].begin(), se[v].end()); se[v].clear();
    fa[v] = u;
    int l = *se[u].begin(), r = *se[u].rbegin(), m = (l + r) >> 1;
    auto a = se[u].lower_bound(m), b = next(a);
    lf res = n;
    if (b != se[u].end()) cmin(res, max(0.5 * (*a + *b) - l, r - 0.5 * (*a + *b)));
    if (a != se[u].begin()) b = a, a = prev(a), cmin(res, max(0.5 * (*a + *b) - l, r - 0.5 * (*a + *b)));
    if (a != se[u].begin()) b = a, a = prev(a), cmin(res, max(0.5 * (*a + *b) - l, r - 0.5 * (*a + *b)));
    return res;
}

int main() {
    io >> T;
    while (T--) {
        io >> n;
        For (i, 1, n) fa[i] = i, se[i].insert(i);
        int u, v;
        For (i, 1, n - 1) io >> u >> v, printf("%.1lf\n", merge(find(u), find(v)));
        se[find(1)].clear();
    }

    return 0;
}
