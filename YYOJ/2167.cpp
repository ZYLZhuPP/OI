#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 5e3 + 5;

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

int n, dep[N], is[N], cnt[2], g[N][N];
char s[N];

inline void dfs(int u, int pre) {
	dep[u] = dep[pre] + 1; cnt[dep[u] & 1]++;
	For (v, 1, n) if (v ^ pre && g[u][v]) {
		if (dep[v]) { if ((dep[u] & 1) == (dep[v] & 1)) puts("No"), exit(0); }
		else dfs(v, u);
	}
}

inline void solve(int u, int x) {
	if ((dep[u] & 1) == x) is[u] = 1;
	For (v, 1, n) if (g[u][v] && dep[v] == dep[u] + 1) solve(v, x);
}

int main() {
	io >> n;
	For (i, 1, n) {
		scanf("%s", s + 1);
		For (j, 1, n) if (s[j] == '1') g[i][j] = g[j][i] = 1;
	}
	For (i, 1, n) if (!dep[i]) {
		cnt[0] = cnt[1] = 0;
		dfs(i, 0);
		solve(i, cnt[1] <= cnt[0]);
	}
	puts("Yes");
	For (i, 1, n) if (is[i]) printf("%d ", i);
	
	return 0;
} 
