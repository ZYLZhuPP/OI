#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
typedef double lf;
const int N = 1e6 + 5;

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

int n, q[N], C;
ll c[N], s[N], S[N], f[N];

inline ll X(int i) { return s[i]; }
inline ll Y(int i) { return f[i] + S[i]; }
inline lf K(int i, int j) { return 1.0 * (Y(i) - Y(j)) / (X(i) - X(j)); }
inline ll F(int i, int j) { return f[j] + (s[i] - s[j]) * i - (S[i] - S[j]) + C; }

int main() {
    io >> n >> C;
    int x, y;
    For (i, 1, n) io >> x >> y, c[x] += y;
    n = 1e6;
    For (i, 1, n) s[i] = s[i - 1] + c[i], S[i] = S[i - 1] + c[i] * i;
    int h = 1, t = 0;
    q[++t] = 0;
    For (i, 1, n) {
        if (!c[i]) { f[i] = f[i - 1]; continue; }
        while (t - h > 0 && K(q[h], q[h + 1]) <= i) h++;
        f[i] = F(i, q[h]);
        while (t - h > 0 && K(i, q[t]) <= K(q[t], q[t - 1])) t--;
        q[++t] = i;
    }
    printf("%lld", f[n]);

    return 0;
}
