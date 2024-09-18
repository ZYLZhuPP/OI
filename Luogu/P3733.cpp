#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
const int N = 1e3 + 5, S = 1e3;
typedef bitset<S> B;

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

struct Edge { int to; B w; };
vector<Edge > es[N];
int n, m, Q, c[N], k, lst[N], ed[N], vis[N];
B a[N], b[N], val[N];

char st[S + 10];
inline void get(B &x) {
    x.reset();
    scanf("%s", st + 1);
    int len = strlen(st + 1);
    For (j, 1, len) x[len - j] = st[j] ^ 48;
}

inline void put(const B &x) {
    int pos = S - 1;
    while (pos && !x[pos]) pos--;
    while (~pos) putchar(x[pos--] ^ 48);
    puts("");
}

namespace Basis {
    B o[S]; int end[S];
    inline void ins(B v, int now) {
        rFor (i, S - 1, 0) if (v[i]) {
            if (end[i] < now) swap(o[i], v), swap(end[i], now);
            v ^= o[i];
        }
    }
    inline void ask(int now) {
        B res;
        rFor (i, S - 1, 0) if (!res[i] && end[i] >= now) res ^= o[i];
        put(res);
    }
}
using namespace Basis;

void dfs(int u) {
    vis[u] = 1;
    for (auto &[v, w] : es[u]) if (!vis[v]) {
        val[v] = val[u] ^ w;
        dfs(v);
    } else ins(val[u] ^ val[v] ^ w, Q + 1);
}

int main() {
    io >> n >> m >> Q;
    int u, v, x; B w;
    For (i, 1, m) io >> u >> v, get(w), es[u].pb({v, w}), es[v].pb({u, w});
    dfs(1);
    char op[10];
    For (i, 1, Q) {
        scanf("%s", op);
        if (op[1] == 'd') {
            c[i] = 1;
            io >> u >> v; get(w);
            a[++k] = val[u] ^ val[v];
            b[i] = a[k] ^ w; ed[i] = Q;
            lst[k] = i;
        } else if (op[1] == 'a') {
            io >> x;
            ed[lst[x]] = i - 1;
        } else if (op[1] == 'h') {
            c[i] = 1;
            io >> x; get(w);
            ed[lst[x]] = i - 1;
            b[i] = a[x] ^ w; ed[i] = Q;
            lst[x] = i;
        }
    }
    ask(0);
    For (i, 1, Q) {
        if (c[i]) ins(b[i], ed[i]);
        ask(i);
    }

    return 0;
}
