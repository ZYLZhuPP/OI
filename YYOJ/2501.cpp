#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 5e5 + 5;
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

int n, B, W, K, tot, s1[N], s2[N], f1[N], f2[N], f[N * 20];
char s[N];
vector<int > es[N * 20];

namespace BIT {
    int lim, o[N];
#define lowbit(x) ((x) & -(x))
    inline void init(int n_) { lim = n_; For (i, 1, lim) o[i] = -1; }
    inline void ins(int x, int id) {
        for (; x <= lim; x += lowbit(x)) {
            es[++tot].pb(id); if (~o[x]) es[tot].pb(o[x]);
            o[x] = tot;
        }
    }
    inline void add(int x, int id) { for (; x; x -= lowbit(x)) if (~o[x]) es[id].pb(o[x]); }
}
using namespace BIT;

int main() {
    io >> n >> B >> W; K = B + W; tot = n;
    scanf("%s", s + 1);
    For (i, 1, n) {
        s1[i] = s1[i - 1] + (s[i] == 'B'), s2[i] = s2[i - 1] + (s[i] == 'W');
        f1[i] = i>=K? f1[i - K] - B + s1[i] - s1[i - K]: 0;
        f2[i] = i>=K? f2[i - K] - W + s2[i] - s2[i - K]: 0;
    }
    For (r, 0, K - 1) {
        vector<int > pos, b;
        for (int i = r; i <= n; i += K) pos.pb(i), b.pb(f2[i]);
        sort(b.begin(), b.end()); b.resize(unique(b.begin(), b.end()) - b.begin());
        init(b.size());
        sort(pos.begin(), pos.end(), [&](const int &i, const int &j) { return f1[i]^f1[j]? f1[i]<f1[j]: f2[i]^f2[j]? f2[i]<f2[j]: i>j; });
        for (auto &i : pos) {
            int x = lower_bound(b.begin(), b.end(), f2[i]) - b.begin() + 1;
            add(x, i);
            ins(x, i);
        }
    }
    memset(f, 31, sizeof f);
    f[0] = 0;
    deque<int > q; q.pb(0);
    while (!q.empty()) {
        int u = q.front(); q.pop_front();
        for (auto &v : es[u]) if (cmin(f[v], f[u])) q.push_front(v);
        if (u + 1 <= n && cmin(f[u + 1], f[u] + 1)) q.pb(u + 1);
    }
    printf("%d", (n - f[n]) / K);

    return 0;
}
