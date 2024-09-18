#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 2e5 + 5;

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

int T, n, K, f[N][10];
array<int, 2 > a[N];

int main() {
    io >> T;
    while (T--) {
        io >> n >> K;
        For (i, 1, n) io >> a[i][0] >> a[i][1];
        sort(a + 1, a + n + 1);
        memset(f[n + 1], 0, sizeof f[n + 1]);
        rFor (i, n, 1) f[i][0] = max(f[i + 1][0], a[i][0] - a[i][1]);
        rFor (i, n, 1) For (j, 1, K) f[i][j] = max(f[i + 1][j], min(f[i + 1][j - 1] - a[i][1], a[i][0] - a[i][1]));
        printf("%d\n", f[1][K]);
    }

    return 0;
}
