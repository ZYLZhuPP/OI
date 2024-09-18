#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
const int N = 5005, Mo = 998244353;
inline int mo(int &x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline int gmo(int x) { return mo(x); }
inline void add(int &x, int y) { mo(x += y); }
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
	inline bool operator ~ () {return ~c;}
} io;

int n, m, ans;
int l[105], la[N], lb[N], ra[N], rb[N];
int s[N][N], f[N][N];
int suba[N], subb[N];
int g[N][N], h[N][N], sg[N][N], sh[N][N];
int a[N], b[N];

void init_last() {
    memset(l, 0, sizeof(l)); For (i, 1, n) la[i] = l[a[i]], l[a[i]] = i;
    memset(l, 0, sizeof(l)); For (i, 1, m) lb[i] = l[b[i]], l[b[i]] = i;
    For (i, 1, 100) l[i] = n + 1; rFor (i, n, 1) ra[i] = l[a[i]], l[a[i]] = i;
    For (i, 1, 100) l[i] = m + 1; rFor (i, m, 1) rb[i] = l[b[i]], l[b[i]] = i;
}

void init_sub() {
    auto gets = [&](int i, int l, int r) { return gmo(s[i][r] - (l>0? s[i][l - 1]: 0)); };
    f[0][0] = s[0][0] = 1;
    For (i, 1, n) s[0][i] = 1;
    For (i, 1, n) {
        For (j, 1, n) {
            f[i][j] = gets(i - 1, la[j], j - 1);
            s[i][j] = gmo(s[i][j - 1] + f[i][j]);
        }
        suba[i] = s[i][n];
    }
    memset(s, 0, sizeof(s));
    memset(f, 0, sizeof(f));
    f[0][0] = s[0][0] = 1;
    For (i, 1, m) s[0][i] = 1;
    For (i, 1, m) {
        For (j, 1, m) {
            f[i][j] = gets(i - 1, lb[j], j - 1);
            s[i][j] = gmo(s[i][j - 1] + f[i][j]);
        }
        subb[i] = s[i][m];
    }
}

int gets1(int x_, int x, int y_, int y) {
    int res = sg[x][y];
    if (x_ > 0) add(res, -sg[x_ - 1][y]);
    if (y_ > 0) add(res, -sg[x][y_ - 1]);
    if (x_ > 0 && y_ > 0) add(res, sg[x_ - 1][y_ - 1]);
    return res;
};

int gets2(int x_, int x, int y_, int y) {
    int res = sh[x_][y_];
    add(res, -sh[x + 1][y_]);
    add(res, -sh[x_][y + 1]);
    add(res, sh[x + 1][y + 1]);
    return res;
}

void init_equal() {
    g[0][0] = sg[0][0] = 1;
    For (i, 1, m) sg[0][i] = 1;
    For (i, 1, n) {
        int s = 0;
        sg[i][0] = sg[i - 1][0];
        For (j, 1, m) {
            if (a[i] == b[j]) g[i][j] = gets1(la[i], i - 1, lb[j], j - 1);
            add(s, g[i][j]);
            sg[i][j] = gmo(sg[i - 1][j] + s);
        }
    }
}

void init_dif() {
    h[n + 1][m + 1] = sh[n + 1][m + 1] = 1;
    rFor (i, m, 1) sh[n + 1][i] = 1;
    rFor (i, n, 1) {
        int s = 0;
        sh[i][m + 1] = sh[i + 1][m + 1];
        rFor (j, m, 1) {
            h[i][j] = gets2(i + 1, ra[i], j + 1, rb[j]);
            add(s, h[i][j]);
            sh[i][j] = gmo(sh[i + 1][j] + s);
        }
    }
}

int main() {
    io >> n >> m;
    For (i, 1, n) io >> a[i];
    For (i, 1, m) io >> b[i];
    init_last();
    init_sub();

    int M = 0;
    For (i, 1, n) {
        add(ans, mul(suba[i], M));
        add(M, subb[i]);
    }

    init_equal();
    init_dif();

    For (i, 1, n) {
        For (j, 1, m) if (a[i] > b[j]) {
            add(ans, mul(gets1(la[i], i - 1, lb[j], j - 1), sh[i + 1][j + 1]));
        }
    }

    printf("%d", ans);

    return 0;
}
