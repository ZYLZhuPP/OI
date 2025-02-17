#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 2e5 + 5;

struct IO {
    char c; int f;
#define gc() getchar()
    inline IO& operator >> (char *x) {
        while ((c = gc()) < 33 && ~c);
        while (c > 32) *x++ = c, c = gc();
        *x = 0; return *this;
    }
    inline bool operator ~ () const { return ~c; }
} io;

int n, m, ans;
char s[N];

int sa[N], h[N], cnt[N], _[2][N], *x = _[0], *rk = _[1];
template<class C> void SA(const C *s, int n, int m) {
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

bool pd[2];
bool ok(int k) {
    pd[0] = pd[1] = 0;
    For (i, 2, n + 1) {
        if (h[i] >= k)
            pd[sa[i - 1] > m] = pd[sa[i] > m] = 1;
        else {
            pd[0] = pd[1] = 0;
            if (pd[0] && pd[1]) return 1;
        }
    }
    return 0;
}

int main() {
    io >> (s + 1); m = strlen(s + 1);
    s[++m] = '#';
    io >> (s + m + 1);
    n = strlen(s + 1);
    SA(s, n, 122);
    int l = 1, r = n;
    while (l <= r) {
        int m = (l + r) >> 1;
        if (ok(m)) ans = m, l = m + 1;
        else r = m - 1;
    }
    printf("%d\n", ans);
    
    return 0;
}
