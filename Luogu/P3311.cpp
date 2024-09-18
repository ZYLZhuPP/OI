#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1505, Mo = 1e9 + 7;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, const int &y) { x = mo(x + y); }

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

int n, m, ch[N][10], tot = 1, ed[N], fail[N], f[N][N];
char s[N], t[N];

inline void add(char s[]) {
    int n = strlen(s + 1), u = 1;
    For (i, 1, n) {
        int c = s[i]^48;
        if (!ch[u][c]) ch[u][c] = ++tot;
        u = ch[u][c];
    }
    ed[u] = 1;
}

inline void build() {
    For (i, 0, 9) ch[0][i] = 1;
    queue<int > q; q.push(1);
    fail[1] = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop(); ed[u] |= ed[fail[u]];
        For (i, 0, 9) (ch[u][i]? q.push(ch[u][i]), fail[ch[u][i]]: ch[u][i]) = ch[fail[u]][i];
    }
}

inline int dfs(int k, int u, bool pre, bool lim) {
    if (ed[u]) return 0;
    if (k > n) return !pre;
    if (!pre && !lim && ~f[k][u]) return f[k][u];
    int res = 0, L = pre, R = lim? t[k]^48: 9;
    if (pre) res = dfs(k + 1, u, pre, 0);
    For (i, L, R) add(res, dfs(k + 1, ch[u][i], 0, lim && i==R));
    if (!pre && !lim) f[k][u] = res;
    return res;
}

int main() {
    memset(f, -1, sizeof f);
    scanf("%s", t + 1);
    n = strlen(t + 1);
    io >> m;
    For (i, 1, m) scanf("%s", s + 1), add(s);
    build();
    printf("%d", dfs(1, 1, 1, 1));
    
    return 0;
}
