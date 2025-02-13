#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e5 + 5;

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

int n, m, dfn[N], tim, dfn_[N], ans[N], stk[N], top;
char s[N];
vector<array<int, 2 > > qs[N];

namespace BIT {
    int o[N];
#define lowbit(x) ((x) & -(x))
    inline void upd(int x, const int &d) { for (; x < N; x += lowbit(x)) o[x] += d; }
    inline int query(int x) { int r = 0; for (; x; x -= lowbit(x)) r += o[x]; return r; }
}
using namespace BIT;

namespace ACAM {
    int ch[N][26], tot = 1, ed[N], pos[N], fail[N], cnt[N], num, dep[N];
    vector<int > T[N];

    inline void build() {
        For (i, 0, 25) ch[0][i] = 1;
        queue<int > q; q.push(1);
        fail[1] = 0;
        while (!q.empty()) {
            int u = q.front(); q.pop(); T[fail[u]].pb(u);
            For (i, 0, 25) (ch[u][i]? q.push(ch[u][i]), fail[ch[u][i]]: ch[u][i]) = ch[fail[u]][i];
        }
    }
}
using namespace ACAM;

inline void dfs0(int u) {
    dfn[u] = ++tim;
    for (auto &v : T[u]) dfs0(v);
    dfn_[u] = tim;
}

inline void dfs(int u) {
    upd(dfn[u], 1);
    for (auto &[v, id] : qs[u]) ans[id] = query(dfn_[v]) - query(dfn[v] - 1);
    For (i, 0, 25) if (ch[u][i] && dep[ch[u][i]] == dep[u] + 1) dfs(ch[u][i]);
    upd(dfn[u], -1);
}

int main() {
    scanf("%s", s + 1);
    n = strlen(s + 1);
    stk[++top] = 1;
    For (i, 1, n) {
        int u = stk[top];
        if (s[i] == 'P') pos[ed[u] = ++num] = u;
        else if (s[i] == 'B') top--;
        else {
            int c = s[i] - 'a';
            if (!ch[u][c]) ch[u][c] = ++tot, dep[tot] = dep[u] + 1;
            stk[++top] = ch[u][c];
        }
    }
    build();
    dfs0(1);
    io >> m;
    int x, y;
    For (i, 1, m) io >> x >> y, qs[pos[y]].pb({pos[x], i});
    dfs(1);
    For (i, 1, m) printf("%d\n", ans[i]);

    return 0;
}
