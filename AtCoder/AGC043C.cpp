#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e5 + 5, Mo = 998244353, V = 716070898;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, const int &y) { x = mo(x + y); }
inline int ml(const int &x, const int &y) { return 1ll * x * y % Mo; }
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
	inline bool operator ~ () const { return ~c; }
} io;

int n, _v[N], a[N], b[N], c[N], A, B, m, sg[N], vis[N];
vector<int > es[N];

int main() {
    io >> n;
    _v[0] = 1; For (i, 1, n) _v[i] = ml(_v[i - 1], V);
    For (o, 1, 3) {
        B = 0;
        io >> m;
        For (i, 1, m) {
        int u, v;
            io >> u >> v;
            if (u > v) swap(u, v);
            es[u].pb(v);
        }
        rFor (i, n, 1) {
            for (auto &j : es[i]) vis[sg[j]] = 1;
            For (j, 0, n) if (!vis[j]) { sg[i] = j; break; }
            for (auto &j : es[i]) vis[sg[j]] = 0;
            cmax(B, sg[i]);
            add(b[sg[i]], _v[i]);
        }
        if (o == 1) {
            A = B;
            For (i, 0, B) a[i] = b[i];
        } else {
            rFor (i, A, 0) For (j, 0, B) {
                add(c[i ^ j], ml(a[i], b[j]));
                cmax(A, i ^ j);
            }
            For (i, 0, A) a[i] = c[i], c[i] = 0;
        }
        For (i, 0, B) b[i] = 0;
        For (i, 1, n) es[i].resize(0);
    }
    printf("%d", a[0]);

    return 0;
}