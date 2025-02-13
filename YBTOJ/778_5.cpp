#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 2e5 + 5;

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

int n, w[N];
ll ans;
vector<int > o, es[N];
priority_queue<int > q[N];

void dfs(int u) {
    for (auto &v : es[u]) {
        dfs(v);
        if (q[v].size() > q[u].size()) swap(q[u], q[v]);
        while (!q[v].empty()) o.pb(max(q[u].top(), q[v].top())), q[u].pop(), q[v].pop();
        for (auto &x : o) q[u].push(x);
        o.resize(0);
    }
    q[u].push(w[u]);
}

int main() {
    io >> n;
    For (i, 1, n) io >> w[i];
    int u;
    For (i, 2, n) io >> u, es[u].pb(i);
    dfs(1);
    while (!q[1].empty()) ans += q[1].top(), q[1].pop();
    printf("%lld", ans);

    return 0;
}
