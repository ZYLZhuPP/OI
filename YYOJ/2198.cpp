#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 5e5 + 5;

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

int n, t[N], fa[N];
ll s[N];
array<int, 3 > es[N];

inline int find(int u) { return u^fa[u]? fa[u] = find(fa[u]): u; }

int main() {
    io >> n;
    int u, v, w;
    For (i, 1, n - 1) io >> u >> v >> w, es[i] = {-w, u, v};
    For (i, 1, n) io >> u, t[u] = i, fa[i] = i;
    sort(es + 1, es + n + 1);
    For (i, 1, n - 1) {
        auto [w, u, v] = es[i]; w = -w;
        u = find(u); v = find(v);
        s[max(t[u], t[v])] += w;
        fa[v] = u; t[u] = min(t[v], t[u]);
    }
    For (i, 1, n) s[i] += s[i - 1], printf("%lld\n", s[i]);

    return 0;
}
