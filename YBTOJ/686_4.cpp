#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define mkp make_pair
#define st first
#define nd second
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
    inline IO& operator >> (char *x) {
        while ((c = gc()) < 33 && ~c);
        while (c > 32) *x++ = c, c = gc();
        *x = 0; return *this;
    }
    inline bool operator ~ () const { return ~c; }
} io;

int n, m, T, mx, a[N], t, ans;
char s[N];
pair<int, int > q[N];

int sa[N], h[N], cnt[N], _[2][N], *x = _[0], *rk = _[1];
template<class C> void SA(const C *s, int n, int m) {
    int t = 0;
    For (i, 0, m) cnt[i] = 0; For (i, 1, n) cnt[rk[i] = s[i]]++;
    For (i, 1, m) cnt[i] += cnt[i - 1];
    rFor (i, n, 1) sa[cnt[rk[i]]--] = i;

    for (int j = 1; ; j <<= 1) {
        swap(x, rk);

        t = 0; For (i, n - j + 1, n) rk[++t] = i;
        For (i, 1, n) if (sa[i] > j) rk[++t] = sa[i] - j;

        For (i, 0, m) cnt[i] = 0; For (i, 1, n) cnt[x[rk[i]]]++;
        For (i, 1, m) cnt[i] += cnt[i - 1];
        rFor (i, n, 1) sa[cnt[x[rk[i]]]--] = rk[i];

        m = 0; For (i, 1, n) rk[sa[i]] = m += x[sa[i - 1]] ^ x[sa[i]] || x[sa[i - 1] + j] ^ x[sa[i] + j];
        if (m == n) break;
    }

    For (i, 1, n) {
        m = max(0, h[rk[i - 1]] - 1);
        while (s[sa[rk[i] - 1] + m] == s[i + m]) m++;
        h[rk[i]] = m;
    }
}

int f[20][N];
void init() {
    For (i, 1, n) f[0][i] = h[i];
    for (int i = 1; (1 << i) <= n; ++i)
        For (j, 1, n - (1 << i) + 1)
            f[i][j] = min(f[i - 1][j], f[i - 1][j + (1 << (i - 1))]);
}

int LCP(int x, int y) {
    if (x > y) swap(x, y);
    int o = log2(y - x);
    return min(f[o][x + 1], f[o][y - (1 << o) + 1]);
}

int main() {
    io >> n >> T;
    io >> (s + 1);
    SA(s, n, 122);
    init();
    
    while (T--) {
        ans = 0;
        io >> m;
        For (i, 1, m) io >> a[i], a[i] = rk[a[i]];
        sort(a + 1, a + m + 1); m = unique(a + 1, a + m + 1) - a - 1;
        int t = 0, sum = 0;
        For (i, 2, m) {
            int x = LCP(a[i], a[i - 1]), y = 1;
            while (t && q[t].st >= x) sum -= q[t].st * q[t].nd, y += q[t].nd, t--;
            q[++t] = mkp(x, y); sum += x * y;
            ans += sum;
        }
        printf("%d\n", ans);
    }

    return 0;
}
