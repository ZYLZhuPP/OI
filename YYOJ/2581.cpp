#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef double lf;
const int N = 1e3 + 5;
template<class C> inline bool cmin(C &x, const C &y) { return y<x? x=y, 1: 0; }

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

struct XY {
    lf x, y;
    bool operator != (const XY &a) const {
        return int(2 * x) ^ int(2 * a.x) || int(2 * y) ^ int (2 * a.y);
    }
} pos[N * N];

int T, n, ans, f[N][N][2][2][2], a[N][N];
lf m;

inline lf P(lf x) { return x -= x>=n? n: x<0? -n: 0; }

inline XY to(lf i, lf j, int x, int y, int kx, int ky, int xy) {
    if (xy) swap(i, j);
    if (kx) i = n - i;
    if (ky) j = n - j;
    return {P(i + x), P(j + y)};
}

int main() {
    io >> T;
    while (T--) {
        io >> n; m = 0.5 * (n + 1); ans = 1e9;
        For (i, 1, n) For (j, 1, n) pos[(i - 1) * n + j] = {P(i - m), P(j - m)};
        For (i, 1, n) For (j, 1, n) io >> a[i][j];
        memset(f, 31, sizeof f);
        queue<array<int, 5> > q;
        f[0][0][0][0][0] = 0; q.push({0, 0, 0, 0, 0});
        while (!q.empty()) {
            auto [x, y, kx, ky, xy] = q.front(); q.pop();
            int d = f[x][y][kx][ky][xy];
            int x_ = (x + 1) % n;
            if (cmin(f[x_][y][kx][ky][xy], d + 1)) q.push({x_, y, kx, ky, xy});
            int y_ = (y + 1) % n;
            if (cmin(f[x][y_][kx][ky][xy], d + 1)) q.push({x, y_, kx, ky, xy});
            if (cmin(f[y][x][ky][kx][!xy], d + 1)) q.push({y, x, ky, kx, !xy});
            x_ = (n - x) % n; y_ = (n - y) % n;
            if (cmin(f[y][x_][ky][!kx][!xy], d + 1)) q.push({y, x_, ky, !kx, !xy});
            if (cmin(f[x_][y][!kx][ky][xy], d + 1)) q.push({x_, y, !kx, ky, xy});
            if (cmin(f[x][y_][kx][!ky][xy], d + 1)) q.push({x, y_, kx, !ky, xy});
        }
        For (kx, 0, 1) For (ky, 0, 1) For (xy, 0, 1) {
            int p = a[1][1];
            auto [x_, y_] = to(P(1 - m), P(1 - m), 0, 0, kx, ky, xy);
            int x = (int(pos[p].x - x_) + n) % n, y = (int(pos[p].y - y_) + n) % n;
            bool flag = 1;
            For (i, 1, n) if (flag) For (j, 1, n) if (flag) {
                if (to(P(i - m), P(j - m), x, y, kx, ky, xy) != pos[a[i][j]]) flag = 0;
            }
            if (flag) cmin(ans, f[x][y][kx][ky][xy]);
        }
        printf("%d\n", ans);
    }

    return 0;
}
