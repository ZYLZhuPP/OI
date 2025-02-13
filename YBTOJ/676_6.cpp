#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 5e5 + 5;

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
ll f[N], s[N];

inline ll dx(int i, int j) { return s[i] - s[j]; }
inline ll dy(int i, int j) { return f[i] + s[i] * s[i] - (f[j] + s[j] * s[j]); }
inline ll F(int i, int j) { return f[j] + (s[i] - s[j]) * (s[i] - s[j]) + m; }

int main() {
    while (~(io >> n >> m)) {
        For (i, 1, n) io >> x, s[i] = s[i - 1] + x;
    
        memset(f, 31, sizeof f); f[0] = 0;
        int h = 1, t = 0; q[++t] = 0;
        For (i, 1, n) {
            ll k = 2ll * s[i];
            while (h < t && dy(q[h + 1], q[h]) <= dx(q[h + 1], q[h]) * k) h++;
            f[i] = F(i, q[h]);
            while (h < t && dy(i, q[t]) * dx(q[t], q[t - 1]) <= dy(q[t], q[t - 1]) * dx(i,   q[t])) t--;
            q[++t] = i;
        }
    
        printf("%lld\n", f[n]);
    }

    return 0;
}
