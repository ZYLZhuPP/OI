#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 3005;

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
	inline bool operator ~ () const { return ~c; }
} io;

int n, a[N], f[N][N];

int main() {
    io >> n;
    For (i, 1, n) io >> a[i];
    For (len, 2, n) For (i, 1, n - len + 1) {
        int j = i + len - 1;
        f[i][j] = min(min(f[i + 1][j], f[i][j - 1]) + 1, f[i + 1][j - 1] + !(a[i] == a[j]));
    }
    printf("%d", f[1][n]);

    return 0;
}
