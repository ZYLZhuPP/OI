#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e3 + 5, Mo = 31011;

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

int n, m, fa[N], ans = 1;
array<int, 3 > es[N];
vector<int > mn;
map<int, vector<int > > mp;

inline int find(int x) { return fa[x]^x? fa[x] = find(fa[x]): x; }

int main() {
    io >> n >> m;
    For (i, 1, n) fa[i] = i;
    int u, v, w;
    For (i, 1, m) io >> u >> v >> w, es[i] = {u, v, w}, mp[w].pb(i);
    for (auto &[val, q] : mp) {
        for (auto &id : q) {
            auto [u, v, w] = es[id];
            u = find(u); v = find(v);
            if (u == v) continue;
            mn.pb(id); fa[u] = v;
        }
    }
    for (auto &[val, q] : mp) {
        int tot = q.size(), cnt = 0, res = 0;
        for (auto &id : mn) if (es[id][2] == val) cnt++;
        if (!cnt) continue;
        For (s, 1, (1 << tot) - 1) if (__builtin_popcount(s) == cnt) {
            For (i, 1, n) fa[i] = i;
            for (auto &id : mn) if (es[id][2] ^ val) {
                auto [u, v, w] = es[id];
                u = find(u); v = find(v);
                fa[u] = v;
            }
            For (i, 0, tot - 1) if (s >> i & 1) {
                auto [u, v, w] = es[q[i]];
                u = find(u); v = find(v);
                fa[u] = v;
            }
            bool flag = 1;
            For (i, 1, n) if (find(i) ^ find(1)) flag = 0;
            if (flag) res++;
        }
        ans = ans * res % Mo;
    }
    printf("%d", ans);

    return 0;
}
