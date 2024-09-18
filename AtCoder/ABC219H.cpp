#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 305;
template<class C> inline bool cmax(C &x, const C &y) { return y>x? x=y, 1: 0; }

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

int n, n1, n2;
ll f[N][N][N][2];
array<int, 2 > a[N], b[N];

int main() {
    io >> n;
    For (i, 1, n) {
        int x, y;
        io >> x >> y;
        if (x >= 0) a[++n1] = {x, y};
        else b[++n2] = {-x, y};
    }
    sort(a + 1, a + n1 + 1); sort(b + 1, b + n2 + 1);
    memset(f, 224, sizeof f);
    For (i, 0, n) f[0][0][i][0] = f[0][0][i][1] = 0;
    For (i, 0, n1) For (j, 0, n2) rFor (k, n, 0) {
        if (i < n1) {
            cmax(f[i + 1][j][k][0], f[i][j][k][0] - 1ll * k * (a[i + 1][0] - a[i][0]));
            cmax(f[i + 1][j][k][0], f[i][j][k][1] - 1ll * k * (a[i + 1][0] + b[j][0]));
            if (k) {
                cmax(f[i + 1][j][k - 1][0], f[i][j][k][0] - 1ll * k * (a[i + 1][0] - a[i][0]) + a[i + 1][1]);
                cmax(f[i + 1][j][k - 1][0], f[i][j][k][1] - 1ll * k * (a[i + 1][0] + b[j][0]) + a[i + 1][1]);
            }
        }
        if (j < n2) {
            cmax(f[i][j + 1][k][1], f[i][j][k][1] - 1ll * k * (b[j + 1][0] - b[j][0]));
            cmax(f[i][j + 1][k][1], f[i][j][k][0] - 1ll * k * (b[j + 1][0] + a[i][0]));
            if (k) {
                cmax(f[i][j + 1][k - 1][1], f[i][j][k][1] - 1ll * k * (b[j + 1][0] - b[j][0]) + b[j + 1][1]);
                cmax(f[i][j + 1][k - 1][1], f[i][j][k][0] - 1ll * k * (b[j + 1][0] + a[i][0]) + b[j + 1][1]);
            }
        }
    }
    printf("%lld", max(f[n1][n2][0][0], f[n1][n2][0][1]));

    return 0;
}
