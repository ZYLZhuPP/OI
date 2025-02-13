#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 2e5 + 5, S = 2e6 + 5;

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
	inline bool operator ~ () { return ~c; }
} io;

int n;
char s[S];

namespace ACAM {
    int ch[N][26], tot = 1, ed[N], pos[N], fail[N], cnt[N];
    vector<int > T[N];

    inline void add(char s[], int id) {
        int n = strlen(s + 1), u = 1;
        For (i, 1, n) {
            int c = s[i] - 'a';
            if (!ch[u][c]) ch[u][c] = ++tot;
            u = ch[u][c];
        }
        ed[pos[id] = u]++;
    }

    inline void build() {
        For (i, 0, 25) ch[0][i] = 1;
        queue<int > q; q.push(1);
        fail[1] = 0;
        while (!q.empty()) {
            int u = q.front(); q.pop(); T[fail[u]].pb(u);
            For (i, 0, 25) (ch[u][i]? q.push(ch[u][i]), fail[ch[u][i]]: ch[u][i]) = ch[fail[u]][i];
        }
    }

    inline void query(char s[]) {
        int n = strlen(s + 1), u = 1;
        For (i, 1, n) {
            int c = s[i] - 'a';
            u = ch[u][c];
            cnt[u]++;
        }
    }

    inline void solve(int u) {
        for (auto &v : T[u]) solve(v), cnt[u] += cnt[v];
    }
}
using namespace ACAM;

int main() {
    io >> n;
    For (i, 1, n) scanf("%s", s + 1), add(s, i);
    build();
    scanf("%s", s + 1);
    query(s);
    solve(1);
    For (i, 1, n) printf("%d\n", cnt[pos[i]]);

    return 0;
}
