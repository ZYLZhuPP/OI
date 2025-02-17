#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e5 + 5, M = 1e5;
template<class C> inline bool cmax(C &x, const C &y) { return y>x? x=y, 1: 0; }

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

int ID, n, m, a[N], b[N], q;

int sa[N], h[N][17], cnt[N], _[2][N], *x = _[0], *rk = _[1];
template<class C>
inline void SA(const C *s, int n, int m) {
    int t = 0;
    For(i, 0, m) cnt[i] = 0; For (i, 1, n) cnt[rk[i] = s[i]]++;
    For (i, 1, m) cnt[i] += cnt[i - 1];
    rFor (i, n, 1) sa[cnt[rk[i]]--] = i;

    for (int j = 1; ; j <<= 1) {
        swap(x, rk);

        t = 0; For (i, n - j + 1, n) rk[++t] = i;
        For (i, 1, n) if (sa[i] > j) rk[++t] = sa[i] - j;

        For(i, 0, m) cnt[i] = 0; For (i, 1, n) cnt[x[i]]++;
        For (i, 1, m) cnt[i] += cnt[i - 1];
        rFor (i, n, 1) sa[cnt[x[rk[i]]]--] = rk[i];

        m = 0; For (i, 1, n) rk[sa[i]] = m += x[sa[i - 1]] ^ x[sa[i]] || x[sa[i - 1] + j] ^ x[sa[i] + j];
        if (m == n) break;
    }

    m = 0;
    For (i, 1, n) {
        m = max(0, m - 1);
        while (s[sa[rk[i] - 1] + m] == s[i + m]) m++;
        h[rk[i]][0] = m;
    }

    For (j, 1, 16) For (i, 1, n - (1 << j) + 1) h[i][j] = min(h[i][j - 1], h[i + (1 << (j - 1))][j - 1]);
}

inline void query1(int l, int r) {
    int mx = 0, cnt = 0;
    For (i, l, r) {
        int x = 0;
        For (j, i, r) if (a[j] == b[j - i + 1]) x++; else break;
        if (cmax(mx, x)) cnt = 1; else if (x == mx) cnt++;
    }
    printf("%d %d\n", mx, cnt);
}

inline int query3(int l, int r) {
    if (l == r) return m - l + 1;
    l = rk[l], r = rk[r]; if (l > r) swap(l, r);
    l++; int k = __lg(r - l + 1);
    return min(h[l][k], h[r - (1 << k) + 1][k]);
}

inline bool query4(int l, int r, int L, int R) {
    For (i, 1, m) if (query3(i, l) >= (r - l + 1) && query3(i + (r - l + 1), L) >= (R - L + 1)) return 1;
    return 0;
}

int main() {
    freopen("sone.in", "r", stdin);
    freopen("sone.out", "w", stdout);
    io >> ID;
    io >> n; For (i, 1, n) io >> a[i];
    io >> m; For (i, 1, m) io >> b[i];
    SA(b, m, M);
    io >> q;
    int k, x, l, r, L, R, op;
    while (q--) {
        io >> op;
        if (op == 1) io >> k >> x, a[k] = x, query1(1, n);
        else if (op == 2) io >> l >> r, query1(l, r);
        else if (op == 3) io >> l >> r, printf("%d\n", query3(l, r));
        else io >> l >> r >> L >> R, puts(query4(l, r, L, R)? "yes": "no");
    }

    fclose(stdin); fclose(stdout);
    return 0;
}