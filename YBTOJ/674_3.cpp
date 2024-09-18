#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 3e3 + 5;

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

int n, m, x, q[N];
ll f0[N], f1[N], s[N];

inline ll dx(int i, int j) { return s[i] - s[j]; }
inline ll dy(int i, int j) { return f0[i] - f0[j] + s[i] * s[i] - s[j] * s[j]; }
inline ll F(int i, int j) { return f0[j] + (s[i] - s[j]) * (s[i] - s[j]); }

int main() {
    io >> n >> m;
    For (i, 1, n) io >> x, s[i] = s[i - 1] + x;

    memset(f1, 31, sizeof f1); f1[0] = 0;
    For (k, 1, m) {
        swap(f0, f1);
        int l = 1, r = 0; q[++r] = 0;
        For (i, 1, n) {
            ll k = 2ll * s[i];
            while (l < r && dy(q[l + 1], q[l]) < dx(q[l + 1], q[l]) * k) l++;
            f1[i] = F(i, q[l]);
            while (l < r && dy(i, q[r]) * dx(q[r], q[r - 1]) < dy(q[r], q[r - 1]) * dx(i, q[r])) r--;
            q[++r] = i;
        }
    }

    printf("%lld", f1[n] * m - s[n] * s[n]);

    return 0;
}
