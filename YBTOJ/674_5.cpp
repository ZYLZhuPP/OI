#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
#define mkp make_pair
#define st first
#define nd second
typedef long long ll;
typedef long double Lf;
const int N = 1e5 + 5;

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

int T, n, P, t, opt[N];
Lf f[N];
ll L, s[N];
pair<int, pair<int, int > > q[N];
char st[N][35];

Lf qPow(Lf a, int b) {
    Lf r = 1;
    while (b) { if (b & 1) r *= a; a *= a; b >>= 1; }
    return r;
}
Lf F(int i, int j) { return f[j] + qPow(abs(s[i] - s[j] + (i - j - 1) - L), P); }

int main() {
    io >> T;
    while (T--) {
        io >> n >> L >> P;
        For (i, 1, n) {
            io >> st[i];
            s[i] = s[i - 1] + strlen(st[i]);
        }
        
        f[0] = 0;
        int h = 1, t = 0;
        q[++t] = mkp(0, mkp(1, n));
        For (i, 1, n) {
            while (h <= t && q[h].nd.nd < i) h++;
            opt[i] = q[h].st; f[i] = F(i, opt[i]);
#define j q[t].st
#define L q[t].nd.st
#define R q[t].nd.nd
            while (h <= t && L > i && F(L, i) <= F(L, j)) t--;
            int l = max(L, i + 1), r = R, pos = L;
            while (l <= r) {
                int m = (l + r) >> 1;
                if (F(m, j) < F(m, i)) pos = m, l = m + 1;
                else r = m - 1;
            }
            if (pos < n) R = pos, q[++t] = mkp(i, mkp(pos + 1, n));
        }

        if (f[n] > 1e18) puts("Too hard to arrange");
        else printf("%lld\n", ll(f[n]));
        puts("--------------------");
    }

    return 0;
}
