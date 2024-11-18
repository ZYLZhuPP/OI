#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 5e5 + 5;

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

int f[N], g[N];
struct Node {int min, max; Node(int ge = 0, int fe = 0): min(ge), max(fe){ } } preX[N], preY[N], sufX[N], sufY[N];
#define upd(T, p) (Node){T[i] < T[p.min] ? i : p.min, T[i] > T[p.max] ? i : p.max};

inline bool check1(int x, int y, int n, int m) {
	if (x == 1 || y == 1) return 1;
	Node X = preX[x - 1], Y = preY[y - 1];
	if (f[X.min] < g[Y.min]) return check1(X.min, y, n, m);
	if (g[Y.max] > f[X.max]) return check1(x, Y.max, n, m);
	return 0;
}

inline bool check2(int x, int y, int n, int m) {
	if (x == n || y == m) return 1;
	Node X = sufX[x + 1], Y = sufY[y + 1];
	if (f[X.min] < g[Y.min]) return check2(X.min, y, n, m);
	if (g[Y.max] > f[X.max]) return check2(x, Y.max, n, m);
	return 0;
}

inline bool solve(int tmpf[], int tmpg[], int n, int m) {
	if (tmpf[1] >= tmpg[1]) return 0;
    memcpy(f, tmpf, sizeof f);
    memcpy(g, tmpg, sizeof g);

	For (i, 1, n) preX[i] = (i == 1) ? (Node){1, 1} : upd(f, preX[i - 1]);
	For (i, 1, m) preY[i] = (i == 1) ? (Node){1, 1} : upd(g, preY[i - 1]);
	rFor (i, n, 1) sufX[i] = (i == n) ? (Node){n, n} : upd(f, sufX[i + 1]);
	rFor (i, m, 1) sufY[i] = (i == m) ? (Node){m, m} : upd(g, sufY[i + 1]);

	Node X = preX[n], Y = preY[m];
	if (f[X.min] >= g[Y.min] || g[Y.max] <= f[X.max]) return 0;
	return check1(X.min, Y.max, n, m) && check2(X.min, Y.max, n, m);
}

int id, n, m, q, tx[N], ty[N], ttx[N], tty[N];

int main() {
    io >> id >> n >> m >> q;
    For (i, 1, n) io >> tx[i];
    For (i, 1, m) io >> ty[i];
	putchar(solve(tx, ty, n, m) || solve(ty, tx, m, n) ? '1' : '0');
	while (q--)	{
        memcpy(ttx, tx, sizeof tx);
        memcpy(tty, ty, sizeof ty);
		int cx, cy, p, v;
        io >> cx >> cy;
		while (cx--) io >> p >> v, ttx[p] = v;
		while (cy--) io >> p >> v, tty[p] = v;
		putchar(solve(ttx, tty, n, m) || solve(tty, ttx, m, n) ? '1' : '0');
	}

	return 0;
}