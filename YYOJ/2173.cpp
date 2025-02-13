#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 3e3 + 5, Mo = 998244353;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, const int &y) { x = mo(x + y); }
inline int ml(const int &x, const int &y) { return 1ll * x * y % Mo; }
inline void mul(int &x, const int &y) { x = ml(x, y); }
inline int qPow(int a, int b) { int r=1; for (;b;b>>=1,mul(a,a)) if (b&1) mul(r,a); return r; }

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

int x, y, S, son[11];

struct Tree {
    int n, f[N][1 << 10];
    vector<int > T[N];
    inline void init() {
        io >> n;
        int u, v;
        For (i, 1, n - 1) io >> u >> v, T[u].pb(v), T[v].pb(u);
    }
    inline void mem() {
        For (i, 1, n) memset(f[i], 0, sizeof f[i]);
    }
    inline void dfs0(int u, int pre) {
        son[u] = 0;
        for (auto &v : T[u]) if (v ^ pre) dfs0(v, u), son[u] |= 1 << (v - 1);
    }
    inline void dfs(int u, int pre) {
        f[u][0] = 1;
        for (auto &v : T[u]) if (v ^ pre) {
            dfs(v, u);
            rFor (s, S, 0) if (f[u][s]) {
                int t = S ^ s;
                while (t) {
                    int x = __builtin_ffs(t);
                    add(f[u][s | (1 << (x - 1))], ml(f[u][s], f[v][son[x]]));
                    t ^= 1 << (x - 1);
                }
            }
        }
    }
} T1, T2;

int main() {
    T1.init(); T2.init();
    S = (1 << T2.n) - 1;
    For (i, 1, T2.n) {
        T1.mem(); T2.mem();
        T2.dfs0(i, 0);
        T1.dfs(1, 0);
        For (j, 1, T1.n) add(x, T1.f[j][son[i]]);
        T2.dfs(1, 0);
        For (j, 1, T2.n) add(y, T2.f[j][son[i]]);
    }
    printf("%d", ml(x, qPow(y, Mo - 2)));

    return 0;
}
