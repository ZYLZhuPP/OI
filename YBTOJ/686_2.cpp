#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 4e4 + 5;

struct IO {
	char c; int f;
#define gc() (getchar())
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
	inline bool operator ~ () { return ~c; }
} io;

int n, ans, s[N], to[N], T, m;
char a[105][105];

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

bool ok(int k) {
    set<int > o;
    For (i, 2, m) {
        if (h[i] >= k)
            o.insert(to[sa[i]]),
            o.insert(to[sa[i - 1]]);
        else {
            if (o.size() == n) return 1;
            o.clear();
        }
    }
    return 0;
}

void init() {
    ans = 0;
}

int main() {
    io >> T;
    while (T--) {
        init();
        io >> n;
        For (i, 1, n) io >> a[i];
        if (n == 1) { printf("%d\n", strlen(a[1])); continue; }
        m = 0; For (i, 1, n) {
            int l = strlen(a[i]);
            For (j, 0, l - 1) s[++m] = a[i][j], to[m] = i;
            s[++m] = 300 - i; to[m] = i;
            rFor (j, l - 1, 0) s[++m] = a[i][j], to[m] = i;
            s[++m] = 300 - i; to[m] = i;
        }
        SA(s, m, 300);
        int l = 1, r = 100;
        while (l <= r) {
            int m = (l + r) >> 1;
            if (ok(m)) ans = m, l = m + 1;
            else r = m - 1;
        }
        printf("%d\n", ans);
    }

    return 0;
}
