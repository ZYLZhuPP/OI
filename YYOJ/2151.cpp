#include<bits/stdc++.h>
#include<time.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i) 
const int N = 2e5 + 5, inf = 1e9;

struct IO {
	char c; int f;
#define gc() getchar()
	IO& operator >> (int &x) {
		x = 0; f = 1;
		while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
		while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
		x *= f; return *this;
	}
} io; 

int n, m, k, x[N][5], d[5][N], id[5], ans;

int dist(int a, int b) {
	int r = 0;
	For (i, 1, k) r += abs(x[a][i] - x[b][i]);
	return r;
}

int solve() {
	int mx = 0, x = 0;
	For (i, 1, n) {
		int s = 0;
		For (j, 1, m - 1) s += d[j][i];
		if (mx < s) mx = s, x = i;
	}
	For (i, 1, m - 1) For (j, 1, i - 1) mx += dist(id[i], id[j]);
	ans = max(ans, mx);
	return x;
}

void get(int x, int d[]) {
	For (i, 1, n) d[i] = dist(x, i);
}

void dfs(int k) {
	if (k == 0) {
		int s = 0;
		For (i, 1, m) For (j, 1, i - 1) s += dist(id[i], id[j]);
		ans = max(ans, s);
		return;
	}
	For (i, 1, n) id[k] = i, dfs(k - 1);
}

int main() {
	freopen("eye.in", "r", stdin);
	freopen("eye.out", "w", stdout);
	int ST = clock();
	io >> n >> k >> m;
	For (i, 1, n) For (j, 1, k) io >> x[i][j];
	if (k == 1) {
		int mn = x[1][1], mx = x[1][1];
		For (i, 2, n) mn = min(mn, x[i][1]), mx = max(mx, x[i][1]);
		ans = (m==2? 1: 4) * (mx - mn);
	} else if (pow(n, m) <= 1e8) {
		dfs(m);
	} else {
		while (clock() - ST < 0.95 * CLOCKS_PER_SEC) {
			//cout << clock() << endl;
			For (i, 1, m - 1) id[i] = rand() % n + 1, get(id[i], d[i]);
			For (o, 1, 8) {
				int x = solve(), mn = inf, y = 0;
				For (i, 1, m - 1) {
					int s = dist(id[i], x);
					For (j, 1, m - 1) s += d[j][id[i]];
					if (s < mn) mn = s, y = i;
				}
				if (id[y] == x) break;
				id[y] = x; get(id[y], d[y]);
			}
		}
	}
	printf("%d", ans);
	
	fclose(stdin); fclose(stdout);
	return 0;
} 
