#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 3e4 + 5;

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

int n, vis[N], in[N];
string s;

namespace ACAM {
    int ch[N][2], tot = 1, ed[N], fail[N];
    vector<int > T[N];

    inline void add(string s) {
        int n = s.length(), u = 1;
        For (i, 0, n - 1) {
            int c = s[i] ^ 48;
            if (!ch[u][c]) ch[u][c] = ++tot;
            u = ch[u][c];
        }
        ed[u] = 1;
    }

    inline void build() {
        For (i, 0, 1) ch[0][i] = 1;
        queue<int > q; q.push(1);
        fail[1] = 0;
        while (!q.empty()) {
            int u = q.front(); q.pop(); ed[u] |= ed[fail[u]];
            For (i, 0, 1) (ch[u][i]? q.push(ch[u][i]), fail[ch[u][i]]: ch[u][i]) = ch[fail[u]][i], T[u].pb(ch[u][i]);
        }
    }
}
using namespace ACAM;

inline bool dfs(int u) {
    in[u] = vis[u] = 1;
    for (auto &v : T[u]) if (!ed[v]) {
        if (in[v]) return 1;
        if (!vis[v] && dfs(v)) return 1;
    }
    in[u] = 0;
    return 0;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    cin >> n;
    For (i, 1, n) cin >> s, add(s);
    build();
    puts(dfs(1)? "TAK": "NIE");

    return 0;
}
