#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
const int N = 1e7 + 5, Mo = 20101009;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, const int &y) { x = mo(x + y); }
inline int ml(const int &x, const int &y) { return 1ll * x * y % Mo; }

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

int n, m, mu[N], pri[N], mip[N], psz, s[N];

void init() {
    mu[1] = 1;
    For (i, 2, N - 1) {
        if (!mip[i]) {
            pri[mip[i] = ++psz] = i;
            mu[i] = -1;
        }
        For (j, 1, mip[i]) {
            int ne = i * pri[j];
            if (ne >= N) break;
            mip[ne] = j;
            if (j ^ mip[i]) mu[ne] = -mu[i];
            else mu[ne] = 0;
        }
    }
    For (i, 1, N - 1) s[i] = mo(s[i - 1] + ml(mu[i], ml(i, i)));
}

inline int G(int n, int m) { return ml(1ll * n * (n + 1) / 2 % Mo, 1ll * m * (m + 1) / 2 % Mo); }
inline int F(int n, int m) {
    int res = 0;
    for (int l = 1, r; l <= min(n, m); l = r + 1) {
        r = min(n / (n / l), m / (m / l));
        add(res, ml(mo(s[r] - s[l - 1]), G(n / l, m / l)));
    }
    return res;
}
inline int solve(int n, int m) {
    int res = 0;
    for (int l = 1, r; l <= min(n, m); l = r + 1) {
        r = min(n / (n / l), m / (m / l));
        add(res, ml(mo(1ll * (l + r) * (r - l + 1) / 2 % Mo), F(n / l, m / l)));
    }
    return res;
}

int main() {
    init();
    io >> n >> m;
    printf("%d", solve(n, m));

    return 0;
}
