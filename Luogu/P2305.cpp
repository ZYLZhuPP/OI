#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
typedef double lf;
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

int n, t, fa[N], p[N], cnt;
ll q[N], s[N], l[N], dis[N], Dis[N], f[N];
vector<int > es[N];

inline lf K(int x, int y) { return 1.l * (f[x] - f[y]) / (dis[x] - dis[y]); }

struct Stk {
    vector<int > o;
    stack<int > top, v;
    Stk() { o.resize(1); top.push(0); v.push(0); }
    void push(int u) {
        int t = top.top();
        while (t > 1 && K(u, o[t]) < K(o[t], o[t - 1])) t--;
        t++; if (t >= o.size()) o.pb(0);
        v.push(o[t]); top.push(t); o[t] = u;
    }
    void pop() {
        o[top.top()] = v.top();
        top.pop(); v.pop();
    }
    int find(int x) {
    //for (auto &x : o) cout << x << " ";
    //cout << endl;
        //cout << top.top() << endl;
        int l = 1, r = top.top() - 1, res = top.top();
        while (l <= r) {
            int m = (l + r) >> 1; //cout << m << "  ";
            //cout << K(o[m + 1], o[m]) << endl;
            if (K(o[m + 1], o[m]) > x) res = m, r = m - 1;
            else l = m + 1;
        }
        return o[res];
    }
};

namespace BIT {
#define lowbit(x) ((x) & -(x))
    Stk o[N];
    inline void ins(int k, int x) { for (; k < N; k += lowbit(k)) o[k].push(x); }
    inline void del(int k) { for (; k < N; k += lowbit(k)) o[k].pop(); }
}
using namespace BIT;

void solve(int u) {
//cout << u << ":";
    int v = lower_bound(Dis + 1, Dis + cnt + 1, dis[u] - l[u]) - Dis;
    //cout << p[u] << endl;
    //For (v, 1, u - 1) cout << f[v] + (dis[u] - dis[v]) * p[u] + q[u] << endl;
    for (int k = N - v; k; k -= lowbit(k)) {
        v = o[k].find(p[u]); //cout << v << "?" << endl;
        if (v) f[u] = min(f[u], f[v] + (dis[u] - dis[v]) * p[u] + q[u]);
    }
}

void dfs(int u) {
    dis[u] = dis[fa[u]] + s[u];
    Dis[++cnt] = dis[u];
    if (u ^ 1) solve(u);
    ins(N - cnt, u);
    for (auto &v : es[u]) dfs(v);
    del(N - cnt);
    cnt--;
}

int main() {
    memset(f, 31, sizeof f); f[1] = 0;
    io >> n >> t;
    For (i, 2, n) io >> fa[i] >> s[i] >> p[i] >> q[i] >> l[i], es[fa[i]].pb(i);
    dfs(1);
    For (i, 2, n) printf("%lld\n", f[i]);

    return 0;
}
/*
6 3
1 721571 0 5206648 200000000000
2 643793 28 0 200000000000
3 55710 105 0 200000000000
4 536152 93 0 200000000000
5 904453 0 81892067 200000000000
*/
