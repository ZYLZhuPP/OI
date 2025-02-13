#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 3e5 + 5;

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

int n, x, y, q[N];
ll S, f[N], c[N], s[N];

inline ll dx(int i, int j) { return c[i] - c[j]; }
inline ll Y(int i) { return f[i] + (S - s[i]) * (c[n] - c[i]); }
inline ll dy(int i, int j) { return  Y(i) - Y(j); }
inline ll F(int i, int j) { return f[j] + (s[i] - s[j] + S) * (c[n] - c[j]); }

int main() {
    io >> n >> S;
    For (i, 1, n) io >> x >> y, s[i] = s[i - 1] + x, c[i] = c[i - 1] + y;

    memset(f, 31, sizeof f); f[0] = 0;
    int h = 1, t = 0; q[++t] = 0;
    For (i, 1, n) {
        ll k = s[i];
        int l = h, r = t - 1, pos = t;
        while (l <= r) {
            int m = (l + r) >> 1;
            if (dy(q[m + 1], q[m]) >= dx(q[m + 1], q[m]) * k) pos = m, r = m - 1;
            else l = m + 1;
        }
        f[i] = F(i, q[pos]);
        while (h < t && dy(i, q[t]) * dx(q[t], q[t - 1]) <= dy(q[t], q[t - 1]) * dx(i, q[t])) t--;
        q[++t] = i;
    }

    printf("%lld", f[n]);

    return 0;
}
