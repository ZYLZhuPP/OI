#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i) 
#define vec vector

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
	inline bool operator ~() {return ~c;}
} io;


int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};
int n, m, ans, mx;
vec<vec<int > > a;

void dfs(int x, int y, int last, int k) {
	ans = max(ans, k);
	if (a[x][y] == last) {
		puts("-1");
		exit(0);
	}
    if (last && a[x][y] * (long long)pow(a[x][y] / last, ans - k) >= mx) return;
	
	For (i, 0, 3) {
		int xx = x + dx[i], yy = y + dy[i];
		if (xx < 1 || xx > n || yy < 1 || yy > m) continue;
		if ((!last && !(a[xx][yy] % a[x][y])) || last * a[xx][yy] == a[x][y] * a[x][y])
			dfs(xx, yy, a[x][y], k + 1);
	}
}

void init() {
	a.resize(n + 2, vec<int >(m + 2, 0));
}

int main() {
	io >> n >> m;
	init();
	For (i, 1, n) {
		For (j, 1, m) {
			io >> a[i][j];
			mx = max(mx, a[i][j]);
		}
	}
	
	For (i, 1, n) {
		For (j, 1, m) {
			dfs(i, j, 0, 1);
		}
	} 
	
	printf("%d", ans);
	
	return 0;
} 
