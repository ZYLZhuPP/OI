#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e5 + 5, Mo = 998244353;
inline int mo(int x) { return x - (x>=Mo? Mo: x<0? -Mo: 0); }
inline void add(int &x, int y) { x = mo(x + y); }
inline int mul(int x, int y) { return 1ll * x * y % Mo; }

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
	inline IO& operator >> (char &x) {
		while ((c = gc()) < 33 && ~c);
		x = c; return *this;
	}
	inline IO& operator >> (char *x) {
		while ((c = gc()) < 33 && ~c);
		while (c > 32) *x++ = c, c = gc();
		*x = 0; return *this;
	}
} io;

int n, m, op, p, l, r;
char a[N], c;

struct mat {
	int v[4][4];
	mat(int x = 0) {
		memset(v, 0, sizeof(v)); if (!x) return;
		v[0][0] = 2; v[x][0] = Mo - 1;
		v[1][1] = v[2][2] = v[3][3] = 1;
		swap(v[0][x], v[x][x]);
 	}
 	mat operator * (const mat &x) const {
 		mat res;
 		For (k, 0, 3) For (i, 0, 3) For (j, 0, 3) add(res.v[i][j], mul(v[i][k], x.v[k][j]));
 		return res;
	}
};

namespace tr {
	mat o[N << 2];
#define ls p << 1
#define rs p << 1 | 1
#define M int m = (l + r) >> 1
#define goL ls, l, m
#define goR rs, m + 1, r
	void pushup(int p) { o[p] = o[ls] * o[rs]; }
	void build(int p, int l, int r) {
		if (l == r) return o[p] = mat(a[l] - 'A' + 1), void();
		M; build(goL); build(goR);
		pushup(p);
	}
	void upd(int p, int l, int r, int x, char c) {
		if (l == r) return o[p] = mat(c - 'A' + 1), void();
		M; x<=m? upd(goL, x, c): upd(goR, x, c);
		pushup(p);
	}
	mat query(int p, int l, int r, int x, int y) {
		if (x <= l && r <= y) return o[p];
		M; return m<x? query(goR, x, y): m+1>y? query(goL, x, y): query(goL, x, y) * query(goR, x, y);
	}
}

int main() {
	io >> n >> m;
	io >> (a + 1);
	
	tr::build(1, 1, n);
	
	For (i, 1, m) {
		io >> op;
		if (op == 1) {
			io >> p >> c;
			tr::upd(1, 1, n, p, c);
		} else {
			io >> l >> r;
			printf("%d\n", mo(tr::query(1, 1, n, l, r).v[0][0] - 1));
		} 
	} 
	
	return 0;
}
