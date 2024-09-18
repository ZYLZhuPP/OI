#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
const int N = 1e5 + 5, Mo = 1e5 + 3;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline int ml(int x, int y) { return 1ll * x * y % Mo; }
inline void mul(int &x, int y) { x = ml(x, y); }

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
	inline bool operator ~ () { return ~c; }
} io;

int n, k, inv[N], a[N], cnt, g[N], f[N];
vector<int > p[N];

int main() {
    io >> n >> k;
    inv[0] = inv[1] = 1;
    For (i, 2, n) inv[i] = ml(Mo - Mo / i, inv[Mo % i]);
    For (i, 1, n) for (int j = i; j <= n; j += i) p[j].push_back(i);
    For (i, 1, n) io >> a[i];
    rFor (i, n, 1) {
        if (a[i]) {
            cnt++;
            for (auto &j : p[i]) a[j] ^= 1;
        }
    }

    g[n - 1] = 1;
    rFor (i, n - 2, k) {
        int x = ml(n, inv[i + 1]);
        g[i] = mo(ml(x - 1, g[i + 1]) + x);
    }
    For (i, 0, k - 1) g[i] = 1;
    For (i, 0, cnt - 1) f[i + 1] = f[i] + g[i];

    For (i, 1, n) mul(f[cnt], i);
    printf("%d", f[cnt]);

    return 0;
}
