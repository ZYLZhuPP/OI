#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
typedef long double Lf;
const int N = 5005;

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
    inline bool operator ~ () { return ~c; }
} io;

int n, h[N], f[N][N], ans;

Lf K(int x, int y) { return 1.L * (h[y] - h[x]) / (y - x); }

int main() {
	io >> n;
	For (i, 1, n) io >> h[i];
	For (i, 1, n) {
		ans ^= (f[i][i] = 1);
		int r = i;
		rFor (j, i - 1, 1) {
			if (j == i - 1 || K(j, i) < K(r, i)) r = j;
			ans ^= (f[j][i] = f[r + 1][i] + min(f[j][r - 1], f[j][r]));
		}
	}
	printf("%d", ans);
	
	return 0;
}
