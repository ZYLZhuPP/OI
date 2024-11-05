#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 2e3 + 5;

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
	inline bool operator ~ () const { return ~c; }
} io;

int T, tot, A, B, n, m, cnt[10], c[N], a[N], b[N], d[N];

int main() {
    io >> T;
    while (T--) {
        tot = A = B = 0;
        io >> n >> m;
        For (i, 1, 9) io >> cnt[i];
        rFor (i, 9, 1) For (j, 1, cnt[i]) c[++tot] = i;
        if (n < m) swap(n, m);
        bool flag = 0;
        For (i, 1, tot) {
            if (B < m) {
                if (!flag && c[i] ^ c[i + 1]) b[++B] = c[i], a[++A] = c[++i], flag = 1;
                else a[++A] = c[i], b[++B] = c[++i];
            } else a[++A] = c[i];
        }
        For (i, 0, n / 2) swap(a[i], a[n - i]);
        For (i, 0, m / 2) swap(b[i], b[m - i]);
        For (i, 0, tot) c[i] = 0;
        For (i, 0, m - 1) {
            For (j, 0, tot) d[j] = 0;
            For (j, 0, n - 1) d[i + j] += b[i] * a[j], d[i + j + 1] += d[i + j] / 10, d[i + j] %= 10;
            For (j, 0, tot) c[j] += d[j], c[j + 1] += c[j] / 10, c[j] %= 10;
        }
        while (!c[tot]) tot--;
        rFor (i, tot, 0) printf("%d", c[i]);
        puts("");
    }

    return 0;
}
