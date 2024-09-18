#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 405, M = 3005, Mo = 998244353;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, int y) { x = mo(x + y); }
inline int ml(int x, int y) { return 1ll * x * y % Mo; }

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

int n, s, m, x, y, ans;
int a[N], iv[N], fc[N], vf[N], to[M][5], f[2][N][M];
int C[5][5] = { {1}, {1, 1}, {1, 2, 1}, {1, 3, 3, 1}, {1, 4, 6, 4, 1} };

inline void upd(const int &x, int &y) { if (x > y) y = min(x, 4); }
struct node {
    int o, f[18];
    node () { memset(f, -1, sizeof f); o = f[0] = 0; }
    bool operator < (const node &x) const {
        if (o ^ x.o) return o < x.o;
        For (i, 0, 17) if (f[i] ^ x.f[i]) return f[i] < x.f[i];
        return 0;
    }
    node operator + (const int &x) const {
        node r;
        r.o = o + (x >= 2);
        For (i, 0, 2) For (j, 0, 2) For (k, 0, min(x - i - j, 2)) {
            int u = i * 3 + j, v = j * 3 + k, _ = x - i - j - k;
            if (~f[u]) upd(f[u] + i + (_ >= 3), r.f[v]);
            if (~f[u + 9]) upd(f[u + 9] + i + (_ >= 3), r.f[v + 9]);
            if (~f[u] && _ >= 2) upd(f[u] + i, r.f[v + 9]);
        }
        return r;
    }
};

map<node, int > id;
int dfs(node x) {
    if (x.o >= 7 || x.f[9] >= 4) return 0;
    if (id.count(x)) return id[x];

    int u = id[x] = ++m;
    For (i, 0, 4) to[u][i] = dfs(x + i);
    return u;
}

void init() {
    iv[0] = iv[1] = 1; For (i, 2, N - 1) iv[i] = ml(Mo - Mo / i, iv[Mo % i]);
    fc[0] = vf[0] = 1; For (i, 1, N - 1) fc[i] = ml(fc[i - 1], i), vf[i] = ml(vf[i - 1], iv[i]);
}

int main() {
    init();
    io >> n; s = n << 2;
    For (i, 1, 13) io >> x >> y, a[x]++;

    dfs(node()); //cout << m << endl;

#define f0 f[!(i & 1)]
#define f1 f[i & 1]
    f[0][0][1] = 1;
    For (i, 1, n) {
        int D = a[i];
        For (j, 0, (i - 1) << 2) For (k, 1, m) if (x = f0[j][k]) {
            For (d, D, 4) add(f1[j + d][to[k][d]], ml(C[4 - D][d - D], x));
            f0[j][k] = 0;
        }
    }

    For (i, 13, s) For (j, 1, m)
        add(ans, ml(ml(fc[s - i], fc[i - 13]), ml(f[n & 1][i][j], vf[s - 13])));
    printf("%d", ans);

    return 0;
}
