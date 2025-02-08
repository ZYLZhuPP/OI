#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e6 + 5, Mo = 1e9 + 7;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, const int &y) { x = mo(x + y); }
inline int ml(const int &x, const int &y) { return 1ll * x * y % Mo; }
template<class C> inline bool cmin(C &x, const C &y) { return y<x? x=y, 1: 0; }

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

int n, a[N], b[N], f[N], s[N], stk[N], top;

inline int query(int l, int r) {
    if (!~l) return s[r];
    return mo(s[r] - s[l - 1]);
}

int main() {
    freopen("candy.in", "r", stdin);
    freopen("candy.out", "w", stdout);
    io >> n;
    int mn = 1e9, k = 1;
    For (i, 1, n) {
        io >> a[i];
        if (cmin(mn, a[i])) k = i;
    }
    For (i, 1, k - 1) b[n - k + i + 1] = a[i];
    For (i, k, n) b[i - k + 1] = a[i];
    f[0] = s[0] = 1;
    stk[++top] = 0;
    int S = 0;
    For (i, 1, n) {
        while (b[i] < b[stk[top]]) add(S, -ml(query(stk[top - 1], stk[top] - 1), b[stk[top]])), top--;
        add(S, ml(query(stk[top], i - 1), b[i]));
        f[i] = Mo - S; s[i] = mo(s[i - 1] + f[i]);
        stk[++top] = i;
    }
    printf("%d", ml(n&1? Mo-1: 1, mo(s[n] - s[1])));

    fclose(stdin); fclose(stdout);
    return 0;
}