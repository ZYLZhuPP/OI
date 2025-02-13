#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 205, M = 4e4 + 5;

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

int n, b[N], c[N], K, f[M], g[M];
int q[M];

int main() {
    io >> n;
    For (i, 1, n) io >> b[i];
    For (i, 1, n) io >> c[i];
    io >> K;

    memset(f, 31, sizeof f); f[0] = 0;
    For (o, 1, n) {
        int k = b[o], m = K / k, L = c[o];
        For (r, 0, k - 1) {
            int h = 1, t = 0;
            For (i, 0, m) {
                int x = i * k + r;
                g[i] = f[x];
                while (h <= t && q[h] < i - L) h++;
                if (h <= t) f[x] = min(f[x], g[q[h]] + i - q[h]);
                while (h <= t && g[i] - i <= g[q[t]] - q[t]) t--;
                q[++t] = i;
            }
        }
    }

    printf("%d", f[K]);

    return 0;
}
