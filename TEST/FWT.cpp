#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1 << 20, Mo = 998244353, inv2 = 499122177;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, const int &y) { x = mo(x + y); }
inline int ml(const int &x, const int &y) { return 1ll * x * y % Mo; }

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

int n, m, A[N], B[N], a[N], b[N], c[N];

inline void OR(int o[], int n, int tp) {
    for (int i = 1; i < n; i <<= 1)
        for (int j = 0; j < n; j += i << 1)
            For (k, j, j + i - 1) add(o[k + i], tp * o[k]);
}

inline void AND(int o[], int n, int tp) {
    for (int i = 1; i < n; i <<= 1)
        for (int j = 0; j < n; j += i << 1)
            For (k, j, j + i - 1) add(o[k], tp * o[k + i]);
}

inline void XOR(int o[], int n, int tp) {
    for (int i = 1; i < n; i <<= 1)
        for (int j = 0; j < n; j += i << 1)
            For (k, j, j + i - 1) {
                int x = o[k], y = o[k + i];
                o[k] = ml(tp, x + y);
                o[k + i] = ml(tp, x - y + Mo);
            }
}

inline void in() { memcpy(a, A, m << 2); memcpy(b, B, m << 2); }
inline void merge() { For (i, 0, m - 1) c[i] = ml(a[i], b[i]); }
inline void out() { For (i, 0, m - 1) printf("%d%c", c[i], " \n"[i==m-1]); }

int main() {
    io >> n; m = 1 << n;
    For (i, 0, m - 1) io >> A[i];
    For (i, 0, m - 1) io >> B[i];
    in(); OR(a, m, 1); OR(b, m, 1); merge(); OR(c, m, -1); out();
    in(); AND(a, m, 1); AND(b, m, 1); merge(); AND(c, m, -1); out();
    in(); XOR(a, m, 1); XOR(b, m, 1); merge(); XOR(c, m, inv2); out();

    return 0;
}