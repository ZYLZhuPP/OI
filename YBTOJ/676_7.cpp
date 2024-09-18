#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 2e5 + 5;

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

int n, x;
ll d[N], s[N], sum, ans, g[N], f[N];
int q[N];

inline ll dx(int i, int j) { return s[i] - s[j]; }
inline ll dy(int i, int j) { return g[i] - g[j]; }
inline ll F(int i, int j) { return g[j] + (s[i] - s[j]) * d[i]; }

int main() {
    io >> n;
    For (i, 1, n) io >> x >> d[i], s[i] = s[i - 1] + x;
    rFor (i, n, 1) sum += s[i] * d[i], d[i] += d[i + 1], g[i] = s[i] * d[i];

    int h = 1, t = 0; q[++t] = 0;
    For (i, 1, n) {
        ll k = d[i];
        while (h < t && dy(q[h + 1], q[h]) >= dx(q[h + 1], q[h]) * k) h++;
        f[i] = F(i, q[h]); ans = max(ans, f[i]);
        while (h < t && dy(i, q[t]) * dx(q[t], q[t - 1]) >= dy(q[t], q[t - 1]) * dx(i, q[t])) t--;
        q[++t] = i;
    }
    printf("%lld", sum - ans);

    return 0;
}
