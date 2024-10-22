#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e6 + 5, inf = 1e9;
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

int T, n, K, L, R, Q, len, dis[N], l[N], r[N], q[N];
vector<int > es[N];

int main() {
    io >> T;
    while (T--) {
        io >> n >> K >> L >> R >> Q; len = R - L;
        int h = 1, t = 0;
        For (i, 0, n - 1) {
            int j = (1ll * i * K + L) % n;
            es[j].pb(i - len);
            if (!i || i + len >= n) dis[i] = 0, q[++t] = i;
            else dis[i] = inf;
        }
        if (!len) {
            while (h <= t) {
                int u = q[h++];
                for (auto &v : es[u]) if (cmin(dis[v], dis[u] + 1)) q[++t] = v;
            }
        } else {
            For (i, 0, (n - 1) / len) l[i] = i * len, r[i] = min(n - 1, (i + 1) * len - 1);
            while (h <= t) {
                int u = q[h++];
                for (auto &v : es[u]) {
                    int x = v / len, y = (v + len) / len;
                    if (v >= 0) for (int &i = r[x]; i >= l[x] && i >= v; --i) if (cmin(dis[i], dis[u] + 1)) q[++t] = i;
                    for (int &i = l[y]; i <= r[y] && i <= v + len; ++i) if (cmin(dis[i], dis[u] + 1)) q[++t] = i;
                }
            }
        }
        int x;
        while (Q--) io >> x, x = (x + L) % n, printf("%d\n", dis[x]<inf? dis[x]: -1);
        For (i, 0, n - 1) es[i].resize(0);
    }

    return 0;
}
