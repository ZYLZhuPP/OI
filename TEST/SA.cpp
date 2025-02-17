#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e6 + 5;

struct IO {
    char c; int f;
#define gc() getchar()
    inline IO& operator >> (char *x) {
        while ((c = gc()) < 33 && ~c);
        while (c > 32) *x++ = c, c = gc();
        *x = 0; return *this;
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

char s[N];

int sa[N], h[N], cnt[N], _[2][N], *x = _[0], *rk = _[1];
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
    
    For (i, 1, n) {
        m = max(0, h[rk[i - 1]] - 1);
        while (s[sa[rk[i] - 1] + m] == s[i + m]) m++;
        h[rk[i]] = m;
    }
}

int main() {
    io >> (s + 1);
    int n = strlen(s + 1);
    SA(s, n, 122);
    For (i, 1, n) io << h[i] << ' ';

    return 0;
}
