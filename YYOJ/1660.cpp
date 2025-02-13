#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (register int i = (l); i <= (r); ++i)
const int N = 1e6 + 5, Mo = 998244353;
inline int mo(int &x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline int gmo(int x) { return mo(x); }
inline void add(int &x, const int &y) { mo(x += y); }
inline int mul(const int &x, const int &y) { return 1ll * x * y % Mo; }

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
	inline bool operator ~ () {return ~c;}
} io;

int n, k, x, w;
int pri[N], psiz, fac[N], inv[N], invfac[N], mip[N], s[N];

int C(int n, int m) { return mul(mul(fac[n], invfac[n - m]), invfac[m]); }

int qPow(int a, int b) {
    int res = 1; 
    do { if (~b&1 || (res = mul(res, a))) a = mul(a, a); } while (b >>= 1); 
    return res;
}

int S(int n, int m) {
    if (n < m) return 0;
    int res = 0;
    s[0] = 0; s[1] = 1;
    For (i, 2, m) {
        int p = pri[mip[i]];
        s[i] = p == i? qPow(i, n): mul(s[i / p], s[p]);
    }
    For (i, 0, m) add(res, (i&1? -1: 1) * mul(C(m, i), s[m - i]));
    return mul(res, invfac[m]);
}

void init() {
#define M 1000000
    inv[0] = inv[1] = 1; For (i, 2, M) inv[i] = mul(Mo - Mo / i, inv[Mo % i]);
    fac[0] = invfac[0] = 1; For (i, 1, M) fac[i] = mul(fac[i - 1], i), invfac[i] = mul(invfac[i - 1], inv[i]);
    For (i, 2, M) {
        if (!mip[i]) pri[++psiz] = i, mip[i] = psiz;
        For (j, 1, mip[i]) {
            int ne = i * pri[j];
            if (ne > M) break;
            mip[ne] = j;
        }
    }
}

int main() {
    init();
    io >> n >> k;
    For (i, 1, n) io >> x, add(w, x);

    printf("%d", mul(w, gmo(S(n, k) + mul(n - 1, S(n - 1, k)))));

    return 0;
}
