#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 1e6 + 5, M = 1e5;
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

int n, m, Q, fa[N], b[N], S;
priority_queue<array<int, 4 > > q;
ll ans[N];

inline int find(int x) { return fa[x]^x? fa[x] = find(fa[x]): x; }

inline bool upd(int a, int s, int &c, int x) {
    if (!c) return 0;
    c--; cmin(s += x? c / x + 1: M, M);
    s = find(s);
    if (!s) return 0;
    if (!--b[s]) fa[s] = s - 1;
    ans[++S] = a;
    return 1;
}

int main() {
    freopen("vegetables.in", "r", stdin);
    freopen("vegetables.out", "w", stdout);
    io >> n >> m >> Q;
    int a, s, c, x;
    For (i, 1, n) io >> a >> s >> c >> x, q.push({a, 0, c - 1, x}), q.push({a + s, x? (c - 1) / x: M, 1, x});
    For (i, 1, M) fa[i] = i, b[i] = m;
    while (S < m * M && !q.empty()) {
        a = q.top()[0], s = q.top()[1], c = q.top()[2], x = q.top()[3]; q.pop();
        while (S < m * M && upd(a, s, c, x));
    }
    For (i, 1, m * M) ans[i] += ans[i - 1];
    while (Q--) io >> x, printf("%lld\n", ans[x * m]);

    fclose(stdin); fclose(stdout);
    return 0;
}
