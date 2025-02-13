#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 1e6 + 5;

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

int head[N], nxt[N << 1], to[N << 1], val[N << 1], en = 1;
int n, v, w, rt[N], m;
int q[N];
bool v1[N], v2[N], vise[N << 1];
ll a[N << 1], s[N << 1], dw[N], ans;

void add(int u, int v, int w) {
    nxt[++en] = head[u];
    to[en] = v; val[en] = w;
    head[u] = en;
}

int findc(int u, int pre) {
    v1[u] = 1;
    for (int i = head[u]; i; i = nxt[i]) if (!vise[i]) {
        int v = to[i]; vise[i] = vise[i ^ 1] = 1;
        if (v1[v]) {
            rt[m = 1] = u; v2[u] = 1;
            s[m] = val[i];
            return v;
        }
        int r = findc(v, u);
        if (r) {
            rt[++m] = u; v2[u] = 1;
            s[m] = s[m - 1] + val[i];
            return r == u? 0: r;
        }
    }
    return 0;
}

void dfs(int u, ll &res) {
    v2[u] = 1;
    for (int i = head[u]; i; i = nxt[i]) if (!v2[to[i]]) {
        int v = to[i];
        dfs(v, res);
        res = max(res, dw[u] + dw[v] + val[i]);
        dw[u] = max(dw[u], dw[v] + val[i]);
    }
}

ll F(int i) { return a[i] - s[i]; }

int main() {
    io >> n;
    For (u, 1, n) io >> v >> w, add(u, v, w), add(v, u, w);

    For (o, 1, n) if (!v2[o]) {
        ll res = 0;
        findc(o, 0);
        For (i, 1, m) dfs(rt[i], res);
        For (i, 1, m) a[i] = a[i + m] = dw[rt[i]];
        For (i, 1, m) s[i + m] = s[i] + s[m];

        int h = 1, t = 0; q[++t] = 1;
        For (i, 2, 2 * m) {
            while (h <= t && q[h] <= i - m) h++;
            res = max(res, s[i] + a[i] + F(q[h]));
            while (h <= t && F(q[t]) <= F(i)) t--;
            q[++t] = i;
        }
        ans += res;
    }
    printf("%lld", ans);

    return 0;
}
