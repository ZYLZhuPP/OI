#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef array<int, 2 > P;
const int N = 1e6 + 5, Mo = 1e9 + 7;
inline int mo(int x) { return x-= x>=Mo? Mo: x<0? -Mo: 0; }

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

int n, m, dis[N], id[N];
vector<vector<int > > a;
vector<P > es[N];

inline void dfs0(int u) {
	dis[u] = 0; a[0].pb(u);
	for (auto &e : es[u]) if (!~dis[e[0]] && !e[1]) dfs0(e[0]);
}

int main() {
	memset(dis, -1, sizeof dis);
	io >> n >> m;
	int u, v, w;
	For (i, 1, m) io >> u >> v >> w, es[u].pb({v, w});
	a.pb(vector<int >()); dfs0(1);
	while (!a.empty()) {
		vector<int > nq;
		for (auto &q : a) {
			for (auto &u : q) {
				for (auto &e : es[u]) if (!~dis[e[0]] && !e[1]) {
					int v = e[0], w = e[1];
					dis[v] = mo(dis[u] << 1 | w); id[v] = id[u] << 1 | w;
					nq.pb(v);
				}
			}
			for (auto &u : q) {
				for (auto &e : es[u]) if (!~dis[e[0]] && e[1]) {
					int v = e[0], w = e[1];
					dis[v] = mo(dis[u] << 1 | w); id[v] = id[u] << 1 | w;
					nq.pb(v);
				}
			}
		}
		a.resize(0);
		For (i, 0, (int)nq.size() - 1) {
			if (!i || id[nq[i]] ^ id[nq[i - 1]]) a.pb(vector<int >(1, nq[i]));
			else (*a.rbegin()).pb(nq[i]);
		}
	}
	For (i, 2, n - 1) printf("%d ", dis[i]);
	printf("%d", dis[n]);
	
	return 0; 
} 
