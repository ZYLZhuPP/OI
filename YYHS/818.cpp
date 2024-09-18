#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e5 + 5, Mo = 1e9 + 7;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
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
	inline IO& operator >> (char *x){
		while ((c = gc()) < 33 && ~c);
		while (c > 32) *x++ = c, c = gc();
		*x = 0; return *this;
	}
	inline bool operator ~ () {return ~c;}
} io;

int n, u, siz[N], sum[N], cnt, inv[N];
char st[N];
vector<int > es[N];

struct Node {
    int a, b, c;
    Node(int a = 0, int b = 0, int c = 0): a(a), b(b), c(c) { }
    Node operator * (const int &x) const {
        return Node(mul(a, x), mul(b, x), mul(c, x));
    }
    Node operator + (const Node &x) const {
        return Node(mo(a + x.a), mo(b + x.b), mo(c + x.c));
    }
    Node operator - (const Node &x) const {
        return *this + x * (-1);
    }
    int operator () (const int &x, const int &y) const {
        return mo(mo(mul(a, x) + mul(b, y)) + c);
    }
} v[N][2];

namespace init {
    void dfs1(int u, int pre) {
        siz[u] = 1;
        for (auto &v : es[u]) if (v ^ pre) {
            dfs1(v, u);
            add(sum[u], mo(sum[v] + siz[v]));
            siz[u] += siz[v];
        }
    }

    void dfs2(int u, int pre) {
        for (auto &v : es[u]) if (v ^ pre) {
            sum[v] = mo(sum[u] + mo(n - siz[v] * 2));
            dfs2(v, u);
        }
    }

    int main() {
        For (i, 0, n - 1) cnt += st[i] - '0';

        dfs1(1, 0);
        dfs2(1, 0);

        inv[0] = inv[1] = 1;
        For (i, 2, n) inv[i] = mul(Mo - Mo / i, inv[Mo % i]);

        return 0;
    }
}

int qPow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) res = mul(res, a);
        a = mul(a, a);
        b >>= 1;
    }
    return res;
}

int solve() {
    v[1][0] = Node(1, 0, 0);
    v[1][1] = Node(0, 1, 0);
    For (i, 1, n - 1) {
        Node &A = v[i + 1][1];
        A = v[i][1] * n - v[i - 1][0] - v[i - 1][1] * (i - 1);
        add(A.c, i>1? -1: 0);
        A = A * inv[n - i];
        Node &B = v[i + 1][0];
        B = v[i][0] * n - v[i - 1][0] * i - v[i + 1][1];
        add(B.c, i<n-1? -1: 0);
        B = B * inv[n - i - 1];
    }

    Node A = v[n][0], B = v[n][1];
    A.c = mul(A.c, -1); B.c = mul(B.c, -1);
    int a0b1 = mul(A.a, B.b), a1b0 = mul(B.a, A.b);
    int c0a1 = mul(A.c, B.a), c1a0 = mul(B.c, A.a);
    int c0b1 = mul(A.c, B.b), c1b0 = mul(B.c, A.b);
    int x = mul(mo(c0b1 - c1b0), qPow(mo(a0b1 - a1b0), Mo - 2));
    int y = mul(mo(c0a1 - c1a0), qPow(mo(a1b0 - a0b1), Mo - 2));

    int v0 = v[cnt][0](x, y);
    int v1 = v[cnt][1](x, y);
    add(v0, inv[n]);
    add(v1, inv[n]);

    int res = 0;
    For (i, 1, n) add(res, mul(mul(sum[i], inv[n]), st[i - 1]=='1'? v1: v0));
    return res;
}

int main() {
    io >> n;
    io >> st;
    For (i, 2, n) {
        io >> u;
        es[i].push_back(u);
        es[u].push_back(i);
    }

    init::main();

    printf("%d", solve());

    return 0;
}
