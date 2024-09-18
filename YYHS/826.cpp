#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
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
	inline bool operator ~ () {return ~c;}
} io;

int n, x[N], y[N], L[N], R[N], to[N], ma, rt;
long long f[N];
int q[N], t;
int suf[N], pre[N];
vector<int > es[N];

bool ok1(int k) {
    return 1ll * (y[q[t]] - y[q[t - 1]]) * abs(x[k] - x[q[t]]) >= 1ll * (y[k] - y[q[t]]) * abs(x[q[t]] - x[q[t - 1]]);
}

bool ok2(int k) {
    return y[to[q[t]]] > y[to[k]] || (y[to[q[t]]] == y[to[k]] && to[q[t]] >= to[k]);
}

void dfs(int u) {
    for (auto &v : es[u]) {
        f[v] = f[u] + abs(u - v);
        dfs(v);
    }
}

int main() {
    io >> n;
    For (i, 1, n) {
        io >> x[i] >> y[i];
        if (y[i] >= ma) rt = i, ma = y[i];
    }
    y[0] = -1;

    t = 0; For (i, 1, n) {
        while (t > 1 && !ok1(i)) t--;
        if (y[q[t]] > y[i]) L[i] = q[t];
        q[++t] = i;
    }
    t = 0; rFor (i, n, 1) {
        while (t > 1 && !ok1(i)) t--;
        if (y[q[t]] >= y[i]) R[i] = q[t];
        q[++t] = i;
    }
    
    For (i, 1, n) to[i] = y[R[i]] >= y[L[i]]? R[i]: L[i];
    to[rt] = rt;

    t = 0; For (i, 1, n) {
        while (t && !ok2(i)) t--;
        pre[i] = t? q[t]: to[i];
        q[++t] = i;
    }
    t = 0; rFor (i, n, 1) {
        while (t && !ok2(i)) t--;
        suf[i] = t? q[t]: to[i];
        q[++t] = i;
    }

    For (i, 1, n) if (i ^ rt) es[to[i] < i? pre[i]: suf[i]].push_back(i);

    dfs(rt);

    For (i, 1, n) printf("%lld\n", f[i]);

    return 0;
}


