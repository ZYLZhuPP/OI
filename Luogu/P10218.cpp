#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
typedef __int128 lll;
const int N = 1.5e7 + 5;
template<class C> inline void cmax(C &x, const C &y) { y>x? x=y: 0; }
template<class C> inline void cmin(C &x, const C &y) { y<x? x=y: 0; }

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
    int st[66], t;
#define pc(c) putchar(c)
    template<class C>
    inline IO& operator << (C x) {
        if (!x) pc('0'); if (x < 0) pc('-'), x = -x;
        while (x) st[++t] = x % 10, x /= 10;
        while (t) pc(st[t--] ^ 48);
        return *this;
    }
    inline IO& operator << (char x) {
        pc(x); return *this;
    }
    inline bool operator ~ () const { return ~c; }
} io;

int id, T, n, m, K, b[N], ch[N][2], tot;
lll a[N], mn[N], ans, S;
ll s[N];

inline int node() { return mn[++tot] = S, ch[tot][0] = ch[tot][1] = s[tot] = 0, tot; }

inline void solve(int u, int k, int m, lll x, lll y, lll z) {
    if (k == -1) return cmax(ans, z);
    lll S = (lll)1 << k;
    if (!u) return cmax(ans, y + (x | (S * 2 - 1)));
    int ls = ch[u][0], rs = ch[u][1];
    bool flag = 0;
    if (s[ls] <= m && min(y, mn[ls]) + (x | (S - 1)) >= (z | S)) solve(rs, k - 1, m - s[ls], x, min(y, mn[ls]), z | S), flag = 1;
    if (s[rs] <= m && min(y, mn[rs]) + (x | (S * 2 - 1)) >= (z | S)) solve(ls, k - 1, m - s[rs], x | S, min(y, mn[rs]), z | S), flag = 1;
    if (flag) return;
    solve(ls, k - 1, m, x, y, z);
    solve(rs, k - 1, m, x | S, y, z);
}

int main() {
    io >> id >> T;
    while (T--) {
        ans = 0;
        io >> n >> m >> K; S = mn[0] = (lll)1 << K; tot = 0; node();
        For (i, 1, n) io >> a[i];
        For (i, 1, n) io >> b[i];
        For (i, 1, n) {
            int u = 1;
            rFor (j, K - 1, 0) {
                int c = a[i] >> j & 1;
                if (!ch[u][c]) ch[u][c] = node();
                cmin(mn[u], a[i]); s[u] += b[i];
                u = ch[u][c];
            }
            cmin(mn[u], a[i]); s[u] += b[i];
        }
        if (s[1] <= m) ans = mn[1] + S - 1;
        else solve(1, K - 1, m, 0, S, 0);
        io << ans << '\n';
    }

    return 0;
}
