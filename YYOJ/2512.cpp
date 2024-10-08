#include<bits/stdc++.h>
using namespace std;

#define st first
#define nd second
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef double lf;
typedef long long ll;
const int N = 1e5 + 5;
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

int n, Q, A, B, bl[105], br[105], be[N], q[N], top[105], a[N], b[N];
ll s[N], S[105], ans;
pair<int, ll > p[N];

inline lf K(const int &i, const int &j) { return 1.0 * (p[i].nd - p[j].nd) / (p[i].st - p[j].st); }

inline void build(int id) {
    int l = bl[id], r = br[id], tot = l - 1;
    p[++tot] = {-b[l], s[l]};
    For (i, l + 1, r) if (-b[i] > p[tot].st) p[++tot] = {-b[i], s[i]};
    int &t = top[id] = l - 1;
    For (i, l, tot) {
        while (t > l && K(i, q[t]) <= K(q[t - 1], q[t])) t--;
        q[++t] = i;
    }
}

inline int get(int id, int k) {
    int l = bl[id] + 1, r = top[id], res = bl[id];
    while (l <= r) {
        int m = (l + r) >> 1;
        if (K(q[m], q[m - 1]) <= k) res = m, l = m + 1;
        else r = m - 1;
    }
    return q[res];
}

inline ll query(int id, int k) {
    int x = get(id, k);
    return p[x].nd + S[id] - 1ll * p[x].st * k;
}

int main() {
    io >> n >> Q;
    For (i, 1, n) io >> a[i], s[i] = s[i - 1] + a[i];
    For (i, 1, n) io >> b[i];

    A = 1500; B = (n + A - 1) / A;
    For (i, 1, B) bl[i] = br[i - 1] + 1, br[i] = i * A;
    br[B] = n;
    For (i, 1, B) For (j, bl[i], br[i]) be[j] = i;
    For (i, 1, B) build(i);

    int op, k, x, v;
    while (Q--) {
        io >> op >> k >> x >> v;
        int id = be[k];
        if (op == 1) {
            int d = x - a[k]; a[k] = x;
            For (i, k, br[id]) s[i] += d;
            build(id);
            For (i, id + 1, B) S[i] += d;
        } else {
            b[k] = x;
            build(id);
        }
        ans = 2e18;
        For (i, 1, B) cmin(ans, query(i, v));
        printf("%lld\n", ans);
    }

    return 0;
}
