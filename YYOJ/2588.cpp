#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e6 + 5;

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

int n, _[13], m, pos[N], len, ch[N][3], t[N], v[N], tot, rt;
char s[N];

inline void build(int &u, int k, int x) {
    u = ++tot;
    if (k == n) return v[u] = x, void();
    For (i, 0, 2) build(ch[u][i], k + 1, x + i * _[k]);
}
inline void mark(int u) { swap(ch[u][1], ch[u][2]); t[u] ^= 1; }
inline void down(int u) { if (t[u]) For (i, 0, 2) mark(ch[u][i]); t[u] = 0; }
inline void Next(int u, int k) {
    if (k == n) return;
    down(u); swap(ch[u][0], ch[u][1]); swap(ch[u][1], ch[u][2]);
    Next(ch[u][2], k + 1);
}
inline void dfs(int u, int k, int x) {
    if (k == n) return pos[v[u]] = x, void();
    down(u); For (i, 0, 2) dfs(ch[u][i], k + 1, x + i * _[k]);
}

int main() {
    io >> n;
    _[0] = 1; For (i, 1, n) _[i] = _[i - 1] * 3;
    m = _[n];
    build(rt, 0, 0);
    scanf("%s", s + 1); len = strlen(s + 1);
    For (i, 1, len) s[i]&1? Next(rt, 0): mark(rt);
    dfs(rt, 0, 0);
    For (i, 0, m - 1) printf("%d ", pos[i]);

    return 0;
}
